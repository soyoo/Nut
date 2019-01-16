#ifndef MAINTEST_H
#define MAINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "testdatabase.h"
class Test;
class MainTest : public QObject
{
    Q_OBJECT
    TestDatabase db;

public:
    explicit MainTest(QObject *parent = 0);

signals:

private slots:
    void initTestCase();
    void add();

    void cleanupTestCase();
};

#endif // MAINTEST_H
