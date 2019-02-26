#ifndef FIELDPHRASE_H
#define FIELDPHRASE_H

#include "../defines.h"

#include "abstractfieldphrase.h"

NUT_BEGIN_NAMESPACE

template<typename T, typename enable = void>
class FieldPhrase : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}

    AssignmentPhrase operator =(const QVariant &other) {
        return AssignmentPhrase(this, other);
    }

    ConditionalPhrase operator ==(const QVariant &other) {
        return ConditionalPhrase(this, PhraseData::Equal, other);
    }

};


template<>
class FieldPhrase<QString> : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}

    ConditionalPhrase like(const QString &term) {
        return ConditionalPhrase(this, PhraseData::Like, term);
    }

    AssignmentPhrase operator =(const QVariant &v) {
        return AssignmentPhrase(this, v);
    }
};

//#define SPECIALIZATION_NUMERIC(type) \
//template<> \
//class FieldPhrase<type> : public AbstractFieldPhrase \
//{   \
//    public: \
//    FieldPhrase(const char *className, const char *s) : \
//        AbstractFieldPhrase(className, s) \
//    {} \
//    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less) \
//    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual) \
//    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater) \
//    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual) \
//    SPECIALIZATION_NUMERIC_MEMBER(type, %,  PhraseData::Mod) \
//    \
//    SPECIALIZATION_NUMERIC_MEMBER(type, +,  PhraseData::Add) \
//    SPECIALIZATION_NUMERIC_MEMBER(type, -,  PhraseData::Minus) \
//    SPECIALIZATION_NUMERIC_MEMBER(type, *,  PhraseData::Multiple) \
//    SPECIALIZATION_NUMERIC_MEMBER(type, /,  PhraseData::Divide) \
//    AssignmentPhrase operator =(const QVariant &other) { \
//        return AssignmentPhrase(this, other); \
//    } \
//    AssignmentPhrase operator =(const ConditionalPhrase &other) { \
//        return AssignmentPhrase(new PhraseData(data, PhraseData::Equal, other.data)); \
//    } \
//    ConditionalPhrase between(const QVariant &min, const QVariant &max) \
//    { \
//        return ConditionalPhrase(this, PhraseData::Between, \
//            QVariantList() << min << max); \
//    } \
//    ConditionalPhrase operator ++() \
//    {return ConditionalPhrase(this, PhraseData::Add, 1);} \
//    ConditionalPhrase operator --() \
//    {return ConditionalPhrase(this, PhraseData::Minus, 1);} \
//    ConditionalPhrase operator ++(int) \
//    {return ConditionalPhrase(this, PhraseData::Add, 1);} \
//    ConditionalPhrase operator --(int) \
//    {return ConditionalPhrase(this, PhraseData::Minus, 1);} \
//};

//SPECIALIZATION_NUMERIC(qint8)
//SPECIALIZATION_NUMERIC(qint16)
//SPECIALIZATION_NUMERIC(qint32)
//SPECIALIZATION_NUMERIC(qint64)

//SPECIALIZATION_NUMERIC(quint8)
//SPECIALIZATION_NUMERIC(quint16)
//SPECIALIZATION_NUMERIC(quint32)
//SPECIALIZATION_NUMERIC(quint64)

//SPECIALIZATION_NUMERIC(qreal)

//Date and time
#define CONDITIONAL_VARIANT_METHOD(name, cond) \
    ConditionalPhrase name(int val) \
    { \
        return ConditionalPhrase(this, cond, val); \
    }

template<>
class FieldPhrase<bool> : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}

    AssignmentPhrase operator =(const bool &other) {
        return AssignmentPhrase(this, other);
    }

    FieldPhrase<bool> operator !()
    {
        FieldPhrase<bool> f(data->className, data->fieldName);
//        f.data = new PhraseData(data);
        f.data->isNot = !data->isNot;
        return f;
    }

    operator ConditionalPhrase()
    {
        return ConditionalPhrase(this, PhraseData::Equal, !data->isNot);
    }
};

//template<>
//class FieldPhrase<QDate> : public AbstractFieldPhrase
//{
//public:
//    FieldPhrase(const char *className, const char *s) :
//        AbstractFieldPhrase(className, s)
//    {}
//    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
//    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
//    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
//    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
//    AssignmentPhrase operator =(const QDate &other) {
//        return AssignmentPhrase(this, other);
//    }
//    ConditionalPhrase between(const QDate &min, const QDate &max)
//    {
//        return ConditionalPhrase(this, PhraseData::Between,
//            QVariantList() << min << max);
//    }
//    CONDITIONAL_VARIANT_METHOD(addYears, PhraseData::AddYears)
//    CONDITIONAL_VARIANT_METHOD(addMonths, PhraseData::AddMonths)
//    CONDITIONAL_VARIANT_METHOD(addDays, PhraseData::AddDays)
//};

//template<>
//class FieldPhrase<QTime> : public AbstractFieldPhrase
//{
//public:
//    FieldPhrase(const char *className, const char *s) :
//        AbstractFieldPhrase(className, s)
//    {}
//    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
//    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
//    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
//    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
//    AssignmentPhrase operator =(const QTime &other) {
//        return AssignmentPhrase(this, other);
//    }
//    ConditionalPhrase between(const QTime &min, const QTime &max)
//    {
//        return ConditionalPhrase(this, PhraseData::Between,
//            QVariantList() << min << max);
//    }

//    CONDITIONAL_VARIANT_METHOD(addHours, PhraseData::AddHours)
//    CONDITIONAL_VARIANT_METHOD(addMinutes, PhraseData::AddMinutes)
//    CONDITIONAL_VARIANT_METHOD(addSeconds, PhraseData::AddSeconds)
//};

//template<>
//class FieldPhrase<QDateTime> : public AbstractFieldPhrase
//{
//public:
//    FieldPhrase(const char *className, const char *s) :
//        AbstractFieldPhrase(className, s)
//    {}
//    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
//    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
//    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
//    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
//    AssignmentPhrase operator =(const QDateTime &other) {
//        return AssignmentPhrase(this, other);
//    }
//    ConditionalPhrase between(const QDateTime &min, const QDateTime &max)
//    {
//        return ConditionalPhrase(this, PhraseData::Between,
//            QVariantList() << min << max);
//    }
//    CONDITIONAL_VARIANT_METHOD(addYears, PhraseData::AddYears)
//    CONDITIONAL_VARIANT_METHOD(addMonths, PhraseData::AddMonths)
//    CONDITIONAL_VARIANT_METHOD(addDays, PhraseData::AddDays)

//    CONDITIONAL_VARIANT_METHOD(addHours, PhraseData::AddHours)
//    CONDITIONAL_VARIANT_METHOD(addMinutes, PhraseData::AddMinutes)
//    CONDITIONAL_VARIANT_METHOD(addSeconds, PhraseData::AddSeconds)
//};

NUT_END_NAMESPACE

#endif // FIELDPHRASE_H
