import qbs

Project {
//    StaticLibrary {
//        name: "nut_static"
//        files: [
//            "src/*.h",
//            "src/*.cpp",
//            "src/generators/*.h",
//            "src/generators/*.cpp"
//        ]
//        Depends { name: 'cpp' }
//        Depends { name: "Qt.core" }
//        Depends { name: "Qt.sql" }
//        Group { qbs.install: true; fileTagsFilter: product.type;}

//        Export {
//            Depends { name: "cpp" }
//            Depends { name: "Qt.core" }
//            Depends { name: "Qt.sql" }
//            cpp.includePaths: [
//                product.sourceDirectory + "/src",
//                product.sourceDirectory + "/include"
//            ]
//        }
//    }

    DynamicLibrary {
        name: "nut"
        files: [
            "src/*.h",
            "src/*.cpp",
            "src/generators/*.h",
            "src/generators/*.cpp"
        ]

        Depends { name: 'cpp' }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.sql" }

        Group { qbs.install: true; fileTagsFilter: product.type;}

        Export {
            Depends { name: "cpp" }
            Depends { name: "Qt.core" }
            Depends { name: "Qt.sql" }
            cpp.includePaths: [
                product.sourceDirectory + "/src",
                product.sourceDirectory + "/include"
            ]
        }
    }
}
