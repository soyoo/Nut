#include "sampledatabase.h"

#include <QtTest>
#include <query.h>
#include "tablechild.h"
#include "consts.h"


class TableInheritance : public QObject
{
    Q_OBJECT

public:
    TableInheritance();
    ~TableInheritance();

private slots:
    void test_case1();

};

TableInheritance::TableInheritance()
{
    REGISTER(SampleDatabase);
    REGISTER(TableBase);
    REGISTER(TableChild);
}

TableInheritance::~TableInheritance()
{

}

void TableInheritance::test_case1()
{
    SampleDatabase db;
    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName(DATABASE);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);

    bool ok = db.open();
    QTEST_ASSERT(ok);
    auto list = db.childs()->query()
            ->where(TableChild::idField() == 1)
            ->toList();
}

QTEST_APPLESS_MAIN(TableInheritance)

#include "tst_tableinheritance.moc"
