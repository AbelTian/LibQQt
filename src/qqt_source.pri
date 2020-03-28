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
contains (DEFINES, __WIN__) {
    #win32 base header
    HEADERS += $$PWD/qqtwin.h
} else:contains (DEFINES, __DARWIN__) {
    #mac base header
    HEADERS += $$PWD/qqtdarwin.h
} else:contains (DEFINES, __ANDROID__) {
    #android base header
    HEADERS += $$PWD/qqtandroid.h
} else {
    #linux base header
    HEADERS += $$PWD/qqtlinux.h
}

#core
SOURCES += \
    $$PWD/core/qqtcore.cpp \
    $$PWD/core/qqtorderedmap.cpp \
    $$PWD/core/qqtdictionary.cpp \
    $$PWD/core/qqtobjectmanager.cpp
HEADERS += \
    $$PWD/core/qqtcore.h \
    $$PWD/core/qqtorderedmap.h \
    $$PWD/core/qqtdictionary.h \
    $$PWD/core/qqtobjectmanager.h

SOURCES += \
    $$PWD/core/qqtevent.cpp
HEADERS += \
    $$PWD/core/qqtevent.h

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
#add_object_class(QQtNoFocusDelegate, $$PWD/gui)
SOURCES += \
    $$PWD/gui/qqtprogressbardelegate.cpp \
    $$PWD/gui/qqtnofocusdelegate.cpp
HEADERS += \
    $$PWD/gui/qqtprogressbardelegate.h \
    $$PWD/gui/qqtnofocusdelegate.h

SOURCES += \
    $$PWD/gui/qqttablemodel.cpp \
    $$PWD/gui/qqtdicttreemodel.cpp \
    $$PWD/gui/qqtdicttablemodel.cpp \
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
    $$PWD/gui/qqtdicttablemodel.h \
    $$PWD/gui/qqtftptreemodel.h \
    $$PWD/gui/qqtsqltreemodel.h \
    $$PWD/gui/qqtjsontreemodel.h \
    $$PWD/gui/qqtxmltreemodel.h \
    $$PWD/gui/qqtfilesystemtreemodel.h \
    $$PWD/gui/qqtgui.h

#widgets
SOURCES += \
    $$PWD/widgets/qqttitlebar.cpp
HEADERS += \
    $$PWD/widgets/qqttitlebar.h

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
    $$PWD/frame/qqtlineeditwithsearch.cpp
HEADERS += \
    $$PWD/frame/qqtlineeditwithsearch.h

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
    $$PWD/frame/qqtmsgbox.cpp
HEADERS += \
    $$PWD/frame/qqtanimation.h \
    $$PWD/frame/qqtapplication.h \
    $$PWD/frame/qqtwifidbwidget.h \
    $$PWD/frame/qqtprogressdialog.h \
    $$PWD/frame/qqtpassworddialog.h \
    $$PWD/frame/qqtframe.h \
    $$PWD/frame/qqtdialog.h \
    $$PWD/frame/qqtmsgbox.h
FORMS += \
    $$PWD/frame/qqtprogressdialog.ui \
    $$PWD/frame/qqtpassworddialog.ui \
    $$PWD/frame/qqtmsgbox.ui

SOURCES += \
    $$PWD/frame/qqtqssmanager.cpp
HEADERS += \
    $$PWD/frame/qqtqssmanager.h

#multimedia
#support Qt5, if Qt4 want to use, you need compile QtMultiMedia for Qt4.
#audio +wav
#video arm mips +logic video; desktop +camera
#TODO: audio mediaextention +mp3 +ogg ...
#TODO: video mediaextention +FFmpeg +Vlc ... +wince +android +ios +macOS +win +linux
contains (DEFINES, __MULTIMEDIA__) {
    #mplayer
    contains (DEFINES, __PROCESSSUPPORT__){
        SOURCES += $$PWD/multimedia/qqtmplayer.cpp
        HEADERS += $$PWD/multimedia/qqtmplayer.h

        SOURCES += $$PWD/multimedia/qqtmplayerwidget.cpp
        HEADERS += $$PWD/multimedia/qqtmplayerwidget.h
        FORMS += $$PWD/multimedia/qqtmplayerwidget.ui
    }

    #audio
    contains (DEFINES, __QQTAUDIOSUPPORT__){
        SOURCES += $$PWD/multimedia/qqtaudiomanager.cpp
        HEADERS += $$PWD/multimedia/qqtaudiomanager.h

        SOURCES += $$PWD/multimedia/qqtwavaudiomanager.cpp
        HEADERS += $$PWD/multimedia/qqtwavaudiomanager.h
        SOURCES += $$PWD/multimedia/qqtwavsoundeffect.cpp
        HEADERS += $$PWD/multimedia/qqtwavsoundeffect.h
    }

    #video
    contains (DEFINES, __QQTVIDEOSUPPORT__){
        SOURCES += $$PWD/multimedia/qqtimageconverter.cpp
        HEADERS += $$PWD/multimedia/qqtimageconverter.h

        SOURCES += $$PWD/multimedia/qqtcamera.cpp
        HEADERS += $$PWD/multimedia/qqtcamera.h
        SOURCES += $$PWD/multimedia/qqtvideomanager.cpp
        HEADERS += $$PWD/multimedia/qqtvideomanager.h
    }

    #logic video
    contains (DEFINES, __LOGICCAMERAMODULE__) {
        SOURCES += $$PWD/multimedia/private/qqtlogicvideomanager_p.cpp
        HEADERS += $$PWD/multimedia/private/qqtlogicvideomanager_p.h

        SOURCES += $$PWD/multimedia/qqtlogicvideomanager.cpp
        HEADERS += $$PWD/multimedia/qqtlogicvideomanager.h

        SOURCES += $$PWD/multimedia/qqtlogicpreviewwidget.cpp
        HEADERS += $$PWD/multimedia/qqtlogicpreviewwidget.h
        FORMS += $$PWD/multimedia/qqtlogicpreviewwidget.ui
    }
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
    contains(DEFINES, __QT_CHARTS__ ){
        SOURCES += \
            $$PWD/charts/qqtchart.cpp \
            $$PWD/charts/qqtchartview.cpp
        HEADERS += \
            $$PWD/charts/qqtchart.h \
            $$PWD/charts/qqtchartview.h
    }
    #customplot 在3rdparty.
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
    contains(DEFINES, __QQTSERIALPORT__){
        SOURCES += $$PWD/network/qqtserialport.cpp
        HEADERS += $$PWD/network/qqtserialport.h
    }

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

    #nfc iodevice
    #注释：在qqt_header.pri打开 DEFINES += __NFC__
    contains (DEFINES, __NFC__) {
        SOURCES += $$PWD/network/qqtnfcclient.cpp
        HEADERS += $$PWD/network/qqtnfcclient.h

        SOURCES += $$PWD/network/qqtnfcserver.cpp
        HEADERS += $$PWD/network/qqtnfcserver.h
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
    contains(DEFINES, QQT_ETHENET_MANAGER) {
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
    #主窗体整体移动 对父、子窗体均可使用
    HEADERS += \
        $$PWD/exquisite/qqtbodymover.h \
        $$PWD/exquisite/qqtbodymover_p.h
    SOURCES += \
        $$PWD/exquisite/qqtbodymover.cpp \
        $$PWD/exquisite/qqtbodymover_p.cpp

    #主窗体整体移动 对父、子窗体均可使用
    #add_object_class(QQtRootBodyMover, $${PWD}/exquisite)
    HEADERS += \
        $$PWD/exquisite/qqtrootbodymover.h
    SOURCES += \
        $$PWD/exquisite/qqtrootbodymover.cpp

    #子窗体在父窗体里移动 只应用于子窗体，不能应用于主窗体
    add_file($$PWD/exquisite/qqtchildbodymover.h)
    add_file($$PWD/exquisite/qqtchildbodymover.cpp)
    HEADERS += \
        $$PWD/exquisite/qqtchildbodymover.h
    SOURCES += \
        $$PWD/exquisite/qqtchildbodymover.cpp

    #窗体大小。一般用于无边框窗体。父、子窗体均可使用
    HEADERS += \
        $$PWD/exquisite/qqtbodyresizer.h \
        $$PWD/exquisite/qqtbodyresizer_p.h
    SOURCES += \
        $$PWD/exquisite/qqtbodyresizer.cpp \
        $$PWD/exquisite/qqtbodyresizer_p.cpp

    #在窗体里锁定鼠标
    HEADERS += \
        $$PWD/exquisite/qqtbodymouselocker_p.h \
        $$PWD/exquisite/qqtbodymouselocker.h
    SOURCES += \
        #$$PWD/exquisite/qqtbodymouselocker_p.cpp \
        $$PWD/exquisite/qqtbodymouselocker.cpp
    contains(DEFINES, __DESKTOP_WIN__){
        HEADERS += \
            $$PWD/exquisite/qqtbodymouselocker_win.h
        SOURCES += \
            $$PWD/exquisite/qqtbodymouselocker_win.cpp
    } else:contains(DEFINES, __DESKTOP_LINUX__) {
        add_file($$PWD/exquisite/qqtbodymouselocker_x11.h)
        add_file($$PWD/exquisite/qqtbodymouselocker_x11.cpp)
        HEADERS += \
            $$PWD/exquisite/qqtbodymouselocker_x11.h
        SOURCES += \
            $$PWD/exquisite/qqtbodymouselocker_x11.cpp
    } else {
        HEADERS += \
            $$PWD/exquisite/qqtbodymouselocker_unix.h
        SOURCES += \
            $$PWD/exquisite/qqtbodymouselocker_unix.cpp
    }

    #在窗体里摁动鼠标滚轮缩放
    add_file($$PWD/exquisite/qqtbodymousewheelscalingeffect.cpp)
    add_file($$PWD/exquisite/qqtbodymousewheelscalingeffect.h)
    SOURCES += \
        $$PWD/exquisite/qqtbodymousewheelscalingeffect.cpp
    HEADERS += \
        $$PWD/exquisite/qqtbodymousewheelscalingeffect.h

    #窗体被选中时的效果
    add_file($$PWD/exquisite/qqtbodyselectedstyle.cpp)
    add_file($$PWD/exquisite/qqtbodyselectedstyle.h)
    SOURCES += \
        $$PWD/exquisite/qqtbodyselectedstyle.cpp
    HEADERS += \
        $$PWD/exquisite/qqtbodyselectedstyle.h

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

    #不规则形状的控件
    contains (DEFINES, __IRREGULARWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/irregularwidgets/qqtirregularwidget.cpp
        HEADERS += \
            $$PWD/exquisite/irregularwidgets/qqtirregularwidget.h

        SOURCES += \
            $$PWD/exquisite/irregularwidgets/qqtirregularlabel.cpp
        HEADERS += \
            $$PWD/exquisite/irregularwidgets/qqtirregularlabel.h

        SOURCES += \
            $$PWD/exquisite/irregularwidgets/qqtirregularpushbutton.cpp
        HEADERS += \
            $$PWD/exquisite/irregularwidgets/qqtirregularpushbutton.h
    }

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
            $$PWD/exquisite/clickwidgets/qqtvirtualclickhelper.cpp \
            $$PWD/exquisite/clickwidgets/qqtclickhelper.cpp \
            $$PWD/exquisite/clickwidgets/qqtlongclickhelper.cpp \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickhelper.cpp
        HEADERS += \
            $$PWD/exquisite/clickwidgets/qqtvirtualclickhelper.h \
            $$PWD/exquisite/clickwidgets/qqtclickhelper.h \
            $$PWD/exquisite/clickwidgets/qqtlongclickhelper.h \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickhelper.h

        SOURCES += \
            $$PWD/exquisite/clickwidgets/qqtvirtualclickwidget.cpp \
            $$PWD/exquisite/clickwidgets/qqtclickwidget.cpp \
            $$PWD/exquisite/clickwidgets/qqtlongclickwidget.cpp \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickwidget.cpp
        HEADERS += \
            $$PWD/exquisite/clickwidgets/qqtvirtualclickwidget.h \
            $$PWD/exquisite/clickwidgets/qqtclickwidget.h \
            $$PWD/exquisite/clickwidgets/qqtlongclickwidget.h \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickwidget.h

        SOURCES += \
            $$PWD/exquisite/clickwidgets/qqtvirtualclicklabel.cpp \
            $$PWD/exquisite/clickwidgets/qqtclicklabel.cpp \
            $$PWD/exquisite/clickwidgets/qqtlongclicklabel.cpp \
            $$PWD/exquisite/clickwidgets/qqtdoubleclicklabel.cpp
        HEADERS += \
            $$PWD/exquisite/clickwidgets/qqtvirtualclicklabel.h \
            $$PWD/exquisite/clickwidgets/qqtclicklabel.h \
            $$PWD/exquisite/clickwidgets/qqtlongclicklabel.h \
            $$PWD/exquisite/clickwidgets/qqtdoubleclicklabel.h

        SOURCES += \
            $$PWD/exquisite/clickwidgets/qqtvirtualclickdialog.cpp \
            $$PWD/exquisite/clickwidgets/qqtclickdialog.cpp \
            $$PWD/exquisite/clickwidgets/qqtlongclickdialog.cpp \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickdialog.cpp
        HEADERS += \
            $$PWD/exquisite/clickwidgets/qqtvirtualclickdialog.h \
            $$PWD/exquisite/clickwidgets/qqtclickdialog.h \
            $$PWD/exquisite/clickwidgets/qqtlongclickdialog.h \
            $$PWD/exquisite/clickwidgets/qqtdoubleclickdialog.h
    }

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

    #color widgets
    contains (DEFINES, __COLORWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/colorwidgets/qqtcolorwidget.cpp \
            $$PWD/exquisite/colorwidgets/qqtcolorlabel.cpp
        HEADERS += \
            $$PWD/exquisite/colorwidgets/qqtcolorwidget.h \
            $$PWD/exquisite/colorwidgets/qqtcolorlabel.h
    }

    #on screen display widgets
    contains (DEFINES, __OSDWIDGETS__) {
        SOURCES += \
            $$PWD/exquisite/osdwidgets/qqtosdwidget.cpp
        HEADERS += \
            $$PWD/exquisite/osdwidgets/qqtosdwidget.h

        SOURCES += \
            $$PWD/exquisite/osdwidgets/qqtosdframe.cpp
        HEADERS += \
            $$PWD/exquisite/osdwidgets/qqtosdframe.h

        SOURCES += \
            $$PWD/exquisite/osdwidgets/qqtosdform.cpp
        HEADERS += \
            $$PWD/exquisite/osdwidgets/qqtosdform.h
    }
}

contains (DEFINES, __HIGHGRADE__) {
    INCLUDEPATH += $${PWD}/highgrade/private

    #shared memory
    #core module
    contains(DEFINES, __SHAREDMEMORY_SUPPORT__){
        SOURCES += \
            $$PWD/highgrade/qqtsharedmemory.cpp
        HEADERS += \
            $$PWD/highgrade/qqtsharedmemory.h
    }

    contains(DEFINES, __MESSAGEQUEUE_SUPPORT__){
        SOURCES += \
            $$PWD/highgrade/private/qqtmessagequeueprivate.cpp
        HEADERS += \
            $$PWD/highgrade/private/qqtmessagequeueprivate.h
        #基于tcp socket实现
        SOURCES += \
            $$PWD/highgrade/qqtmessagequeue.cpp
        HEADERS += \
            $$PWD/highgrade/qqtmessagequeue.h
    }

    #local socket iodevice
    #network module
    contains(DEFINES, __NAMEDPIPE_SUPPORT__){
        #local client iodevice
        SOURCES += $$PWD/highgrade/private/qqtnamedpipeclient.cpp
        HEADERS += $$PWD/highgrade/private/qqtnamedpipeclient.h

        #local server iodevice
        SOURCES += $$PWD/highgrade/private/qqtnamedpipeserver.cpp
        HEADERS += $$PWD/highgrade/private/qqtnamedpipeserver.h

        SOURCES += $$PWD/highgrade/private/qqtnamedpipeprivate.cpp
        HEADERS += $$PWD/highgrade/private/qqtnamedpipeprivate.h

        SOURCES += \
            $$PWD/highgrade/qqtnamedpipe.cpp
        HEADERS += \
            $$PWD/highgrade/qqtnamedpipe.h
    }

    #singleton application
    contains(DEFINES, __NAMEDPIPE_SUPPORT__){
        SOURCES += \
            $$PWD/highgrade/private/qqtsingletonapplicationprivate.cpp
        HEADERS += \
            $$PWD/highgrade/private/qqtsingletonapplicationprivate.h
        #依赖local socket
        SOURCES += \
            $$PWD/highgrade/qqtsingletonapplication.cpp
        HEADERS += \
            $$PWD/highgrade/qqtsingletonapplication.h
    }

    SOURCES += \
        $$PWD/highgrade/qqtdatapersistence.cpp
    HEADERS += \
        $$PWD/highgrade/qqtdatapersistence.h

    add_object_class(QQtDataSerialization, $$PWD/highgrade)
    SOURCES += \
        $$PWD/highgrade/qqtdataserialization.cpp
    HEADERS += \
        $$PWD/highgrade/qqtdataserialization.h

    add_object_class(QQtStandardProtocol, $$PWD/highgrade)
    SOURCES += \
        $$PWD/highgrade/qqtstandardprotocol.cpp
    HEADERS += \
        $$PWD/highgrade/qqtstandardprotocol.h
}

include ($$PWD/qqt_3rdparty.pri)
