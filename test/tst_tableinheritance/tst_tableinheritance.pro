QT += testlib sql

include(../common/nut-lib.pri)

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tableinheritance.cpp \
    sampledatabase.cpp \
    tablebase.cpp \
    tablechild.cpp

include($$PWD/../../ci-test-init.pri)

HEADERS += \
    sampledatabase.h \
    tablebase.h \
    tablechild.h
