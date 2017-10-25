#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

#############
##libraries
#############
win32 {
    LIBS += -luser32
}else: unix {
    equals(QKIT_, macOS) {
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

#exquisite
SOURCES = \
    $$PWD/exquisite/qqtcustomspeedmeter.cpp \
    $$PWD/exquisite/qqtframelesshelper.cpp \
    $$PWD/exquisite/qqtframelesshelperprivate.cpp \
    $$PWD/exquisite/qqtcustompianokeyboard.cpp \
    $$PWD/exquisite/qqtrippleeffectpushbutton.cpp \
    $$PWD/exquisite/qqtrulereffectslider.cpp \
    $$PWD/exquisite/qqtflipeffectstackedwidget.cpp \
    $$PWD/exquisite/qqtledbannereffectlabel.cpp \
    $$PWD/exquisite/qqtmarqueeeffectlabel.cpp \
    $$PWD/exquisite/qqtcustomverificationcode.cpp \
    $$PWD/exquisite/qqtfadeeffectwidget.cpp \
    $$PWD/exquisite/qqtshadoweffectwidget.cpp \
    $$PWD/exquisite/qqtpopeffectdialog.cpp \
    $$PWD/exquisite/qqtcustomeffectprogressbar.cpp \
    $$PWD/widgets/qqtlabel.cpp
HEADERS = \
    $$PWD/exquisite/qqtcustomspeedmeter.h \
    $$PWD/exquisite/qqtframelesshelper.h \
    $$PWD/exquisite/qqtframelesshelperprivate.h \
    $$PWD/exquisite/qqtcustompianokeyboard.h \
    $$PWD/exquisite/qqtrippleeffectpushbutton.h \
    $$PWD/exquisite/qqtrulereffectslider.h \
    $$PWD/exquisite/qqtflipeffectstackedwidget.h \
    $$PWD/exquisite/qqtmarqueeeffectlabel.h \
    $$PWD/exquisite/qqtledbannereffectlabel.h \
    $$PWD/exquisite/qqtcustomverificationcode.h \
    $$PWD/exquisite/qqtfadeeffectwidget.h \
    $$PWD/exquisite/qqtshadoweffectwidget.h \
    $$PWD/exquisite/qqtpopeffectdialog.h \
    $$PWD/exquisite/qqtcustomeffectprogressbar.h \
    $$PWD/widgets/qqtlabel.h

#qrcode
#DEFINES += __QRENCODE__
contains (DEFINES, __QRENCODE__) {
    HEADERS += \
        $$PWD/qrencode/bitstream.h \
        $$PWD/qrencode/config.h \
        $$PWD/qrencode/mask.h \
        $$PWD/qrencode/mmask.h \
        $$PWD/qrencode/mqrspec.h \
        $$PWD/qrencode/qrencode.h \
        $$PWD/qrencode/qrencode_inner.h \
        $$PWD/qrencode/qrinput.h \
        $$PWD/qrencode/qrspec.h \
        $$PWD/qrencode/rscode.h \
        $$PWD/qrencode/split.h

    SOURCES += \
        $$PWD/qrencode/bitstream.c \
        $$PWD/qrencode/mask.c \
        $$PWD/qrencode/mmask.c \
        $$PWD/qrencode/mqrspec.c \
        $$PWD/qrencode/qrencode.c \
        $$PWD/qrencode/qrinput.c \
        $$PWD/qrencode/qrspec.c \
        $$PWD/qrencode/rscode.c \
        $$PWD/qrencode/split.c

    HEADERS += \
        $$PWD/exquisite/qqtcustomqrencodewidget.h
    SOURCES += \
        $$PWD/exquisite/qqtcustomqrencodewidget.cpp
}

#root dir
win32 {
    #win32 base type
    HEADERS += $$PWD/qqtwin.h
}
unix {
    equals(QKIT_, macOS) {
        HEADERS += $$PWD/qqtdarwin.h
    } else {
        HEADERS += $$PWD/qqtlinux.h
    }
}
HEADERS += $$PWD/qqt.h \
    $$PWD/qqt-local.h \
    $$PWD/qqtversion.h \
    $$PWD/qqt-qt.h

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


#network
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
##websocket
contains (DEFINES, __WEBSOCKETSUPPORT__) {
    SOURCES += $$PWD/network/qqtwebclient.cpp \
        $$PWD/network/qqtftpprotocol.cpp \
        $$PWD/network/qqthttpprotocol.cpp \
        $$PWD/network/qqtwebprotocol.cpp
    HEADERS += $$PWD/network/qqtwebclient.h \
        $$PWD/network/qqtftpprotocol.h \
        $$PWD/network/qqthttpprotocol.h \
        $$PWD/network/qqtwebprotocol.h
}
#bluetooth
#DEFINES += __BLUETOOTH__
contains (DEFINES, __BLUETOOTH__) {
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
#serialport
SOURCES += \
    $$PWD/network/qqtserialport.cpp
HEADERS += \
    $$PWD/network/qqtserialport.h
#qextserialport support
#if you use qextserialport, open the two annotation
#DEFINES += __QEXTSERIALPORT__
contains (DEFINES, __QEXTSERIALPORT__) {
    #include ( $$PWD/network/qextserialport/qextserialport.pri )
    HEADERS += $$PWD/network/qextserialport/qextserialbase.h \
              $$PWD/network/qextserialport/qextserialport.h \
              $$PWD/network/qextserialport/qextserialenumerator.h
    SOURCES += $$PWD/network/qextserialport/qextserialbase.cpp \
              $$PWD/network/qextserialport/qextserialport.cpp \
              $$PWD/network/qextserialport/qextserialenumerator.cpp
    unix:HEADERS += $$PWD/network/qextserialport/posix_qextserialport.h
    unix:SOURCES += $$PWD/network/qextserialport/posix_qextserialport.cpp
    win32:HEADERS += $$PWD/network/qextserialport/win_qextserialport.h
    win32:SOURCES += $$PWD/network/qextserialport/win_qextserialport.cpp
}

#ethnet(+wifi) manager
#arm mips
#TODO: +wince +android +ios +macOS? +win? +linux?
equals(QKIT_, EMBEDDED) {
    SOURCES += $$PWD/network/qqtethenetmanager.cpp
    HEADERS += $$PWD/network/qqtethenetmanager.h
    SOURCES += $$PWD/frame/qqtwifiwidget.cpp
    HEADERS += $$PWD/frame/qqtwifiwidget.h
    FORMS += $$PWD/frame/qqtwifiwidget.ui
}

#dmmu preview
#arm mips
#TODO: +wince +android +ios +macOS +win +linux
equals(QKIT_, EMBEDDED) {
    SOURCES += $$PWD/dmmu/dmmu.c
    HEADERS += $$PWD/dmmu/dmmu.h \
                $$PWD/dmmu/jz_cim.h \
                $$PWD/dmmu/graphics.h \
                $$PWD/dmmu/hal.h
    SOURCES += $$PWD/frame/qqtpreviewwidget.cpp
    HEADERS += $$PWD/frame/qqtpreviewwidget.h
    FORMS += $$PWD/frame/qqtpreviewwidget.ui
}

#customplot
#need print support
#DEFINES += __CUSTOMPLOT__
contains (DEFINES, __CUSTOMPLOT__) {
    message (qcustomplot is used in $${TARGET})
    contains (DEFINES, QQT_LIBRARY) {
        DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY
    }
    SOURCES += $$PWD/customplot/qcpdocumentobject.cpp \
                $$PWD/customplot/qcustomplot.cpp
    HEADERS += $$PWD/customplot/qcpdocumentobject.h \
                $$PWD/customplot/qcustomplot.h
}
#printsupport
#DEFINES += __PRINTSUPPORT__
contains (DEFINES, __PRINTSUPPORT__) {
    SOURCES += $$PWD/printsupport/qqtprinter.cpp
    HEADERS += $$PWD/printsupport/qqtprinter.h
    SOURCES += \
        $$PWD/frame/qqtword.cpp
    HEADERS += \
        $$PWD/frame/qqtword.h
}
#frame
SOURCES += \
    $$PWD/frame/qqtprogressdialog.cpp \
    $$PWD/frame/qqtpassworddialog.cpp \
    $$PWD/frame/qqtframe.cpp \
    $$PWD/frame/qqtdialog.cpp \
    $$PWD/frame/qqtmsgbox.cpp \
    $$PWD/frame/qqtinput.cpp
HEADERS += \
    $$PWD/frame/qqtprogressdialog.h \
    $$PWD/frame/qqtpassworddialog.h \
    $$PWD/frame/qqtframe.h \
    $$PWD/frame/qqtdialog.h \
    $$PWD/frame/qqtmsgbox.h \
    $$PWD/frame/qqtinput.h
FORMS += \
    $$PWD/frame/qqtprogressdialog.ui \
    $$PWD/frame/qqtpassworddialog.ui \
    $$PWD/frame/qqtdialog.ui \
    $$PWD/frame/qqtinput.ui \
    $$PWD/frame/qqtmsgbox.ui


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
#arm mips
#TODO: +wince +android +ios +macOS +win +linux
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
    mac* {
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
