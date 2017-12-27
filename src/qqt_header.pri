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
##this is QQt feature pri you can modify QQt feature at this pri in QQt project

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

#################################################################
##build qqt or link qqt
#################################################################
##different target:
##-----------------------------------------------
##win platform:
##build qqt dll + QQT_LIBRARY
##build qqt lib + QQT_STATIC_LIBRARY
##link qqt lib + QQT_STATIC_LIBRARY
##link qqt dll + ~~
##- - - - - - - - - - - - - - - - - - - - -
##*nix platform:
##build and link qqt dll or lib + ~~
##-----------------------------------------------
#link QQt static library in some occation on windows
#when link QQt    static library, if no this macro, headers can't be linked on windows.
contains(QKIT_PRIVATE, WIN32) {
    #Qt is static by mingw32 building
    mingw{
        #on my computer, Qt library are all static library?
        DEFINES += QQT_STATIC_LIBRARY
        message($${TARGET} QQT_STATIC_LIBRARY is defined. build and link)
    }
    #link and build all need this macro
    contains(DEFINES, QQT_STATIC_LIBRARY) {
        DEFINES += QCUSTOMPLOT_STATIC_LIBRARY
        DEFINES += QZXING_STATIC_LIBRARY
        DEFINES += QT_QTSOAP_STATIC_LIBRARY
        DEFINES += BUILD_QDEVICEWATCHER_STATIC
        DEFINES += QT_QTMMLWIDGET_STATIC_LIBRARY
    }
}

################################################################
##build cache
################################################################
isEmpty(OBJECTS_DIR):OBJECTS_DIR = obj
isEmpty(MOC_DIR):MOC_DIR = obj/moc.cpp
isEmpty(UI_DIR):UI_DIR = obj/ui.h
isEmpty(RCC_DIR):RCC_DIR = qrc
isEmpty(DESTDIR):DESTDIR = bin

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
    #LibQQt used override identifier
    #lambda also need c++11
}

##################MultiMedia Module###############################
DEFINES += __MULTIMEDIA__
#mac no multimedia
contains(QKIT_PRIVATE, macOS) {
    lessThan(QT_MAJOR_VERSION, 5):DEFINES-=__MULTIMEDIA__
}
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

##################PrintSupport Module###############################
#if you use printsupport , open this annotation
DEFINES += __PRINTSUPPORT__
#Qt 5.9.1, ios and android can't support this feature, because Qt 5.9.1, broken
equals(QT_VERSION, 5.9.1) {
    contains(QKIT_PRIVATE, iOS||iOSSimulator||ANDROID||ANDROIDX86) {
        DEFINES -= __PRINTSUPPORT__
    }
}
#Qt 5.9.2, android support this feature
#Qt 5.9.2, ios can't use printsupport
contains(QKIT_PRIVATE, iOS||iOSSimulator) {
    DEFINES -= __PRINTSUPPORT__
}
contains (DEFINES, __PRINTSUPPORT__) {
    #qtHaveModule(printsupport) : message(qqt use module printsupport)
    greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
}

##################Exquisite Module###############################
#if you use Exquisite widgets, open this annotation
DEFINES += __EXQUISITE__
contains (DEFINES, __EXQUISITE__) {
    #if you use QR encode, open this annotation
    DEFINES += __QRENCODE__
    #if you use QR decode, open this annotation
    #QZXing isnan_z function error. fixed
    #QZxing delegating constructors used. need c++11,but qt4.8.7 dont support c++11
    #DEFINES += __QRDECODE__
    contains(DEFINES, __QRDECODE__) {
        #lessThan(QT_MAJOR_VERSION, 5): QT += declarative
        greaterThan(QT_MAJOR_VERSION, 4): QT += quick
    }
    #if you use Svg widgets, open this annotation
    DEFINES += __SVGWIDGETS__
    contains(QKIT_PRIVATE, macOS) {
        lessThan(QT_MAJOR_VERSION, 5):DEFINES-=__SVGWIDGETS__
    }
    contains (DEFINES, __SVGWIDGETS__) {
        QT += svg
    }
    #Gumbo need std support
    QMAKE_CFLAGS += -std=c99
    #c++ html parser query
    #if you use Gumbo parser query, open this annotation
    DEFINES += __GUMBOSUPPORT__
}
##################WebSocket Module###############################
#don't close this macro ...
DEFINES += __TCPUDPSOCKET__
#if you use Qt Service Support ( QtSoap ), open this annotation
DEFINES += __WEBSERVICESUPPORT__
#One Ftp Http 单工...
#Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
#if you use QNetworkAccessManagerSupport , open this annotation
DEFINES += __WEBACCESSSUPPORT__
lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __WEBACCESSSUPPORT__
contains (DEFINES, __WEBACCESSSUPPORT__) {
    #QSslError not found, you need recompiler Qt4
}
DEFINES += __WEBKITSUPPORT__
contains (DEFINES, __WEBKITSUPPORT__) {
    #TODO: QT += webkit
}
DEFINES += __WEBENGINESUPPORT__
contains (DEFINES, __WEBENGINESUPPORT__) {
}

#Multi New Protocol 全双工 QWebSocket
#if you use QWebSocketSupport , open this annotation
DEFINES += __WEBSOCKETSUPPORT__
#equals(QKIT_PRIVATE, macOS):DEFINES += __WEBSOCKETSUPPORT__
lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __WEBSOCKETSUPPORT__
contains (DEFINES, __WEBSOCKETSUPPORT__) {
    QT += websockets
    #QSslError not found, you need recompiler Qt4
    #TODO: QT += webkit
}

##################Charts Module###############################
#if you use QQtCharts, open this annotation
DEFINES += __QQTCHARTS__
lessThan(QT_MAJOR_VERSION, 5):DEFINES-=__QQTCHARTS__
contains(QKIT_PRIVATE, ARM32||MIPS32||EMBEDDED):DEFINES-=__QQTCHARTS__
#based on QtCharts, need charts module
contains(DEFINES, __QQTCHARTS__) {
    QT += charts
}
#if you use qcustomplot, open this annotation
#qcustomplot use QPrinter to export pdf file, QChart haven't use it, but compiler ok.
#in ios qcustomplot can't call savePdf now, no result but a log no printer error.
DEFINES += __CUSTOMPLOT__

##################Mathes Module###############################
DEFINES += __MATHSUPPORT__

##################QQtLogFile Module###############################
DEFINES += __QQTLOGFILESUPPORT__

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
defineReplace(qqt_header){
    path = $$1
    isEmpty(1) : error("qqt_header(path) requires one arguments.")
    command += $${path}
    command += $${path}/core
    command += $${path}/customplot
    command += $${path}/frame
    command += $${path}/frame/dmmu
    command += $${path}/gui
    command += $${path}/multimedia
    command += $${path}/network
    command += $${path}/network/qextserialport
    command += $${path}/network/soap
    command += $${path}/pluginwatcher
    command += $${path}/printsupport
    command += $${path}/sql
    command += $${path}/widgets
    command += $${path}/charts

    #exquisite widget
    command += $${path}/exquisite
    command += $${path}/exquisite/svgwidgets

    ##qr code library
    command += $${path}/exquisite/qrcode/qrencode
    command += $${path}/exquisite/qrcode/qrdecode
    command += $${path}/exquisite/qrcode/qrdecode/zxing
    win32-g++{
        command += $${path}/exquisite/qrcode/qrdecode/zxing/win32/zxing
    }
    win32-msvc*{
        command += $${path}/exquisite/qrcode/qrdecode/zxing/win32/zxing \
                    $${path}/exquisite/qrcode/qrdecode/zxing/win32/zxing/msvc
    }

    ##gumbo library
    command += $${path}/exquisite/gumbo/parser/src
    command += $${path}/exquisite/gumbo/query/src
    win32{
        command += $${path}/exquisite/gumbo/parser/visualc/include
    }
    return ($$command)
}

INCLUDEPATH += $$qqt_header($$PWD)
