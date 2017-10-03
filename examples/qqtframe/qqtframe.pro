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
macx {
    CONFIG += app_bundle
}

QT_KIT = $$(QKIT)
message($${QT_KIT} Defined in qqtframe)
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
} else:equals(QT_KIT, Android) {
    DEFINES += __ANDROID__
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
macx {
    LIBS += -F/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/MacOS/Release/src/bin
    LIBS += -framework QQt
}
equals(QT_KIT, Android) {
    LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/Android-arm/Release/src/bin
    LIBS += -lQQt
}

OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
#user directory
DESTDIR = bin
equals(QT_KIT, MIPS32) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    macx{
        target.path = /Users/abel/Develop/b1-Product
        INSTALLS += target
    }
}

INCLUDEPATH +=  $$PWD

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h

FORMS    += $$PWD/qqtwindow.ui
