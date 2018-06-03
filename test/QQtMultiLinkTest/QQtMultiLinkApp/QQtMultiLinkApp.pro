#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T13:55:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQtMultiLinkApp
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

#必须的，否则POST LINK不启动
system(touch main.cpp)

include (../../../multi-link/add_base_manager.pri)

#这个的设置有特点，要先设置
add_version (1,0,0,0)

#先发布App
#app从build到deploy
add_deploy()

#后发布依赖
#libQQt从sdk到build和deploy
add_dependent_manager(QQt)

#发布配置文件 把AppRoot里的配置项目拷贝到运行目录和发布目录
add_deploy_config($${PWD}/AppRoot)

#对于这个先后顺序，macOS下要求比较严格。
#必须先发布App

#添加语言 de_DE
add_language($${PWD}/$${TARGET}.pro, $${PWD}/AppRoot/lang, de_DE)
#添加语言 zh_CN en_US
add_zh_CN_en_US($${PWD}/$${TARGET}.pro, $${PWD}/AppRoot/lang)

add_include(QQtBasedLibTest)
add_library(QQtBasedLibTest)
add_deploy_library(QQtBasedLibTest)
mingw:add_defines(QQTBASEDLIBTEST_STATIC_LIBRARY)

message($$QMAKE_PRE_LINK)
message($$QMAKE_POST_LINK)
