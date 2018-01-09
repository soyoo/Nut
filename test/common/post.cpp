#include "post.h"
#include "comment.h"
#include "tableset.h"

Post::Post(QObject *parent) : Table(parent),
    m_id(0), m_title(""), m_comments(new TableSet<Comment>(this))
{

}

NUT_IMPLEMENT_CHILD_TABLE(Post, Comment, comments)
