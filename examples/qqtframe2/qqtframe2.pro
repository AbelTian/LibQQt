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

#include QQt's header (add QQt header to includepath)
include(../../src/qqt_header.pri)

#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    #include(../../src/qqt.pri)
} else {
    #if you want to link QQt library
    message(Link QQt to $${TARGET} $${QT_KIT} from $${SYSNAME} $${BUILD} on $${QMAKE_HOST.os})
    equals(QMAKE_HOST.os, Darwin) {
        equals(QT_KIT, macOS) {
            LIBS += -F/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
            LIBS += -framework QQt
        } else: equals(QT_KIT, Android) {
            LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
            LIBS += -lQQt
        } else: equals(QT_KIT, ANDROIDX86) {
            LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
            LIBS += -lQQt
        }
    } else: equals(QMAKE_HOST.os, Linux) {
        LIBS += -L/home/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
        LIBS += -lQQt
    } else: equals(QMAKE_HOST.os, Windows) {
        LIBS += -LC:/Users/Administrator/Develop/c0-build/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
        LIBS += -lQQt
    }
}
############
##install
############
#CONFIG += can_install
can_install:equals(QT_KIT, MIPS32) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    equals(QT_KIT, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

equals(QT_KIT, macOS) {
    CONFIG += app_bundle
}
equals(QT_KIT, Android) {
    CONFIG += mobility
    MOBILITY =
    #DISTFILES += \
    #    android/AndroidManifest.xml

    #ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

TARGET = qqtframe2
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
