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

#Project link: https://gitee.com/drabel/LibQt
#if you succeed with LibQQt, please thumb up.
#2017年11月10日18:53:56

##Don't modify this file outside QQt project
##this is QQt feature pri you can modify QQt feature in QQt project at this pri

#################################################################
##definition and configration
##need QKIT
#################################################################

##Qt version
QT += core sql network gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# release open debug output
CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}
#close win32 no using fopen_s warning
win32 {
    win32:DEFINES += _CRT_SECURE_NO_WARNINGS #fopen fopen_s
    #this three pragma cause errors
    #QMAKE_CXXFLAGS += /wd"4819" /wd"4244" /wd"4100"
}
#compatible old version QQt (deperated)
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

#defined in qqtcore.h
#lessThan(QT_MAJOR_VERSION, 5):DEFINES += nullptr=0
################################################################
##build cache
################################################################
OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
DESTDIR = bin

################################################################
##QQt Functions Macro
################################################################
#You need switch these more macro according to your needs when you build this library
#You can tailor QQt  with these macro.
#Default: macroes is configed, some open, some close, compatibled to special accotation.

##################SerialPort Module##################################
#if you use qextserialport, open the annotation
#suggest: Qt5 use factory-packed, Qt4 use forming Qt5, extra use this.
#DEFINES += __QEXTSERIALPORT__
#if compiler QtSerialPort module manual, note this line is a good idea. default: qt4 qextserialport
lessThan(QT_MAJOR_VERSION, 5): DEFINES += __QEXTSERIALPORT__
#to ios, use qextserialport #android qt5 support serialport default?
contains (DEFINES, __IOS__): DEFINES += __QEXTSERIALPORT__
contains (DEFINES, __QEXTSERIALPORT__) {
    CONFIG += thread
    unix:DEFINES += _TTY_POSIX_
    win32:DEFINES += _TTY_WIN_
    #message ( __QEXTSERIALPORT__ Defined in $${TARGET})
} else {
    #message ( __QSERIALPORT__ Defined in $${TARGET})
    greaterThan(QT_MAJOR_VERSION, 4): QT += serialport
    lessThan(QT_MAJOR_VERSION, 5): CONFIG += serialport
    unix {
        DEFINES += _TTY_POSIX_
    } else {
        DEFINES += _TTY_WIN_
    }
}

##################Bluetooth Module###############################
#if you use qtbluetooth, open this annotation
DEFINES += __BLUETOOTH__
#if you compiler QtBluetooth module manual, note this line is a good idea. default qt4 don't use bluetooth
lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __BLUETOOTH__
#condation
contains (DEFINES, __BLUETOOTH__) {
    greaterThan(QT_MAJOR_VERSION, 4): QT += bluetooth
    lessThan(QT_MAJOR_VERSION, 5): CONFIG += bluetooth
}

##################C++11 Module###############################
#if you use C++11, open this annotation. suggest: ignore
#DEFINES += __CPP11__
contains (DEFINES, __CPP11__) {
    #macOS gcc Qt4.8.7
    #qobject.h fatal error: 'initializer_list' file not found,
    #Qt4.8.7 can't support c++11 features
    #QMAKE_CXXFLAGS += "-std=c++11"
    #QMAKE_CXXFLAGS += "-std=c++0x"

    #below: gcc version > 4.6.3
    #Open this Config, Why in Qt4 works? see qmake config auto ignored this feature.
    #In Qt5? don't need open this config, qmake auto add c++11 support on linux plat.
    #on windows mingw32? need test
    #CONFIG += c++11

    #compile period
    #LibQQt need c++11 support. Please ensure your compiler version.
    #LibQQt used Q_DECL_OVERRIDE identifier
    #lambda also need c++11
}

##################MultiMedia Module###############################
DEFINES += __MULTIMEDIA__
contains (DEFINES, __MULTIMEDIA__) {
    QT += multimedia
}

##################DeviceWatcher Module###############################
#used in windows linux e-linux android, mac ios not support exactly
#if you use DeviceWatcher , open this annotation
DEFINES += __PLUGINWATCHER__
contains(QKIT_PRIVATE, iOS||iOSSimulator||macOS) {
    DEFINES -= __PLUGINWATCHER__
}

##################Process Module###############################
#if you use qprocess , open this annotation
DEFINES += __PROCESSMODULE__
#ios has no backend process
contains(QKIT_PRIVATE, iOS||iOSSimulator) {
    DEFINES -= __PROCESSMODULE__
}

##################PrintSupport Module###############################
#if you use printsupport , open this annotation
DEFINES += __PRINTSUPPORT__
#Qt5.9.1, ios android can't support this feature.
#Qt5.9.1, broken
equals(QT_VERSION, 5.9.1) {
    contains(QKIT_PRIVATE, iOS||iOSSimulator||ANDROID||ANDROIDX86) {
        DEFINES -= __PRINTSUPPORT__
    }
}
#ios can't use printsupport
contains(QKIT_PRIVATE, iOS||iOSSimulator) {
    DEFINES -= __PRINTSUPPORT__
}
contains (DEFINES, __PRINTSUPPORT__) {
    #qtHaveModule(printsupport) : message(qqt use module printsupport)
    greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
    #if you use qcustomplot, open this annotation
    DEFINES += __CUSTOMPLOT__
}

##################Exquisite Module###############################
#if you use Exquisite widgets, open this annotation
DEFINES += __EXQUISITE__
#if you use QR encode, open this annotation
DEFINES += __QRENCODE__

##################WebSocket Module###############################
#if you use QtSoap, open this annotation
DEFINES += __QTSOAP__
#don't close this macro ...
DEFINES += __TCPUDPSOCKET__
#One Ftp Http 单工...
#Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
#if you use QNetworkAccessManagerSupport , open this annotation
DEFINES += __WEBWORKSUPPORT__
lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __WEBWORKSUPPORT__
contains (DEFINES, __WEBWORKSUPPORT__) {
    #QSslError not found, you need recompiler Qt4
    #TODO: QT += webkit
}
#Multi New Protocol 全双工 QWebSocket
#if you use QWebSocketSupport , open this annotation
DEFINES += __WEBSOCKETSUPPORT__
equals(QKIT_PRIVATE, macOS):DEFINES += __WEBSOCKETSUPPORT__
lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __WEBSOCKETSUPPORT__
contains (DEFINES, __WEBSOCKETSUPPORT__) {
    QT += websockets
    #QSslError not found, you need recompiler Qt4
    #TODO: QT += webkit
}

##################################################################
##library
##################################################################
equals (QKIT_PRIVATE, iOSSimulator):{
    #error need
    #QMAKE_CXXFLAGS +=-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk
}
win32 {
    LIBS += -luser32
}else: unix {
    equals(QKIT_PRIVATE, macOS) {
        #min macosx target
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
        #deperated
        #QMAKE_MAC_SDK=macosx10.12
        #MACOSXSDK = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX$${QMAKE_MACOSX_DEPLOYMENT_TARGET}.sdk
        #QMAKE_LIBDIR = $${MACOSXSDK}
        #LIBS += -F$${MACOSXSDK}/System/Library/Frameworks
        #LIBS += -L$${MACOSXSDK}/usr/lib
        LIBS += -framework DiskArbitration -framework Cocoa -framework IOKit
    }else:contains(QKIT_PRIVATE, iOS|iOSSimulator){
        QMAKE_LFLAGS += -ObjC -lsqlite3 -lz
        QMAKE_IOS_DEPLOYMENT_TARGET = 8
    }
}
##################################################################
##include directories
##################################################################
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/core
INCLUDEPATH += $$PWD/customplot
# c support
INCLUDEPATH += $$PWD/dmmu
INCLUDEPATH += $$PWD/frame
INCLUDEPATH += $$PWD/gui
INCLUDEPATH += $$PWD/multimedia
INCLUDEPATH += $$PWD/network
INCLUDEPATH += $$PWD/network/qextserialport
INCLUDEPATH += $$PWD/pluginwatcher
INCLUDEPATH += $$PWD/printsupport
INCLUDEPATH += $$PWD/sql
INCLUDEPATH += $$PWD/widgets
INCLUDEPATH += $$PWD/exquisite
# c support
INCLUDEPATH += $$PWD/qrencode
INCLUDEPATH += $$PWD/soap
