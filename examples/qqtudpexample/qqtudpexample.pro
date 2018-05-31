#-------------------------------------------------
#
# Project created by QtCreator 2018-01-30T15:14:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqtudpexample
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    cedianudpmessage.cpp \
    cedianudpprotocol.cpp \
    cedianudpserver.cpp \
    kongzhiqiudpmessage.cpp \
    kongzhiqiudpprotocol.cpp


HEADERS += \
        mainwindow.h \
    cedianudpmessage.h \
    cedianudpprotocol.h \
    cedianudpserver.h \
    kongzhiqiudpmessage.h \
    kongzhiqiudpprotocol.h


FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

#促使编译源代码，qmake pri配置里面的QMAKE_XX_LINK命令就会执行。
system("touch main.cpp")
include(../../multi-link/add_base_manager.pri)
include (../../app-lib/add_custom_manager.pri)

#这个的设置有特点，要先设置
add_version (1,0,0,0)

#先发布App
#app从build到deploy
add_deploy()

#后发布依赖
#libQQt从sdk到build和deploy
add_dependent_manager_QQt()

