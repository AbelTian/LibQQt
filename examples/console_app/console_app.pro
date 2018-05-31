QT -= gui

CONFIG += c++11
#防止弹出一个控制台窗口
CONFIG -= console
#我需要使用console窗口，所以
CONFIG += console
#苹果电脑下我不使用bundle
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp

#促使编译源代码，qmake pri配置里面的QMAKE_XX_LINK命令就会执行。
system("touch main.cpp")
#用户在console工程中，只要不使用LibQQt的图形Class，就可以在控制台程序中游刃有余的完成app功能了。
#你用也没必要，而且不能用，控制台工程就是不能用widgets。不如在widgets工程当中隐藏窗口，然后在某个时机显示。
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

