
win32 {
#    CONFIG(debug,debug|release):   DESTDIR = $$absolute_path($$OUT_PWD/../../src/debug)
#    CONFIG(release,debug|release): DESTDIR = $$absolute_path($$OUT_PWD/../../src/release)
} else {
#    CONFIG(debug,debug|release):   DESTDIR = $$absolute_path($$OUT_PWD/../../debug)
#    CONFIG(release,debug|release): DESTDIR = $$absolute_path($$OUT_PWD/../../release)
}

#LIBS += -l$$OUT_PWD/../../src/debug/nut

INCLUDEPATH += $$PWD/../../src $$PWD/../common

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../build-nut-Desktop_Qt_5_12_0_MSVC2015_64bit-Debug/src/release/ -lnut
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build-nut-Desktop_Qt_5_12_0_MSVC2015_64bit-Debug/src/debug/ -lnut
else:unix: LIBS += -L$$PWD/../../../build-nut-Desktop_Qt_5_12_0_MSVC2015_64bit-Debug/src/ -lnut

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
