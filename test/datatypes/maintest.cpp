#include <QtTest>
#include <QDebug>
#include <QSqlError>
#include <QElapsedTimer>

#include "consts.h"

#include "maintest.h"
#include "query.h"
#include "tableset.h"
#include "tablemodel.h"
#include "databasemodel.h"

#include "sampletable.h"

#include "generators/sqlitegenerator.h"
#include "generators/sqlservergenerator.h"

#define PRINT(x) qDebug() << #x "=" << x;

#define REGISTER(x) qDebug() << #x << "type id:" << qRegisterMetaType<x*>()

MainTest::MainTest(QObject *parent) : QObject(parent)
{
}

void MainTest::initTestCase()
{
    //register all entities with Qt-MetaType mechanism
    REGISTER(SampleTable);
    REGISTER(DB);

    db.setDriver(DRIVER);
    db.setHostName(HOST);
    db.setDatabaseName("nut_tst_basic");
//    db.setUserName(USERNAME);
//    db.setPassword(PASSWORD);

    bool ok = db.open();
    QTEST_ASSERT(ok);
}

void MainTest::types()
{
    QList<QMetaType::Type> types;
    types
             << QMetaType::Bool
             << QMetaType::Int
             << QMetaType::UInt
             << QMetaType::Double
             << QMetaType::QChar
             << QMetaType::QString
             << QMetaType::QByteArray
             << QMetaType::Long
             << QMetaType::LongLong
             << QMetaType::Short
             << QMetaType::Char
             << QMetaType::ULong
             << QMetaType::ULongLong
             << QMetaType::UShort
             << QMetaType::SChar
             << QMetaType::UChar
             << QMetaType::Float
             << QMetaType::QDate
//             << QMetaType::QSize
             << QMetaType::QTime
//             << QMetaType::QPolygon
//             << QMetaType::QPolygonF
//             << QMetaType::QColor
//             << QMetaType::QSizeF
//             << QMetaType::QRectF
//             << QMetaType::QLine
//             << QMetaType::QStringList
//             << QMetaType::QLineF
//             << QMetaType::QRect
//             << QMetaType::QPoint
             << QMetaType::QUrl
             << QMetaType::QDateTime
//             << QMetaType::QPointF
//             << QMetaType::QRegion
//             << QMetaType::QBitArray
//             << QMetaType::QImage
//             << QMetaType::QPixmap
//             << QMetaType::QLocale
//             << QMetaType::QMatrix
//             << QMetaType::QMatrix4x4
//             << QMetaType::QVector2D
//             << QMetaType::QVector3D
//             << QMetaType::QVector4D
             << QMetaType::QJsonValue
             << QMetaType::QJsonObject
             << QMetaType::QJsonArray
             << QMetaType::QJsonDocument
             << QMetaType::QUuid
//             << QMetaType::QByteArrayList
                ;

    Nut::SqliteGenerator g;
    Nut::FieldModel m;
    foreach (QMetaType::Type t, types) {
        m.type = t;
        QString fn = g.fieldType(&m);
        Q_ASSERT(!fn.isEmpty());
    }
//    for (int i = 0; i < en.keyCount(); i++)
//        qDebug() << en.value(i);
}

void MainTest::cleanupTestCase()
{
    db.close();
    QFile::remove("nut_tst_basic");

    PRINT_FORM(db);
}

QTEST_MAIN(MainTest)
