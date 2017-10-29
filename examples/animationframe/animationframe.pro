#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------
#this link struct can't support macOS
#include QQt's header (add QQt header to includepath)
include(../../src/qqt_version.pri)
include(../../src/qqt_header.pri)

#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    #include(../../src/qqt.pri)
} else {
    #if you want to link QQt library
    include(../qqtframe2/qqt_library.pri)
}

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
