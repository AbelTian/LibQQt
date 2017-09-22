#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
TARGET = QQt
TEMPLATE = lib

macx {
    CONFIG += lib_bundle
}

#QQT LIBRARY (DLL)
#DEFINES += QQT_LIBRARY

DEFINES += QQT_LIBRARY


include ($$PWD/qqt.pri)
