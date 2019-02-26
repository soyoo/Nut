#ifndef PHRASELIST_H
#define PHRASELIST_H

#include "../defines.h"

#include "phrasedatalist.h"

NUT_BEGIN_NAMESPACE

class AbstractFieldPhrase;
class PhraseList{
public:
    bool isValid;
    PhraseDataList data;
    explicit PhraseList();
    PhraseList(const PhraseList &other);
    PhraseList(PhraseList &&other);
    PhraseList(const AbstractFieldPhrase &other);
    PhraseList(const AbstractFieldPhrase *left, const AbstractFieldPhrase &right);
    PhraseList(PhraseList *left, PhraseList *right);
    PhraseList(PhraseList *left, const AbstractFieldPhrase *right);
    virtual ~PhraseList() = default;

    PhraseList &operator =(const PhraseList &other);
    PhraseList operator |(PhraseList &other);
    PhraseList operator |(const AbstractFieldPhrase &other);

private:
    void incAllDataParents();
};

NUT_END_NAMESPACE

#endif // PHRASELIST_H
