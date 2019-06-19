QT       += testlib sql gui

TARGET = tst_datatypes
TEMPLATE = app

CONFIG   += warn_on c++11

DEFINES += DOC_PATH=\\\"$$PWD/../../doc\\\"

include(../common/nut-lib.pri)

SOURCES += \
    tst_supported_datatypes.cpp

HEADERS += \
    tst_supported_datatypes.h

include($$PWD/../../ci-test-init.pri)
