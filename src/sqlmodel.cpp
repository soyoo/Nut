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

#include "sqlmodel_p.h"
#include "sqlmodel.h"

NUT_BEGIN_NAMESPACE

SqlModel::SqlModel(Database *database, TableSetBase *tableSet, QObject *parent) :
    QAbstractTableModel(parent)
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
        Table *t = d->rows.at(index.row());
        return t->property(d->model->field(index.column())->name.toLocal8Bit().data());
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

SqlModelPrivate::SqlModelPrivate()
{

}

NUT_END_NAMESPACE
