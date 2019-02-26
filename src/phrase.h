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

#include "phrases/conditionalphrase.h"
#include "phrases/abstractfieldphrase.h"
#include "phrases/fieldphrase.h"
#include "phrases/phraselist.h"
#include "phrases/assignmentphraselist.h"
#include "phrases/phrasedatalist.h"
#include "phrases/phrasedata.h"
#include "phrases/assignmentphrase.h"
#include "phrases/numericphrase.h"
#include "phrases/datephrase.h"

NUT_BEGIN_NAMESPACE

#define SPECIALIZATION_NUMERIC_MEMBER(type, op, cond) \
ConditionalPhrase operator op(const QVariant &other) \
{ \
    return ConditionalPhrase(this, cond, other); \
}

class AbstractFieldPhrase;
class AssignmentPhrase;
class PhraseList;

//AssignmentPhraseList operator &(const AssignmentPhrase &l, const AssignmentPhrase &r);
//AssignmentPhraseList operator &(const AssignmentPhrase &l, AssignmentPhrase &&r);
//AssignmentPhraseList operator &(AssignmentPhrase &&l, const AssignmentPhrase &r);
//AssignmentPhraseList operator &(AssignmentPhrase &&l, AssignmentPhrase &&r);


//ConditionalPhrase operator <(AbstractFieldPhrase &l, ConditionalPhrase &&other)
//{
//    return ConditionalPhrase(&l, PhraseData::Less, other);
//}

//template<typename T>
//class FieldPhrase : public AbstractFieldPhrase
//{
//public:
//    FieldPhrase(const char *className, const char *s) :
//        AbstractFieldPhrase(className, s)
//    {}

//    AssignmentPhrase operator =(const QVariant &other) {
//        return AssignmentPhrase(this, other);
//    }
//};

NUT_END_NAMESPACE

#endif // PHRASE_H
