#ifndef TABLECHILD_H
#define TABLECHILD_H

#include "tablebase.h"

class TableChild : public TableBase
{
    Q_OBJECT
    NUT_DECLARE_FIELD(QString, name, getName, setName)

public:
    Q_INVOKABLE TableChild(QObject *tableSet = nullptr);
};

#endif // TABLECHILD_H
