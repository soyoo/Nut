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

#include "database.h"
#include "tablesetbase_p.h"
#include "databasemodel.h"
#include "tablemodel.h"
#include "table.h"
#include "sqlmodel_p.h"
#include "sqlmodel.h"
#include "query.h"

NUT_BEGIN_NAMESPACE

//SqlModel::SqlModel(Query *q) : QAbstractItemModel(q.)
//{

//}

void SqlModel::setRenderer(const std::function<QVariant (int, QVariant)> &renderer)
{
    _renderer = renderer;
}

SqlModel::SqlModel(Database *database, TableSetBase *tableSet, QObject *parent) :
    QAbstractTableModel(parent), d_ptr(new SqlModelPrivate(this)), _renderer(nullptr)
{
    Q_D(SqlModel);
    d->model = database->model()
            .tableByClassName(tableSet->childClassName());
    d->tableName = d->model->name();


    //     setQuery("SELECT * FROM " + d->tableName, database->databaseName());
}

int SqlModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const SqlModel);
    return d->rows.count();
}

int SqlModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const SqlModel);
    return d->model->fields().count();
}

QVariant SqlModel::data(const QModelIndex &index, int role) const
{
    Q_D(const SqlModel);
    if (!index.isValid())
        return QVariant();

    if (index.row() >= d->rows.count() || index.row() < 0)
        return QVariant("-");

    if (role == Qt::DisplayRole) {
        Row<Table> t = d->rows.at(index.row());
        QVariant v = t->property(d->model->field(index.column())->name.toLocal8Bit().data());
//        emit beforeShowText(index.column(), v);
        if (_renderer != nullptr)
            v = _renderer(index.column(), v);
        return v;
//        LogData *d = dataList.at(index.row());

//        switch (index.column()) {
//        case COL_ID:
//            return index.row() + 1;
//        case COL_Type: {
//            return typeText(d->type);
//        }
//        case COL_TITLE:
//            return d->title;
//        case COL_File:
//            return d->file;
//        case COL_Function:
//            return d->function;
//        case COL_Line:
//            return d->line;
//        }
    }
    return QVariant();
}

void SqlModel::setRows(RowList<Table> rows)
{
    Q_D(SqlModel);
    beginRemoveRows(QModelIndex(), 0, d->rows.count());
    d->rows.clear();
    endRemoveRows();
    beginInsertRows(QModelIndex(), 0, rows.count());
    d->rows = rows;
    endInsertRows();
}

void SqlModel::append(Row<Table> table)
{
    Q_D(SqlModel);
    beginInsertRows(QModelIndex(), d->rows.count(), d->rows.count());
    d->rows.append(table);
    endInsertRows();
}

//void SqlModel::append(Table *table)
//{
//    append(TableType<Table>::Row(table));
//}

QVariant SqlModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        Q_D(const SqlModel);
        return d->model->field(section)->displayName;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

Row<Table> SqlModel::at(const int &i) const
{
    Q_D(const SqlModel);
    return d->rows.at(i);
}

SqlModelPrivate::SqlModelPrivate(SqlModel *parent) : q_ptr(parent)
{

}


NUT_END_NAMESPACE
