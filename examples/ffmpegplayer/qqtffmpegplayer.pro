#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtffmpegplayer
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc

#user directory
#DESTDIR = bin
DESTDIR = ../../../Product/install/Application

INCLUDEPATH += ../qqtfoundation \
	/usr/include/x86_64-linux-gnu

include(../qqtfoundation/qqtfoundation.pri)

QT_KIT = $$(QKIT)

message($${QT_KIT} Defined in qqtffmpegplayer)

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

target.path += /application

INSTALLS += target

INCLUDEPATH +=  .

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp \
    FFmpegPlayer.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h \
    FFmpegPlayer.h

FORMS    += $$PWD/qqtwindow.ui


LIBS += -L/usr/lib/x86_64-linux-gnu -lavutil -lavcodec -lswscale -lswresample -lavformat -lSDL2

