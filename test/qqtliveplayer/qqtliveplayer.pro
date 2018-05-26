#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------
include(../../multi-link/add_base_manager.pri)


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtliveplayer
TEMPLATE = app

INCLUDEPATH +=  .


CONFIG += c++11

unix {
    LIBS += -lVLCQtCore -lVLCQtWidgets
    #QMAKE_CXXFLAGS += -std=c++11
    #LIBS +=  -L/usr/local/lib -lVLCQtCore -lVLCQtWidgets
    INCLUDEPATH += /usr/local/include
}

win32 {
    ## Windows common build here

    contains(QMAKE_TARGET.arch, x86) {
        message("x86 build")

        ## Windows x86 (32bit) specific build here
        CONFIG(debug, debug|release) {
            LIBS +=  -LC:\\Users\\tdr\\Documents\\QtSolution\\qt4web\\vlcqt\\lib -lVLCQtCored -lVLCQtWidgetsd
        } else {
            LIBS +=  -LC:\\Users\\tdr\\Documents\\QtSolution\\qt4web\\vlcqt\\lib -lVLCQtCore -lVLCQtWidgets
        }
        INCLUDEPATH += C:\\Users\\tdr\\Documents\\QtSolution\\qt4web\\vlcqt\\include
    } else {
        message("x86_64 build")

        ## Windows x64 (64bit) specific build here
        CONFIG(debug, debug|release) {
            LIBS +=  -LC:\\Users\\tdr\\Documents\\QtSolution\\qt4web\\vlcqt64\\lib -lVLCQtCored -lVLCQtWidgetsd
        } else {
            LIBS +=  -LC:\\Users\\tdr\\Documents\\QtSolution\\qt4web\\vlcqt64\\lib -lVLCQtCore -lVLCQtWidgets
        }
        INCLUDEPATH += C:\\Users\\tdr\\Documents\\QtSolution\\qt4web\\vlcqt64\\include
    }
}


SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp \
    animationmanager.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h \
    animationmanager.h

FORMS    += $$PWD/qqtwindow.ui

#这个的设置有特点，要先设置
add_version (1,0,0,0)

#先发布App
#app从build到deploy
add_deploy()

#后发布依赖
#libQQt从sdk到build和deploy
add_deploy_library(QQt)

