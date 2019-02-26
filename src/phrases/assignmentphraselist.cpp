#include "assignmentphraselist.h"
#include "phrasedata.h"
#include <phrase.h>

NUT_BEGIN_NAMESPACE


AssignmentPhraseList AssignmentPhrase::operator &(const AssignmentPhrase &other)
{
    return AssignmentPhraseList(this, &other);
}

AssignmentPhraseList::AssignmentPhraseList(const AssignmentPhrase &l)
{
    data.append(l.data);
    incAllDataParents();
}

AssignmentPhraseList::AssignmentPhraseList(AssignmentPhraseList *l,
                                           const AssignmentPhrase *r)
{
    data.append(l->data);
    data.append(r->data);
    incAllDataParents();
}

AssignmentPhraseList::AssignmentPhraseList(AssignmentPhrase *l,
                                           const AssignmentPhrase *r)
{
    data.append(l->data);
    data.append(r->data);
    incAllDataParents();
}

AssignmentPhraseList::AssignmentPhraseList(const AssignmentPhrase &r,
                                           const AssignmentPhrase &l)
{
    data.append(l.data);
    data.append(r.data);
    incAllDataParents();
}

AssignmentPhraseList AssignmentPhraseList::operator &(const AssignmentPhrase
                                                      &ph)
{
    return AssignmentPhraseList(this, &ph);
}

AssignmentPhraseList::~AssignmentPhraseList()
{
    foreach (PhraseData *d, data)
        if (!--d->parents)
            delete d;
//    qDeleteAll(data);
    //    data.clear();
}

void AssignmentPhraseList::incAllDataParents()
{
    foreach (PhraseData *d, data)
        d->parents++;
}


NUT_END_NAMESPACE
