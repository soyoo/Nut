#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <QVariant>

class SerializableObject
{
public:
    SerializableObject();

    virtual void load(const QVariant &value) = 0;
    virtual QVariant save() = 0;
};

#endif // SERIALIZABLEOBJECT_H
