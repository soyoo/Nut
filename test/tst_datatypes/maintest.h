#ifndef MAINTEST_H
#define MAINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "db.h"
class MainTest : public QObject
{
    Q_OBJECT
    DB db;

//    void test_generator();
public:
    explicit MainTest(QObject *parent = nullptr);

signals:

private slots:
    void initTestCase();

    void types();
    void insert();
    void cleanupTestCase();
};

#endif // MAINTEST_H
