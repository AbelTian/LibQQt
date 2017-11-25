#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------
include(../qqtframe2/link_qqt_library.pri)

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

