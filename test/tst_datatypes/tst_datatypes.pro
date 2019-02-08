QT       += qml quick testlib sql
QT       -= gui

TARGET = tst_datatypes
TEMPLATE = app

CONFIG   += warn_on qmltestcase c++11
INCLUDEPATH += $$PWD/../../src $$PWD/../common
include(../../nut.pri)
IMPORTPATH += $$OUT_PWD/../src/imports
SOURCES += \
    maintest.cpp \
    db.cpp \
    sampletable.cpp

HEADERS += \
    maintest.h \
    db.h \
    sampletable.h
