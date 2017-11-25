#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------
include(../examples/qqtframe2/link_qqt_library.pri)

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqthttpclient
TEMPLATE = app


INCLUDEPATH +=  .

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h

FORMS    += $$PWD/qqtwindow.ui
