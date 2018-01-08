#include "user.h"

#include "comment.h"

User::User(QObject *tableSet) : Table(tableSet),
    m_comments(new TableSet<Comment*>(this))
{

}
