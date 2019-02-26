QT       += testlib sql
QT       -= gui

TARGET = tst_upgrades
TEMPLATE = app

CONFIG   += warn_on c++11
INCLUDEPATH += $$PWD/../../src $$PWD/../common
include(../../nut.pri)
IMPORTPATH += $$OUT_PWD/../src/imports

SOURCES +=  tst_upgrades.cpp \
    db1.cpp \
    table1.cpp \
    db2.cpp \
    table2.cpp \
    db3.cpp \
    table3.cpp

HEADERS += \
    tst_upgrades.h \
    db1.h \
    table1.h \
    db2.h \
    table2.h \
    db3.h \
    table3.h
