#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = animationframe
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = qrc
UI_DIR = ui_h
DESTDIR = bin

INCLUDEPATH += ../qqtfoundation

include(../qqtfoundation/qqtfoundation.pri)

QKIT_ = $$(QKIT)

message($${QKIT_} Defined in qqtframe)

DEFINES += _TTY_POSIX_

equals(QKIT_, MIPS32) {
	QT += multimedia
	DEFINES += __EMBEDDED_LINUX__
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

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp \
    animationmanager.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h \
    animationmanager.h

FORMS    += $$PWD/qqtwindow.ui
