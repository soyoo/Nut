#ifndef MAINTEST_H
#define MAINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "weblogdatabase.h"
class Post;
class BenchmarkTest : public QObject
{
    Q_OBJECT
    WeblogDatabase db;
    int postId;
    Post *post;
    Query<Post> *q;
public:
    explicit BenchmarkTest(QObject *parent = nullptr);

signals:

private slots:
    void initTestCase();

    void insert1kPost();
};

#endif // MAINTEST_H
