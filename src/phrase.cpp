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

#include "phrase.h"

#include <QDebug>

NUT_BEGIN_NAMESPACE

#define LOG(s) qDebug() << __func__ << s;

PhraseData::PhraseData(const char *className, const char *fieldName) :
    className(className), fieldName(fieldName),
    type(Field), operatorCond(NotAssign),
    left(0), right(0), operand(QVariant::Invalid), isNot(false)
{ }

PhraseData::PhraseData(PhraseData *l, PhraseData::Condition o)
    : className(0), fieldName(0),
      type(WithoutOperand), operatorCond(o), left(l), right(0), isNot(false)
{ }

PhraseData::PhraseData(PhraseData *l, PhraseData::Condition o,
                       const PhraseData *r)
    : className(0), fieldName(0),
      type(WithOther), operatorCond(o), left(l), right(r), isNot(false)
{ }

PhraseData::PhraseData(PhraseData *l, PhraseData::Condition o, QVariant r)
    : className(0), fieldName(0),
      type(WithVariant), operatorCond(o), left(l), operand(r), isNot(false)
{ }

PhraseData::PhraseData(const PhraseData *other)
{
    left = other->left;
    right = other->right;
    operand = other->operand;
    operatorCond = other->operatorCond;
    className = other->className;
    fieldName = other->fieldName;
    type = other->type;
}

QString PhraseData::toString() const
{
    return QString("[%1].%2").arg(className).arg(fieldName);
}

PhraseData::~PhraseData()
{
//    if (type == WithOther) {
//        delete left;
//        delete right;
//    }
//    if (type == WithVariant) {
//        if (left)
//            delete left;
//    }
    LOG("");
}

AbstractFieldPhrase::AbstractFieldPhrase(const char *className, const char *fieldName)
    :data(new PhraseData(className, fieldName))
{
    qDebug() <<"AbstractFieldPhrase created"<<className<<fieldName;
}

AbstractFieldPhrase::AbstractFieldPhrase(const AbstractFieldPhrase &other)
{
    qDebug() <<"4444444444444444";
    data = new PhraseData(other.data);
}

AbstractFieldPhrase::~AbstractFieldPhrase()
{
    if (data) {
        LOG(data->toString());
    } else {
        LOG("");
    }

    if (data) {
        delete data;
        data = 0;
    }
}

PhraseList AbstractFieldPhrase::operator |(const AbstractFieldPhrase &other) {
    return PhraseList(this, &other);
}

ConditionalPhrase AbstractFieldPhrase::isNull()
{
    return ConditionalPhrase(this, PhraseData::Null);
}


ConditionalPhrase AbstractFieldPhrase::operator ==(const ConditionalPhrase &other)
{
    return ConditionalPhrase(this, PhraseData::Equal, const_cast<ConditionalPhrase&>(other));
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
    //TODO: classname and s
    AbstractFieldPhrase f(data->className, data->fieldName);
    f.data = new PhraseData(data);
    f.data->isNot = !data->isNot;
    return f;
}

AssignmentPhrase AbstractFieldPhrase::operator =(const QVariant &other)
{
    return AssignmentPhrase(this, other);
}

AssignmentPhrase AbstractFieldPhrase::operator <<(const QVariant &other)
{
    return AssignmentPhrase(this, other);
}

PhraseList::PhraseList() : isValid(false)
{

}

PhraseList::PhraseList(const AbstractFieldPhrase &other) : isValid(true)
{
    data.append(other.data);
}

PhraseList::PhraseList(AbstractFieldPhrase *left, const AbstractFieldPhrase *right)
    : isValid(true)
{
    data.append(left->data);
    data.append(right->data);
}

PhraseList::PhraseList(PhraseList *left, PhraseList *right) : isValid(true)
{
    data = left->data;
    data.append(right->data);
}

PhraseList::PhraseList(PhraseList *left, const AbstractFieldPhrase *right)
    : isValid(true)
{
    data = left->data;
    data.append(right->data);
}

PhraseList::~PhraseList()
{
    data.clear();
}

PhraseList PhraseList::operator |(const AbstractFieldPhrase &other) {
    return PhraseList(this, &other);
}

PhraseList PhraseList::operator |(PhraseList &other) {
    return PhraseList(this, &other);
}

AssignmentPhrase::AssignmentPhrase(AbstractFieldPhrase *l, QVariant r)
{
    data = new PhraseData(l->data, PhraseData::Equal, r);
//    l->data = 0;
}

AssignmentPhrase::AssignmentPhrase(AbstractFieldPhrase *l, const AssignmentPhrase *r)
{
    data = new PhraseData(l->data, PhraseData::Equal, r->data);
    //    l->data = 0;
}

//AssignmentPhrase::AssignmentPhrase(AssignmentPhrase *l, const AssignmentPhrase *r)
//{
////    data = new PhraseData(l->data, PhraseData::Append, r->data);
//    qFatal("SS");
//}

AssignmentPhraseList AssignmentPhrase::operator &(const AssignmentPhrase &other)
{
    return AssignmentPhraseList(this, &other);
}

AssignmentPhraseList::AssignmentPhraseList(const AssignmentPhrase &l)
{
    data.append(l.data);
}

AssignmentPhraseList::AssignmentPhraseList(AssignmentPhraseList *l, const AssignmentPhrase *r)
{
    data.append(l->data);
    data.append(r->data);
}

AssignmentPhraseList::AssignmentPhraseList(AssignmentPhrase *l, const AssignmentPhrase *r)
{
    data.append(l->data);
    data.append(r->data);
}

AssignmentPhraseList AssignmentPhraseList::operator &(const AssignmentPhrase &ph)
{
    return AssignmentPhraseList(this, &ph);
}

ConditionalPhrase::ConditionalPhrase()
{
    this->data = 0;
}

ConditionalPhrase::ConditionalPhrase(const ConditionalPhrase &other)
{
    qDebug() << "************* ctor called:";
    this->data = new PhraseData(other.data);
}

ConditionalPhrase::ConditionalPhrase(const ConditionalPhrase &&other)
{
    qDebug() << "************* ctor called:";
    this->data = new PhraseData(other.data);
}

ConditionalPhrase::ConditionalPhrase(const PhraseData *data)
{
    this->data = new PhraseData(data);
}

ConditionalPhrase::ConditionalPhrase(AbstractFieldPhrase *l,
                                     PhraseData::Condition cond)
{
    data = new PhraseData(l->data, cond);
}

ConditionalPhrase::ConditionalPhrase(AbstractFieldPhrase *l,
                                     PhraseData::Condition cond,
                                     const QVariant &v)
{
    data = new PhraseData(l->data, cond, v);
}

ConditionalPhrase::ConditionalPhrase(AbstractFieldPhrase *l,
                                     PhraseData::Condition cond,
                                     const AbstractFieldPhrase &other)
{
    data = new PhraseData(l->data, cond, other.data);
}

ConditionalPhrase::ConditionalPhrase(AbstractFieldPhrase *l,
                                     PhraseData::Condition cond,
                                     ConditionalPhrase &r)
{
    data = new PhraseData(l->data, cond, r.data);
    r.data = 0;
}

ConditionalPhrase::ConditionalPhrase(ConditionalPhrase *l,
                                     PhraseData::Condition cond,
                                     const AbstractFieldPhrase &r)
{
    data = new PhraseData(l->data, cond, r.data);
    l->data = 0;
}

ConditionalPhrase::ConditionalPhrase(ConditionalPhrase *l,
                                     PhraseData::Condition cond,
                                     const QVariant &r)
{
    data = new PhraseData(l->data, cond, r);
    l->data = 0;
}

ConditionalPhrase::ConditionalPhrase(ConditionalPhrase *l,
                                     PhraseData::Condition cond,
                                     ConditionalPhrase &r)
{
    data = new PhraseData(l->data, cond, r.data);
    l->data = 0;
    r.data = 0;
}

ConditionalPhrase::~ConditionalPhrase()
{
    LOG("");
    if (data)
        delete data;
}

ConditionalPhrase ConditionalPhrase::operator =(const ConditionalPhrase &other)
{
    return ConditionalPhrase(other.data);
    const_cast<ConditionalPhrase&>(other).data = 0;
}

ConditionalPhrase ConditionalPhrase::operator ==(const QVariant &other)
{
    return ConditionalPhrase(this, PhraseData::Equal, other);
}

ConditionalPhrase ConditionalPhrase::operator ==(const AbstractFieldPhrase &other)
{
    return ConditionalPhrase(this, PhraseData::Equal, other);
}

ConditionalPhrase ConditionalPhrase::operator &&(const ConditionalPhrase &other)
{
    return ConditionalPhrase(this, PhraseData::And,
                             const_cast<ConditionalPhrase&>(other));
}

ConditionalPhrase ConditionalPhrase::operator ||(const ConditionalPhrase &other)
{
    return ConditionalPhrase(this, PhraseData::Or,
                             const_cast<ConditionalPhrase&>(other));
}

ConditionalPhrase ConditionalPhrase::operator !()
{
    ConditionalPhrase f(data);
    f.data->isNot = !data->isNot;
    return f;
}

NUT_END_NAMESPACE
