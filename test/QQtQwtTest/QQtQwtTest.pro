#-------------------------------------------------
#
# Project created by QtCreator 2018-05-30T18:19:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQtQwtTest
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

system(touch main.cpp)

#基本上，用户包含这三个就足够。
#要添加library支持，按照模板添加一个pri文件， 使用add_dependent_manager(XXX)调用即可。
#用add_custom_manager.pri保存这些链接函数即可，拷贝到自己目录哦。
#add_custom_manager也不想用的，就加到自己pro文件里好了。
include (../../multi-link/add_base_manager.pri)
include (../../app-lib/add_custom_manager.pri)


#add version 调用时机 在lib里有个约束，必须在add_sdk之前调用，其他时候没有约束。
add_version(1,0,0,0)
add_deploy()

#app链接library lib也会链接
#app发布library 只有app才会发布

add_dependent_manager(QQt)
add_dependent_manager(Qwt)

#打印状态
message($$TARGET config $$CONFIG)
message($$TARGET define $$DEFINES)
message($$TARGET pre link $$QMAKE_PRE_LINK)
message($$TARGET post link $$QMAKE_POST_LINK)
message($$LIBS)
