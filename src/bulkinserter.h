#ifndef BULKINSERTER_H
#define BULKINSERTER_H

#include <initializer_list>
#include <QDebug>
#include "defines.h"
#include "phrases/phraselist.h"
#include "phrases/fieldphrase.h"

NUT_BEGIN_NAMESPACE

class PhraseList;
class Database;
class BulkInserter
{
    Database *_database;
    QString _className;
    Nut::PhraseList _fields;
    QList<QVariantList> variants;
    size_t _fieldCount;

public:
    BulkInserter(Database *db, QString &className);
    void setFields(const PhraseList &ph);

    void insert(std::initializer_list<QVariant> vars);
    template<typename... Args>
    void insert(Args... args) {
        insert({args...});
    }
    int apply();
};

//#define HEAD(x, ...) x
//#define TAIL(x, ...) __VA_ARGS__
//#define ENCLOSE(...) ( __VA_ARGS__ )
//#define REM_ENCLOSE_(...) __VA_ARGS__
//#define REM_ENCLOSE(...) REM_ENCLOSE_ __VA_ARGS__

//#define IF_ENCLOSED_1(true, ...) true
//#define IF_ENCLOSED_0(true, ...) __VA_ARGS__
//#define IF_ENCLOSED(...) CAT(IF_ENCLOSED_, IF_ENCLOSED(__VA_ARGS__))
//// This function will optionally remove brackets around its arguments
//// if there are any. Otherwise it will return normally
//#define OPT_REM_ENCLOSE(...) \
//  IF_ENCLOSED (__VA_ARGS__) ( REM_ENCLOSE(__VA_ARGS__), __VA_ARGS__ )

//#define TEST_LAST EXISTS(1)
//#define IS_LIST_EMPTY(...) \
//  TRY_EXTRACT_EXISTS( \
//    DEFER(HEAD) (__VA_ARGS__ EXISTS(1))\
//  , 0)
//#define IS_LIST_NOT_EMPTY(...) NOT(IS_LIST_EMPTY(__VA_ARGS__))

//#define FOR_EACH(fVisitor, ...) \
//    fVisitor( OPT_REM_ENCLOSE(HEAD(__VA_ARGS__)) ) \
//    FOR_EACH(fVisitor, TAIL(__VA_ARGS__))

//#define NUT_FOREACH(F, ...) \
//    F(HEAD(__VA_ARGS__)); \
//    NUT_FOREACH(F, TAIL(__VA_ARGS__))
//template <typename... ETC>
//class Bulk
//{
//public:
//    void f(int){}
//    Bulk()
//    {
//        int a, b, c, d;
//        NUT_FOREACH(f, a, c, d)

//    }
//};

//template <typename T1, typename... ETC>
//class Bulk<T1, ETC...>
//{
//public:
//    Bulk(FieldPhrase<T1>)
//    {}
//};

//template <typename T1, typename T2, typename... ETC>
//class Bulk<T1, T2, ETC...>
//{
//public:
//    Bulk(FieldPhrase<T1>, FieldPhrase<T2>)
//    {}
//};

NUT_END_NAMESPACE

#endif // BULKINSERTER_H
