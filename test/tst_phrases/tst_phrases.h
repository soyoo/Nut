#ifndef MAINTEST_H
#define MAINTEST_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Post;
class User;

namespace Nut {
class PhraseList;
class AssignmentPhraseList;
class ConditionalPhrase;
}
class PhrasesTest : public QObject
{
    Q_OBJECT

public:
    explicit PhrasesTest(QObject *parent = nullptr);

signals:

private slots:
    void initTestCase();
    void no1();

    void numeric();
    void string();
    void boolean();
    void datetime();
    void extra();
    void mix();

private:
    void select(const Nut::PhraseList &ph);
    void where(const Nut::ConditionalPhrase &ph);
    void update(const Nut::AssignmentPhraseList &p);
    void insert(const Nut::AssignmentPhraseList &p);
    void order_by(const Nut::PhraseList &ph);
};

#endif // MAINTEST_H
