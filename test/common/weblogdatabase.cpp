#include <QDebug>

#include "user.h"
#include "post.h"
#include "comment.h"
#include "user.h"
#include "score.h"
#include "weblogdatabase.h"

WeblogDatabase::WeblogDatabase() : Database(),
    m_postTable(new TableSet<Post>(this)),
    m_commentTable(new TableSet<Comment>(this)),
    m_userTable(new TableSet<User>(this)),
    m_scoreTable(new TableSet<Score>(this))
{
}
