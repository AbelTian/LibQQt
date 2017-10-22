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
    include(qqt_library.pri)
}


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

