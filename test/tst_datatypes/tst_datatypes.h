#ifndef MAINTEST_H
#define MAINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include <QColor>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPolygonF>
#include <QUrl>
#include <QUuid>

#include "db.h"
class DataTypesTest : public QObject
{
    Q_OBJECT
    DB db;

    qint8 n8;
    qint16 n16;
    qint32 n32;
    qint64 n64;
    quint8 nu8;
    quint16 nu16;
    quint32 nu32;
    quint64 nu64;
    qreal r;
    float f;
    QPoint point;
    QPointF pointf;
    QPolygon polygon;
    QPolygonF polygonf;
    QUrl url;

    QTime time;
    QDate date;
    QDateTime dateTime;

    QUuid uuid;
    QJsonDocument jsonDoc;
    QJsonObject jsonObj;
    QJsonArray jsonArr;
    QJsonValue jsonValue;

    QString string;
    QStringList stringList;

    QChar qchar;
    QColor color;

public:
    explicit DataTypesTest(QObject *parent = nullptr);

signals:

private slots:
    void initTestCase();

    void insert();
    void retrive();
    void cleanupTestCase();
};

#endif // MAINTEST_H
