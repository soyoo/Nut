#include "user.h"

User::User(QObject *tableSet) : Table(tableSet),
    m_comments(new TableSet<Comment*>(this))
{

}
