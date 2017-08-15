#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5): CONFIG += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

QT += core gui network sql

DEFINES += _TTY_POSIX_

INCLUDEPATH += $$PWD \
                $$PWD/customplot \
                $$PWD/pluginwatcher \
                $$PWD/dmmu \
                $$PWD/frame

QT_KIT = $$(QKIT)

message($${QT_KIT} Defined in qqtfoundation)
#MIPS __MIPS_LINUX__
#LINUX __LINUX__
#LINUX64 __LINUX64__
#WIN __WIN__
#WIN64 __WIN64__
#处理文件内平台小差异
equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else:equals(QT_KIT, LINUX) {
    DEFINES += __LINUX__
}  else:equals(QT_KIT, LINUX64) {
    DEFINES += __LINUX64__
}  else:equals(QT_KIT, WIN) {
    DEFINES += __WIN__
} else:equals(QT_KIT, WIN64) {
    DEFINES += __WIN64__
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}

win32 {
    win32:DEFINES += _CRT_SECURE_NO_WARNINGS #fopen fopen_s

    QMAKE_CXXFLAGS += /wd"4819" /wd"4244" /wd"4100"

    LIBS += -luser32
}


win32 {
    #win32 base type
    HEADERS += $$PWD/qqtwin.h

    wince*: SOURCES += $$PWD/pluginwatcher/qdevicewatcher_wince.cpp
    else:  SOURCES += $$PWD/pluginwatcher/qdevicewatcher_win32.cpp
}

unix {
    macx {
        SOURCES += $$PWD/pluginwatcher/qdevicewatcher_mac.cpp
        LIBS += -framework DiskArbitration -framework Foundation
    } else {
        SOURCES += $$PWD/pluginwatcher/qdevicewatcher_linux.cpp
    }
#frame
    SOURCES += $$PWD/frame/qqtprogressdialog.cpp \
                $$PWD/frame/qqtpassworddialog.cpp \
                $$PWD/frame/qqtpreviewwidget.cpp \
                $$PWD/frame/qqtwifiwidget.cpp
    HEADERS += $$PWD/frame/qqtprogressdialog.h \
                $$PWD/frame/qqtpassworddialog.h \
                $$PWD/frame/qqtpreviewwidget.h \
                $$PWD/frame/qqtwifiwidget.h
    FORMS += $$PWD/frame/qqtprogressdialog.ui \
                $$PWD/frame/qqtpassworddialog.ui \
                $$PWD/frame/qqtpreviewwidget.ui \
                $$PWD/frame/qqtwifiwidget.ui
#dmmu
    SOURCES += $$PWD/dmmu/dmmu.c
    HEADERS += $$PWD/dmmu/dmmu.h \
                $$PWD/dmmu/jz_cim.h \
                $$PWD/dmmu/graphics.h \
                $$PWD/dmmu/hal.h
#
    SOURCES += $$PWD/qqtethenetmanager.cpp
    HEADERS += $$PWD/qqtethenetmanager.h \
                $$PWD/qqtlinux.h
}

#customplot
SOURCES += $$PWD/customplot/qcpdocumentobject.cpp \
            $$PWD/customplot/qcustomplot.cpp
HEADERS += $$PWD/customplot/qcpdocumentobject.h \
            $$PWD/customplot/qcustomplot.h
#pluginwatcher
SOURCES += $$PWD/pluginwatcher/qdevicewatcher.cpp \
            $$PWD/pluginwatcher/qqtpluginwatcher.cpp
HEADERS += $$PWD/pluginwatcher/qqtpluginwatcher.h \
            $$PWD/pluginwatcher/qdevicewatcher.h \
            $$PWD/pluginwatcher/qdevicewatcher_p.h

SOURCES += $$PWD/qqtcheckbox.cpp \
        $$PWD/qqtdefine.cpp \
    $$PWD/qqtdialog.cpp \
    $$PWD/qqtheaderview.cpp \
    $$PWD/qqtlistview.cpp \
    $$PWD/qqtprinter.cpp \
    $$PWD/qqtprogressbar.cpp \
    $$PWD/qqtpushbutton.cpp \
    $$PWD/qqtradiobutton.cpp \
    $$PWD/qqttabbar.cpp \
    $$PWD/qqttableview.cpp \
    $$PWD/qqttabwidget.cpp \
    $$PWD/qqttabwidgetb.cpp \
    $$PWD/qqttreeview.cpp \
    $$PWD/qqtwidget.cpp \
    $$PWD/qqtclient.cpp \
    $$PWD/qqtlineeditwithsearch.cpp \
    $$PWD/qqtplayer.cpp \
    $$PWD/qqtserialport.cpp \
    $$PWD/qqtserver.cpp \
    $$PWD/qqttablemodel.cpp \
    $$PWD/qqtstandarditemmodel.cpp \
    $$PWD/qqtmptablewidget.cpp \
    $$PWD/qqttablewidget.cpp \
    $$PWD/qqtgraphicsscene.cpp \
    $$PWD/qqtgraphicsitem.cpp \
    $$PWD/qqtgraphicsview.cpp \
    $$PWD/qqtword.cpp \
    $$PWD/qqtreport.cpp \
    $$PWD/qqtobjectfactory.cpp \
    $$PWD/qqttreemodel.cpp \
    $$PWD/qqtfilesystem.cpp \
    $$PWD/qqttreewidget.cpp \
    $$PWD/qqtinput.cpp \
    $$PWD/qqtmsgbox.cpp \
    $$PWD/qqtcloudprotocol.cpp \
    $$PWD/qqtmessage.cpp \
    $$PWD/qqtprotocol.cpp \
    $$PWD/qqtserialmessage.cpp \
    $$PWD/qqtnetworkmessage.cpp \
    $$PWD/qqtuserserialprotocol.cpp \
    $$PWD/qqtlanprotocol.cpp \
    $$PWD/qqtanimation.cpp

HEADERS  += $$PWD/qqtcheckbox.h \
        $$PWD/qqtdefine.h \
    $$PWD/qqtdialog.h \
    $$PWD/qqtgui.h \
    $$PWD/qqtgui-qt.h \
    $$PWD/qqtheaderview.h \
    $$PWD/qqtlistview.h \
    $$PWD/qqtprinter.h \
    $$PWD/qqtprogressbar.h \
    $$PWD/qqtFoundation.h \
    $$PWD/qqtpushbutton.h \
    $$PWD/qqtradiobutton.h \
    $$PWD/qqttabbar.h \
    $$PWD/qqttableview.h \
    $$PWD/qqttabwidget.h \
    $$PWD/qqttabwidgetb.h \
    $$PWD/qqttreeview.h \
    $$PWD/qqtwidget.h \
    $$PWD/qqtclient.h \
    $$PWD/qqtlineeditwithsearch.h \
    $$PWD/qqtplayer.h \
    $$PWD/qqtserialport.h \
    $$PWD/qqtserver.h \
    $$PWD/qqttablemodel.h \
    $$PWD/qqtstandarditemmodel.h \
    $$PWD/qqtmptablewidget.h \
    $$PWD/qqttablewidget.h \
    $$PWD/qqtgraphicsscene.h \
    $$PWD/qqtgraphicsitem.h \
    $$PWD/qqtgraphicsview.h \
    $$PWD/qqtword.h \
    $$PWD/qqtreport.h \
    $$PWD/version.h \
    $$PWD/qqtobjectfactory.h \
    $$PWD/qqttreemodel.h \
    $$PWD/qqtfilesystem.h \
    $$PWD/qqttreewidget.h \
    $$PWD/qqtinput.h \
    $$PWD/qqtmsgbox.h \
    $$PWD/qqtcloudprotocol.h \
    $$PWD/qqtprotocol.h \
    $$PWD/qqtmessage.h \
    $$PWD/qqtserialmessage.h \
    $$PWD/qqtnetworkmessage.h \
    $$PWD/qqtuserserialprotocol.h \
    $$PWD/qqtlanprotocol.h \
    $$PWD/qqtanimation.h \


FORMS    += $$PWD/qqtcheckbox.ui \
    $$PWD/qqtdialog.ui \
    $$PWD/qqtlistview.ui \
    $$PWD/qqtprogressbar.ui \
    $$PWD/qqtpushbutton.ui \
    $$PWD/qqtradiobutton.ui \
    $$PWD/qqttableview.ui \
    $$PWD/qqttabwidget.ui \
    $$PWD/qqttabwidgetb.ui \
    $$PWD/qqttreeview.ui \
    $$PWD/qqtwidget.ui \
    $$PWD/qqttablewidget.ui \
    $$PWD/qqtmptablewidget.ui \
    $$PWD/qqttreewidget.ui \
    $$PWD/qqtinput.ui \
    $$PWD/qqtmsgbox.ui
