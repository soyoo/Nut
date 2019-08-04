#include <QtTest>
#include <QDate>

#include "tst_phrases.h"
#include "phrase.h"

using namespace Nut;

PhrasesTest::PhrasesTest(QObject *parent) : QObject(parent)
{
}

void PhrasesTest::initTestCase()
{

}

void PhrasesTest::no1()
{
    FieldPhrase<int> id("main", "id");
    FieldPhrase<QString> name("main", "name");
    FieldPhrase<QString> last_name("main", "last_name");
    FieldPhrase<QDate> date("main", "date");
    auto w = (id == 4 && name == "hi");
}

void PhrasesTest::numeric()
{
    FieldPhrase<int> n("main", "int");
    FieldPhrase<float> f("main", "float");

    auto p1 = n == 1;
    auto p2 = n <= 1;
    auto p3 = n >= 1;
    auto p4 = n < 1;
    auto p5 = n > 1;
    auto p6 = n != 1;
    auto p7 = n = n + 1;
    auto p8 = n < n + 1;
    auto p9 = n <= n + 1;
    auto p10 = n > n + 1;
    auto p11 = n >= n + 1;
    auto p12 = n + 1 > n - 2;
    auto p13 = ++n;
    auto p14 = n++;
    auto p15 = n.between(1, 2);
    auto p16 = n + 1 < n + 2;

    auto p21 = p1 && p2;
    auto p22 = p3 == p4;
    auto p23 = f == n + 1;

    auto p24 = n = 4;
    auto p26 = (n = 4) & (n = 5);
    auto p27 = n | f;
}

void PhrasesTest::string()
{
    FieldPhrase<QString> str("main", "string");

    auto p1 = str == "salam";
    auto p2 = str.like("%hi%");
    auto p3 = str.isNull();
    auto p4 = str.in(QStringList() << "one" << "two" << "three");
    auto p5 = str != "hi" && str.like("%s");
}

void PhrasesTest::boolean()
{
    FieldPhrase<bool> b("main", "bool");

    auto p1 = b;
    auto p2 = !b;
    auto p3 = b == false;

    QTEST_ASSERT(p1.data);
    QTEST_ASSERT(p2.data);
    QTEST_ASSERT(p3.data);
}

void PhrasesTest::datetime()
{
    FieldPhrase<QTime> time("main", "time");
    FieldPhrase<QDate> date("main", "date");
    FieldPhrase<QDateTime> datetime("main", "datetime");

    auto p1 = time <= QTime::currentTime();
    auto p2 = time.addHours(2) < QTime::currentTime();
    auto p3 = date == QDate::currentDate();
    auto p4 = date.addDays(1) == QDate::currentDate();
    auto p5 = datetime > QDateTime::currentDateTime();
    auto p6 = datetime.addMonths(1) >= QDateTime::currentDateTime();
    auto p7 = time.between(QTime::currentTime().addSecs(-100), QTime::currentTime());
    auto p8 = time.hour() == 3;
    auto p9 = time = QTime::currentTime();

//    auto pi1 = time.addYears(1);
//    auto pi2 = date.addMinutes(3);

//    QTEST_ASSERT(!pi1.data);
//    QTEST_ASSERT(!pi2.data);
}

void PhrasesTest::extra()
{
    FieldPhrase<QUrl> url("main", "url");

    auto p1 = url == QUrl();
    auto p2 = url == "http://google.com";
}

void PhrasesTest::mix()
{
    FieldPhrase<int> id("", "");
    FieldPhrase<QString> name("", "");
    FieldPhrase<QString> lastName("", "");
    FieldPhrase<QDate> birthDate("", "");

    select(id);
    select(id | name | lastName);
    update((name = "john") & (lastName = "snow"));
    insert(id = 0);
    insert((id = 4) & (name = "john"));
    order_by(id);
    order_by(id | !name);
}

void PhrasesTest::select(const PhraseList &ph)
{
    QTEST_ASSERT(ph.data.count());
}

void PhrasesTest::where(const ConditionalPhrase &ph)
{
    QTEST_ASSERT(ph.data);
}

void PhrasesTest::update(const AssignmentPhraseList &p)
{
    QTEST_ASSERT(p.data.count());
}

void PhrasesTest::insert(const AssignmentPhraseList &p)
{
    QTEST_ASSERT(p.data.count());
}

void PhrasesTest::order_by(const PhraseList &ph)
{
    QTEST_ASSERT(ph.data.count());
}

QTEST_MAIN(PhrasesTest)
