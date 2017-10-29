#include QQt's header (add QQt header to includepath)
include(../../src/qqt_header.pri)
include(../../src/qqt_version.pri)

#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    #include(../../src/qqt.pri)
} else {
    #if you want to link QQt library
    include(../qqtframe2/qqt_library.pri)
}

TEMPLATE = app
INCLUDEPATH += .
CONFIG += console

# Input
HEADERS += easter.h
SOURCES += main.cpp easter.cpp
