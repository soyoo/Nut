#ifndef CONDITIONALPHRASE_H
#define CONDITIONALPHRASE_H

#include "phrasedata.h"

NUT_BEGIN_NAMESPACE

class PhraseData;
class AbstractFieldPhrase;

#define SPECIALIZATION_NUMERIC_MEMBER(type, op, cond) \
ConditionalPhrase operator op(const QVariant &other) \
{ \
    return ConditionalPhrase(this, cond, other); \
}
class ConditionalPhrase
{
public:
    PhraseData *data;
//    QSharedPointer<PhraseData> leftDataPointer;
//    QSharedPointer<PhraseData> rightDataPointer;
    ConditionalPhrase();
    ConditionalPhrase(const ConditionalPhrase &other);
#ifdef Q_COMPILER_RVALUE_REFS
    ConditionalPhrase(const ConditionalPhrase &&other);
#endif
    ConditionalPhrase(const PhraseData *data);
    ConditionalPhrase(AbstractFieldPhrase *, PhraseData::Condition);
    ConditionalPhrase(AbstractFieldPhrase *, PhraseData::Condition, const QVariant &v);
    ConditionalPhrase(AbstractFieldPhrase *, PhraseData::Condition, const AbstractFieldPhrase &v);
    ConditionalPhrase(AbstractFieldPhrase *l, PhraseData::Condition cond, ConditionalPhrase &r);
    ConditionalPhrase(ConditionalPhrase *l, PhraseData::Condition cond, const AbstractFieldPhrase  &r);
    ConditionalPhrase(ConditionalPhrase *l, PhraseData::Condition cond, const QVariant &r);
    ConditionalPhrase(ConditionalPhrase *l, PhraseData::Condition cond, ConditionalPhrase &r);
    virtual ~ConditionalPhrase();

    ConditionalPhrase &operator =(const ConditionalPhrase &other);
    ConditionalPhrase operator ==(const QVariant &other);
//    ConditionalPhrase operator ==(const AbstractFieldPhrase &other);
//    ConditionalPhrase operator &&(const ConditionalPhrase &other);
//    ConditionalPhrase operator ||(const ConditionalPhrase &other);
    ConditionalPhrase operator !();

    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
};


#define DECLARE_CONDITIONALPHRASE_OPERATORS(op) \
ConditionalPhrase operator op(const ConditionalPhrase &l, const ConditionalPhrase &r); \
ConditionalPhrase operator op(const ConditionalPhrase &l, ConditionalPhrase &&r); \
ConditionalPhrase operator op(ConditionalPhrase &&l, const ConditionalPhrase &r); \
ConditionalPhrase operator op(ConditionalPhrase &&l, ConditionalPhrase &&r);

DECLARE_CONDITIONALPHRASE_OPERATORS(==)
DECLARE_CONDITIONALPHRASE_OPERATORS(&&)
DECLARE_CONDITIONALPHRASE_OPERATORS(||)

ConditionalPhrase operator <(AbstractFieldPhrase &l, ConditionalPhrase &&r);
ConditionalPhrase operator <=(AbstractFieldPhrase &l, ConditionalPhrase &&r);
ConditionalPhrase operator >(AbstractFieldPhrase &l, ConditionalPhrase &&r);
ConditionalPhrase operator >=(AbstractFieldPhrase &l, ConditionalPhrase &&r);

ConditionalPhrase operator <(ConditionalPhrase &&l, ConditionalPhrase &&r);
ConditionalPhrase operator <=(ConditionalPhrase &&l, ConditionalPhrase &&r);
ConditionalPhrase operator >(ConditionalPhrase &&l, ConditionalPhrase &&r);
ConditionalPhrase operator >=(ConditionalPhrase &&l, ConditionalPhrase &&r);


NUT_END_NAMESPACE

#endif // CONDITIONALPHRASE_H
