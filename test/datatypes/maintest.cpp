#include <QtTest>
#include <QDebug>
#include <QSqlError>
#include <QElapsedTimer>

#include "consts.h"

#include "maintest.h"
#include "query.h"
#include "tableset.h"
#include "tablemodel.h"
#include "databasemodel.h"

#include "sampletable.h"

#define PRINT(x) qDebug() << #x "=" << x;
#define TIC()  QElapsedTimer timer; timer.start()
#define TOC()  qDebug() << QString("Elapsed time: %1ms for %2") \
    .arg(timer.elapsed() / 1000.) \
    .arg(__func__)

#define REGISTER(x) qDebug() << #x << "type id:" << qRegisterMetaType<x*>()

MainTest::MainTest(QObject *parent) : QObject(parent)
{
}

void MainTest::initTestCase()
{
    //register all entities with Qt-MetaType mechanism
    REGISTER(SampleTable);
    REGISTER(DB);

    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName("nut_tst_basic");
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);

    bool ok = db.open();
    QTEST_ASSERT(ok);
}

void MainTest::types()
{
//    QMetaEnum en = QMetaEnum::fromType<QMetaType::Type>();
//    for (int i = 0; i < en.keyCount(); i++)
//        qDebug() << en.value(i);
}

void MainTest::cleanupTestCase()
{
    db.close();
    QFile::remove("nut_tst_basic");

    PRINT_FORM(db);
}

QTEST_MAIN(MainTest)
