QT       += testlib sql

TARGET = tst_upgrades
TEMPLATE = app
CONFIG   += warn_on c++11

include(../common/nut-lib.pri)

SOURCES +=  \
    tst_json.cpp \
    db.cpp \
    sampletable.cpp

HEADERS += \
    tst_json.h \
    db.h \
    sampletable.h

include($$PWD/../../ci-test-init.pri)
