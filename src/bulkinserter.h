#ifndef BULKINSERTER_H
#define BULKINSERTER_H

#include <initializer_list>
#include <QDebug>
#include "defines.h"

NUT_BEGIN_NAMESPACE

class PhraseList;
class BulkInserter
{
public:
    BulkInserter(QString &className);
    void setFields(const PhraseList &ph);

    void insert(std::initializer_list<QVariant> vars);
    template<typename... Args>
    void insert(Args... args) {
        insert({args...});
    }
};

NUT_END_NAMESPACE

#endif // BULKINSERTER_H
