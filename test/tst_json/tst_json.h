#ifndef TST_TESTJSON_H
#define TST_TESTJSON_H

#include <QObject>

namespace Nut {
class Database;
}
class TestJson : public QObject
{
    Q_OBJECT

    void initDb(Nut::Database &db);

    int id;
public:
    TestJson();
    ~TestJson();

private slots:
    void initTestCase();

    void store();

};

#endif // TST_TESTJSON_H
