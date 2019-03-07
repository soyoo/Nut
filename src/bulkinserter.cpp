#include "bulkinserter.h"
#include "phrases/phraselist.h"

Nut::BulkInserter::BulkInserter(QString &className)
{

}

void Nut::BulkInserter::setFields(const Nut::PhraseList &ph)
{

}

void Nut::BulkInserter::insert(std::initializer_list<QVariant> vars)
{
    std::initializer_list<QVariant>::iterator it;  // same as: const int* it
    for (it = vars.begin(); it != vars.end(); ++it)
        qDebug() << *it;
}

