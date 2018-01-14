#ifndef JOINTEST_H
#define JOINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "weblogdatabase.h"

class JoinTest : public QObject
{
    Q_OBJECT
    WeblogDatabase db;

public:
    explicit JoinTest(QObject *parent = 0);

signals:

private slots:
    void initTestCase();

    void join2();
    void join();
};

#endif // JOINTEST_H
