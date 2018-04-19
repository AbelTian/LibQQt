#-------------------------------------------------
#
# Project created by QtCreator 2017-10-17T21:33:06
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtnetworkexample
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

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qqtcloudprotocol.cpp \
    qqtlanprotocol.cpp \
    qqtnetworkmessage.cpp \
    qqtserialmessage.cpp \
    qqtuserserialprotocol.cpp \
    qqtsubprotocoltest.cpp \
    qqtuserprotocol1.cpp \
    qqtuserprotocol2.cpp \
    qqtuserprotocol3.cpp \
    main.cpp \
    mainwindow.cpp \
    qqtcloudprotocol.cpp \
    qqtlanprotocol.cpp \
    qqtnetworkmessage.cpp \
    qqtserialmessage.cpp \
    qqtsubprotocoltest.cpp \
    qqtuserprotocol1.cpp \
    qqtuserprotocol2.cpp \
    qqtuserprotocol3.cpp \
    qqtuserserialprotocol.cpp \
    quserbluetoothprotocol.cpp \
    usernode0protocol.cpp \
    usernode1protocol.cpp \
    usernode2protocol.cpp \
    usernode3protocol.cpp \
    usernode4protocol.cpp \
    usernode5protocol.cpp \
    usernode6protocol.cpp \
    usernode7protocol.cpp \
    usernode8protocol.cpp \
    usernode9protocol.cpp \
    usertest0protocol.cpp \
    usertest1protocol.cpp \
    usertest2protocol.cpp \
    usertest3protocol.cpp \
    usertest4protocol.cpp \
    usertest5protocol.cpp \
    usertest6protocol.cpp \
    usertest7protocol.cpp \
    usertest8protocol.cpp \
    usertest9protocol.cpp

HEADERS += \
        mainwindow.h \
    qqtcloudprotocol.h \
    qqtlanprotocol.h \
    qqtnetworkmessage.h \
    qqtserialmessage.h \
    qqtuserserialprotocol.h \
    qqtsubprotocoltest.h \
    qqtuserprotocol1.h \
    qqtuserprotocol2.h \
    qqtuserprotocol3.h \
    mainwindow.h \
    qqtcloudprotocol.h \
    qqtlanprotocol.h \
    qqtnetworkmessage.h \
    qqtserialmessage.h \
    qqtsubprotocoltest.h \
    qqtuserprotocol1.h \
    qqtuserprotocol2.h \
    qqtuserprotocol3.h \
    qqtuserserialprotocol.h \
    quserbluetoothprotocol.h \
    usernode0protocol.h \
    usernode1protocol.h \
    usernode2protocol.h \
    usernode3protocol.h \
    usernode4protocol.h \
    usernode5protocol.h \
    usernode6protocol.h \
    usernode7protocol.h \
    usernode8protocol.h \
    usernode9protocol.h \
    usertest0protocol.h \
    usertest1protocol.h \
    usertest2protocol.h \
    usertest3protocol.h \
    usertest4protocol.h \
    usertest5protocol.h \
    usertest6protocol.h \
    usertest7protocol.h \
    usertest8protocol.h \
    usertest9protocol.h

FORMS += \
        mainwindow.ui \
    mainwindow.ui

#qmake_pre/post_link will work after source changed but not pro pri changed.
system("touch main.cpp")

#-------------------------------------------------
#link qqt library
#if you link a library to your app, on android you must select the running kit to the app, not LibQQt e.g.
#user can modify any infomation under this annotation
#-------------------------------------------------
include(../../src/app_base_manager.pri)

contains (DEFINES, __BLUETOOTH__){
    SOURCES += \
        quserbluetoothprotocol.cpp
    HEADERS += \
        quserbluetoothprotocol.h
}

#-------------------------------------------------
#user app may use these these settings prefertly
#-------------------------------------------------
#-------------------------------------------------
#install app
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

############
##config defination
############
equals(QKIT_PRIVATE, macOS) {
    CONFIG += app_bundle
}

contains(QKIT_PRIVATE, ANDROID|ANDROIDX86) {
    CONFIG += mobility
    MOBILITY =
    DISTFILES += \
        android/AndroidManifest.xml

    ANDROID_PACKAGE_SOURCE_DIR = $${PWD}/android
}


#-------------------------------------------------
##project environ
#-------------------------------------------------
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})

SUBDIRS += \
    qqtnetworkexample.pro


