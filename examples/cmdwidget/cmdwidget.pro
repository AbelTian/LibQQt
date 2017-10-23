#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T09:34:03
#
#-------------------------------------------------
#include QQt's header (add QQt header to includepath)
include(../../src/qqt_header.pri)

#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    #include(../../src/qqt.pri)
} else {
    #if you want to link QQt library
    #include(../qqt_library.pri)
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cmdwidget
TEMPLATE = app


SOURCES += main.cpp\
        cmdwidget.cpp \
    rlineedit.cpp

HEADERS  += cmdwidget.h \
    rlineedit.h

FORMS    += cmdwidget.ui
