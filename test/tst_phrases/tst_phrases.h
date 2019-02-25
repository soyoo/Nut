#ifndef MAINTEST_H
#define MAINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Post;
class User;
class MainTest : public QObject
{
    Q_OBJECT

public:
    explicit MainTest(QObject *parent = nullptr);

signals:

private slots:
    void initTestCase();
    void no1();

    void numeric();
    void string();
    void boolean();
    void datetime();
    void extra();
};

#endif // MAINTEST_H
