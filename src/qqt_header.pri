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
message($${QT_KIT} Defined to $${TARGET})
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
    DEFINES += __LINUX64__
} else:equals(QT_KIT, WIN) {
    DEFINES += __WIN__
} else:equals(QT_KIT, WIN64) {
    DEFINES += __WIN64__
} else:equals(QT_KIT, macOS) {
    DEFINES += __DARWIN__
} else:equals(QT_KIT, Android) {
    DEFINES += __ANDROID__
} else:equals(QT_KIT, ANDROIDX86) {
    DEFINES += __ANDROIDX86__
    #todo:no customplot word printer
}

CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}
win32 {
    win32:DEFINES += _CRT_SECURE_NO_WARNINGS #fopen fopen_s
    #QMAKE_CXXFLAGS += /wd"4819" /wd"4244" /wd"4100"
}


#############
##variables
#############
CONFIG(debug, debug|release) {
    BUILD=Debug
} else {
    BUILD=Release
}
equals(QT_KIT, MIPS32) {
    SYSNAME = Mips32
} else:equals(QT_KIT, LINUX) {
    SYSNAME = Linux
} else:equals(QT_KIT, LINUX64) {
    SYSNAME = Linux64
} else:equals(QT_KIT, WIN) {
    SYSNAME = Windows
} else:equals(QT_KIT, WIN64) {
    SYSNAME = Win64
} else:equals(QT_KIT, macOS) {
    SYSNAME = MacOS
} else:equals(QT_KIT, Android) {
    SYSNAME = Android
} else:equals(QT_KIT, ANDROIDX86) {
    SYSNAME = Android_x86
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

