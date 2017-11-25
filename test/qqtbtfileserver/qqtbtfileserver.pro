#-------------------------------------------------
#
# Project created by QtCreator 2017-10-17T17:48:58
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtbtfileserver
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

#-------------------------------------------------
#link qqt library
#-------------------------------------------------
include(../../examples/qqtframe2/link_qqt_library.pri)

#-------------------------------------------------
#install
#-------------------------------------------------
#CONFIG += can_install
can_install:equals(QKIT_PRIVATE, EMBEDDED) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    equals(QKIT_PRIVATE, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

equals(QKIT_PRIVATE, ANDROID) {
    CONFIG += mobility
    MOBILITY =
}

#-------------------------------------------------
##project environ
#-------------------------------------------------
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})

