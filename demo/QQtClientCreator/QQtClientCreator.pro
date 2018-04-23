#-------------------------------------------------
#
# Project created by QtCreator 2018-04-19T20:04:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQtClientCreator
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    #测试这个模板是不是正确的。
    AppRoot/templete/qqtuserprotocol.cpp

HEADERS += \
        mainwindow.h \
    AppRoot/templete/qqtuserprotocol.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

#促使qqt_deploy_config配置执行，没有这个变量不执行。
APP_CONFIG_PWD = $${PWD}/AppRoot
equals(QMAKE_HOST.os, Windows) {
    APP_CONFIG_PWD ~=s,/,\\,g
}

#促使编译源代码，qmake pri配置里面的QMAKE_XX_LINK命令就会执行。
system("touch main.cpp")
include(../../src/app_base_manager.pri)
