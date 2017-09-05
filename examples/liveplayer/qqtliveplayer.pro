#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtliveplayer
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc

#user directory
#DESTDIR = bin
DESTDIR = ../../../Product/install/Application

INCLUDEPATH += ../qqtfoundation

include(../qqtfoundation/qqtfoundation.pri)

QT_KIT = $$(QKIT)

message($${QT_KIT} Defined in qqtframe)

DEFINES += _TTY_POSIX_

equals(QT_KIT, MIPS32) {
	QT += multimedia
	DEFINES += __MIPS_LINUX__
} else {
	DEFINES += __LINUX64__
}

CONFIG(debug, debug|release) {
} else {
	DEFINES -= QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH +=  .

target.path += /application

INSTALLS += target

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

