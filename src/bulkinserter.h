#ifndef BULKINSERTER_H
#define BULKINSERTER_H

#include <initializer_list>
#include <QDebug>
#include "defines.h"
#include "phrases/phraselist.h"
#include "phrases/fieldphrase.h"

NUT_BEGIN_NAMESPACE

class PhraseList;
class Database;
class BulkInserter
{
    Database *_database;
    QString _className;
    Nut::PhraseList _fields;
    QList<QVariantList> variants;
    size_t _fieldCount;

public:
    BulkInserter(Database *db, QString &className);
    void setFields(const PhraseList &ph);

    void insert(std::initializer_list<QVariant> vars);
    template<typename... Args>
    void insert(Args... args) {
        insert({args...});
    }
    int apply();
};

NUT_END_NAMESPACE

#endif // BULKINSERTER_H
