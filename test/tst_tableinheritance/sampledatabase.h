#ifndef DATABASE_H
#define DATABASE_H

#include <database.h>

class TableChild;
class SampleDatabase : public Nut::Database
{
    Q_OBJECT

    NUT_DB_VERSION(1)
    NUT_DECLARE_TABLE(TableChild, childs)

public:
    SampleDatabase();
};

#endif // DATABASE_H
