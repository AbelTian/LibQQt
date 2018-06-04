#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtliveplayer
TEMPLATE = app

INCLUDEPATH +=  .

CONFIG += c++11

SOURCES += $$PWD/main.cpp $$PWD/qqtapp.cpp $$PWD/qqtwindow.cpp \
    animationmanager.cpp

HEADERS  += $$PWD/qqtapp.h $$PWD/qqtwindow.h \
    animationmanager.h

FORMS    += $$PWD/qqtwindow.ui

############################################
#添加所有提供函数的pri 很有美感
############################################
include(../../multi-link/add_base_manager.pri)

############################################
#对产品线的控制结构Multi-link下命令 开启产品线
############################################
#这个的设置有特点，要先设置
add_version (1,0,0,0)
#先发布App
#app从build到deploy
add_deploy()

#后发布依赖
#libQQt从sdk到build和deploy
add_dependent_manager(QQt)
#添加其他library
#libVLCQt从sdk到build和deploy
add_dependent_manager(VLC)
