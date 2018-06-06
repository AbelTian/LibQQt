#-------------------------------------------------
#
# Project created by QtCreator 2018-05-27T22:58:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQtOpenCVExample
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
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

system(touch main.cpp)
############################################
#添加所有提供函数的pri 很有美感
############################################
include (../../multi-link/multi-link/add_base_manager.pri)
include (../../multi-link/app-lib/add_library_OpenCV.pri)

############################################
#对产品线的控制结构Multi-link下命令 开启产品线
############################################
#这里做的事情，可以拷贝custom manager到app目录里再custom manager里面完成。
add_version(1,0,0,0)
add_deploy()
add_deploy_config($$PWD/AppRoot)

#添加其他library
#app 发布library OpenCV 只有app才会发布
add_dependent_manager(QQtBase)
add_dependent_library_OpenCV()

