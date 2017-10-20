#-------------------------------------------------
#
# Project created by QtCreator 2017-10-17T17:48:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += core gui network sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

#############
##definition
#############
##Arch type
QKIT_ = $$(QKIT)
message($${QKIT_} Defined in $${TARGET})
#MIPS __EMBEDDED_LINUX__
#ARM __ARM_LINUX__
#LINUX __LINUX__
#LINUX64 __LINUX64__
#WIN __WIN__
#WIN64 __WIN64__
#macOS __DARWIN__
#Android __ANDROID__
#处理文件内平台小差异
equals(QKIT_, MIPS32) {
    QT += multimedia
    DEFINES += __EMBEDDED_LINUX__
} else:equals(QKIT_, LINUX) {
    DEFINES += __LINUX__
} else:equals(QKIT_, LINUX64) {
    DEFINES += __LINUX__
    DEFINES += __LINUX64__
} else:equals(QKIT_, WIN) {
    DEFINES += __WIN__
} else:equals(QKIT_, WIN64) {
    DEFINES += __WIN__
    DEFINES += __WIN64__
} else:equals(QKIT_, macOS) {
    DEFINES += __DARWIN__
} else:equals(QKIT_, Android) {
    DEFINES += __ANDROID__
} else:equals(QKIT_, ANDROIDX86) {
    DEFINES += __ANDROID__
    DEFINES += __ANDROIDX86__
    #todo:no customplot word printer
}

TARGET = qqtbluetoothfiletransferserver
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

equals(QKIT_, macOS) {
    CONFIG += app_bundle
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}
INCLUDEPATH += $$PWD \
    $$PWD/../../src \
    $$PWD/../../src/core \
    $$PWD/../../src/gui \
    $$PWD/../../src/multimedia \
    $$PWD/../../src/network \
    $$PWD/../../src/printsupport \
    $$PWD/../../src/sql \
    $$PWD/../../src/widgets \
    $$PWD/../../src/customplot \
    $$PWD/../../src/pluginwatcher \
    $$PWD/../../src/dmmu \
    $$PWD/../../src/frame

#include(../../src/qqt.pri)
CONFIG(debug, debug|release) {
    BUILD=Debug
} else {
    BUILD=Release
}
message(Link QQt to $${TARGET} $${QKIT_} $${BUILD} on $${QMAKE_HOST.os})
equals(QMAKE_HOST.os, Darwin) {
    equals(QKIT_, macOS) {
        LIBS += -F/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/MacOS/$${BUILD}/src/bin
        LIBS += -framework QQt
    } else: equals(QKIT_, Android) {
        LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/Android/$${BUILD}/src/bin
        LIBS += -lQQt
    } else: equals(QKIT_, ANDROIDX86) {
        LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/Android_x86/$${BUILD}/src/bin
        LIBS += -lQQt
    }
} else: equals(QMAKE_HOST.os, Linux) {
    LIBS += -L/mnt/hgfs/abel/Develop/c0-buildstation/a0-qqtfoundation/Linux/$${BUILD}/src/bin
    LIBS += -lQQt
} else: equals(QMAKE_HOST.os, Windows) {
    LIBS += -LC:/Users/Administrator/Develop/c0-build/a0-qqtfoundation/Mingw32/$${BUILD}/src/bin
    LIBS += -lQQt
}


############
##build cache
############
OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
DESTDIR = bin
############
##install
############
#CONFIG += can_install
can_install:equals(QKIT_, MIPS32) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    equals(QKIT_, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

INCLUDEPATH +=  $$PWD


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    filetransferprotocol.cpp

HEADERS += \
        mainwindow.h \
    filetransferprotocol.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

