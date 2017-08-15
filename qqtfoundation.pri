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

INCLUDEPATH += $$PWD

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

    wince*: SOURCES += $$PWD/qdevicewatcher_wince.cpp
    else:  SOURCES += $$PWD/qdevicewatcher_win32.cpp
}

unix {
    macx {
        SOURCES += $$PWD/qdevicewatcher_mac.cpp
        LIBS += -framework DiskArbitration -framework Foundation
    } else {
        SOURCES += $$PWD/qdevicewatcher_linux.cpp
    }

    HEADERS += $$PWD/qqtpreviewwidget.h \
                $$PWD/dmmu.h \
                $$PWD/jz_cim.h \
                $$PWD/graphics.h \
                $$PWD/hal.h \
                $$PWD/qqtethenetmanager.h \
                $$PWD/qqtwifiwidget.h \
                #linux base type
                $$PWD/qqtlinux.h

    SOURCES += $$PWD/qqtpreviewwidget.cpp \
                $$PWD/dmmu.c \
                $$PWD/qqtethenetmanager.cpp \
                $$PWD/qqtwifiwidget.cpp

    FORMS   += $$PWD/qqtpreviewwidget.ui \
                $$PWD/qqtwifiwidget.ui
}

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
    $$PWD/qcpdocumentobject.cpp \
    $$PWD/qcustomplot.cpp \
    $$PWD/qqtclient.cpp \
    $$PWD/qqtlineeditwithsearch.cpp \
    $$PWD/qqtplayer.cpp \
    $$PWD/qqtpluginwatcher.cpp \
    $$PWD/qqtserialport.cpp \
    $$PWD/qqtserver.cpp \
    $$PWD/qqttablemodel.cpp \
    $$PWD/qqtstandarditemmodel.cpp \
    $$PWD/qdevicewatcher.cpp \
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
    $$PWD/qqtpassworddialog.cpp \
    $$PWD/qqtprogressdialog.cpp \
    $$PWD/qqtcloudprotocol.cpp \
    $$PWD/qqtmessage.cpp \
    $$PWD/qqtprotocol.cpp \
    $$PWD/qqtserialmessage.cpp \
    $$PWD/qqtnetworkmessage.cpp \
    $$PWD/qqtuserserialprotocol.cpp \
    $$PWD/qqtlanprotocol.cpp \
    $$PWD/qqtanimation.cpp \
    $$PWD/qqtanimationmanager.cpp

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
    $$PWD/qcpdocumentobject.h \
    $$PWD/qcustomplot.h \
    $$PWD/qqtclient.h \
    $$PWD/qqtlineeditwithsearch.h \
    $$PWD/qqtplayer.h \
    $$PWD/qqtpluginwatcher.h \
    $$PWD/qqtserialport.h \
    $$PWD/qqtserver.h \
    $$PWD/qqttablemodel.h \
    $$PWD/qqtstandarditemmodel.h \
    $$PWD/qdevicewatcher.h \
    $$PWD/qdevicewatcher_p.h \
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
    $$PWD/qqtpassworddialog.h \
    $$PWD/qqtprogressdialog.h \
    $$PWD/qqtcloudprotocol.h \
    $$PWD/qqtprotocol.h \
    $$PWD/qqtmessage.h \
    $$PWD/qqtserialmessage.h \
    $$PWD/qqtnetworkmessage.h \
    $$PWD/qqtuserserialprotocol.h \
    $$PWD/qqtlanprotocol.h \
    $$PWD/qqtanimation.h \
    $$PWD/qqtanimationmanager.h


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
    $$PWD/qqtmptablewidget.ui \
    $$PWD/qqttablewidget.ui \
    $$PWD/qqttreewidget.ui \
    $$PWD/qqtinput.ui \
    $$PWD/qqtmsgbox.ui \
    $$PWD/qqtpassworddialog.ui \
    $$PWD/qqtprogressdialog.ui
