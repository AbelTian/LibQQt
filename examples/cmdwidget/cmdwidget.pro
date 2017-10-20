#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T09:34:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cmdwidget
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = qrc
UI_DIR = ui_h
DESTDIR = bin

QKIT_ = $$(QKIT)

message($${QKIT_} Defined in cmdwidget)

#MIPS __EMBEDDED_LINUX__
#LINUX64 __LINUX64__
#WIN64 __WIN64__

equals(QKIT_, MIPS32) {
    QT += multimedia
    DEFINES += __EMBEDDED_LINUX__
} else:equals(QKIT_, LINUX64){
    DEFINES += __LINUX64__
} else:equals(QKIT_, WIN64){
    DEFINES += __WIN64__
}

SOURCES += main.cpp\
        cmdwidget.cpp \
    rlineedit.cpp

HEADERS  += cmdwidget.h \
    rlineedit.h

FORMS    += cmdwidget.ui
