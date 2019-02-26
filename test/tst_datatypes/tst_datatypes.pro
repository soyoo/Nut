QT       += testlib sql
QT       -= gui

TARGET = tst_datatypes
TEMPLATE = app

CONFIG   += warn_on c++11
INCLUDEPATH += $$PWD/../../src $$PWD/../common
include(../../nut.pri)
IMPORTPATH += $$OUT_PWD/../src/imports
SOURCES += \
    db.cpp \
    sampletable.cpp \
    tst_datatypes.cpp

HEADERS += \
    db.h \
    sampletable.h \
    tst_datatypes.h
