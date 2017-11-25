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
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

#this name must be equals to pro name? no, this must place before qqt_library.pri
#qmake pro pri is sequential
TARGET = QQtSdkManager
TEMPLATE = app

include(../qqtframe2/link_qqt_library.pri)



INCLUDEPATH +=  $$PWD

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    httpdownloaddialog.cpp \
    qqthttpdownloadmanager.cpp \
    qqtqtiofilezise.cpp \
    qqtqtiowebpageparser.cpp

HEADERS += \
        mainwindow.h \
    httpdownloaddialog.h \
    qqthttpdownloadmanager.h \
    qqtqtiofilezise.h \
    qqtqtiowebpageparser.h

FORMS += \
        mainwindow.ui \
    httpdownloaddialog.ui
