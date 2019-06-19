#ifndef SQLMODEL_P_H
#define SQLMODEL_P_H

#include <QSharedPointer>
#include <QString>
#include "defines.h"

NUT_BEGIN_NAMESPACE

class SqlModel;
class Table;
class TableModel;
class SqlModelPrivate {
    SqlModel *q_ptr;
    Q_DECLARE_PUBLIC(SqlModel)
public:
    explicit SqlModelPrivate(SqlModel *parent);

    QString tableName;

    RowList<Table> rows;
    TableModel *model;
};

NUT_END_NAMESPACE

#endif // SQLMODEL_P_H
