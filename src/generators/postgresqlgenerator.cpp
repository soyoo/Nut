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

    case QMetaType::ULongLong:
    case QMetaType::LongLong:
        if(field->isAutoIncrement)
            dbType = "BIGSERIAL";
        else
            dbType = "BIGINT";
        break;

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
    if (v.type() == QVariant::DateTime)
        return "'" + v.toDateTime().toString("yyyy-MM-dd HH:mm:ss") + "'";

    return SqlGeneratorBase::escapeValue(v);
}

QVariant PostgreSqlGenerator::readValue(const QMetaType::Type &type, const QVariant &dbValue)
{
    if (type == QMetaType::QDateTime)
        return dbValue.toDateTime();// QDateTime::fromString(dbValue.toString(), "yyyy-MM-dd HH:mm:ss");

    return SqlGeneratorBase::readValue(type, dbValue);
}


NUT_END_NAMESPACE
