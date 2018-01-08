#include "user.h"

#include "comment.h"

User::User(QObject *parent) : Nut::Table(parent)
{

}

NUT_IMPLEMENT_CHILD_TABLE(User, Comment, comments)
