#ifndef ASSIGNMENTPHRASELIST_H
#define ASSIGNMENTPHRASELIST_H

#include "../defines.h"

NUT_BEGIN_NAMESPACE

class PhraseData;
class AssignmentPhrase;
class NUT_EXPORT AssignmentPhraseList
{
public:
    QList<PhraseData*> data;
    explicit AssignmentPhraseList() = default;
    AssignmentPhraseList(const AssignmentPhrase &l);
    AssignmentPhraseList(AssignmentPhraseList *l, const AssignmentPhrase *r);
    AssignmentPhraseList(AssignmentPhrase *l, const AssignmentPhrase *r);
    AssignmentPhraseList(const AssignmentPhrase &r, const AssignmentPhrase &l);

    AssignmentPhraseList operator &(const AssignmentPhrase &ph);

    ~AssignmentPhraseList();

private:
    void incAllDataParents();
};

NUT_END_NAMESPACE

#endif // ASSIGNMENTPHRASELIST_H
