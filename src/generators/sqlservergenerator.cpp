/**************************************************************************
**
** This file is part of Nut project.
** https://github.com/HamedMasafi/Nut
**
** Nut is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Nut is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Nut.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include "sqlservergenerator.h"
#include "../table.h"
#include "../tablemodel.h"

#include <QPoint>
#include <QRegularExpression>

NUT_BEGIN_NAMESPACE

SqlServerGenerator::SqlServerGenerator(Database *parent)
    : SqlGeneratorBase(parent)
{
}

QString SqlServerGenerator::masterDatabaseName(QString databaseName)
{
    return databaseName.replace(
        QRegularExpression("DATABASE\\=(\\w+)",
                           QRegularExpression::CaseInsensitiveOption),
        "DATABASE=");
}

QString SqlServerGenerator::fieldType(FieldModel *field)
{
    QString dbType;

    switch (field->type) {
    case QMetaType::Bool:
        dbType = "BIT";
        break;

    case QMetaType::Char:
    case QMetaType::QChar:
        dbType = "CHAR(1)";
        break;

    case QMetaType::SChar:
    case QMetaType::UChar:
        return "tinyint";

    case QMetaType::Short:
    case QMetaType::UShort:
        return "smallint";

    case QMetaType::UInt:
    case QMetaType::Int:
        dbType = "INT";
        if (field->isAutoIncrement)
            dbType += " IDENTITY(1,1)";
        break;

    case QMetaType::Long:
    case QMetaType::ULong:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
        return "bigint";

    case QMetaType::Float:
        return "FLOAT(24)";

    case QMetaType::Double:
        return "REAL";

    case QMetaType::QBitArray:
    case QMetaType::QByteArray:
        dbType = "VARBINARY";

        if (field->length)
            dbType.append(" (" + QString::number(field->length) + ")");
        else
            dbType.append(" (MAX)");
        break;
    case QMetaType::QDate:
        dbType = "DATE";
        break;
    case QMetaType::QDateTime:
        dbType = "DATETIME";
        break;
    case QMetaType::QTime:
        dbType = "TIME";
        break;

    case QMetaType::QPoint:
    case QMetaType::QPointF:
        dbType = "GEOMETRY";
        break;

    case QMetaType::QString:
        if (field->length)
            dbType = QString("NVARCHAR(%1)").arg(field->length);
        else
            dbType = "NVARCHAR(MAX)";
        break;

    case QMetaType::QUuid:
        dbType = "UNIQUEIDENTIFIER";
        break;

    case QMetaType::QPolygon:
    case QMetaType::QPolygonF:
    case QMetaType::QSize:
    case QMetaType::QSizeF:
    case QMetaType::QRect:
    case QMetaType::QRectF:
    case QMetaType::QLine:
    case QMetaType::QLineF:
    case QMetaType::QColor:
    case QMetaType::QStringList:
    case QMetaType::QJsonArray:
    case QMetaType::QJsonValue:
    case QMetaType::QJsonObject:
    case QMetaType::QJsonDocument:
    case QMetaType::QUrl:
        return "TEXT";

    default:
//        Q_UNREACHABLE();
        dbType = QString();
    }

    return dbType;
}

QString SqlServerGenerator::diff(FieldModel *oldField, FieldModel *newField)
{
    QString sql = QString();
    if (oldField && newField)
        if (*oldField == *newField)
            return sql;

    if (!newField) {
        sql = "DROP COLUMN " + oldField->name;
    } else {
        if (oldField)
            sql = "MODIFY COLUMN ";
        else
            sql = "ADD ";

        sql.append(fieldDeclare(newField));
    }
    return sql;
}

QString SqlServerGenerator::escapeValue(const QVariant &v) const
{
    auto mid = static_cast<QMetaType::Type>(v.userType());

    if (mid == QMetaType::QString || mid == QMetaType::QChar)
        return "N'" + v.toString() + "'";
    else if (mid == QMetaType::QPoint) {
        QPoint pt = v.toPoint();
        return QString("geography::POINT(%1, %2, 4326)").arg(pt.x()).arg(
            pt.y());
    } else if (mid == QMetaType::QPointF) {
        QPointF pt = v.toPointF();
        return QString("geography::POINT(%1, %2, 4326)").arg(pt.x()).arg(
            pt.y());
    }
    return SqlGeneratorBase::escapeValue(v);
}

void SqlServerGenerator::appendSkipTake(QString &sql, int skip, int take)
{
    if (take != -1 && skip != -1)
        sql.append(QString(" OFFSET %1 ROWS FETCH NEXT %2 ROWS ONLY")
                   .arg(skip).arg(take));
}

void SqlServerGenerator::replaceTableNames(QString &command)
{
    foreach (TableModel *m, TableModel::allModels())
        command = command
                .replace("[" + m->className() + "]", m->name() );
}

NUT_END_NAMESPACE
