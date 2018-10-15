#include <QtTest>
#include <QJsonDocument>
#include <QSqlError>
#include <QDebug>
#include <QElapsedTimer>

#include "consts.h"

#include "maintest.h"
#include "query.h"
#include "tableset.h"
#include "tablemodel.h"

#include "test.h"

MainTest::MainTest(QObject *parent) : QObject(parent)
{
}

void MainTest::initTestCase()
{
    qDebug() << "Test type id:" << qRegisterMetaType<Test*>();
    qDebug() << "DB type id:" << qRegisterMetaType<TestDatabase*>();

    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName("nut_tst_quuid");
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);

    bool ok = db.open();

    db.tests()->query()->remove();

    QTEST_ASSERT(ok);
}

void MainTest::add()
{
    TIC();
    QUuid uuid = QUuid::createUuid();
    Test t;
    t.setId(uuid);
    t.setUsername("test username");
    db.tests()->append(&t);
    db.saveChanges();
    TOC();

    Test *t2 = db.tests()->query()
            ->where(Test::idField() == uuid)
            ->first();

    TOC();
    QTEST_ASSERT(t2->id() == uuid);
}

void MainTest::cleanupTestCase()
{
    qDeleteAll(Nut::TableModel::allModels());
//    Nut::DatabaseModel::deleteAllModels();
}

QTEST_MAIN(MainTest)
