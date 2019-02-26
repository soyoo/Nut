QT       += testlib sql
QT       -= gui

TARGET = tst_uuid
TEMPLATE = app

CONFIG   += warn_on c++11
INCLUDEPATH += $$PWD/../../src $$PWD/../common
include(../../nut.pri)
IMPORTPATH += $$OUT_PWD/../src/imports
SOURCES += \
    testdatabase.cpp \
    test.cpp \
    tst_uuid.cpp

HEADERS += \
    ../common/consts.h \
    testdatabase.h \
    test.h \
    tst_uuid.h
