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

#define REGISTER(x) qDebug() << #x << "type id:" << qMetaTypeId<x*>()

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
    db.setDatabaseName(DATABASE);
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD);

    QFile::remove(DATABASE);
    bool ok = db.open();
    n8 = 8;
    n16 = 16;
    n32 = 32l;
    n64 = 64ll;
    nu8 = 8u;
    nu16 = 16u;
    nu32 = 32ul;
    nu64 = 64ull;
    r = 1.2;
    f = 2.3f;
    point = QPoint(1, 2);
    pointf  = QPointF(1.2, 3.4);
    polygon = QPolygon() << QPoint(1, 2) << QPoint(3, 4) << QPoint(5, 6);
    polygonf = QPolygonF() << QPointF(1.2, 2.3) << QPointF(3.4, 4.5) << QPointF(5.6, 6.7);

    url = QUrl("http://google.com/search?q=nut");

    time = QTime::currentTime();
    date = QDate::currentDate();
    dateTime = QDateTime::currentDateTime();

    uuid = QUuid::createUuid();
    jsonDoc = QJsonDocument::fromJson("{\"a\": 1}");
    jsonObj = jsonDoc.object();
    jsonArr.insert(0, QJsonValue(1));
    jsonArr.insert(1, QJsonValue("Hi"));
    jsonArr.insert(2, QJsonValue(true));

    jsonValue = QJsonValue(true);

    stringList.append("One");
    stringList.append("Two");
    stringList.append("Three");
    string = "this is \n sample ' unescapped \r\n text";

    qchar = QChar('z');

    color = Qt::red;

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

    Nut::FieldModel m;
    foreach (QMetaType::Type t, types) {
        m.type = t;
        QString fn = db.sqlGenertor()->fieldType(&m);
        Q_ASSERT(!fn.isEmpty());
    }
//    for (int i = 0; i < en.keyCount(); i++)
    //        qDebug() << en.value(i);
}

void MainTest::insert()
{
    SampleTable t;
    t.setInt8(n8);
    t.setInt16(n16);
    t.setInt32(n32);
    t.setInt64(n64);

    t.setUint8(nu8);
    t.setUint16(nu16);
    t.setUint32(nu32);
    t.setUint64(nu64);

    t.setReal(r);
    t.setFloat(f);

    t.setPoint(point);
    t.setPointf(pointf);

    t.setPolygon(polygon);
    t.setPolygonf(polygonf);

    t.setUrl(url);

    t.setTime(time);
    t.setDate(date);
    t.setDateTime(dateTime);
    t.setUuid(uuid);

    t.setJsonDoc(jsonDoc);
    t.setJsonObj(jsonObj);
    t.setJsonArray(jsonArr);
    t.setJsonValue(jsonValue);

    t.setString(string);
    t.setStringList(stringList);
    t.setQchar(qchar);
    t.setColor(color);

    db.sampleTables()->append(&t);
    db.saveChanges();
}

void MainTest::retrive()
{
    QList<SampleTable*> list = db.sampleTables()->query()->toList();
    QTEST_ASSERT(list.count() == 1);
    SampleTable *t = list.first();

    QTEST_ASSERT(t->f_int8() == n8);
    QTEST_ASSERT(t->f_int16() == n16);
    QTEST_ASSERT(t->f_int32() == n32);
    QTEST_ASSERT(t->f_int64() == n64);

    QTEST_ASSERT(t->f_uint8() == nu8);
    QTEST_ASSERT(t->f_uint16() == nu16);
    QTEST_ASSERT(t->f_uint32() == nu32);
    QTEST_ASSERT(t->f_uint64() == nu64);

    QTEST_ASSERT(qFuzzyCompare(t->f_real(), r));
    QTEST_ASSERT(qFuzzyCompare(t->f_float(), f));

    QTEST_ASSERT(t->f_point() == point);
    QTEST_ASSERT(t->f_pointf() == pointf);

    QTEST_ASSERT(t->f_polygon() == polygon);
    QTEST_ASSERT(t->f_polygonf() == polygonf);

    QTEST_ASSERT(t->f_url() == url);
    QTEST_ASSERT(t->f_uuid() == uuid);

    QTEST_ASSERT(t->f_time() == time);
    QTEST_ASSERT(t->f_date() == date);
    QTEST_ASSERT(t->f_dateTime() == dateTime);

    QTEST_ASSERT(t->f_jsonDoc() == jsonDoc);
    QTEST_ASSERT(t->f_jsonObj() == jsonObj);
    QTEST_ASSERT(t->f_jsonArray() == jsonArr);
    QTEST_ASSERT(t->f_jsonValue() == jsonValue);

    qDebug() << t->f_string() << string;
    QTEST_ASSERT(t->f_string() == string);
    QTEST_ASSERT(t->f_stringList() == stringList);
    QTEST_ASSERT(t->f_qchar() == qchar);
    QTEST_ASSERT(t->f_color() == color);
}

void MainTest::cleanupTestCase()
{
    db.sampleTables()->query()->remove();
    db.close();

    PRINT_FORM(db);
}

QTEST_MAIN(MainTest)
