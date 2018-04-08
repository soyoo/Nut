#ifndef COMMENT_H
#define COMMENT_H

#include <QtCore/qglobal.h>
#include <QtCore/QDateTime>
#include <QtCore/QUuid>
#include "table.h"

#ifdef NUT_NAMESPACE
using namespace NUT_NAMESPACE;
#endif

class Post;
class User;
class Comment : public Table
{
    Q_OBJECT

    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(QUuid, id, id, setId)
    NUT_DECLARE_FIELD(QString, message, message, setMessage)
    NUT_DECLARE_FIELD(QDateTime, saveDate, saveDate, setSaveDate)
    NUT_DECLARE_FIELD(qreal, point, point, setPoint)

    NUT_FOREGION_KEY(Post, int, post, post, setPost)
    NUT_FOREGION_KEY(User, QUuid, author, author, setAuthor)

public:
    Q_INVOKABLE explicit Comment(QObject *parentTableSet = 0);
};

Q_DECLARE_METATYPE(Comment*)

#endif // COMMENT_H
