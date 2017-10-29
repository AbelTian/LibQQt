#include QQt's header (add QQt header to includepath)
#QQt source root on your computer
equals(QMAKE_HOST.os, Darwin) {
    QQT_SOURCE_ROOT = /Users/abel/Develop/a0-develop/a0-qqtfoundation
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_SOURCE_ROOT = /home/abel/Develop/a0-develop/LibQt
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_SOURCE_ROOT = C:/Users/Administrator/Develop/a0-develop/a0-qqtfoundation
}

include($${QQT_SOURCE_ROOT}/src/qqt_version.pri)
include($${QQT_SOURCE_ROOT}/src/qqt_header.pri)
#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    include($${QQT_SOURCE_ROOT}/src/qqt_source.pri)
} else {
    #if you want to link QQt library
    include($${QQT_SOURCE_ROOT}/src/qqt_library.pri)
}

############
##install
############
#CONFIG += can_install
can_install:equals(QKIT_PRIVATE, EMBEDDED) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    equals(QKIT_PRIVATE, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

equals(QKIT_PRIVATE, ANDROID) {
    CONFIG += mobility
    MOBILITY =
}

#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})

TEMPLATE = app
INCLUDEPATH += .
CONFIG += console

# Input
HEADERS += easter.h
SOURCES += main.cpp easter.cpp
