#include "bulkinserter.h"
#include "phrases/phraselist.h"
#include "database.h"
#include "generators/sqlgeneratorbase_p.h"
#include "databasemodel.h"

#include <QDebug>

Nut::BulkInserter::BulkInserter(Nut::Database *db, QString &className)
    : _database(db), _fieldCount(0)
{
    foreach (TableModel *m, db->model())
        if (m->className() == className)
            _className = m->name();
}

void Nut::BulkInserter::setFields(const Nut::PhraseList &ph)
{
    _fields = ph;
    _fieldCount = static_cast<size_t>(ph.data.count());
}

void Nut::BulkInserter::insert(std::initializer_list<QVariant> vars)
{
    if (vars.size() != _fieldCount) {
        qInfo("Number of rows mstake");
        return;
    }

    QVariantList list;
    std::initializer_list<QVariant>::iterator it;
    for (it = vars.begin(); it != vars.end(); ++it)
        list.append(*it);
    variants.append(list);
}

int Nut::BulkInserter::apply()
{
    auto sql = _database->sqlGenertor()->insertBulk(_className, _fields, variants);
    QSqlQuery q = _database->exec(sql);
    return q.numRowsAffected();
}

