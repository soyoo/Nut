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

    db.open();

    Table *t = new Table;
    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(R"({"a": 4, "b":3.14})", &e);
    qDebug() << e.errorString();
    t->setDoc(doc);
    db.sampleTable()->append(t);
    db.saveChanges(true);

    int id = t->id();
    auto newObj = db.sampleTable()->query()
            ->where(Table::idField() == id)
            ->first();

    Q_ASSERT(newObj != nullptr);
    Q_ASSERT(newObj->doc() == t->doc());
}

QTEST_APPLESS_MAIN(TestJson)

