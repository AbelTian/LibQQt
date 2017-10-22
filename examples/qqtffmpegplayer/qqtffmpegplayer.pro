#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
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
    include(../qqt_library.pri)
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtffmpegplayer
TEMPLATE = app

INCLUDEPATH +=  .

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp \
    FFmpegPlayer.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h \
    FFmpegPlayer.h

FORMS    += $$PWD/qqtwindow.ui

unix {
    equals(QKIT_, macOS){
    }
    else{
        INCLUDEPATH += /usr/include/x86_64-linux-gnu
        LIBS += -L/usr/lib/x86_64-linux-gnu -lavutil -lavcodec -lswscale -lswresample -lavformat -lSDL2
    }
}

