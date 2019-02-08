#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include <QPoint>
#include <QPolygon>
#include "table.h"

#define FIELD_Q(type) NUT_DECLARE_FIELD(q##type, f##type, f##type, setF##type)

class SampleTable : public Nut::Table
{
    Q_OBJECT

    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(int, id, id, setId)

    NUT_DECLARE_FIELD(qint8, fint8, fint8, setFint8)
    NUT_DECLARE_FIELD(qint16, fint16, fint16, setFint16)
    NUT_DECLARE_FIELD(qint32, fint32, fint32, setFint32)
    NUT_DECLARE_FIELD(qint64, fint64, fint64, setFint64)

    NUT_DECLARE_FIELD(quint8, fuint8, fuint8, setFuint8)
    NUT_DECLARE_FIELD(quint16, fuint16, fuint16, setFuint16)
    NUT_DECLARE_FIELD(quint32, fuint32, fuint32, setFuint32)
    NUT_DECLARE_FIELD(quint64, fuint64, fuint64, setFuint64)

    NUT_DECLARE_FIELD(qreal, freal, freal, setFreal)
    NUT_DECLARE_FIELD(float, ffloat, ffloat, setFfloat)
//    NUT_DECLARE_FIELD(long double, fldouble, fldouble, setFldouble)
    NUT_DECLARE_FIELD(QString, string, string, setString)
    NUT_DECLARE_FIELD(QPoint, point, point, setPoint)
    NUT_DECLARE_FIELD(QPolygon, polygon, polygon, setPolygon)

public:
    Q_INVOKABLE SampleTable(QObject *parent = Q_NULLPTR);
};

#endif // SAMPLETABLE_H
