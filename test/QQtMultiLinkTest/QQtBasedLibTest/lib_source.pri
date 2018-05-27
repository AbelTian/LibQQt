#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
#-------------------------------------------------
#QQt source
#Don't modify this pri
#FDLv1.3 GPLv3 LGPLv2.1 PreviewCommercial

#Project link: https://gitee.com/drabel/LibQQt
#if you succeed with LibQQt, please thumb up.
#这里是LibQQt源文件pri，所有开关宏都在LibQQt头文件pri里开关。

#-------------------------------------------------
#root dir
HEADERS += $$PWD/qqt.h \
    $$PWD/qqt-local.h \
    $$PWD/qqtversion.h \
    $$PWD/qqt-qt.h
#platform header
contains (QKIT_PRIVATE, WIN32||WIN64) {
    #win32 base header
    HEADERS += $$PWD/qqtwin.h
} else:contains (QKIT_PRIVATE, macOS||iOS||iOSSimulator) {
    #mac base header
    HEADERS += $$PWD/qqtdarwin.h
} else:contains (QKIT_PRIVATE, ANDROID||ANDROIDX86) {
    #android base header
    HEADERS += $$PWD/qqtandroid.h
} else {
    #linux base header
    HEADERS += $$PWD/qqtlinux.h
}

#core
SOURCES += \
    $$PWD/core/qqtcore.cpp \
    $$PWD/core/qqtevent.cpp \
    $$PWD/core/qqtdictionary.cpp \
    $$PWD/core/qqtobjectmanager.cpp
HEADERS += \
    $$PWD/core/qqtcore.h \
    $$PWD/core/qqtevent.h \
    $$PWD/core/qqtdictionary.h \
    $$PWD/core/qqtobjectmanager.h

#后台进程支持，这个只有ios不支持，这个支持在源文件pri里处理。
DEFINES += __PROCESSMODULE__
#ios has no backend process
contains(QKIT_PRIVATE, iOS||iOSSimulator) {
    DEFINES -= __PROCESSMODULE__
}

#sql
SOURCES += \
    $$PWD/sql/qqtsql.cpp
HEADERS += \
    $$PWD/sql/qqtsql.h
SOURCES += \
    $$PWD/sql/qqtsqlquery.cpp
HEADERS += \
    $$PWD/sql/qqtsqlquery.h

#gui
SOURCES += \
    $$PWD/gui/qqttablemodel.cpp \
    $$PWD/gui/qqtdicttreemodel.cpp \
    $$PWD/gui/qqttreemodel.cpp \
    $$PWD/gui/qqtftptreemodel.cpp \
    $$PWD/gui/qqtsqltreemodel.cpp \
    $$PWD/gui/qqtjsontreemodel.cpp \
    $$PWD/gui/qqtxmltreemodel.cpp \
    $$PWD/gui/qqtfilesystemtreemodel.cpp

HEADERS += \
    $$PWD/gui/qqttablemodel.h \
    $$PWD/gui/qqttreemodel.h \
    $$PWD/gui/qqtdicttreemodel.h \
    $$PWD/gui/qqtftptreemodel.h \
    $$PWD/gui/qqtsqltreemodel.h \
    $$PWD/gui/qqtjsontreemodel.h \
    $$PWD/gui/qqtxmltreemodel.h \
    $$PWD/gui/qqtfilesystemtreemodel.h \
    $$PWD/gui/qqtgui.h

#widgets
SOURCES += \
    $$PWD/widgets/qqtspinbox.cpp \
    $$PWD/widgets/qqtdoublespinbox.cpp \
    $$PWD/widgets/qqtdateedit.cpp \
    $$PWD/widgets/qqttimeedit.cpp \
    $$PWD/widgets/qqtdatetimeedit.cpp
HEADERS += \
    $$PWD/widgets/qqtspinbox.h \
    $$PWD/widgets/qqtdoublespinbox.h \
    $$PWD/widgets/qqtdateedit.h \
    $$PWD/widgets/qqttimeedit.h \
    $$PWD/widgets/qqtdatetimeedit.h

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
    $$PWD/widgets/qqttablewidget.h \
    $$PWD/widgets/qqtgraphicsscene.h \
    $$PWD/widgets/qqtgraphicsitem.h \
    $$PWD/widgets/qqtgraphicsview.h \
    $$PWD/widgets/qqttreewidget.h \
    $$PWD/widgets/qqtwidget.h \
    $$PWD/widgets/qqtwidgets.h \
    $$PWD/widgets/qqtlabel.h
FORMS += \
    $$PWD/widgets/qqtprogressbar.ui

#frame
SOURCES += \
    $$PWD/frame/qqtsysteminfo.cpp
HEADERS += \
    $$PWD/frame/qqtsysteminfo.h

SOURCES += \
    $$PWD/frame/qqtlineeditwithsearch.cpp \
    $$PWD/frame/qqtosdwidget.cpp
HEADERS += \
    $$PWD/frame/qqtlineeditwithsearch.h \
    $$PWD/frame/qqtosdwidget.h

SOURCES += \
    $$PWD/frame/qqtmultipagetablewidget.cpp
HEADERS += \
    $$PWD/frame/qqtmultipagetablewidget.h
FORMS += \
    $$PWD/frame/qqtmultipagetablewidget.ui

SOURCES += \
    $$PWD/frame/qqtanimation.cpp \
    $$PWD/frame/qqtapplication.cpp \
    $$PWD/frame/qqtwifidbwidget.cpp \
    $$PWD/frame/qqtprogressdialog.cpp \
    $$PWD/frame/qqtpassworddialog.cpp \
    $$PWD/frame/qqtframe.cpp \
    $$PWD/frame/qqtdialog.cpp \
    $$PWD/frame/qqtinput.cpp \
    $$PWD/frame/qqtmsgbox.cpp
HEADERS += \
    $$PWD/frame/qqtanimation.h \
    $$PWD/frame/qqtapplication.h \
    $$PWD/frame/qqtwifidbwidget.h \
    $$PWD/frame/qqtprogressdialog.h \
    $$PWD/frame/qqtpassworddialog.h \
    $$PWD/frame/qqtframe.h \
    $$PWD/frame/qqtdialog.h \
    $$PWD/frame/qqtinput.h \
    $$PWD/frame/qqtmsgbox.h
FORMS += \
    $$PWD/frame/qqtprogressdialog.ui \
    $$PWD/frame/qqtpassworddialog.ui \
    $$PWD/frame/qqtinput.ui \
    $$PWD/frame/qqtmsgbox.ui


#multimedia
#support Qt5, if Qt4 want to use, you need compile QtMultiMedia for Qt4.
#audio success. video arm mips
#TODO: video +wince +android +ios +macOS +win +linux
contains (DEFINES, __MULTIMEDIA__) {
    #mplayer
    contains (DEFINES, __PROCESSMODULE__){
        SOURCES += $$PWD/multimedia/qqtmplayer.cpp
        HEADERS += $$PWD/multimedia/qqtmplayer.h
    }

    #audio
    SOURCES += \
        $$PWD/multimedia/qqtwavaudiomanager.cpp \
        $$PWD/multimedia/qqtaudiomanager.cpp
    HEADERS += \
        $$PWD/multimedia/qqtwavaudiomanager.h \
        $$PWD/multimedia/qqtaudiomanager.h

    #audio effect
    #using QSound (QSoundEffect optional)
    SOURCES += \
        $$PWD/multimedia/qqtsoundeffect.cpp
    HEADERS += \
        $$PWD/multimedia/qqtsoundeffect.h
}


#printsupport
#注释：在qqt_header.pri打开 DEFINES += __PRINTSUPPORT__
contains (DEFINES, __PRINTSUPPORT__) {
    SOURCES += $$PWD/printsupport/qqtprinter.cpp
    HEADERS += $$PWD/printsupport/qqtprinter.h
    SOURCES += \
        $$PWD/frame/qqtword.cpp
    HEADERS += \
        $$PWD/frame/qqtword.h

}

contains(DEFINES, __QQTCHARTS__) {
    SOURCES += \
        $$PWD/charts/qqtchart.cpp \
        $$PWD/charts/qqtchartview.cpp
    HEADERS += \
        $$PWD/charts/qqtchart.h \
        $$PWD/charts/qqtchartview.h
}

#network
contains (DEFINES, __NETWORKSUPPORT__) {
    SOURCES += $$PWD/network/qqtnetwork.cpp
    HEADERS += $$PWD/network/qqtnetwork.h

    #报文 用户重要
    HEADERS += $$PWD/network/qqtmessage.h

    #协议 用户重要
    HEADERS += $$PWD/network/qqtprotocol.h

    #protocol manager for server iodevice
    SOURCES += $$PWD/network/qqtprotocolmanager.cpp
    HEADERS += $$PWD/network/qqtprotocolmanager.h

    #tcp and udp iodevice
    contains(DEFINES, __TCPUDPSOCKET__){
        #tcp client iodevice
        SOURCES += $$PWD/network/qqttcpclient.cpp
        HEADERS += $$PWD/network/qqttcpclient.h

        #tcp server iodevice
        SOURCES += $$PWD/network/qqttcpserver.cpp
        HEADERS += $$PWD/network/qqttcpserver.h

        #udp client iodevice
        SOURCES += $$PWD/network/qqtudpclient.cpp
        HEADERS += $$PWD/network/qqtudpclient.h

        #udp server iodevice
        SOURCES += $$PWD/network/qqtudpserver.cpp
        HEADERS += $$PWD/network/qqtudpserver.h
    }

    #serialport iodevice
    SOURCES += $$PWD/network/qqtserialport.cpp
    HEADERS += $$PWD/network/qqtserialport.h

    #bluetooth iodevice
    #注释：在qqt_header.pri打开 DEFINES += __BLUETOOTH__
    contains (DEFINES, __BLUETOOTH__) {
        #bluetooth client iodevice
        SOURCES += $$PWD/network/qqtbluetoothclient.cpp
        HEADERS += $$PWD/network/qqtbluetoothclient.h

        #bluetooth server iodevice
        SOURCES += $$PWD/network/qqtbluetoothserver.cpp
        HEADERS += $$PWD/network/qqtbluetoothserver.h

        #bluetooth manager
        SOURCES += $$PWD/network/qqtbluetoothmanager.cpp
        HEADERS += $$PWD/network/qqtbluetoothmanager.h
    }

    contains (DEFINES, __WEBSOCKETSUPPORT__) {
        #websocket client iodevice
        SOURCES += $$PWD/network/qqtwebsocketclient.cpp
        HEADERS += $$PWD/network/qqtwebsocketclient.h
        #websocket server iodevice
        SOURCES += $$PWD/network/qqtwebsocketserver.cpp
        HEADERS += $$PWD/network/qqtwebsocketserver.h
    }

    #ethnet(+wifi) manager
    #arm mips
    #TODO: +wince +android +ios +macOS? +win? +linux?
    contains(QKIT_PRIVATE, Embedded||Arm32||Mips32) {
        SOURCES += $$PWD/network/qqtethenetmanager.cpp
        HEADERS += $$PWD/network/qqtethenetmanager.h
        SOURCES += $$PWD/frame/qqtwifiwidget.cpp
        HEADERS += $$PWD/frame/qqtwifiwidget.h
        FORMS += $$PWD/frame/qqtwifiwidget.ui
    }

    #webaccess manager
    contains (DEFINES, __WEBACCESSSUPPORT__) {
        SOURCES += $$PWD/network/qqtwebaccessmanager.cpp
        HEADERS += $$PWD/network/qqtwebaccessmanager.h
    }
}

contains (DEFINES, __EXQUISITE__) {
    #exquisite
    SOURCES += \
        $$PWD/exquisite/qqtframelesshelper.cpp \
        $$PWD/exquisite/qqtframelesshelperprivate.cpp
    HEADERS += \
        $$PWD/exquisite/qqtframelesshelper.h \
        $$PWD/exquisite/qqtframelesshelperprivate.h

    #can click sound support widgets
    contains (DEFINES, __CLICKSOUNDWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/clicksoundwidgets/qqtclicksoundhelper.cpp \
            $$PWD/exquisite/clicksoundwidgets/qqtlongclicksoundhelper.cpp \
            $$PWD/exquisite/clicksoundwidgets/qqtdoubleclicksoundhelper.cpp
        HEADERS += \
            $$PWD/exquisite/clicksoundwidgets/qqtclicksoundhelper.h \
            $$PWD/exquisite/clicksoundwidgets/qqtlongclicksoundhelper.h \
            $$PWD/exquisite/clicksoundwidgets/qqtdoubleclicksoundhelper.h

        SOURCES += \
            $$PWD/exquisite/clicksoundwidgets/qqtclicksoundwidget.cpp \
            $$PWD/exquisite/clicksoundwidgets/qqtlongclicksoundwidget.cpp \
            $$PWD/exquisite/clicksoundwidgets/qqtdoubleclicksoundwidget.cpp
        HEADERS += \
            $$PWD/exquisite/clicksoundwidgets/qqtclicksoundwidget.h \
            $$PWD/exquisite/clicksoundwidgets/qqtlongclicksoundwidget.h \
            $$PWD/exquisite/clicksoundwidgets/qqtdoubleclicksoundwidget.h

        SOURCES += \
            $$PWD/exquisite/clicksoundwidgets/qqtclicksoundlabel.cpp \
            $$PWD/exquisite/clicksoundwidgets/qqtlongclicksoundlabel.cpp \
            $$PWD/exquisite/clicksoundwidgets/qqtdoubleclicksoundlabel.cpp
        HEADERS += \
            $$PWD/exquisite/clicksoundwidgets/qqtclicksoundlabel.h \
            $$PWD/exquisite/clicksoundwidgets/qqtlongclicksoundlabel.h \
            $$PWD/exquisite/clicksoundwidgets/qqtdoubleclicksoundlabel.h
    }

    #can click support widgets
    contains (DEFINES, __CLICKWIDGETS__) {

        SOURCES += \
            $$PWD/exquisite/clickwidgets/qqtclickhelper.cpp \
            $$PWD/exquisite/clickwidgets/qqtlongclickhelper.cpp \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickhelper.cpp
        HEADERS += \
            $$PWD/exquisite/clickwidgets/qqtclickhelper.h \
            $$PWD/exquisite/clickwidgets/qqtlongclickhelper.h \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickhelper.h

        SOURCES += \
            $$PWD/exquisite/clickwidgets/qqtclickwidget.cpp \
            $$PWD/exquisite/clickwidgets/qqtlongclickwidget.cpp \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickwidget.cpp
        HEADERS += \
            $$PWD/exquisite/clickwidgets/qqtclickwidget.h \
            $$PWD/exquisite/clickwidgets/qqtlongclickwidget.h \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickwidget.h

        SOURCES += \
            $$PWD/exquisite/clickwidgets/qqtclicklabel.cpp \
            $$PWD/exquisite/clickwidgets/qqtlongclicklabel.cpp \
            $$PWD/exquisite/clickwidgets/qqtdoubleclicklabel.cpp
        HEADERS += \
            $$PWD/exquisite/clickwidgets/qqtclicklabel.h \
            $$PWD/exquisite/clickwidgets/qqtlongclicklabel.h \
            $$PWD/exquisite/clickwidgets/qqtdoubleclicklabel.h
    }

    #dialog
    SOURCES += \
        $$PWD/exquisite/qqtpopupdialog.cpp
    HEADERS += \
        $$PWD/exquisite/qqtpopupdialog.h

    #widget
    SOURCES += \
        $$PWD/exquisite/qqtfadewidget.cpp \
        $$PWD/exquisite/qqtninepatchwidget.cpp \
        $$PWD/exquisite/qqtshadowwidget.cpp \
        $$PWD/exquisite/qqtflipstackedwidget.cpp
    HEADERS += \
        $$PWD/exquisite/qqtninepatchwidget.h \
        $$PWD/exquisite/qqtfadewidget.h \
        $$PWD/exquisite/qqtshadowwidget.h \
        $$PWD/exquisite/qqtflipstackedwidget.h

    #special
    SOURCES += \
        $$PWD/exquisite/qqtcustompianokeyboard.cpp \
        $$PWD/exquisite/qqtcustomverificationcode.cpp \
        $$PWD/exquisite/qqtrulerslider.cpp
    HEADERS += \
        $$PWD/exquisite/qqtcustompianokeyboard.h \
        $$PWD/exquisite/qqtcustomverificationcode.h \
        $$PWD/exquisite/qqtrulerslider.h

    #progressbar
    SOURCES += \
        $$PWD/exquisite/qqtcustomprogressbar.cpp \
        $$PWD/exquisite/qqtcustomspeedmeter.cpp
    HEADERS += \
        $$PWD/exquisite/qqtcustomprogressbar.h \
        $$PWD/exquisite/qqtcustomspeedmeter.h

    #pushbutton
    SOURCES += \
        $$PWD/exquisite/qqtripplepushbutton.cpp
    HEADERS += \
        $$PWD/exquisite/qqtripplepushbutton.h

    #label
    SOURCES += \
        $$PWD/exquisite/qqtledbannerlabel.cpp \
        $$PWD/exquisite/qqtmarqueelabel.cpp

    HEADERS += \
        $$PWD/exquisite/qqtmarqueelabel.h \
        $$PWD/exquisite/qqtledbannerlabel.h

    #tabwidget
    SOURCES += \
        $$PWD/exquisite/qqthorizontaltexttabbar.cpp \
        $$PWD/exquisite/qqthorizontaltexttabwidget.cpp \
        $$PWD/exquisite/qqtpicturetabbar.cpp \
        $$PWD/exquisite/qqtpicturetabwidget.cpp \
        $$PWD/exquisite/qqtslidetabbar.cpp \
        $$PWD/exquisite/qqtslidetabwidget.cpp

    HEADERS += \
        $$PWD/exquisite/qqtslidetabbar.h \
        $$PWD/exquisite/qqtslidetabwidget.h \
        $$PWD/exquisite/qqtpicturetabwidget.h \
        $$PWD/exquisite/qqtpicturetabbar.h \
        $$PWD/exquisite/qqthorizontaltexttabwidget.h \
        $$PWD/exquisite/qqthorizontaltexttabbar.h


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

    #gif widgets
    contains (DEFINES, __GIFWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/gifwidgets/qqtgifwidget.cpp \
            $$PWD/exquisite/gifwidgets/qqtgiflabel.cpp \
            $$PWD/exquisite/gifwidgets/qqtgifpushbutton.cpp \
            $$PWD/exquisite/gifwidgets/qqtgifcheckbox.cpp \
            $$PWD/exquisite/gifwidgets/qqtgifradiobutton.cpp \
            $$PWD/exquisite/gifwidgets/qqtgifprogressbar.cpp
        HEADERS += \
            $$PWD/exquisite/gifwidgets/qqtgifwidget.h \
            $$PWD/exquisite/gifwidgets/qqtgiflabel.h \
            $$PWD/exquisite/gifwidgets/qqtgifpushbutton.h \
            $$PWD/exquisite/gifwidgets/qqtgifcheckbox.h \
            $$PWD/exquisite/gifwidgets/qqtgifradiobutton.h \
            $$PWD/exquisite/gifwidgets/qqtgifprogressbar.h
    }

    #opengl widgets
    contains (DEFINES, __OPENGLWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/openglwidgets/qqtopenglwidget.cpp \
            $$PWD/exquisite/openglwidgets/qqtopenglwindow.cpp
        HEADERS += \
            $$PWD/exquisite/openglwidgets/qqtopenglwidget.h \
            $$PWD/exquisite/openglwidgets/qqtopenglwindow.h
    }

    contains (DEFINES, __COLORWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/colorwidgets/qqtcolorwidget.cpp \
            $$PWD/exquisite/colorwidgets/qqtcolorlabel.cpp
        HEADERS += \
            $$PWD/exquisite/colorwidgets/qqtcolorwidget.h \
            $$PWD/exquisite/colorwidgets/qqtcolorlabel.h
    }
}

include ($$PWD/qqt_3rdparty.pri)
