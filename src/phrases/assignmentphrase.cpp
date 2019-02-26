#include "abstractfieldphrase.h"
#include "assignmentphrase.h"
#include "phrasedata.h"

NUT_BEGIN_NAMESPACE

AssignmentPhrase::AssignmentPhrase(PhraseData *d) : data(d)
{
    d->parents++;
}

AssignmentPhrase::AssignmentPhrase(AbstractFieldPhrase *l, const QVariant r)
{

    data = new PhraseData(l->data, PhraseData::Equal, r);
//    l->data = 0;
}

AssignmentPhrase::AssignmentPhrase(AbstractFieldPhrase *l,
                                   const AssignmentPhrase *r)
{
    data = new PhraseData(l->data, PhraseData::Equal, r->data);
    //    l->data = 0;
}

AssignmentPhrase::AssignmentPhrase(AssignmentPhrase *ph, const QVariant &v)
{
    data = new PhraseData(ph->data, PhraseData::Equal, v);
}

//AssignmentPhrase::AssignmentPhrase(AssignmentPhrase &other)
//{
//    data = other.data;
//    other.data = 0;
//}

AssignmentPhrase::~AssignmentPhrase()
{
    if (data)
        if (!--data->parents)
            delete data;
}

NUT_END_NAMESPACE
