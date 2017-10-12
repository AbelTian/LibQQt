#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T23:30:20
#
#-------------------------------------------------
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += core gui network sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

TARGET = QtBuildTool
TEMPLATE = app
macx {
    CONFIG += app_bundle
}

QT_KIT = $$(QKIT)
message($${QT_KIT} Defined in $${TARGET})
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
    macx{
        target.path = /Applications
        INSTALLS += target
    }
}

INCLUDEPATH +=  $$PWD

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
