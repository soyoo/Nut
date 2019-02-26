#ifndef TESTDATABASE_H
#define TESTDATABASE_H

#include "database.h"

class Test;
class TestDatabase : public Nut::Database
{
    Q_OBJECT

    NUT_DB_VERSION(1)

    NUT_DECLARE_TABLE(Test, tests)
public:
    TestDatabase(QObject *parent = nullptr);
};

#endif // TESTDATABASE_H
