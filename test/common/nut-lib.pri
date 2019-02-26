
win32 {
    CONFIG(debug,debug|release):   LIBDIR = $$absolute_path($$OUT_PWD/../../src/debug)
    CONFIG(release,debug|release): LIBDIR = $$absolute_path($$OUT_PWD/../../src/release)
} else {
    CONFIG(debug,debug|release):   LIBDIR = $$absolute_path($$OUT_PWD/../../debug)
    CONFIG(release,debug|release): LIBDIR = $$absolute_path($$OUT_PWD/../../release)
}
LIBS += -L$$LIBDIR -lnut

INCLUDEPATH += $$PWD/../../src $$PWD/../common
