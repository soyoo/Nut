QT       += testlib sql

TARGET = tst_phrases
TEMPLATE = app

CONFIG   += warn_on c++11

include(../common/nut-lib.pri)

SOURCES += \
    tst_phrases.cpp

HEADERS += \
    tst_phrases.h
