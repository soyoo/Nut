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

NUT_BEGIN_NAMESPACE

TableSetBase::TableSetBase(Database *parent) : QObject(parent),
    _database(parent), _table(nullptr)//, _tableName(QString())
{
    parent->add(this);
}

TableSetBase::TableSetBase(Table *parent) : QObject(parent),
    _database(nullptr), _table(parent)//, _tableName(QString())
{
    parent->add(this);
}

TableSetBase::~TableSetBase()
{
    foreach (Table *t, _tables)
        t->setParentTableSet(nullptr);
}

int TableSetBase::save(Database *db, bool cleanUp)
{
    int rowsAffected = 0;
    TableModel *masterModel = nullptr;
    if (_table)
        masterModel = db->model().tableByClassName(_table->metaObject()->className());

    foreach (Table *t, _childRows) {
        if(_table)
            t->setParentTable(_table, masterModel,
                              db->model().tableByClassName(t->metaObject()->className()));

        if(t->status() == Table::Added
                || t->status() == Table::Modified
                || t->status() == Table::Deleted){
            rowsAffected += t->save(db);

            if(cleanUp)
                t->deleteLater();
        }
    }

    if (cleanUp)
        _childRows.clear();

    return rowsAffected;
}

void TableSetBase::clearChilds()
{
    foreach (Table *t, _childRows)
        t->deleteLater();
    _childRows.clear();
}

void TableSetBase::add(Table *t)
{
    if(!_tables.contains(t)){
        _tables.insert(t);
        _childRows.append(t);
    }
}

void TableSetBase::remove(Table *t)
{
    _tables.remove(t);
    _childRows.removeOne(t);
}

QString TableSetBase::childClassName() const
{
    return _childClassName;
}

Database *TableSetBase::database() const
{
    return _database;
}

void TableSetBase::setDatabase(Database *database)
{
    _database = database;
}

NUT_END_NAMESPACE
