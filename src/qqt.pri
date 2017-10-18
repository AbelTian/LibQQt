#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

#############
##project version
#############
unix:VERSION            = 1.0.0

##Qt version
QT += core gui network sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

#############
##definition
#############
##Arch type
QT_KIT = $$(QKIT)
message($${QT_KIT} Defined in $${TARGET})
#MIPS __MIPS_LINUX__
#ARM __ARM_LINUX__
#LINUX __LINUX__
#LINUX64 __LINUX64__
#WIN __WIN__
#WIN64 __WIN64__
#macOS __DARWIN__
#Android __ANDROID__
#处理文件内平台小差异
equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else:equals(QT_KIT, LINUX) {
    DEFINES += __LINUX__
} else:equals(QT_KIT, LINUX64) {
    DEFINES += __LINUX__
    DEFINES += __LINUX64__
} else:equals(QT_KIT, WIN) {
    DEFINES += __WIN__
} else:equals(QT_KIT, WIN64) {
    DEFINES += __WIN__
    DEFINES += __WIN64__
} else:equals(QT_KIT, macOS) {
    DEFINES += __DARWIN__
} else:equals(QT_KIT, Android) {
    DEFINES += __ANDROID__
} else:equals(QT_KIT, ANDROIDX86) {
    DEFINES += __ANDROID__
    DEFINES += __ANDROIDX86__
    #todo:no customplot word printer
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}
win32 {
    win32:DEFINES += _CRT_SECURE_NO_WARNINGS #fopen fopen_s
    QMAKE_CXXFLAGS += /wd"4819" /wd"4244" /wd"4100"
}

#############
##libraries
#############
win32 {
    LIBS += -luser32
}else: unix {
    equals(QT_KIT, macOS) {
        #min macosx target
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
        #deperated
        #QMAKE_MAC_SDK=macosx10.12
        #MACOSXSDK = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX$${QMAKE_MACOSX_DEPLOYMENT_TARGET}.sdk
        #QMAKE_LIBDIR = $${MACOSXSDK}
        #LIBS += -F$${MACOSXSDK}/System/Library/Frameworks
        #LIBS += -L$${MACOSXSDK}/usr/lib
        LIBS += -framework DiskArbitration -framework Cocoa -framework IOKit
    } else {
    }
}

############
##build cache
############
OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
DESTDIR = bin

###########################
##include directories
###########################
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/core
INCLUDEPATH += $$PWD/customplot
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

SOURCES =
HEADERS =

#root dir
win32 {
    #win32 base type
    HEADERS += $$PWD/qqtwin.h
}
unix {
    equals(QT_KIT, macOS) {
        HEADERS += $$PWD/qqtdarwin.h
    } else {
        HEADERS += $$PWD/qqtlinux.h
    }
}
HEADERS += $$PWD/qqt.h \
    $$PWD/qqtversion.h \
    $$PWD/qqt-local.h \
    $$PWD/qqt-qt.h


#network
##websocket
SOURCES += $$PWD/network/qqtwebclient.cpp \
    $$PWD/network/qqtftpprotocol.cpp \
    $$PWD/network/qqthttpprotocol.cpp \
    $$PWD/network/qqtwebprotocol.cpp
HEADERS += $$PWD/network/qqtwebclient.h \
    $$PWD/network/qqtftpprotocol.h \
    $$PWD/network/qqthttpprotocol.h \
    $$PWD/network/qqtwebprotocol.h
#tcpsocket
SOURCES += \
    $$PWD/network/qqtclient.cpp \
    $$PWD/network/qqtserver.cpp \
    $$PWD/network/qqtmessage.cpp \
    $$PWD/network/qqtprotocol.cpp \
    $$PWD/network/qqtnetwork.cpp
HEADERS += \
    $$PWD/network/qqtclient.h \
    $$PWD/network/qqtserver.h \
    $$PWD/network/qqtmessage.h \
    $$PWD/network/qqtprotocol.h \
    $$PWD/network/qqtnetwork.h
#serialport
SOURCES += \
    $$PWD/network/qqtserialport.cpp
HEADERS += \
    $$PWD/network/qqtserialport.h
#bluetooth
DEFINES += __BLUETOOTH__
contains (DEFINES, __BLUETOOTH__) {
    greaterThan(QT_MAJOR_VERSION, 4): QT += bluetooth
    #bluetooth socket
    SOURCES += \
        $$PWD/network/qqtbluetoothclient.cpp \
        $$PWD/network/qqtbluetoothserver.cpp
    HEADERS += \
        $$PWD/network/qqtbluetoothclient.h \
        $$PWD/network/qqtbluetoothserver.h
    #bluetooth manager
    SOURCES += \
        $$PWD/network/qqtbluetoothmanager.cpp
    HEADERS += \
        $$PWD/network/qqtbluetoothmanager.h
}
#ethnet manager
equals(QT_KIT, MIPS32) {
    SOURCES += $$PWD/network/qqtethenetmanager.cpp
    HEADERS += $$PWD/network/qqtethenetmanager.h
}
#qextserialport support
#if you use qextserialport, open the two annotation
#DEFINES += __QTEXTSERIALPORT__
contains (DEFINES, __QTEXTSERIALPORT__) {
    #include ( $$PWD/network/qextserialport/qextserialport.pri )
    #message ( __QTEXTSERIALPORT__ Defined in $${TARGET})
} else {
    greaterThan(QT_MAJOR_VERSION, 4): QT += serialport
    lessThan(QT_MAJOR_VERSION, 5): CONFIG += serialport
    unix {
        DEFINES += _TTY_POSIX_
    } else {
        DEFINES += _TTY_WIN_
    }
}



#core
SOURCES += \
    $$PWD/core/qqtcore.cpp \
    $$PWD/core/qqtanimation.cpp \
    $$PWD/core/qqtobjectfactory.cpp \
    $$PWD/widgets/qqtapplication.cpp
HEADERS += \
    $$PWD/core/qqtcore.h \
    $$PWD/core/qqtanimation.h \
    $$PWD/core/qqtobjectfactory.h


#customplot
contains (DEFINES, QQT_LIBRARY) {
	DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY
}
SOURCES += $$PWD/customplot/qcpdocumentobject.cpp \
			$$PWD/customplot/qcustomplot.cpp
HEADERS += $$PWD/customplot/qcpdocumentobject.h \
			$$PWD/customplot/qcustomplot.h
equals(QT_KIT, Android) {
    SOURCES -= $$PWD/customplot/qcpdocumentobject.cpp \
                            $$PWD/customplot/qcustomplot.cpp
    HEADERS -= $$PWD/customplot/qcpdocumentobject.h \
                            $$PWD/customplot/qcustomplot.h
}



#dmmu
equals(QT_KIT, MIPS32) {
    SOURCES += $$PWD/dmmu/dmmu.c
    HEADERS += $$PWD/dmmu/dmmu.h \
                $$PWD/dmmu/jz_cim.h \
                $$PWD/dmmu/graphics.h \
                $$PWD/dmmu/hal.h
}


#frame
equals(QT_KIT, MIPS32) {
    SOURCES += $$PWD/frame/qqtpreviewwidget.cpp \
                $$PWD/frame/qqtwifiwidget.cpp
    HEADERS += $$PWD/frame/qqtpreviewwidget.h \
                $$PWD/frame/qqtwifiwidget.h
    FORMS += $$PWD/frame/qqtpreviewwidget.ui \
                $$PWD/frame/qqtwifiwidget.ui
}
SOURCES += \
    $$PWD/frame/qqtprogressdialog.cpp \
    $$PWD/frame/qqtpassworddialog.cpp \
    $$PWD/frame/qqtframe.cpp \
    $$PWD/frame/qqtdialog.cpp \
    $$PWD/frame/qqtmsgbox.cpp \
    $$PWD/frame/qqtinput.cpp \
    $$PWD/frame/qqtword.cpp
HEADERS += \
    $$PWD/frame/qqtprogressdialog.h \
    $$PWD/frame/qqtpassworddialog.h \
    $$PWD/frame/qqtframe.h \
    $$PWD/frame/qqtdialog.h \
    $$PWD/frame/qqtmsgbox.h \
    $$PWD/frame/qqtinput.h \
    $$PWD/frame/qqtword.h
FORMS += \
    $$PWD/frame/qqtprogressdialog.ui \
    $$PWD/frame/qqtpassworddialog.ui \
    $$PWD/frame/qqtdialog.ui \
    $$PWD/frame/qqtinput.ui \
    $$PWD/frame/qqtmsgbox.ui
equals(QT_KIT, Android) {
    SOURCES -= $$PWD/frame/qqtword.cpp
    HEADERS -= $$PWD/frame/qqtword.h
}


#gui
SOURCES += \
    $$PWD/gui/qqtftptreemodel.cpp \
    $$PWD/gui/qqtsqltreemodel.cpp \
    $$PWD/gui/qqttablemodel.cpp \
    $$PWD/gui/qqttreemodel.cpp \
    $$PWD/gui/qqtxmltreemodel.cpp

HEADERS += \
    $$PWD/gui/qqtftptreemodel.h \
    $$PWD/gui/qqtsqltreemodel.h \
    $$PWD/gui/qqttablemodel.h \
    $$PWD/gui/qqttreemodel.h \
    $$PWD/gui/qqtxmltreemodel.h \
    $$PWD/gui/qqtgui.h


#multimedia
SOURCES += $$PWD/multimedia/qqtmplayer.cpp
HEADERS += $$PWD/multimedia/qqtmplayer.h

#pluginwatcher
contains (DEFINES, QQT_LIBRARY) {
    DEFINES += BUILD_QDEVICEWATCHER_LIB
}
win32 {
    wince*: SOURCES += $$PWD/pluginwatcher/qdevicewatcher_wince.cpp
    else:  SOURCES += $$PWD/pluginwatcher/qdevicewatcher_win32.cpp
}
unix {
    equals(QT_KIT, macOS) {
        SOURCES += $$PWD/pluginwatcher/qdevicewatcher_mac.cpp
    } else {
        SOURCES += $$PWD/pluginwatcher/qdevicewatcher_linux.cpp
    }
}
SOURCES += $$PWD/pluginwatcher/qdevicewatcher.cpp \
            $$PWD/pluginwatcher/qqtpluginwatcher.cpp
HEADERS += $$PWD/pluginwatcher/qqtpluginwatcher.h \
            $$PWD/pluginwatcher/qdevicewatcher.h \
            $$PWD/pluginwatcher/qdevicewatcher_p.h

#printsupport
SOURCES += $$PWD/printsupport/qqtprinter.cpp
HEADERS += $$PWD/printsupport/qqtprinter.h
equals(QT_KIT, Android) {
    SOURCES -= $$PWD/printsupport/qqtprinter.cpp
    HEADERS -= $$PWD/printsupport/qqtprinter.h
}

#sql
SOURCES += $$PWD/sql/qqtsql.cpp
HEADERS += $$PWD/sql/qqtsql.h


#widgets
SOURCES += \
    $$PWD/widgets/qqtcheckbox.cpp \
    $$PWD/widgets/qqtheaderview.cpp \
    $$PWD/widgets/qqtlistview.cpp \
    $$PWD/widgets/qqtprogressbar.cpp \
    $$PWD/widgets/qqtpushbutton.cpp \
    $$PWD/widgets/qqtradiobutton.cpp \
    $$PWD/widgets/qqttabbar.cpp \
    $$PWD/widgets/qqttableview.cpp \
    $$PWD/widgets/qqttabwidget.cpp \
    $$PWD/widgets/qqttabwidgetb.cpp \
    $$PWD/widgets/qqttreeview.cpp \
    $$PWD/widgets/qqtlineeditwithsearch.cpp \
    $$PWD/widgets/qqtmptablewidget.cpp \
    $$PWD/widgets/qqttablewidget.cpp \
    $$PWD/widgets/qqtgraphicsscene.cpp \
    $$PWD/widgets/qqtgraphicsitem.cpp \
    $$PWD/widgets/qqtgraphicsview.cpp \
    $$PWD/widgets/qqttreewidget.cpp \
    $$PWD/widgets/qqtwidget.cpp \
    $$PWD/widgets/qqtwidgets.cpp
HEADERS += \
    $$PWD/widgets/qqtcheckbox.h \
    $$PWD/widgets/qqtheaderview.h \
    $$PWD/widgets/qqtlistview.h \
    $$PWD/widgets/qqtprogressbar.h \
    $$PWD/widgets/qqtpushbutton.h \
    $$PWD/widgets/qqtradiobutton.h \
    $$PWD/widgets/qqttabbar.h \
    $$PWD/widgets/qqttableview.h \
    $$PWD/widgets/qqttabwidget.h \
    $$PWD/widgets/qqttabwidgetb.h \
    $$PWD/widgets/qqttreeview.h \
    $$PWD/widgets/qqtlineeditwithsearch.h \
    $$PWD/widgets/qqtmptablewidget.h \
    $$PWD/widgets/qqttablewidget.h \
    $$PWD/widgets/qqtgraphicsscene.h \
    $$PWD/widgets/qqtgraphicsitem.h \
    $$PWD/widgets/qqtgraphicsview.h \
    $$PWD/widgets/qqttreewidget.h \
    $$PWD/widgets/qqtwidget.h \
    $$PWD/widgets/qqtwidgets.h \
    $$PWD/widgets/qqtapplication.h
FORMS += \
    $$PWD/widgets/qqtcheckbox.ui \
    $$PWD/widgets/qqtlistview.ui \
    $$PWD/widgets/qqtprogressbar.ui \
    $$PWD/widgets/qqtpushbutton.ui \
    $$PWD/widgets/qqtradiobutton.ui \
    $$PWD/widgets/qqttableview.ui \
    $$PWD/widgets/qqttabwidget.ui \
    $$PWD/widgets/qqttabwidgetb.ui \
    $$PWD/widgets/qqttreeview.ui \
    $$PWD/widgets/qqtwidget.ui \
    $$PWD/widgets/qqttablewidget.ui \
    $$PWD/widgets/qqtmptablewidget.ui \
    $$PWD/widgets/qqttreewidget.ui
