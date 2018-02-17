/**************************************************************************
**
** This file is part of Nut project.
** https://github.com/HamedMasafi/Nut
**
** Nut is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Nut is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Nut.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef PHRASE_H
#define PHRASE_H

#include <QSharedPointer>
#include <QString>
#include <QVariant>
#include <QtGlobal>
#if __cplusplus >= 201103L
#   include <initializer_list>
#endif

#include "defines.h"

NUT_BEGIN_NAMESPACE

#define SPECIALIZATION_NUMERIC_MEMBER(type, op, cond) \
ConditionalPhrase operator op(const QVariant &other) \
{ \
    return ConditionalPhrase(this, cond, other); \
}

class AbstractFieldPhrase;
class AssignmentPhrase;
class PhraseList;

class PhraseData
{
public:
    enum Condition {
        NotAssign = 0,
        Equal,
        Less,
        LessEqual,
        Null,
        In,
        Like,

        Not = 10,
        NotEqual,
        GreaterEqual,
        Greater,
        NotNull,
        NotIn,
        NotLike,

        And = 20,
        Or,

//        Append,
//        Set,

        Add,
        Minus,
        Multiple,
        Divide,
        Mod,

        Between,

        //date and time
        AddYears,
        AddMonths,
        AddDays,
        AddHours,
        AddMinutes,
        AddSeconds
//        // special types
//        Distance
    };

    enum Type { Field, WithVariant, WithOther, WithoutOperand };

    const char *className;
    const char *fieldName;

    Type type;
    Condition operatorCond;

    const PhraseData *left;
    const PhraseData *right;

    QVariant operand;
    bool isNot;

    PhraseData(const char *className, const char *fieldName);
    PhraseData(PhraseData *l, Condition o);
    PhraseData(PhraseData *l, Condition o, const PhraseData *r);
    PhraseData(PhraseData *l, Condition o, QVariant r);

    PhraseData(const PhraseData *other);

    QString toString() const;

    ~PhraseData();
};

class AssignmentPhraseList
{
public:
    QList<PhraseData*> data;
    AssignmentPhraseList(const AssignmentPhrase &l);
    AssignmentPhraseList(AssignmentPhraseList *l, const AssignmentPhrase *r);
    AssignmentPhraseList(AssignmentPhrase *l, const AssignmentPhrase *r);

    AssignmentPhraseList operator &(const AssignmentPhrase &ph);
};

class AssignmentPhrase
{
public:
    PhraseData *data;
    AssignmentPhrase(AbstractFieldPhrase *l, QVariant r);
    AssignmentPhrase(AbstractFieldPhrase *l, const AssignmentPhrase *r);
//    AssignmentPhrase(AssignmentPhrase *l, const AssignmentPhrase *r);

    AssignmentPhraseList operator &(const AssignmentPhrase &other);

};

class PhraseList{
public:
    bool isValid;
    QList<const PhraseData*> data;
    PhraseList();
    PhraseList(const AbstractFieldPhrase &other);
    PhraseList(AbstractFieldPhrase *left, const AbstractFieldPhrase *right);
    PhraseList(PhraseList *left, PhraseList *right);
    PhraseList(PhraseList *left, const AbstractFieldPhrase *right);
    virtual ~PhraseList();

    PhraseList operator |(PhraseList &other);
    PhraseList operator |(const AbstractFieldPhrase &other);
};

class ConditionalPhrase
{
public:
    PhraseData *data;
    QSharedPointer<PhraseData> leftDataPointer;
    QSharedPointer<PhraseData> rightDataPointer;
    ConditionalPhrase();
    ConditionalPhrase(const ConditionalPhrase &other);
#if __cplusplus >= 201103L
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

    ConditionalPhrase operator =(const ConditionalPhrase &other);
    ConditionalPhrase operator ==(const QVariant &other);
    ConditionalPhrase operator ==(const AbstractFieldPhrase &other);
    ConditionalPhrase operator &&(const ConditionalPhrase &other);
    ConditionalPhrase operator ||(const ConditionalPhrase &other);
    ConditionalPhrase operator !();

    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
};

class AbstractFieldPhrase
{
public:
    PhraseData *data;
    AbstractFieldPhrase(const char *className, const char *fieldName);
    AbstractFieldPhrase(const AbstractFieldPhrase &other);

    virtual ~AbstractFieldPhrase();

    PhraseList operator |(const AbstractFieldPhrase &other);

    template<typename T>
    ConditionalPhrase in(QList<T> list)
    {
        QVariantList vlist;
        foreach (T t, list)
            vlist.append(QVariant::fromValue(t));

        return ConditionalPhrase(this, PhraseData::In, vlist);
    }
#if __cplusplus >= 201103L
    ConditionalPhrase in(std::initializer_list<int> list) {
        QVariantList vlist;
        std::initializer_list<int>::iterator it;
        for (it = list.begin(); it != list.end(); ++it)
            vlist.append(*it);
        return ConditionalPhrase(this, PhraseData::In, vlist);
    }
#endif

    ConditionalPhrase isNull();

    ConditionalPhrase operator ==(const QVariant &other);
    ConditionalPhrase operator ==(const ConditionalPhrase &other);
    ConditionalPhrase operator !=(const QVariant &other);

    ConditionalPhrase operator ==(const AbstractFieldPhrase &other);
    ConditionalPhrase operator !=(const AbstractFieldPhrase &other);
    ConditionalPhrase operator <(const AbstractFieldPhrase &other);
    ConditionalPhrase operator >(const AbstractFieldPhrase &other);
    ConditionalPhrase operator <=(const AbstractFieldPhrase &other);
    ConditionalPhrase operator >=(const AbstractFieldPhrase &other);

    AbstractFieldPhrase operator !();
    AssignmentPhrase operator =(const QVariant &other);
    AssignmentPhrase operator <<(const QVariant &other);
};

template<typename T>
class FieldPhrase : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}

    AssignmentPhrase operator =(const QVariant &other) {
        return AssignmentPhrase(this, other);
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

    AssignmentPhrase operator =(const QVariant &other) {
        return AssignmentPhrase(this, other);
    }
};

#define SPECIALIZATION_NUMERIC(type) \
template<> \
class FieldPhrase<type> : public AbstractFieldPhrase \
{   \
    public: \
    FieldPhrase(const char *className, const char *s) : \
        AbstractFieldPhrase(className, s) \
    {} \
    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less) \
    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual) \
    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater) \
    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual) \
    SPECIALIZATION_NUMERIC_MEMBER(type, %,  PhraseData::Mod) \
    \
    SPECIALIZATION_NUMERIC_MEMBER(type, +,  PhraseData::Add) \
    SPECIALIZATION_NUMERIC_MEMBER(type, -,  PhraseData::Minus) \
    SPECIALIZATION_NUMERIC_MEMBER(type, *,  PhraseData::Multiple) \
    SPECIALIZATION_NUMERIC_MEMBER(type, /,  PhraseData::Divide) \
    AssignmentPhrase operator =(const QVariant &other) { \
        return AssignmentPhrase(this, other); \
    } \
    ConditionalPhrase between(const QVariant &min, const QVariant &max) \
    { \
        return ConditionalPhrase(this, PhraseData::Between, \
            QVariantList() << min << max); \
    } \
};

SPECIALIZATION_NUMERIC(qint8)
SPECIALIZATION_NUMERIC(qint16)
SPECIALIZATION_NUMERIC(qint32)
SPECIALIZATION_NUMERIC(qint64)

SPECIALIZATION_NUMERIC(quint8)
SPECIALIZATION_NUMERIC(quint16)
SPECIALIZATION_NUMERIC(quint32)
SPECIALIZATION_NUMERIC(quint64)

SPECIALIZATION_NUMERIC(qreal)

//Date and time
#define CONDITIONAL_VARIANT_METHOD(name, cond) \
    ConditionalPhrase name(int val) \
    { \
        return ConditionalPhrase(this, cond, val); \
    }

template<>
class FieldPhrase<QDate> : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}
    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
    AssignmentPhrase operator =(const QDate &other) {
        return AssignmentPhrase(this, other);
    }
    ConditionalPhrase between(const QDate &min, const QDate &max)
    {
        return ConditionalPhrase(this, PhraseData::Between,
            QVariantList() << min << max);
    }
    CONDITIONAL_VARIANT_METHOD(addYears, PhraseData::AddYears)
    CONDITIONAL_VARIANT_METHOD(addMonths, PhraseData::AddMonths)
    CONDITIONAL_VARIANT_METHOD(addDays, PhraseData::AddDays)
};

template<>
class FieldPhrase<QTime> : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}
    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
    AssignmentPhrase operator =(const QTime &other) {
        return AssignmentPhrase(this, other);
    }
    ConditionalPhrase between(const QTime &min, const QTime &max)
    {
        return ConditionalPhrase(this, PhraseData::Between,
            QVariantList() << min << max);
    }

    CONDITIONAL_VARIANT_METHOD(addHours, PhraseData::AddHours)
    CONDITIONAL_VARIANT_METHOD(addMinutes, PhraseData::AddMinutes)
    CONDITIONAL_VARIANT_METHOD(addSeconds, PhraseData::AddSeconds)
};

template<>
class FieldPhrase<QDateTime> : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}
    SPECIALIZATION_NUMERIC_MEMBER(type, <,  PhraseData::Less)
    SPECIALIZATION_NUMERIC_MEMBER(type, <=, PhraseData::LessEqual)
    SPECIALIZATION_NUMERIC_MEMBER(type, >,  PhraseData::Greater)
    SPECIALIZATION_NUMERIC_MEMBER(type, >=, PhraseData::GreaterEqual)
    AssignmentPhrase operator =(const QDateTime &other) {
        return AssignmentPhrase(this, other);
    }
    ConditionalPhrase between(const QDateTime &min, const QDateTime &max)
    {
        return ConditionalPhrase(this, PhraseData::Between,
            QVariantList() << min << max);
    }
    CONDITIONAL_VARIANT_METHOD(addYears, PhraseData::AddYears)
    CONDITIONAL_VARIANT_METHOD(addMonths, PhraseData::AddMonths)
    CONDITIONAL_VARIANT_METHOD(addDays, PhraseData::AddDays)

    CONDITIONAL_VARIANT_METHOD(addHours, PhraseData::AddHours)
    CONDITIONAL_VARIANT_METHOD(addMinutes, PhraseData::AddMinutes)
    CONDITIONAL_VARIANT_METHOD(addSeconds, PhraseData::AddSeconds)
};

NUT_END_NAMESPACE

#endif // PHRASE_H
