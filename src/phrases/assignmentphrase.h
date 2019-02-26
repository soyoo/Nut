#ifndef ASSIGNMENTPHRASE_H
#define ASSIGNMENTPHRASE_H

#include "../defines.h"

#include "assignmentphraselist.h"

NUT_BEGIN_NAMESPACE

class PhraseData;
class AbstractFieldPhrase;
class NUT_EXPORT AssignmentPhrase
{
public:
    PhraseData *data;
    explicit AssignmentPhrase(PhraseData *d);
    explicit AssignmentPhrase(AbstractFieldPhrase *l, const QVariant r);
    explicit AssignmentPhrase(AbstractFieldPhrase *l, const AssignmentPhrase *r);
    explicit AssignmentPhrase(AssignmentPhrase *ph, const QVariant &v);
//    explicit AssignmentPhrase(AssignmentPhrase &other);
    ~AssignmentPhrase();
//    AssignmentPhrase(AssignmentPhrase *l, const AssignmentPhrase *r);

    AssignmentPhraseList operator &(const AssignmentPhrase &other);

};

NUT_END_NAMESPACE

#endif // ASSIGNMENTPHRASE_H
