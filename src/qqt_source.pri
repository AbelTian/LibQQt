#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
#-------------------------------------------------
#QQt source
#Don't modify this pri
#FDLv1.3 GPLv3 LGPLv2.1 PreviewCommercial
#2017年10月29日09:16:41
#Project link: https://gitee.com/drabel/LibQt
#if you succeed with LibQQt, please thumb up.
#2017年11月10日18:53:56
#-------------------------------------------------
SOURCES +=
HEADERS +=


#root dir
HEADERS += $$PWD/qqt.h \
    $$PWD/qqt-local.h \
    $$PWD/qqtversion.h \
    $$PWD/qqt-qt.h
#platform header
contains (QKIT_PRIVATE, WIN32||WIN64) {
    #win32 base type
    HEADERS += $$PWD/qqtwin.h
} else:contains (QKIT_PRIVATE, macOS||iOS||iOSSimulator) {
    #mac base type
    HEADERS += $$PWD/qqtdarwin.h
} else:contains (QKIT_PRIVATE, ANDROID||ANDROIDX86) {
    #android base type
    HEADERS += $$PWD/qqtandroid.h
} else {
    #linux base type
    HEADERS += $$PWD/qqtlinux.h
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

#sql
SOURCES += $$PWD/sql/qqtsql.cpp
HEADERS += $$PWD/sql/qqtsql.h

#gui
SOURCES += \
    $$PWD/gui/qqtftptreemodel.cpp \
    $$PWD/gui/qqtsqltreemodel.cpp \
    $$PWD/gui/qqttablemodel.cpp \
    $$PWD/gui/qqttreemodel.cpp \
    $$PWD/gui/qqtfilesystemtreemodel.cpp \
    $$PWD/gui/qqtjsontreemodel.cpp \
    $$PWD/gui/qqtxmltreemodel.cpp

HEADERS += \
    $$PWD/gui/qqtftptreemodel.h \
    $$PWD/gui/qqtsqltreemodel.h \
    $$PWD/gui/qqttablemodel.h \
    $$PWD/gui/qqttreemodel.h \
    $$PWD/gui/qqtfilesystemtreemodel.h \
    $$PWD/gui/qqtjsontreemodel.h \
    $$PWD/gui/qqtxmltreemodel.h \
    $$PWD/gui/qqtgui.h

#widgets
SOURCES += \
    $$PWD/widgets/qqtcheckbox.cpp \
    $$PWD/widgets/qqtheaderview.cpp \
    $$PWD/widgets/qqtlistview.cpp \
    $$PWD/widgets/qqtprogressbar.cpp \
    $$PWD/widgets/qqtpushbutton.cpp \
    $$PWD/widgets/qqtradiobutton.cpp \
    $$PWD/widgets/qqttableview.cpp \
    $$PWD/widgets/qqttabbar.cpp \
    $$PWD/widgets/qqttabwidget.cpp \
    $$PWD/widgets/qqttreeview.cpp \
    $$PWD/widgets/qqtlineeditwithsearch.cpp \
    $$PWD/widgets/qqtmptablewidget.cpp \
    $$PWD/widgets/qqttablewidget.cpp \
    $$PWD/widgets/qqtgraphicsscene.cpp \
    $$PWD/widgets/qqtgraphicsitem.cpp \
    $$PWD/widgets/qqtgraphicsview.cpp \
    $$PWD/widgets/qqttreewidget.cpp \
    $$PWD/widgets/qqtwidget.cpp \
    $$PWD/widgets/qqtwidgets.cpp \
    $$PWD/widgets/qqtlabel.cpp
HEADERS += \
    $$PWD/widgets/qqtcheckbox.h \
    $$PWD/widgets/qqtheaderview.h \
    $$PWD/widgets/qqtlistview.h \
    $$PWD/widgets/qqtprogressbar.h \
    $$PWD/widgets/qqtpushbutton.h \
    $$PWD/widgets/qqtradiobutton.h \
    $$PWD/widgets/qqttableview.h \
    $$PWD/widgets/qqttabbar.h \
    $$PWD/widgets/qqttabwidget.h \
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
    $$PWD/widgets/qqtapplication.h \
    $$PWD/widgets/qqtlabel.h
FORMS += \
    $$PWD/widgets/qqtprogressbar.ui \
    $$PWD/widgets/qqtmptablewidget.ui

DEFINES += __PROCESSMODULE__
#ios has no backend process
contains(QKIT_PRIVATE, iOS||iOSSimulator) {
    DEFINES -= __PROCESSMODULE__
}


#multimedia
#arm mips
#TODO: +wince +android +ios +macOS +win +linux
contains (DEFINES, __MULTIMEDIA__) {
    contains (DEFINES, __PROCESSMODULE__){
        SOURCES += $$PWD/multimedia/qqtmplayer.cpp
        HEADERS += $$PWD/multimedia/qqtmplayer.h
    }
}

#pluginwatcher
#TODO: macOS dump
contains(DEFINES, __PLUGINWATCHER__) {
    contains(QKIT_PRIVATE, WIN32|WIN64) {
        contains (DEFINES, QQT_LIBRARY) {
            DEFINES += BUILD_QDEVICEWATCHER_LIB
        } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
            DEFINES += BUILD_QDEVICEWATCHER_STATIC
        }
        wince*: SOURCES += $$PWD/pluginwatcher/qdevicewatcher_wince.cpp
        else:  SOURCES += $$PWD/pluginwatcher/qdevicewatcher_win32.cpp
    }else:contains(QKIT_PRIVATE, macOS) {
        SOURCES += $$PWD/pluginwatcher/qdevicewatcher_mac.cpp
    }else {
        SOURCES += $$PWD/pluginwatcher/qdevicewatcher_linux.cpp
    }
    SOURCES += $$PWD/pluginwatcher/qdevicewatcher.cpp \
                $$PWD/pluginwatcher/qqtpluginwatcher.cpp
    HEADERS += $$PWD/pluginwatcher/qqtpluginwatcher.h \
                $$PWD/pluginwatcher/qdevicewatcher.h \
                $$PWD/pluginwatcher/qdevicewatcher_p.h
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

    #customplot
    #need print support
    #DEFINES += __CUSTOMPLOT__
    contains (DEFINES, __CUSTOMPLOT__) {
        #message (qcustomplot is used in $${TARGET})
        win32 {
            contains (DEFINES, QQT_LIBRARY) {
                DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY
            } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
                #build static library - customplot
                DEFINES += QCUSTOMPLOT_STATIC_LIBRARY
            }
        }
        SOURCES += $$PWD/customplot/qcpdocumentobject.cpp \
                    $$PWD/customplot/qcustomplot.cpp
        HEADERS += $$PWD/customplot/qcpdocumentobject.h \
                    $$PWD/customplot/qcustomplot.h
    }
}

#network
#udpsocket
SOURCES += \
    $$PWD/network/qqtudpclient.cpp \
    $$PWD/network/qqtudpserver.cpp
HEADERS += \
    $$PWD/network/qqtudpclient.h \
    $$PWD/network/qqtudpserver.h
#tcpsocket
SOURCES += \
    $$PWD/network/qqtclient.cpp \
    $$PWD/network/qqtserver.cpp \
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
#ethnet(+wifi) manager
#arm mips
#TODO: +wince +android +ios +macOS? +win? +linux?
equals(QKIT_PRIVATE, EMBEDDED) {
    SOURCES += $$PWD/network/qqtethenetmanager.cpp
    HEADERS += $$PWD/network/qqtethenetmanager.h
    SOURCES += $$PWD/frame/qqtwifiwidget.cpp
    HEADERS += $$PWD/frame/qqtwifiwidget.h
    FORMS += $$PWD/frame/qqtwifiwidget.ui
}
##webservice
contains(DEFINES, __WEBSERVICESUPPORT__) {
    win32 {
        contains (DEFINES, QQT_LIBRARY) {
            DEFINES += QT_QTSOAP_LIBRARY
        } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
            DEFINES += QT_QTSOAP_STATIC_LIBRARY
        }
    }
    SOURCES += \
        $$PWD/network/soap/qtsoap.cpp
    HEADERS += \
        $$PWD/network/soap/qtsoap.h
}
contains (DEFINES, __WEBWORKSUPPORT__) {
    SOURCES += \
        $$PWD/network/qqtftpprotocol.cpp \
        $$PWD/network/qqthttpprotocol.cpp \
        $$PWD/network/qqtwebprotocol.cpp
    HEADERS += \
        $$PWD/network/qqtftpprotocol.h \
        $$PWD/network/qqthttpprotocol.h \
        $$PWD/network/qqtwebprotocol.h
    SOURCES += \
        $$PWD/network/qqtwebworkclient.cpp \
        $$PWD/network/qqtwebworkserver.cpp
    HEADERS += \
        $$PWD/network/qqtwebworkclient.h \
        $$PWD/network/qqtwebworkserver.h
}
contains (DEFINES, __WEBSOCKETSUPPORT__) {
    SOURCES += \
        $$PWD/network/qqtwebclient.cpp \
        $$PWD/network/qqtwebserver.cpp
    HEADERS += \
        $$PWD/network/qqtwebclient.h \
        $$PWD/network/qqtwebserver.h
}


#dmmu preview
#arm mips
#TODO: +wince +android +ios +macOS +win +linux
equals(QKIT_PRIVATE, EMBEDDED) {
    SOURCES += $$PWD/frame/dmmu/dmmu.c
    HEADERS += $$PWD/frame/dmmu/dmmu.h \
                $$PWD/frame/dmmu/jz_cim.h \
                $$PWD/frame/dmmu/graphics.h \
                $$PWD/frame/dmmu/hal.h
    SOURCES += $$PWD/frame/qqtpreviewwidget.cpp
    HEADERS += $$PWD/frame/qqtpreviewwidget.h
    FORMS += $$PWD/frame/qqtpreviewwidget.ui
}

#frame
SOURCES += \
    $$PWD/frame/qqtwifidbwidget.cpp
HEADERS += \
    $$PWD/frame/qqtwifidbwidget.h
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
    $$PWD/frame/qqtinput.ui \
    $$PWD/frame/qqtmsgbox.ui


contains (DEFINES, __EXQUISITE__) {
    #exquisite
    SOURCES += \
        $$PWD/exquisite/qqtninepatcheffectwidget.cpp \
        $$PWD/exquisite/qqtcustompianokeyboard.cpp \
        $$PWD/exquisite/qqtrippleeffectpushbutton.cpp \
        $$PWD/exquisite/qqtrulereffectslider.cpp \
        $$PWD/exquisite/qqtcustomverificationcode.cpp \
        $$PWD/exquisite/qqtframelesshelper.cpp \
        $$PWD/exquisite/qqtframelesshelperprivate.cpp \
        $$PWD/exquisite/qqtflipeffectstackedwidget.cpp \
        $$PWD/exquisite/qqtfadeeffectwidget.cpp \
        $$PWD/exquisite/qqtshadoweffectwidget.cpp \
        $$PWD/exquisite/qqtpopeffectdialog.cpp
    HEADERS += \
        $$PWD/exquisite/qqtninepatcheffectwidget.h \
        $$PWD/exquisite/qqtframelesshelper.h \
        $$PWD/exquisite/qqtframelesshelperprivate.h \
        $$PWD/exquisite/qqtcustompianokeyboard.h \
        $$PWD/exquisite/qqtrippleeffectpushbutton.h \
        $$PWD/exquisite/qqtrulereffectslider.h \
        $$PWD/exquisite/qqtflipeffectstackedwidget.h \
        $$PWD/exquisite/qqtcustomverificationcode.h \
        $$PWD/exquisite/qqtfadeeffectwidget.h \
        $$PWD/exquisite/qqtshadoweffectwidget.h \
        $$PWD/exquisite/qqtpopeffectdialog.h

    #progressbar
    SOURCES += \
        $$PWD/exquisite/qqtcustomspeedmeter.cpp \
        $$PWD/exquisite/qqtcustomeffectprogressbar.cpp
    HEADERS += \
        $$PWD/exquisite/qqtcustomspeedmeter.h \
        $$PWD/exquisite/qqtcustomeffectprogressbar.h

    #label
    SOURCES += \
        $$PWD/exquisite/qqtledbannereffectlabel.cpp \
        $$PWD/exquisite/qqtmarqueeeffectlabel.cpp
    HEADERS += \
        $$PWD/exquisite/qqtmarqueeeffectlabel.h \
        $$PWD/exquisite/qqtledbannereffectlabel.h

    #tabwidget
    SOURCES += \
        $$PWD/exquisite/qqthorizontaltexteffecttabbar.cpp \
        $$PWD/exquisite/qqthorizontaltexteffecttabwidget.cpp \
        $$PWD/exquisite/qqtpictureeffecttabbar.cpp \
        $$PWD/exquisite/qqtpictureeffecttabwidget.cpp \
        $$PWD/exquisite/qqtslideeffecttabbar.cpp \
        $$PWD/exquisite/qqtslideeffecttabwidget.cpp
    HEADERS += \
        $$PWD/exquisite/qqthorizontaltexteffecttabbar.h \
        $$PWD/exquisite/qqthorizontaltexteffecttabwidget.h \
        $$PWD/exquisite/qqtpictureeffecttabbar.h \
        $$PWD/exquisite/qqtpictureeffecttabwidget.h \
        $$PWD/exquisite/qqtslideeffecttabbar.h \
        $$PWD/exquisite/qqtslideeffecttabwidget.h

    #svg widgets
    contains (DEFINES, __SVGWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/svgwidgets/qqtsvgwidget.cpp \
            $$PWD/exquisite/svgwidgets/qqtsvgpushbutton.cpp \
            $$PWD/exquisite/svgwidgets/qqtsvgcheckbox.cpp \
            $$PWD/exquisite/svgwidgets/qqtsvgradiobutton.cpp \
            $$PWD/exquisite/svgwidgets/qqtgraphicssvgitem.cpp \
            $$PWD/exquisite/svgwidgets/qqtsvglabel.cpp \
            $$PWD/exquisite/svgwidgets/qqtsvgprogressbar.cpp
        HEADERS += \
            $$PWD/exquisite/svgwidgets/qqtsvgwidget.h \
            $$PWD/exquisite/svgwidgets/qqtsvgpushbutton.h \
            $$PWD/exquisite/svgwidgets/qqtsvgcheckbox.h \
            $$PWD/exquisite/svgwidgets/qqtsvgradiobutton.h \
            $$PWD/exquisite/svgwidgets/qqtgraphicssvgitem.h \
            $$PWD/exquisite/svgwidgets/qqtsvglabel.h \
            $$PWD/exquisite/svgwidgets/qqtsvgprogressbar.h
    }
}

include ($$PWD/qqt_3rdparty.pri)
