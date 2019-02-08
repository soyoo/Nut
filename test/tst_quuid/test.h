#ifndef TEST_H
#define TEST_H

#include <QUuid>

#include "table.h"

class Test : public Nut::Table
{
    Q_OBJECT

    NUT_PRIMARY_KEY(id)
    NUT_DECLARE_FIELD(QUuid, id, id, setId)

    NUT_NOT_NULL(username)
    NUT_LEN(username, 50)
    NUT_DECLARE_FIELD(QString, username, username, setUsername)

public:
    Q_INVOKABLE Test(QObject *parentTableSet = 0);
};

Q_DECLARE_METATYPE(Test*)

#endif // TEST_H
