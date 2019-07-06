#include <QtTest>
#include <QDebug>
#include <QSqlError>
#include <QElapsedTimer>

#include "consts.h"

#include "tst_datetime.h"
#include "query.h"
#include "tableset.h"
#include "tablemodel.h"
#include "databasemodel.h"

#include "sampletable.h"

DateTimeTest::DateTimeTest(QObject *parent) : QObject(parent)
{
    _baseDateTime = QDateTime::currentDateTime();
}

void DateTimeTest::initTestCase()
{
    //register all entities with Qt-MetaType mechanism
    REGISTER(SampleTable);
    REGISTER(DB);

    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName(DATABASE);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);

    QTEST_ASSERT(db.open());

    db.sampleTables()->query()->remove();
}

void DateTimeTest::date()
{
    auto s = Nut::create<SampleTable>();
    s->setD(_baseDateTime.addDays(10).date());
    db.sampleTables()->append(s);
    db.saveChanges();

    auto q = db.sampleTables()->query()
            ->where(SampleTable::dField().addDays(9) < QDate::currentDate().addDays(10));

    auto count = q->count();
    qDebug() << q->sqlCommand();
    QTEST_ASSERT(count);
}

void DateTimeTest::cleanupTestCase()
{
    db.sampleTables()->query()->remove();
    db.close();
}

QTEST_MAIN(DateTimeTest)
