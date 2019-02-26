#ifndef PHRASEDATA_H
#define PHRASEDATA_H

#include "../defines.h"

NUT_BEGIN_NAMESPACE

class NUT_EXPORT PhraseData
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
        AddSeconds,

        DatePartYear,
        DatePartMonth,
        DatePartDay,
        DatePartHour,
        DatePartMinute,
        DatePartSecond,
        DatePartMilisecond
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

    ~PhraseData() = default;

    void cleanUp();
private:
    void cleanUp(PhraseData *d);
};

NUT_END_NAMESPACE

#endif // PHRASEDATA_H
