#include "abstractfieldphrase.h"

NUT_BEGIN_NAMESPACE

AbstractFieldPhrase::AbstractFieldPhrase(PhraseData *d) : data(d)
{ }

AbstractFieldPhrase::AbstractFieldPhrase(const char *className,
                                         const char *fieldName)
    :data(new PhraseData(className, fieldName))
{
}

AbstractFieldPhrase::AbstractFieldPhrase(const AbstractFieldPhrase &other)
{
    data = other.data;
    data->parents++;
}

AbstractFieldPhrase::AbstractFieldPhrase(AbstractFieldPhrase &&other)
{
    data = other.data;
    data->parents++;
    other.data = nullptr;
}

AbstractFieldPhrase::~AbstractFieldPhrase()
{
    if (data) {
        --data->parents;
        if (data->parents <= 0)
            delete data;
    }
}

PhraseList AbstractFieldPhrase::operator |(const AbstractFieldPhrase &other)
{
    return PhraseList(this, other);
}

ConditionalPhrase AbstractFieldPhrase::isNull()
{
    return ConditionalPhrase(this, PhraseData::Null);
}


ConditionalPhrase AbstractFieldPhrase::operator ==(const ConditionalPhrase
                                                   &other)
{
    return ConditionalPhrase(this, PhraseData::Equal,
                             const_cast<ConditionalPhrase&>(other));
}


AssignmentPhrase AbstractFieldPhrase::operator =(const QVariant &other)
{
    return AssignmentPhrase(this, other);
}

AssignmentPhrase AbstractFieldPhrase::operator =(const ConditionalPhrase &other)
{
    return AssignmentPhrase(new PhraseData(data, PhraseData::Equal, other.data));
}

AssignmentPhrase AbstractFieldPhrase::operator <<(const QVariant &other)
{
    return AssignmentPhrase(this, other);
}

#define AbstractFieldPhraseOperatorVariant(class, op, cond) \
ConditionalPhrase class::operator op(const QVariant &other) \
{ \
    return ConditionalPhrase(this, cond, other); \
}

AbstractFieldPhraseOperatorVariant(AbstractFieldPhrase, ==, PhraseData::Equal)
AbstractFieldPhraseOperatorVariant(AbstractFieldPhrase, !=, PhraseData::NotEqual)

#define AbstractFieldPhraseOperatorField(op, cond) \
ConditionalPhrase AbstractFieldPhrase::operator op(const AbstractFieldPhrase &other) \
{ \
    return ConditionalPhrase(this, cond, other); \
}

AbstractFieldPhraseOperatorField(==, PhraseData::Equal)
AbstractFieldPhraseOperatorField(!=, PhraseData::NotEqual)
AbstractFieldPhraseOperatorField(< , PhraseData::Less)
AbstractFieldPhraseOperatorField(<=, PhraseData::LessEqual)
AbstractFieldPhraseOperatorField(> , PhraseData::Greater)
AbstractFieldPhraseOperatorField(>=, PhraseData::GreaterEqual)

AbstractFieldPhrase AbstractFieldPhrase::operator !()
{
    AbstractFieldPhrase f(data->className, data->fieldName);
    f.data->isNot = !data->isNot;
    return f;
}

NUT_END_NAMESPACE
