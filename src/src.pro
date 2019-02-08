QT       += sql
QT       -= gui

TARGET = nut
TEMPLATE = lib
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    $$PWD/generators/sqlgeneratorbase_p.h \
    $$PWD/generators/postgresqlgenerator.h \
    $$PWD/generators/mysqlgenerator.h \
    $$PWD/generators/sqlitegenerator.h \
    $$PWD/generators/sqlservergenerator.h \
    $$PWD/types/dbgeography.h \
    $$PWD/tableset.h \
    $$PWD/defines_p.h \
    $$PWD/defines.h \
    $$PWD/query.h \
    $$PWD/databasemodel.h \
    $$PWD/changelogtable.h \
    $$PWD/tablesetbase_p.h \
    $$PWD/querybase_p.h \
    $$PWD/tablemodel.h \
    $$PWD/query_p.h \
    $$PWD/table.h \
    $$PWD/database.h \
    $$PWD/database_p.h \
    $$PWD/serializableobject.h \
    $$PWD/sqlmodel.h \
    $$PWD/sqlmodel_p.h \
    $$PWD/phrase.h

SOURCES += \
    $$PWD/generators/sqlgeneratorbase.cpp \
    $$PWD/generators/postgresqlgenerator.cpp \
    $$PWD/generators/mysqlgenerator.cpp \
    $$PWD/generators/sqlitegenerator.cpp \
    $$PWD/generators/sqlservergenerator.cpp \
    $$PWD/types/dbgeography.cpp \
    $$PWD/tableset.cpp \
    $$PWD/query.cpp \
    $$PWD/databasemodel.cpp \
    $$PWD/tablesetbase.cpp \
    $$PWD/changelogtable.cpp \
    $$PWD/querybase.cpp \
    $$PWD/tablemodel.cpp \
    $$PWD/table.cpp \
    $$PWD/database.cpp \
    $$PWD/serializableobject.cpp \
    $$PWD/sqlmodel.cpp \
    $$PWD/phrase.cpp

include($$PWD/../3rdparty/serializer/src/src.pri)
