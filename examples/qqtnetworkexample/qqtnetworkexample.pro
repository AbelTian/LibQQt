#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T18:27:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtnetworkexample
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
SOURCES -= \
    qqtlanprotocol.cpp

HEADERS -= \
    qqtlanprotocol.h

SOURCES += \
    qqtcloudprotocol.cpp \
    qqtnetworkmessage.cpp \
    qqtserialmessage.cpp \
    qqtuserserialprotocol.cpp \
    qqtsubprotocoltest.cpp


HEADERS += \
    qqtcloudprotocol.h \
    qqtnetworkmessage.h \
    qqtserialmessage.h \
    qqtuserserialprotocol.h \
    qqtsubprotocoltest.h


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

#qmake_pre/post_link will work after source changed but not pro pri changed.
system("touch main.cpp")

#-------------------------------------------------
#link qqt library
#if you link a library to your app, on android you must select the running kit to the app, not LibQQt e.g.
#user can modify any infomation under this annotation
#-------------------------------------------------
include(../../multi-link/add_base_manager.pri)

contains (DEFINES, __BLUETOOTH__){
    SOURCES += \
        quserbluetoothprotocol.cpp
    HEADERS += \
        quserbluetoothprotocol.h
}

#这个的设置有特点，要先设置
add_version (1,0,0,0)

#先发布App
#app从build到deploy
add_deploy()

#后发布依赖
#libQQt从sdk到build和deploy
add_dependent_library_QQt()

