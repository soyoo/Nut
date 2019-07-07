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

#ifndef DATEPHRASE_H
#define DATEPHRASE_H

#include "fieldphrase.h"
#include <QDateTime>
#include <type_traits>

NUT_BEGIN_NAMESPACE


template<typename>
struct __is_date_helper
        : public std::false_type { };

template<>
struct __is_date_helper<QTime>
        : public std::true_type { };

template<>
struct __is_date_helper<QDate>
        : public std::true_type { };

template<>
struct __is_date_helper<QDateTime>
        : public std::true_type { };

template<typename _Tp>
struct is_date
        : public __is_date_helper<typename std::remove_cv<_Tp>::type>::type
{ };


template <class T, class P>
inline bool is_valid_template() {return false;}

template <>
inline bool is_valid_template<QDateTime, QTime>() {return true;}

template <>
inline bool is_valid_template<QDateTime, QDate>() {return true;}

template <>
inline bool is_valid_template<QDate, QDate>() {return true;}

template <>
inline bool is_valid_template<QTime, QTime>() {return true;}

template <typename T>
class NUT_EXPORT FieldPhrase<T, typename std::enable_if<is_date<T>::value>::type>
        : public AbstractFieldPhrase
{
public:
    FieldPhrase(const char *className, const char *s) :
        AbstractFieldPhrase(className, s)
    {}

    AssignmentPhrase operator =(const T &other) {
        return AssignmentPhrase(this, other);
    }

    ConditionalPhrase operator <(const QVariant &other) {
        return ConditionalPhrase(this, PhraseData::Less, other);
    }
    ConditionalPhrase operator <=(const QVariant &other) {
        return ConditionalPhrase(this, PhraseData::LessEqual, other);
    }
    ConditionalPhrase operator >(const QVariant &other) {
        return ConditionalPhrase(this, PhraseData::Greater, other);
    }
    ConditionalPhrase operator >=(const QVariant &other) {
        return ConditionalPhrase(this, PhraseData::GreaterEqual, other);
    }

    ConditionalPhrase between(const QVariant &min, const QVariant &max)
    {
        return ConditionalPhrase(this, PhraseData::Between,
                                 QVariantList() << min << max);
    }

//    template<class P = T,
//             class std::enable_if<std::is_same<P, QDateTime>::value, int>::type = 0>
    ConditionalPhrase addYears(int val) {
        if (!is_valid_template<T, QDate>())
            return ConditionalPhrase();
        if (std::is_same<T, QDateTime>::value)
            return ConditionalPhrase(this, PhraseData::AddYearsDateTime, val);

        return ConditionalPhrase(this, PhraseData::AddYears, val);
    }
    ConditionalPhrase addMonths(int val) {
        if (!is_valid_template<T, QDate>())
            return ConditionalPhrase();
        if (std::is_same<T, QDateTime>::value)
            return ConditionalPhrase(this, PhraseData::AddMonthsDateTime, val);
        return ConditionalPhrase(this, PhraseData::AddMonths, val);
    }
    ConditionalPhrase addDays(int val) {
        if (!is_valid_template<T, QDate>())
            return ConditionalPhrase();
        if (std::is_same<T, QDateTime>::value)
            return ConditionalPhrase(this, PhraseData::AddDaysDateTime, val);
        return ConditionalPhrase(this, PhraseData::AddDays, val);
    }

    ConditionalPhrase addHours(int val) {
        if (!is_valid_template<T, QTime>())
            return ConditionalPhrase();
        if (std::is_same<T, QDateTime>::value)
            return ConditionalPhrase(this, PhraseData::AddHoursDateTime, val);
        return ConditionalPhrase(this, PhraseData::AddHours, val);
    }
    ConditionalPhrase addMinutes(int val) {
        if (!is_valid_template<T, QTime>())
            return ConditionalPhrase();
        if (std::is_same<T, QDateTime>::value)
            return ConditionalPhrase(this, PhraseData::AddMinutesDateTime, val);
        return ConditionalPhrase(this, PhraseData::AddMinutes, val);
    }
    ConditionalPhrase addSeconds(int val) {
        if (!is_valid_template<T, QTime>())
            return ConditionalPhrase();
        if (std::is_same<T, QDateTime>::value)
            return ConditionalPhrase(this, PhraseData::AddSecondsDateTime, val);
        return ConditionalPhrase(this, PhraseData::AddSeconds, val);
    }

    ConditionalPhrase year() {
        if (!is_valid_template<T, QDate>())
            return ConditionalPhrase();
        return ConditionalPhrase(this, PhraseData::DatePartYear);
    }
    ConditionalPhrase month() {
        if (!is_valid_template<T, QDate>())
            return ConditionalPhrase();
        return ConditionalPhrase(this, PhraseData::DatePartMonth);
    }
    ConditionalPhrase day() {
        if (!is_valid_template<T, QDate>())
            return ConditionalPhrase();
        return ConditionalPhrase(this, PhraseData::DatePartDay);
    }
    ConditionalPhrase hour() {
        if (!is_valid_template<T, QTime>())
            return ConditionalPhrase();
        return ConditionalPhrase(this, PhraseData::DatePartHour);
    }
    ConditionalPhrase minute() {
        if (!is_valid_template<T, QTime>())
            return ConditionalPhrase();
        return ConditionalPhrase(this, PhraseData::DatePartMinute);
    }
    ConditionalPhrase second() {
        if (!is_valid_template<T, QTime>())
            return ConditionalPhrase();
        return ConditionalPhrase(this, PhraseData::DatePartSecond);
    }
    ConditionalPhrase msec() {
        if (!is_valid_template<T, QTime>())
            return ConditionalPhrase();
        return ConditionalPhrase(this, PhraseData::DatePartMilisecond);
    }
};

NUT_END_NAMESPACE

#endif // DATEPHRASE_H
