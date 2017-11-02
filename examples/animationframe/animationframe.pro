#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------
#this link struct can't support macOS
#include QQt's header (add QQt header to includepath)
#include(../../src/qqt_version.pri)
#include(../../src/qqt_header.pri)
#include(../qqtframe2/qqt_library.pri)

#QQt source root on your computer
equals(QMAKE_HOST.os, Darwin) {
    QQT_SOURCE_ROOT = /Users/abel/Develop/a0-develop/a0-qqtfoundation
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_SOURCE_ROOT = /home/abel/Develop/a0-develop/LibQt
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_SOURCE_ROOT = C:/Users/Administrator/Develop/a0-develop/LibQt
}

#include QQt's version
include($${QQT_SOURCE_ROOT}/src/qqt_version.pri)
#include QQt's header (add QQt header to includepath)
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

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = animationframe
TEMPLATE = app

INCLUDEPATH +=  $$PWD

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp \
    animationmanager.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h \
    animationmanager.h

FORMS    += $$PWD/qqtwindow.ui
