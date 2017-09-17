#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

TARGET = qqtframe
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
#user directory
DESTDIR = bin
#DESTDIR = ../../../Product/install/Application

INCLUDEPATH += ../../src
include(../../src/qqt.pri)

QT_KIT = $$(QKIT)

message($${QT_KIT} Defined in qqtframe)

DEFINES += _TTY_POSIX_

equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else:equals(QT_KIT, LINUX) {
    DEFINES += __LINUX__
} else:equals(QT_KIT, LINUX64) {
    DEFINES += __LINUX64__
} else:equals(QT_KIT, WIN) {
    DEFINES += __WIN__
} else:equals(QT_KIT, WIN64) {
    DEFINES += __WIN64__
} else:equals(QT_KIT, macOS) {
    DEFINES += __DARWIN__
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}


equals(QT_KIT, MIPS32) {
	mips32.path = /Application
	INSTALLS += mips32
} else {
}

INCLUDEPATH +=  $$PWD

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h

FORMS    += $$PWD/qqtwindow.ui
