#include "post.h"
#include "comment.h"
#include "score.h"
#include "tableset.h"

Post::Post(QObject *parent) : Table(parent),
    m_id(0), m_title(""),
    m_comments(new TableSet<Comment>(this)),
    m_scores(new TableSet<Score>(this))
{

}

NUT_IMPLEMENT_CHILD_TABLE(Post, Comment, comments)
NUT_IMPLEMENT_CHILD_TABLE(Post, Score, scores)
