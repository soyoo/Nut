#include "abstractfieldphrase.h"
#include "phraselist.h"

NUT_BEGIN_NAMESPACE

PhraseList::PhraseList() : isValid(false)
{

}

PhraseList::PhraseList(const PhraseList &other) : isValid(true)
{
    data = qMove(other.data);
    const_cast<PhraseList&>(other).data.clear();
}

PhraseList::PhraseList(PhraseList &&other)
{
    data = other.data;
}

PhraseList::PhraseList(const AbstractFieldPhrase &other) : isValid(true)
{
    data.append(other.data);
    incAllDataParents();
}

PhraseList::PhraseList(const AbstractFieldPhrase *left,
                       const AbstractFieldPhrase &right)
    : isValid(true)
{
    data.append(left->data);
    data.append(right.data);
    incAllDataParents();
}

PhraseList::PhraseList(PhraseList *left, PhraseList *right) : isValid(true)
{
//    data = qMove(left->data + right->data);
    data.append(left->data);
    data.append(right->data);
//    left->data.clear();
//    right->data.clear();
}

PhraseList::PhraseList(PhraseList *left, const AbstractFieldPhrase *right)
    : isValid(true)
{
    data.append(left->data);
    data.append(right->data);
    incAllDataParents();
}

PhraseList &PhraseList::operator =(const PhraseList &other)
{
    data.append(const_cast<PhraseList&>(other).data);
    return *this;
}

PhraseList PhraseList::operator |(const AbstractFieldPhrase &other) {
    return PhraseList(this, &other);
}

void PhraseList::incAllDataParents()
{
//    foreach (PhraseData *d, data)
//        d->parents++;
}

PhraseList PhraseList::operator |(PhraseList &other) {
    return PhraseList(this, &other);
}

NUT_END_NAMESPACE
