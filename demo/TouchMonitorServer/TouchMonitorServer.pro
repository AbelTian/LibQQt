#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T15:03:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchMonitorServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += touchmonitorserverprotocol.cpp \
    controlorwidget.cpp
HEADERS += touchmonitorserverprotocol.h \
    controlorwidget.h

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    testwidget.cpp \
    qqtosdform.cpp

HEADERS += \
        mainwindow.h \
    testwidget.h \
    qqtosdform.h

FORMS += \
        mainwindow.ui \
    qqtosdform.ui

system("touch main.cpp")
#CONFIG += deploy_config
contains(CONFIG, deploy_config) {
    APP_CONFIG_PWD = $${PWD}/AppRoot
    equals(QMAKE_HOST.os, Windows) {
        APP_CONFIG_PWD ~=s,/,\\,g
    }
}
include(../../src/app_base_manager.pri)
