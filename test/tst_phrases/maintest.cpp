#include <QtTest>
#include <QDate>

#include "maintest.h"
#include "phrase.h"

using namespace Nut;

MainTest::MainTest(QObject *parent) : QObject(parent)
{
}

void MainTest::initTestCase()
{

}

void MainTest::no1()
{
    FieldPhrase<int> id("main", "id");
    FieldPhrase<QString> name("main", "name");
    FieldPhrase<QString> last_name("main", "last_name");
    FieldPhrase<QDate> date("main", "date");
    auto w = (id == 4 && name == "hi");
}

QTEST_MAIN(MainTest)
