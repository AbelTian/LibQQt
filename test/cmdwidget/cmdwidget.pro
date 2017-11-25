#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T09:34:03
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cmdwidget
TEMPLATE = app


SOURCES += main.cpp\
        cmdwidget.cpp \
    rlineedit.cpp

HEADERS  += cmdwidget.h \
    rlineedit.h

FORMS    += cmdwidget.ui

include($$PWD/../../examples/qqtframe2/link_qqt_library.pri)

############
##install
############
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

#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})

