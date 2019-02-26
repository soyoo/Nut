#include "phrasedatalist.h"

NUT_BEGIN_NAMESPACE

PhraseDataList::PhraseDataList() : QList<PhraseData*>()
{

}

PhraseDataList::PhraseDataList(const PhraseDataList &other) : QList<PhraseData*>()
{
//    auto &o = const_cast<PhraseDataList&>(other);
    PhraseDataList::const_iterator i;
    for (i = other.constBegin(); i != other.constEnd(); ++i)
        append(*i);
}

void PhraseDataList::append(PhraseData *d)
{
    d->parents++;
    QList<PhraseData*>::append(d);
}

void PhraseDataList::append(QList<PhraseData *> &dl)
{
    foreach (PhraseData *d, dl)
        d->parents++;
    QList<PhraseData*>::append(dl);
}

PhraseDataList::~PhraseDataList()
{
    QList<PhraseData*>::iterator i;
    for (i = begin(); i != end(); ++i) {
        (*i)->cleanUp();
        if (!--(*i)->parents)
            delete *i;
    }
}

NUT_END_NAMESPACE
