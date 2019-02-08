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

#include "sqlitegenerator.h"
#include "../table.h"
#include "../tablemodel.h"

NUT_BEGIN_NAMESPACE

SqliteGenerator::SqliteGenerator(Database *parent) : SqlGeneratorBase(parent)
{

}

QString SqliteGenerator::fieldType(FieldModel *field)
{
    QString ret = field->name + " ";
    QString dbType;
    if (field->isPrimaryKey) {
        QString primaryKeyPerfix = " PRIMARY KEY";
        if (field->isAutoIncrement)
            primaryKeyPerfix += " AUTOINCREMENT";
        return "INTEGER" + primaryKeyPerfix;
    }
    switch (field->type) {
    case QMetaType::Bool:           return "BOOLEAN";
    case QMetaType::QByteArray:     return "BLOB";
    case QMetaType::QDate:          return "DATE";
    case QMetaType::QDateTime:      return "DATETIME";
    case QMetaType::QTime:          return "TIME";
    case QMetaType::Double:         return "DOUBLE";
    case QMetaType::Float:          return "FLOAT";

    case QMetaType::SChar:
    case QMetaType::Char:           return "TINYINT";
    case QMetaType::UChar:          return "TINYINT UNSIGNED";
    case QMetaType::Short:          return "SMALLINT";
    case QMetaType::UShort:         return "SMALLINT UNSIGNED";
    case QMetaType::Int:            return "INT";
    case QMetaType::UInt:           return "INT UNSIGNED";
    case QMetaType::Long:           return "MEDIUMINT";
    case QMetaType::ULong:          return "MEDIUMINT UNSIGNED";
    case QMetaType::LongLong:       return "BIGINT";
    case QMetaType::ULongLong:      return "BIGINT UNSIGNED";

    case QMetaType::QChar:          return "NCHAR(1)";

    case QMetaType::QUrl:
    case QMetaType::QJsonArray:
    case QMetaType::QJsonValue:
    case QMetaType::QJsonObject:
    case QMetaType::QJsonDocument:
    case QMetaType::QPoint:
    case QMetaType::QPointF:
    case QMetaType::QPolygon:
    case QMetaType::QPolygonF:
    case QMetaType::QUuid:          return "text";

//        if (field->isAutoIncrement)
//            dbType.append(" PRIMARY KEY AUTOINCREMENT");

    case QMetaType::QString:
        if(field->length)
            return QString("VARCHAR(%1)").arg(field->length);
        else
            return "TEXT";
    default:
//        qWarning("The type (%s) does not supported",
//                 QMetaType::typeName(field->type));
        return QString();
    }
}

void SqliteGenerator::appendSkipTake(QString &sql, int skip, int take)
{
    if (take != -1 && skip != -1)
        sql.append(QString(" LIMIT %1 OFFSET %2")
                       .arg(take)
                   .arg(skip));
}

QString SqliteGenerator::primaryKeyConstraint(const TableModel *table) const
{
    Q_UNUSED(table);
    return QString();
//    QString sql = QString("CONSTRAINT pk_%1 PRIMARY KEY (%2)")
//            .arg(table->name())
//            .arg(table->primaryKey());
//    if (table->field(table->primaryKey())->isAutoIncrement)
//        sql += " AUTOINCREMENT";
//    return sql;
}

NUT_END_NAMESPACE
