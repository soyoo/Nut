#ifndef PHRASEDATALIST_H
#define PHRASEDATALIST_H

#include "phrasedata.h"

NUT_BEGIN_NAMESPACE

class NUT_EXPORT PhraseDataList : public QList<PhraseData*>
{
public:
    PhraseDataList();
    PhraseDataList(const PhraseDataList &other);
    void append(PhraseData *d);
    void append(QList<PhraseData*> &dl);
    virtual ~PhraseDataList();
};

NUT_END_NAMESPACE

#endif // PHRASEDATALIST_H
