#ifndef MAINTEST_H
#define MAINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class SupportedDataTypesTest : public QObject
{
    Q_OBJECT
    QList<QMetaType::Type> types;

    struct Result
    {
        QMetaType::Type type;
        QString mssql;
        QString sqlite;
        QString pgsql;
        QString mysql;

        Result(QMetaType::Type type, QString mssql, QString sqlite,
        QString pgsql, QString mysql)
            : type(type), mssql(mssql), sqlite(sqlite), pgsql(pgsql), mysql(mysql)
        {}
    };
    QList<Result> result;

public:
    explicit SupportedDataTypesTest(QObject *parent = nullptr);

signals:

private slots:
    void initTestCase();

    void cleanupTestCase();
};

#endif // MAINTEST_H
