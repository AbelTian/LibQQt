#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT += core gui network sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

TARGET = qqtframe
TEMPLATE = app

QT_KIT = $$(QKIT)
message($${QT_KIT} Defined in qqtframe)
equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else:equals(QT_KIT, LINUX) {
    DEFINES += __LINUX__
} else:equals(QT_KIT, LINUX64) {
    DEFINES += __LINUX__
    DEFINES += __LINUX64__
} else:equals(QT_KIT, WIN) {
    DEFINES += __WIN__
} else:equals(QT_KIT, WIN64) {
    DEFINES += __WIN__
    DEFINES += __WIN64__
} else:equals(QT_KIT, macOS) {
    DEFINES += __DARWIN__
} else:equals(QT_KIT, Android) {
    DEFINES += __ANDROID__
} else:equals(QT_KIT, ANDROIDX86) {
    DEFINES += __ANDROID__
    DEFINES += __ANDROIDX86__
}
equals(QT_KIT, macOS) {
    CONFIG += app_bundle
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}

equals(QT_KIT, Android) {
    CONFIG += mobility
    MOBILITY =
    #DISTFILES += \
    #    android/AndroidManifest.xml

    #ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
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
message(Link QQt to $${TARGET} $${QT_KIT} on $${QMAKE_HOST.os})
equals(QMAKE_HOST.os, Darwin) {
    equals(QT_KIT, macOS) {
        LIBS += -F/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/MacOS/Release/src/bin
        LIBS += -framework QQt
    } else: equals(QT_KIT, Android) {
        LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/Android/Release/src/bin
        LIBS += -lQQt
    } else: equals(QT_KIT, ANDROIDX86) {
        LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/Android_x86/Release/src/bin
        LIBS += -lQQt
    }
} else: equals(QMAKE_HOST.os, Linux) {
    LIBS += -L/mnt/hgfs/abel/Develop/c0-buildstation/a0-qqtfoundation/Linux/Release/src/bin
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
can_install:equals(QT_KIT, MIPS32) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    equals(QT_KIT, macOS){
        target.path = /Applications
        INSTALLS += target
    }
}

INCLUDEPATH +=  $$PWD

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h

FORMS    += $$PWD/qqtwindow.ui
