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

#ifndef FIELDPHRASE_H
#define FIELDPHRASE_H

#include "../defines.h"

#include "abstractfieldphrase.h"

NUT_BEGIN_NAMESPACE

template<typename T, typename enable = void>
class NUT_EXPORT FieldPhrase : public AbstractFieldPhrase
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
class NUT_EXPORT FieldPhrase<QString> : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}

    ConditionalPhrase like(const QString &term) {
        return ConditionalPhrase(this, PhraseData::Like, term);
    }

    ConditionalPhrase contains(const QString &term) {
        return ConditionalPhrase(this, PhraseData::Like, "%" + term + "%");
    }

    AssignmentPhrase operator =(const QVariant &v) {
        return AssignmentPhrase(this, v);
    }
};

//Date and time
#define CONDITIONAL_VARIANT_METHOD(name, cond) \
    ConditionalPhrase name(int val) \
    { \
        return ConditionalPhrase(this, cond, val); \
    }

template<>
class NUT_EXPORT FieldPhrase<bool> : public AbstractFieldPhrase
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

NUT_END_NAMESPACE

#endif // FIELDPHRASE_H
