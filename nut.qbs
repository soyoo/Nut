import qbs

Product {
    type: "staticlibrary"
    name: "nut"
    Depends { name: 'cpp' }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.sql" }

    Export {
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.sql" }
        cpp.includePaths: [
            product.sourceDirectory + "/src",
            product.sourceDirectory + "/include"
        ]
    }

    files: [
        "src/tableset.cpp",
        "src/query.cpp",
        "src/databasemodel.cpp",
        "src/tablesetbase.cpp",
        "src/changelogtable.cpp",
        "src/querybase.cpp",
        "src/tablemodel.cpp",
        "src/wherephrase.cpp",
        "src/table.cpp",
        "src/database.cpp",
        "src/generators/sqlgeneratorbase.cpp",
        "src/generators/postgresqlgenerator.cpp",
        "src/generators/mysqlgenerator.cpp",
        "src/generators/sqlitegenerator.cpp",
        "src/generators/sqlservergenerator.cpp",
        "src/types/dbgeography.cpp",
        "src/serializableobject.cpp"
    ]
}
