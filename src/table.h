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

#ifndef TABLE_H
#define TABLE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QtCore/QSet>

#include "tablemodel.h"
#include "defines.h"
#include "phrase.h"

NUT_BEGIN_NAMESPACE

class Database;
class TableSetBase;
class TableModel;
class TablePrivate;
class NUT_EXPORT Table : public QObject
{
    Q_OBJECT
    TablePrivate *d_ptr;
    Q_DECLARE_PRIVATE(Table)

public:
    explicit Table(QObject *parentTableSet = nullptr);
    virtual ~Table();

    enum Status{
        NewCreated,
        FeatchedFromDB,
        Added,
        Modified,
        Deleted
    };

    int save(Database *db);

//    Q_DECL_DEPRECATED
//    QString primaryKey() const;

//    Q_DECL_DEPRECATED
//    bool isPrimaryKeyAutoIncrement() const;

//    Q_DECL_DEPRECATED
//    QVariant primaryValue() const;

    Status status() const;
    void setStatus(const Status &status);

    TableSetBase *parentTableSet() const;
    void setParentTableSet(TableSetBase *parentTableSet);

    TableSetBase *childTableSet(const QString &name) const;

    QSet<QString> changedProperties() const;

    bool setParentTable(Table *master, TableModel *masterModel, TableModel *model);
signals:

public slots:

protected:
    void propertyChanged(const QString &propName);

private:
    void setModel(TableModel *model);
//    TableModel *myModel;
//    Status _status;
//    QSet<QString> _changedProperties;
    //TODO: is this removable?
//    TableSetBase *_parentTableSet;

//    QSet<TableSetBase*> childTableSets;
    void clear();
    void add(TableSetBase *);

    template<class T>
    friend class Query;

    template<class T>
    friend class TableSet;
    friend class TableSetBase;
};

NUT_END_NAMESPACE

#endif // TABLE_H
