#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------
include(../../multi-link/add_base_manager.pri)

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

#这个的设置有特点，要先设置
add_version (1,0,0,0)

#先发布App
#app从build到deploy
add_deploy()

#后发布依赖
#libQQt从sdk到build和deploy
add_dependent_library_QQt()

