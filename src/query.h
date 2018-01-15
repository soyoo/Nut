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
    QList<T*> returnList;
    d->select = "*";
    QElapsedTimer t;
    t.start();


    d->sql = d->database->sqlGenertor()->selectCommand(
                SqlGeneratorBase::SelectAll, "",
                d->tableName,
                d->wheres, d->orderPhrases, d->relations,
                d->skip, d->take);
    QSqlQuery q = d->database->exec(d->sql);
    if (q.lastError().isValid()) {
        qDebug() << q.lastError().text();
        return returnList;
    }

    QSet<TableModel*> relatedTables;
    relatedTables << d->database->model().tableByName(d->tableName);
    foreach (RelationModel *rel, d->relations)
        relatedTables << rel->slaveTable << rel->masterTable;


    struct LevelData{
        QList<int> masters;
        QList<int> slaves;
        QList<QString> masterFields;
        QString keyFiledname;
        QVariant lastKeyValue;
        TableModel *table;
        Table *lastRow;
    };
    QVector<LevelData> levels;
    QSet<QString> importedTables;
    auto add_table = [&](int i, TableModel* table) {
        if (importedTables.contains(table->name()))
            return;
        importedTables.insert(table->name());

        LevelData data;
        data.table = table;
        data.keyFiledname = data.table->name() + "." + data.table->primaryKey();
        data.lastKeyValue = QVariant();

        QHash<QString, QString> masters;
        foreach (RelationModel *rel, d->relations)
            if (rel->slaveTable->name() == table->name())
                masters.insert(rel->masterTable->name(), rel->localProperty);

        for (int j = 0; j < levels.count(); ++j) {
            LevelData &dt = levels[j];
            qDebug() <<"[check]"<<table->name() << dt.table->name();

            QHashIterator<QString, QString> it(masters);
            while (it.hasNext()) {
                it.next();

                if (dt.table->name() == it.key()) {
                    data.masters.append(j);
                    data.masterFields.append(it.value());
                    dt.slaves.append(i);
                }
            }
        }
        qDebug() << data.table->name() <<"added";
        levels.append(data);
    };
    for (int i = 0; i < d->relations.count(); ++i) {
        RelationModel *rel = d->relations[i];
        add_table(i, rel->masterTable);
        add_table(i, rel->slaveTable);
    }

    if (!importedTables.count()) {
        LevelData data;
        data.table = d->database->model().tableByName(d->tableName);
        data.keyFiledname = d->tableName + "." + data.table->primaryKey();
        data.lastKeyValue = QVariant();

        levels.append(data);
    }

    QVector<bool> checked;
    checked.reserve(levels.count());
    for (int i = 0; i < levels.count(); ++i)
        checked.append(false);
    qDebug() << "Elapsed time:" << QString("%1ms").arg(t.elapsed() / 1000.);
    while (q.next()) {
        checked.fill(false);

        int p = levels.count();
        qDebug() << "p is"<<p;
        int n = -1;
        int lastP = p;

        while (p) {
            //            Q_ASSERT(p != lastP);
            //            if (p == lastP)
            //                qFatal("NULL Loop detected");

            n = (++n) % levels.count();
            if (checked[n])
                continue;
            LevelData &data = levels[n];

            // check if key value is changed
            if (data.lastKeyValue == q.value(data.keyFiledname)) {
                --p;
                continue;
            }

            // check if master if current table has processed
            foreach (int m, data.masters)
                if (!checked[m])
                    continue;

            checked[n] = true;
            --p;
            data.lastKeyValue = q.value(data.keyFiledname);

            //create table row
            Table *table;
            if (data.table->className() == d->className) {
                table = new T();
                table->setParentTableSet(d->tableSet);
                returnList.append(dynamic_cast<T*>(table));
            } else {
                const QMetaObject *childMetaObject
                        = QMetaType::metaObjectForType(data.table->typeId());
                table = qobject_cast<Table *>(childMetaObject->newInstance());

            }
            qDebug() << "table created" << table;

            QStringList childFields = data.table->fieldsNames();
            foreach (QString field, childFields)
                table->setProperty(field.toLatin1().data(),
                                   q.value(data.table->name() + "." + field));

            for (int i = 0; i < data.masters.count(); ++i) {
                int master = data.masters[i];
                table->setProperty(data.masterFields[i].toLocal8Bit().data(),
                                   QVariant::fromValue(levels[master].lastRow));

                table->setParentTableSet(levels[master].lastRow->childTableSet(data.table->className()));
                TableSetBase *ts = levels[master].lastRow->childTableSet(data.table->className());
                qDebug() << table << "added to"
                         << levels[master].lastRow
                         << ts->childClassName()
                         << data.masterFields[i];
            }

            table->setStatus(Table::FeatchedFromDB);
            table->setParent(this);
            table->clear();

            //set last created row
            data.lastRow = table;



            lastP = p;
        } //while
    } // while
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

    if (!rel) {
        qInfo("No relation between %s and %s",
              qPrintable(d->className), qPrintable(className));
        return this;
    }

    d->relations.append(rel);
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
    return this;
}

template <class T>
Q_OUTOFLINE_TEMPLATE Query<T> *Query<T>::include(Table *t)
{
    Q_D(Query);
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
