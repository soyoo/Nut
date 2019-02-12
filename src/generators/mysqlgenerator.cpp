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

#include "mysqlgenerator.h"
#include "../tablemodel.h"

#include <QPoint>
#include <QPointF>

NUT_BEGIN_NAMESPACE

MySqlGenerator::MySqlGenerator(Database *parent) : SqlGeneratorBase(parent)
{

}

QString MySqlGenerator::fieldType(FieldModel *field)
{
    QString dbType;

    switch (field->type) {
    case QMetaType::Bool:        return "BOOLEAN";
    case QMetaType::Char:
    case QMetaType::QChar:       return "CHAR(1)";
    case QMetaType::SChar:
    case QMetaType::UChar:        return "TINYINT";
    case QMetaType::Short:
    case QMetaType::UShort:        return "SMALLINT";
    case QMetaType::UInt:
    case QMetaType::Int:
        dbType = "INT";
        if(field->isAutoIncrement)
            dbType += " AUTO_INCREMENT";
        break;
    case QMetaType::Long:
    case QMetaType::ULong:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
        return "BIGINT";

    case QMetaType::Float:
        return "FLOAT";

    case QMetaType::Double:
        return "REAL";

    case QMetaType::QBitArray:      return "VARBINARY";
    case QMetaType::QByteArray:     return "BLOB";
    case QMetaType::QDate:          return "DATE";
    case QMetaType::QTime:          return "TIME";
    case QMetaType::QDateTime:      return "DATETIME";

    case QMetaType::QString:
        if(field->length)
            dbType = QString("VARCHAR(%1)").arg(field->length);
        else
            dbType = "TEXT";
        break;

    case QMetaType::QPoint:
    case QMetaType::QPointF:
        dbType = "POINT";
        break;

    case QMetaType::QPolygon:
    case QMetaType::QPolygonF:
        dbType = "POLYGON";
        break;

    case QMetaType::QUuid:
        dbType = "VARCHAR(64)";
        break;

    case QMetaType::QSize:
    case QMetaType::QSizeF:
    case QMetaType::QRect:
    case QMetaType::QRectF:
    case QMetaType::QLine:
    case QMetaType::QLineF:
    case QMetaType::QColor:
    case QMetaType::QUrl:
    case QMetaType::QJsonArray:
    case QMetaType::QJsonValue:
    case QMetaType::QJsonObject:
    case QMetaType::QJsonDocument:
    case QMetaType::QStringList:    return "TEXT";

    default:
        qWarning("Type %s::%s(%d) is not supported",
                 qPrintable(field->name),
                 QMetaType::typeName(field->type),
                 field->type);
        dbType = QString();
    }

    if(field->typeName == QStringLiteral("Nut::DbGeography"))
        dbType = "GEOMETRY";

    return dbType;
}

QString MySqlGenerator::escapeValue(const QVariant &v) const
{
    switch (v.type()) {
    case QMetaType::QPoint: {
        QPoint pt = v.toPoint();
        return QString("GeomFromText('POINT(%1 %2)',0)").arg(pt.x()).arg(pt.y());
    }

    case QMetaType::QPointF: {
        QPointF pt = v.toPointF();
        return QString("GeomFromText('POINT(%1 %2)',0)").arg(pt.x()).arg(pt.y());
    }

    default:
        return SqlGeneratorBase::escapeValue(v);
    }
}

QVariant MySqlGenerator::readValue(const QMetaType::Type &type, const QVariant &dbValue)
{
    if (type == QMetaType::QPointF) {
        qDebug() << "QVariant::PointF" << dbValue;
    }
    return SqlGeneratorBase::readValue(type, dbValue);
}

//QString MySqlGenerator::phrase(const PhraseData *d) const
//{
//    if (d->operatorCond == PhraseData::Distance) {
//        return QString("ST_Distance(%1, %2)")
//                .arg(d->left->text)
//                .arg(escapeValue(d->operand.toPointF()));
//    }

//    return SqlGeneratorBase::phrase(d);
//}

//QString MySqlGenerator::selectCommand(SqlGeneratorBase::AgregateType t,
//                                      QString agregateArg,
//                                      QString tableName,
//                                      QList<WherePhrase> &wheres,
//                                      QList<WherePhrase> &orders,
//                                      QList<RelationModel*> joins,
//                                      int skip, int take)
//{
//    QString command = SqlGeneratorBase::selectCommand(t, agregateArg,
//                                                      tableName,
//                                                      wheres, orders,
//                                                      joins, skip, take);

//    if (take != -1 && skip != -1)
//        command.append(QString(" LIMIT %1 OFFSET %2")
//                       .arg(take)
//                       .arg(skip));
//    return command;
//}

NUT_END_NAMESPACE
