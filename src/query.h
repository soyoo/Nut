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

#ifndef QUERY_H
#define QUERY_H

#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtCore/QScopedPointer>
#include <QtCore/QRegularExpression>
#include <QtCore/QMetaObject>
#include <QtSql/QSqlResult>
#include <QElapsedTimer>
#include <QSqlError>

#include "query_p.h"
#include "database.h"
#include "databasemodel.h"
#include "tablesetbase_p.h"
#include "generators/sqlgeneratorbase_p.h"
#include "querybase_p.h"
#include "wherephrase.h"
#include "tablemodel.h"

NUT_BEGIN_NAMESPACE

template <class T>
        class NUT_EXPORT Query : public QueryBase
{
    QueryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(Query)

    bool m_autoDelete;

public:
    Query(Database *database, TableSetBase *tableSet, bool autoDelete);
    ~Query();

    //ddl
    Query<T> *setWhere(WherePhrase where);

    Query<T> *join(const QString &className);
    Query<T> *join(Table *c);

    template<class TABLE>
    Query<T> *join()
    {
        join(TABLE::staticMetaObject.className());
        return this;
    }


    //    Query<T> *orderBy(QString fieldName, QString type);
    Query<T> *skip(int n);
    Query<T> *take(int n);
    Query<T> *orderBy(WherePhrase phrase);
    Query<T> *include(TableSetBase *t);
    Query<T> *include(Table *t);

    //data selecting
    T *first();
    QList<T*> toList(int count = -1);
    template <typename F>
    QList<F> select(const FieldPhrase<F> f);
    int count();
    QVariant max(FieldPhrase<int> &f);
    QVariant min(FieldPhrase<int> &f);
    QVariant average(FieldPhrase<int> &f);

    //data mailpulation
    int update(WherePhrase phrase);
    int remove();

    //debug purpose
    QString sqlCommand() const;
};

template <typename T>
inline Query<T> *createQuery(TableSet<T> *tableSet)
{
    return tableSet->query();
}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T>::Query(Database *database, TableSetBase *tableSet,
                                     bool autoDelete)
    : QueryBase(database), d_ptr(new QueryPrivate(this)),
      m_autoDelete(autoDelete)
{
    Q_D(Query);

    d->database = database;
    d->tableSet = tableSet;
    d->className = T::staticMetaObject.className();
    d->tableName
            = // TableModel::findByClassName(T::staticMetaObject.className())->name();
            d->database->model()
            .tableByClassName(T::staticMetaObject.className())
            ->name();
}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T>::~Query()
{
    Q_D(Query);
    delete d;
}

template <class T>
Q_OUTOFLINE_TEMPLATE QList<T *> Query<T>::toList(int count)
{
    Q_UNUSED(count);
    Q_D(Query);
    QList<T*> result;
    d->select = "*";
    QElapsedTimer t;
    t.start();


    d->sql = d->database->sqlGenertor()->selectCommand(
                SqlGeneratorBase::SelectAll, "",
                d->tableName,
                d->wheres, d->orderPhrases, d->relations,
                d->skip, d->take);
    QSqlQuery q = d->database->exec(d->sql);
    if (q.lastError().isValid())
        qDebug() << q.lastError().text();


    QSet<QString> relatedTables;
    foreach (RelationModel *rel, d->relations)
        relatedTables << rel->slaveTable->name() << rel->masterTable->name();


    QStringList childTables, masterTables;
    QMap<QString, Table*> lastClassRow;

    foreach (RelationModel *rel, d->relations) {
        childTables.append(rel->slaveTable->name());
        masterTables.append(rel->masterTable->name());
    }
qDebug() << childTables;
qDebug() << masterTables;

    struct LevelData{
        QVariant keyValue;
        TableSetBase *tableSet;
        RelationModel *relation;
        QList<int> masters;
        QList<int> slaves;

        QString key;
        QString className;
        QString tableName;
        int typeId;
        Table *lastRow;
    };
    QVector<LevelData> levels;
    QList<T*> returnList;
    QList<RelationModel*>::iterator i;
    for (int i = 0; i < d->relations.count(); ++i) {
        LevelData data;
        data.relation = d->relations[i];
        qDebug() <<"relation" << data.relation->masterTable->name() << data.relation->slaveTable->name();
        data.key = data.relation->slaveTable->name() + "." + data.relation->localColumn;
        data.className = data.relation->slaveTable->className();
        data.typeId = d->relations[i]->slaveTable->typeId();
        data.tableName = data.relation->slaveTable->name();

        data.tableSet = 0;
        for (int j = 0; j < i; ++j) {
            if (d->relations[i]->masterTable->name() == d->relations[j]->slaveTable->name()) {
                data.masters.append(j);
                levels[i].slaves.append(i);
            }
        }
        levels.append(data);
    }
qDebug()<<"count="<<levels.count();

    /*for (int i = d->joins.count() - 1; i >= 0; i--) {
        QString className = d->joins[i];
        //    foreach (QString className, d->joins) {
        LevelData data;
        data.className = className;
        TableModel *m = d->database->model().tableByClassName(className);
        if (!m) {
            qWarning("Model '%s' not found!!!", qPrintable(className));
            return returnList;
        }
        data.key = m->name() + "." + m->primaryKey();
        data.typeId = m->typeId();
        data.keyValue = QVariant();
        data.tableSet = 0;
        data.tableName = m->name();
        levels.append(data);
    }*/

    while (q.next()) {
        qDebug() << "HAS";
        int p = levels.count();
        while (p) {
            for (int i = 0; i < levels.count(); i++) {
                LevelData &data = levels[i];
                qDebug() << "level"<<i << data.className;
                --p;
                if (/*!data.tableSet ||*/ data.keyValue != q.value(data.key)) {
                    data.keyValue = q.value(data.key);

                    //create table row
                    Table *table;
                    if (data.className == d->className) {
                        table = new T();
                        table->setTableSet(d->tableSet);
                        returnList.append(dynamic_cast<T*>(table));
                    } else {
                        const QMetaObject *childMetaObject
                                = QMetaType::metaObjectForType(data.typeId);
                        table = qobject_cast<Table *>(childMetaObject->newInstance());
                    }

                    QStringList childFields
                            = d->database->model().tableByClassName(data.className)->fieldsNames();
                    foreach (QString field, childFields)
                        table->setProperty(field.toLatin1().data(),
                                           q.value(data.tableName + "." + field));

                    table->setStatus(Table::FeatchedFromDB);
                    table->setParent(this);
                    table->clear();

                    qDebug() << "table created" << table;
                    //set last created row
                    data.lastRow = table;
                }
            }
        }
    }
    if (m_autoDelete)
        deleteLater();

    qDebug() << "Elapsed time:" << QString("%1ms").arg(t.elapsed() / 1000.);
    return returnList;
}

template <typename T>
template <typename F>
Q_OUTOFLINE_TEMPLATE QList<F> Query<T>::select(const FieldPhrase<F> f)
{
    Q_D(Query);
    QList<F> ret;

    d->joins.prepend(d->tableName);
    d->sql = d->database->sqlGenertor()->selectCommand(
                SqlGeneratorBase::SignleField, f.data()->text,
                d->tableName, d->wheres,
                d->orderPhrases, d->relations, d->skip, d->take);

    QSqlQuery q = d->database->exec(d->sql);

    while (q.next()) {
        QVariant v = q.value(0);
        ret.append(v.value<F>());
    }

    if (m_autoDelete)
        deleteLater();
    return ret;
}

template <class T>
Q_OUTOFLINE_TEMPLATE T *Query<T>::first()
{
    skip(0);
    take(1);
    QList<T*> list = toList(1);

    if (list.count())
        return list.first();
    else
        return 0;
}

template <class T>
Q_OUTOFLINE_TEMPLATE int Query<T>::count()
{
    Q_D(Query);

    d->joins.prepend(d->tableName);
    d->select = "COUNT(*)";
    d->sql = d->database->sqlGenertor()->selectCommand(SqlGeneratorBase::Count,
                                                       QStringLiteral("*"),
                                                       d->tableName,
                                                       d->wheres,
                                                       d->orderPhrases,
                                                       d->relations);
    QSqlQuery q = d->database->exec(d->sql);

    if (q.next())
        return q.value(0).toInt();
    return 0;
}

template <class T>
Q_OUTOFLINE_TEMPLATE QVariant Query<T>::max(FieldPhrase<int> &f)
{
    Q_D(Query);

    d->joins.prepend(d->tableName);
    d->sql = d->database->sqlGenertor()->selectCommand(
                SqlGeneratorBase::Max, f.data()->text, d->tableName,
                d->wheres, d->orderPhrases,
                d->relations);
    QSqlQuery q = d->database->exec(d->sql);

    if (q.next())
        return q.value(0).toInt();
    return 0;
}

template <class T>
Q_OUTOFLINE_TEMPLATE QVariant Query<T>::min(FieldPhrase<int> &f)
{
    Q_D(Query);

    d->joins.prepend(d->tableName);
    d->sql = d->database->sqlGenertor()->selectCommand(
                SqlGeneratorBase::Min, f.data()->text, d->tableName,
                d->wheres, d->orderPhrases,
                d->relations);
    QSqlQuery q = d->database->exec(d->sql);

    if (q.next())
        return q.value(0).toInt();
    return 0;
}

template <class T>
Q_OUTOFLINE_TEMPLATE QVariant Query<T>::average(FieldPhrase<int> &f)
{
    Q_D(Query);

    d->joins.prepend(d->tableName);
    d->sql = d->database->sqlGenertor()->selectCommand(
                SqlGeneratorBase::Average, f.data()->text, d->tableName,
                d->wheres, d->orderPhrases,
                d->relations);
    QSqlQuery q = d->database->exec(d->sql);

    if (q.next())
        return q.value(0).toInt();
    return 0;
}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::join(const QString &className)
{
    Q_D(Query);

    RelationModel *rel = d->database->model().relationByClassNames(d->className, className);
    if (!rel)
        rel = d->database->model().relationByClassNames(className, d->className);

    if (!rel)
        qFatal("No relation beyween %s and %s",
               qPrintable(d->className), qPrintable(className));

    d->relations.append(rel);
    d->joinClassName = className;
    d->joins.append(className);
    return this;
}

template<class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::join(Table *c)
{
    join(c->metaObject()->className());
    return this;
}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::setWhere(WherePhrase where)
{
    Q_D(Query);
    d->wheres.append(where);
    return this;
}

template<class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::skip(int n)
{
    Q_D(Query);
    d->skip = n;
    return this;
}

template<class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::take(int n)
{
    Q_D(Query);
    d->take = n;
    return this;
}

//template <class T>
//Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::orderBy(QString fieldName,
//                                                 QString type)
//{
//    Q_D(Query);
//    d->orderPhrases.append(fieldName, type);
//    return this;
//}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::orderBy(WherePhrase phrase)
{
    Q_D(Query);
    d->orderPhrases.append(phrase);
    return this;
}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::include(TableSetBase *t)
{
    Q_D(Query);
    d->joinClassName = t->childClassName();
    return this;
}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::include(Table *t)
{
    Q_D(Query);
    d->joinClassName = t->metaObject()->className();
    return this;
}

template <class T>
Q_OUTOFLINE_TEMPLATE int Query<T>::update(WherePhrase phrase)
{
    Q_D(Query);

    d->sql = d->database->sqlGenertor()->updateCommand(phrase, d->wheres,
                                                       d->tableName);
    QSqlQuery q = d->database->exec(d->sql);

    if (m_autoDelete)
        deleteLater();
    return q.numRowsAffected();
}

template <class T>
Q_OUTOFLINE_TEMPLATE int Query<T>::remove()
{
    Q_D(Query);

    d->sql = d->database->sqlGenertor()->deleteCommand(d->wheres, d->tableName);
    QSqlQuery q = d->database->exec(d->sql);

    if (m_autoDelete)
        deleteLater();
    return q.numRowsAffected();
}

template <class T>
Q_OUTOFLINE_TEMPLATE QString Query<T>::sqlCommand() const
{
    Q_D(const Query);
    return d->sql;
}

NUT_END_NAMESPACE

#endif // QUERY_H
