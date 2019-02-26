QT       += testlib sql
QT       -= gui

TARGET = tst_phrases
TEMPLATE = app

CONFIG   += warn_on c++11
INCLUDEPATH += $$PWD/../../src $$PWD/../common
include(../../nut.pri)
IMPORTPATH += $$OUT_PWD/../src/imports
SOURCES += \
    tst_phrases.cpp

HEADERS += \
    tst_phrases.h
