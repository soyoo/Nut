QT += core sql

CONFIG += c++11

INCLUDEPATH += $$PWD/include
include(3rdparty/serializer/src/src.pri)

HEADERS += \
    $$PWD/src/generators/sqlgeneratorbase_p.h \
    $$PWD/src/generators/postgresqlgenerator.h \
    $$PWD/src/generators/mysqlgenerator.h \
    $$PWD/src/generators/sqlitegenerator.h \
    $$PWD/src/generators/sqlservergenerator.h \
    $$PWD/src/types/dbgeography.h \
    $$PWD/src/tableset.h \
    $$PWD/src/defines_p.h \
    $$PWD/src/defines.h \
    $$PWD/src/query.h \
    $$PWD/src/databasemodel.h \
    $$PWD/src/changelogtable.h \
    $$PWD/src/tablesetbase_p.h \
    $$PWD/src/querybase_p.h \
    $$PWD/src/tablemodel.h \
    $$PWD/src/query_p.h \
    $$PWD/src/table.h \
    $$PWD/src/database.h \
    $$PWD/src/database_p.h \
    $$PWD/src/serializableobject.h \
    $$PWD/src/sqlmodel.h \
    $$PWD/src/sqlmodel_p.h \
    $$PWD/src/phrase.h \
    $$PWD/src/tuple.h

SOURCES += \
    $$PWD/src/generators/sqlgeneratorbase.cpp \
    $$PWD/src/generators/postgresqlgenerator.cpp \
    $$PWD/src/generators/mysqlgenerator.cpp \
    $$PWD/src/generators/sqlitegenerator.cpp \
    $$PWD/src/generators/sqlservergenerator.cpp \
    $$PWD/src/types/dbgeography.cpp \
    $$PWD/src/tableset.cpp \
    $$PWD/src/query.cpp \
    $$PWD/src/databasemodel.cpp \
    $$PWD/src/tablesetbase.cpp \
    $$PWD/src/changelogtable.cpp \
    $$PWD/src/querybase.cpp \
    $$PWD/src/tablemodel.cpp \
    $$PWD/src/table.cpp \
    $$PWD/src/database.cpp \
    $$PWD/src/serializableobject.cpp \
    $$PWD/src/sqlmodel.cpp \
    $$PWD/src/phrase.cpp \
    $$PWD/src/tuple.cpp
