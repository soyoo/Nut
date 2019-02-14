#include <QtTest>

#include "db1.h"
#include "db2.h"
#include "db3.h"

#include "table1.h"
#include "table2.h"
#include "table3.h"

#include "tst_upgrades.h"
#include "consts.h"

void Upgrades::initDb(Nut::Database &db)
{
    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName(DATABASE);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);
}

Upgrades::Upgrades()
{

}

Upgrades::~Upgrades()
{

}

void Upgrades::initTestCase()
{
    QFile::remove(DATABASE);

    REGISTER(DB1);
    REGISTER(DB2);
    REGISTER(DB3);

    REGISTER(Table1);
    REGISTER(Table2);
    REGISTER(Table3);
}

void Upgrades::version1()
{
    DB1 db;
    initDb(db);
    QTEST_ASSERT(db.open());
}

void Upgrades::version2()
{
    DB2 db;
    initDb(db);
    QTEST_ASSERT(db.open());
}

void Upgrades::version3()
{
    DB3 db;
    initDb(db);
    QTEST_ASSERT(db.open());
}


QTEST_APPLESS_MAIN(Upgrades)

