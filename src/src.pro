QT       += sql gui

TARGET = nut
TEMPLATE = lib
CONFIG += c++11
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS NUT_COMPILE_STATIC

include($$PWD/src.pri)
include($$PWD/../3rdparty/serializer/src/src.pri)
include($$PWD/../ci-test-init.pri)
