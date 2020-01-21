#ifndef TABLEBASE_H
#define TABLEBASE_H

#include <table.h>

class TableBase : public Nut::Table
{
    Q_OBJECT
    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(int, id, getId, setId)

public:
    Q_INVOKABLE TableBase(QObject *parentTableSet = nullptr);
};

#endif // TABLEBASE_H
