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

#include <QDateTime>
#include <QPoint>
#ifdef QT_GUI_LIB
#include <QPolygon>
#endif
#include <QVariant>

#include "postgresqlgenerator.h"
#include "../table.h"
#include "../tablemodel.h"

NUT_BEGIN_NAMESPACE

PostgreSqlGenerator::PostgreSqlGenerator(Database *parent) : SqlGeneratorBase (parent)
{

}

QString PostgreSqlGenerator::fieldType(FieldModel *field)
{
    QString dbType;

    switch (field->type) {
    case QMetaType::Bool:
        dbType = "BOOLEAN";
        break;

    case QMetaType::QBitArray:
    case QMetaType::QByteArray:
        dbType = "BYTEA";
        break;
    case QMetaType::QDate:
        dbType = "DATE";
        break;
    case QMetaType::QDateTime:
        dbType = "TIMESTAMP";
        break;
    case QMetaType::QTime:
        dbType = "TIME";
        break;

    case QMetaType::SChar:
    case QMetaType::UChar:
    case QMetaType::Short:
    case QMetaType::UShort:
        dbType = "SMALLINT";
        break;

    case QMetaType::Float:
        dbType = "FLOAT";
        break;

    case QMetaType::Double:
        dbType = "REAL";
        break;

    case QMetaType::Int:
    case QMetaType::UInt:
        if(field->isAutoIncrement)
            dbType = "SERIAL";
        else
            dbType = "INTEGER";
        break;

    case QMetaType::Long:
    case QMetaType::ULong:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
        if(field->isAutoIncrement)
            dbType = "BIGSERIAL";
        else
            dbType = "BIGINT";
        break;

    case QMetaType::Char:
    case QMetaType::QChar:
        return "CHAR(1)";

    case QMetaType::QString:
        if(field->length)
            dbType = QString("VARCHAR(%1)").arg(field->length);
        else
            dbType = "TEXT";
        break;

    case QMetaType::QPoint:
    case QMetaType::QPointF:
        dbType="POINT";
        break;

    case QMetaType::QUuid:
        dbType = "UUID";
        break;

    case QMetaType::QPolygon:
    case QMetaType::QPolygonF:
        dbType = "POLYGON";
        break;

    case QMetaType::QLine:
    case QMetaType::QLineF:
        return "LINE";

    case QMetaType::QRect:
    case QMetaType::QRectF:
        return "BOX";

    case QMetaType::QJsonArray:
    case QMetaType::QJsonValue:
    case QMetaType::QJsonObject:
    case QMetaType::QJsonDocument:
        return "JSON";

    case QMetaType::QStringList:
        return "TEXT[]";

    case QMetaType::QSize:
    case QMetaType::QSizeF:
    case QMetaType::QUrl:
    case QMetaType::QColor:
        return "TEXT";

    default:
        qDebug() << "Type for " << (int)field->type << field->type << "(" << QMetaType::typeName(field->type) << ")" << "nut supported";
        dbType = QString();
    }

    if(field->type == (unsigned)QMetaType::type("Nut::DbGeography"))
        dbType = "GEOGRAPHY";

    return dbType;
}

QString PostgreSqlGenerator::diff(FieldModel *oldField, FieldModel *newField)
{
    QString sql = QString();
    if(oldField && newField)
        if(*oldField == *newField)
            return QString();

    if(!newField){
        sql = "DROP COLUMN " + oldField->name;
    }else{
        if(oldField){
            sql = "ALTER COLUMN ";
            sql.append(newField->name + " TYPE " + fieldType(newField));
        } else {
            sql = "ADD COLUMN ";
            sql.append(fieldDeclare(newField));
        }
    }
    return sql;
}

QString PostgreSqlGenerator::escapeValue(const QVariant &v) const
{
    if (v.type() == QVariant::Time)
        return "'" + v.toTime().toString("HH:mm:ss") + "'";

    if (v.type() == QVariant::Date)
        return "'" + v.toDate().toString("yyyy-MM-dd") + "'";

    if (v.type() == QVariant::DateTime)
        return "'" + v.toDateTime().toString("yyyy-MM-dd HH:mm:ss") + "'";

    if (v.type() == QVariant::StringList)
        return "'{" + v.toStringList().join(",") + "}'";

    if (v.type() == QVariant::Point) {
        QPoint pt = v.toPoint();
        return QString("'(%1, %2)'").arg(pt.x()).arg(pt.y());
    }
    if (v.type() == QVariant::PointF) {
        QPointF pt = v.toPointF();
        return QString("'(%1, %2)'").arg(pt.x()).arg(pt.y());
    }

#ifdef QT_GUI_LIB
    if (v.type() == QVariant::Polygon) {
        QString ret;
        QPoint pt;
        QPolygon pol = v.value<QPolygon>();
        for (int i = 0; i < pol.size(); ++i) {
            pt = pol.at(i);
            if (!ret.isEmpty())
                ret.append("),(");
            ret.append(QString::number(pt.x()) + ", " + QString::number(pt.y()));
        }
        return "'((" + ret + "))'";
    }
    if (v.type() == QVariant::PolygonF) {
        QString ret;
        QPointF pt;
        QPolygonF pol = v.value<QPolygonF>();
        for (int i = 0; i < pol.size(); ++i) {
            pt = pol.at(i);
            if (!ret.isEmpty())
                ret.append("),(");
            ret.append(QString::number(pt.x()) + ", " + QString::number(pt.y()));
        }
        return "'((" + ret + "))'";
    }
#endif

    return SqlGeneratorBase::escapeValue(v);
}

QVariant PostgreSqlGenerator::readValue(const QMetaType::Type &type, const QVariant &dbValue)
{
    if (type == QMetaType::QDateTime)
        return dbValue.toDateTime();// QDateTime::fromString(dbValue.toString(), "yyyy-MM-dd HH:mm:ss");

    if (type == QMetaType::QPoint) {
        return SqlGeneratorBase::readValue(QMetaType::QPoint, dbValue.toString()
                                           .replace("(", "").replace(")", ""));
    }
    if (type == QMetaType::QPointF) {
        return SqlGeneratorBase::readValue(QMetaType::QPointF, dbValue.toString()
                                           .replace("(", "").replace(")", ""));
    }
    return SqlGeneratorBase::readValue(type, dbValue);
}


NUT_END_NAMESPACE
