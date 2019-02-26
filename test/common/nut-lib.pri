
win32 {
    CONFIG(debug,debug|release):   LIBDIR = $$absolute_path($$OUT_PWD/../../src/debug)
    CONFIG(release,debug|release): LIBDIR = $$absolute_path($$OUT_PWD/../../src/release)
} else {
    LIBDIR = $$absolute_path($$OUT_PWD/../../src)
}
LIBS += -L$$LIBDIR -lnut

INCLUDEPATH += $$PWD/../../src $$PWD/../common
