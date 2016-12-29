#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

QT       += core gui network sql

CONFIG += serialport

DEFINES += _TTY_POSIX_

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

QT_KIT = $$(QKIT)

message($${QT_KIT} Defined in qqtfoundation)

#MIPS __MIPS_LINUX__
#PC64 __LINUX64__

equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else {
    DEFINES += __LINUX64__
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}

SOURCES += \
        $$PWD/qqtcheckbox.cpp \
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
    $$PWD/qdevicewatcher_linux.cpp \
        $$PWD/qqtpreviewwidget.cpp \
    $$PWD/dmmu.c \
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
    $$PWD/qqtethenetmanager.cpp \
    $$PWD/qqtmessage.cpp \
    $$PWD/qqtprotocol.cpp \
    $$PWD/qqtserialmessage.cpp \
    $$PWD/qqtnetworkmessage.cpp \
    $$PWD/qqtuserserialprotocol.cpp \
    $$PWD/qqtlanprotocol.cpp

HEADERS  += \
        $$PWD/qqtcheckbox.h \
        $$PWD/qqtdefine.h \
    $$PWD/qqtdialog.h \
    $$PWD/qqtgui.h \
    $$PWD/qqtgui-qt.h \
    $$PWD/qqtheaderview.h \
    $$PWD/qqtlinux.h \
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
    $$PWD/dmmu.h \
    $$PWD/graphics.h \
    $$PWD/hal.h \
        $$PWD/qqtpreviewwidget.h \
    $$PWD/jz_cim.h \
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
    $$PWD/qqtethenetmanager.h \
    $$PWD/qqtprotocol.h \
    $$PWD/qqtmessage.h \
    $$PWD/qqtserialmessage.h \
    $$PWD/qqtnetworkmessage.h \
    $$PWD/qqtuserserialprotocol.h \
    $$PWD/qqtlanprotocol.h

FORMS    += \
        $$PWD/qqtcheckbox.ui \
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
        $$PWD/qqtpreviewwidget.ui \
    $$PWD/qqtmptablewidget.ui \
    $$PWD/qqttablewidget.ui \
        $$PWD/qqttreewidget.ui \
        $$PWD/qqtinput.ui \
    $$PWD/qqtmsgbox.ui \
