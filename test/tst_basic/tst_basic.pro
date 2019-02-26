QT       += testlib sql
QT       -= gui

TARGET = tst_nut
TEMPLATE = app

CONFIG   += warn_on c++11
INCLUDEPATH += $$PWD/../../src $$PWD/../common
include(../../nut.pri)
IMPORTPATH += $$OUT_PWD/../src/imports
SOURCES += \
    ../common/comment.cpp \
    ../common/post.cpp \
    ../common/user.cpp \
    ../common/weblogdatabase.cpp \
    ../common/score.cpp \
    tst_basic.cpp

HEADERS += \
    ../common/consts.h \
    ../common/comment.h \
    ../common/post.h \
    ../common/user.h \
    ../common/weblogdatabase.h \
    ../common/score.h \
    tst_basic.h
