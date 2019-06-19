#include <QtTest>
#include <QDebug>
#include <QSqlError>
#include <QElapsedTimer>
#include <tablemodel.h>

#include "tst_supported_datatypes.h"

#include "generators/sqlitegenerator.h"
#include "generators/postgresqlgenerator.h"
#include "generators/mysqlgenerator.h"
#include "generators/sqlservergenerator.h"

SupportedDataTypesTest::SupportedDataTypesTest(QObject *parent) : QObject(parent)
{
    types
            << QMetaType::Bool
            << QMetaType::QBitArray
            << QMetaType::QByteArray
            << QMetaType::QDate
            << QMetaType::QDateTime
            << QMetaType::QTime
            << QMetaType::Double
            << QMetaType::Float

            << QMetaType::SChar
            << QMetaType::Char
            << QMetaType::UChar
            << QMetaType::Short
            << QMetaType::UShort
            << QMetaType::Int
            << QMetaType::UInt
            << QMetaType::Long
            << QMetaType::ULong
            << QMetaType::LongLong
            << QMetaType::ULongLong

            << QMetaType::QChar

            << QMetaType::QUrl
            << QMetaType::QJsonArray
            << QMetaType::QJsonValue
            << QMetaType::QJsonObject
            << QMetaType::QJsonDocument
            << QMetaType::QPoint
            << QMetaType::QPointF
            << QMetaType::QSize
            << QMetaType::QSizeF
            << QMetaType::QLine
            << QMetaType::QLineF
            << QMetaType::QRect
            << QMetaType::QRectF
            << QMetaType::QPolygon
            << QMetaType::QPolygonF
            << QMetaType::QStringList
            << QMetaType::QColor
            << QMetaType::QUuid

            << QMetaType::QString;
}

void SupportedDataTypesTest::initTestCase()
{
    Nut::SqliteGenerator sqlite;
    Nut::SqlServerGenerator mssql;
    Nut::PostgreSqlGenerator pgsql;
    Nut::MySqlGenerator mysql;

    Nut::FieldModel *field = new Nut::FieldModel;
    foreach (QMetaType::Type type, types) {
        field->type = type;
        result.append(Result(
                          type,
                          mssql.fieldType(field),
                          sqlite.fieldType(field),
                          pgsql.fieldType(field),
                          mysql.fieldType(field)
                          ));
    }
}

void SupportedDataTypesTest::cleanupTestCase()
{
    qDebug() << DOC_PATH;
    QString md("| Type  | Sqlite | MySql  | Postgresql| Ms Sql server |\n");
    md.append("|--------|--------|--------|--------|--------|\n");
    foreach (Result r, result)
        md.append(QString("| %1 | %2 | %3 | %4 | %5 |\n")
                  .arg(QMetaType::typeName(r.type), r.sqlite, r.mysql, r.pgsql, r.mssql));

    QFile file(DOC_PATH "/datatypes.md");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(md.toUtf8());
        file.close();
    }
}

QTEST_MAIN(SupportedDataTypesTest)
