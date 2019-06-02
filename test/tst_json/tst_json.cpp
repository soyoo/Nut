#include <QtTest>

#include "db.h"
#include "sampletable.h"
#include "query.h"

#include "tst_json.h"
#include "consts.h"

void TestJson::initDb(Nut::Database &db)
{
    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName(DATABASE);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);
}

TestJson::TestJson()
{

}

TestJson::~TestJson()
{

}

void TestJson::initTestCase()
{
    QFile::remove(DATABASE);
    REGISTER(DB);
    REGISTER(Table);
}

void TestJson::store()
{
    DB db;
    initDb(db);

    QTEST_ASSERT(db.open());
}

QTEST_APPLESS_MAIN(TestJson)

