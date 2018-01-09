#include "user.h"

#include "comment.h"

User::User(QObject *tableSet) : Table(tableSet),
    m_comments(new TableSet<Comment>(this))
{

}

NUT_IMPLEMENT_CHILD_TABLE(User, Comment, comments)
