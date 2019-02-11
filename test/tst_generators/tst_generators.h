#ifndef TST_GENERATORS_H
#define TST_GENERATORS_H

#include <QObject>

namespace Nut {
class SqlGeneratorBase;
}

class GeneratorsTest : public QObject
{
    Q_OBJECT

public:
    explicit GeneratorsTest(QObject *parent = nullptr);

    void types(Nut::SqlGeneratorBase *g);

private slots:
    void test_sqlite();
    void test_psql();
    void test_sqlserver();
    void test_mysql();

};

#endif // TST_GENERATORS_H
