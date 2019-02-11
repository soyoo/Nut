#include <QtTest>

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>

#include "tablemodel.h"
#include "generators/sqlitegenerator.h"
#include "generators/sqlservergenerator.h"
#include "generators/mysqlgenerator.h"
#include "generators/mysqlgenerator.h"

class tst_generators : public QObject
{
    Q_OBJECT

public:
    tst_generators();
    ~tst_generators();

    void types(Nut::SqlGeneratorBase *g);

private slots:
    void test_sqlite();
    void test_sqlserver();
    void test_psql();
    void test_mysql();

};

tst_generators::tst_generators()
{

}

tst_generators::~tst_generators()
{

}

void tst_generators::types(Nut::SqlGeneratorBase *g)
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
        QString fn = g->fieldType(&m);
        Q_ASSERT(!fn.isEmpty());
    }
//    for (int i = 0; i < en.keyCount(); i++)
    //        qDebug() << en.value(i);
}


QTEST_APPLESS_MAIN(tst_generators)

//#include "tst_tst_generators.moc"
