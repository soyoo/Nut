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

#include "table.h"
#include "database.h"
#include "tablesetbase_p.h"
#include "databasemodel.h"
#include "tablesetbasedata.h"

NUT_BEGIN_NAMESPACE

TableSetBase::TableSetBase(Database *parent) : QObject(parent),
    data(new TableSetBaseData(parent))
{
    parent->add(this);
}

TableSetBase::TableSetBase(Table *parent) : QObject(parent),
    data(new TableSetBaseData(parent))
{
    parent->add(this);
}

TableSetBase::~TableSetBase()
{
    foreach (Table *t, data->tables)
        t->setParentTableSet(nullptr);

    foreach (Row<Table> t, data->childs)
        t->setParentTableSet(nullptr);
}

int TableSetBase::save(Database *db, bool cleanUp)
{
    int rowsAffected = 0;
    TableModel *masterModel = nullptr;
    if (data->table)
        masterModel = db->model().tableByClassName(data->table->metaObject()->className());

    foreach (Table *t, data->childRows) {
        if(data->table)
            t->setParentTable(data->table,
                              masterModel,
                              db->model().tableByClassName(t->metaObject()->className()));

        if(t->status() == Table::Added
                || t->status() == Table::Modified
                || t->status() == Table::Deleted){
            rowsAffected += t->save(db);
            if(cleanUp)
#ifndef NUT_SHARED_POINTER
                t->deleteLater();
#else
                remove(t);
#endif
        }
    }

    if (cleanUp)
        data->childRows.clear();

    return rowsAffected;
}

void TableSetBase::clearChilds()
{
#ifndef NUT_SHARED_POINTER
    foreach (Table *t, data->childRows)
        t->deleteLater();
#endif
    data->childRows.clear();
}

void TableSetBase::add(Table *t)
{
    if(!data->tables.contains(get(t))){
        data.detach();
        data->tables.insert(get(t));
        data->childRows.append(get(t));
    }
}

void TableSetBase::remove(Table *t)
{
    data.detach();
    data->tables.remove(get(t));
    data->childRows.removeOne(get(t));
}

void TableSetBase::add(Row<Table> t)
{
    data.detach();
    data->childs.append(t);
}

void TableSetBase::remove(Row<Table> t)
{
    data.detach();
    data->childs.removeOne(t);
}

QString TableSetBase::childClassName() const
{
    return data->childClassName;
}

Database *TableSetBase::database() const
{
    return data->database;
}

void TableSetBase::setDatabase(Database *database)
{
    data.detach();
    data->database = database;
}

NUT_END_NAMESPACE
