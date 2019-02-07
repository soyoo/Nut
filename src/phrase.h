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
#ifdef Q_COMPILER_INITIALIZER_LISTS
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

    PhraseData *left;
    PhraseData *right;

    QVariant operand;
    bool isNot;
    quint16 parents;

    PhraseData();
    PhraseData(const char *className, const char *fieldName);
    PhraseData(PhraseData *l, Condition o);
    PhraseData(PhraseData *l, Condition o, PhraseData *r);
    PhraseData(PhraseData *l, Condition o, QVariant r);
//    explicit PhraseData(const PhraseData &other);
//    explicit PhraseData(const PhraseData *other);

    PhraseData *operator =(PhraseData *other);
    PhraseData &operator =(PhraseData &other);

    QString toString() const;

    ~PhraseData();

    void cleanUp();
private:
    void cleanUp(PhraseData *d);
};

class PhraseDataList : public QList<PhraseData*>
{
public:
    PhraseDataList();
    PhraseDataList(const PhraseDataList &other);
    void append(PhraseData *d);
    void append(QList<PhraseData*> &dl);
    virtual ~PhraseDataList();
};

class AssignmentPhraseList
{
public:
    QList<PhraseData*> data;
    explicit AssignmentPhraseList();
    AssignmentPhraseList(const AssignmentPhrase &l);
    AssignmentPhraseList(AssignmentPhraseList *l, const AssignmentPhrase *r);
    AssignmentPhraseList(AssignmentPhrase *l, const AssignmentPhrase *r);
    AssignmentPhraseList(const AssignmentPhrase &r, const AssignmentPhrase &l);

    AssignmentPhraseList operator &(const AssignmentPhrase &ph);

    ~AssignmentPhraseList();

private:
    void incAllDataParents();
};

class AssignmentPhrase
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

//AssignmentPhraseList operator &(const AssignmentPhrase &l, const AssignmentPhrase &r);
//AssignmentPhraseList operator &(const AssignmentPhrase &l, AssignmentPhrase &&r);
//AssignmentPhraseList operator &(AssignmentPhrase &&l, const AssignmentPhrase &r);
//AssignmentPhraseList operator &(AssignmentPhrase &&l, AssignmentPhrase &&r);

class PhraseList{
public:
    bool isValid;
    PhraseDataList data;
    explicit PhraseList();
    PhraseList(const PhraseList &other);
    PhraseList(PhraseList &&other);
    PhraseList(const AbstractFieldPhrase &other);
    PhraseList(const AbstractFieldPhrase *left, const AbstractFieldPhrase &right);
    PhraseList(PhraseList *left, PhraseList *right);
    PhraseList(PhraseList *left, const AbstractFieldPhrase *right);
    virtual ~PhraseList();

    PhraseList &operator =(const PhraseList &other);
    PhraseList operator |(PhraseList &other);
    PhraseList operator |(const AbstractFieldPhrase &other);

private:
    void incAllDataParents();
};

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

class AbstractFieldPhrase
{
public:
    PhraseData *data;
    explicit AbstractFieldPhrase(PhraseData *d);
    AbstractFieldPhrase(const char *className, const char *fieldName);
    AbstractFieldPhrase(const AbstractFieldPhrase &other);
    AbstractFieldPhrase(AbstractFieldPhrase &&other);

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
#ifdef Q_COMPILER_INITIALIZER_LISTS
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
    //why?
    ConditionalPhrase operator !=(const QVariant &other);

    ConditionalPhrase operator ==(const AbstractFieldPhrase &other);
    ConditionalPhrase operator !=(const AbstractFieldPhrase &other);
    ConditionalPhrase operator <(const AbstractFieldPhrase &other);
    ConditionalPhrase operator >(const AbstractFieldPhrase &other);
    ConditionalPhrase operator <=(const AbstractFieldPhrase &other);
    ConditionalPhrase operator >=(const AbstractFieldPhrase &other);

    AbstractFieldPhrase operator !();
    AssignmentPhrase operator =(const QVariant &other);
    AssignmentPhrase operator =(const ConditionalPhrase &other);
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

    AssignmentPhrase operator =(const QVariant &v) {
        return AssignmentPhrase(this, v);
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
    AssignmentPhrase operator =(const ConditionalPhrase &other) { \
        return AssignmentPhrase(new PhraseData(data, PhraseData::Equal, other.data)); \
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
