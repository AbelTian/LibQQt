#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
#Project link: https://gitee.com/drabel/LibQQt
#github link: https://github.com/AbelTian/LibQQt

#2017年11月10日18:53:56
#if you succeed with LibQQt, please thumb up.

#2018年02月09日10:40:10
#开发者建议：中级工程师及以上学者，再打算学习这些pri文件的思路、结构、编写。

#2018年02月13日09:58:25
#LibQQt设计宗旨：为内存服务。Service for memory.

#################################################################
##Usage
#################################################################
#Suggest Qt 5.9.2/4.8.6/4.8.7
#please dont use Qt 5.9.1, it is broken with android and ios.
#please dont modify this pro
#use LibQQt you need change Qt Creator default build directory: your-pc-build-station/%{CurrentProject:Name}/%{CurrentKit:FileSystemName}
#in Qt kit page, set kit's File System Name. (Creator Ver.>v3.5)
#in project build page, def env QSYS
#in app_configure.pri (auto createed) define QQT_BUILD_ROOT= and QQT_SDK_ROOT= and or APP_DEPLOY_ROOT

#################################################################
##project name
#################################################################
TARGET = QQtBase
TEMPLATE = lib

#################################################################
#包含基础管理者
#################################################################
include ($${PWD}/../multi-link/multi-link/add_base_manager.pri)

#根据multi-link提供的动态编译 静态编译设定进行编译，添加我自己的QQt的宏定义。
contains(DEFINES, LIB_LIBRARY) {
    DEFINES += QQT_LIBRARY
    message(Build $${TARGET} QQT_LIBRARY is defined. build)
}

#static library宏的管理，一律放在头文件.pri

#################################################################
##project version
#################################################################
#这个的设置有特点，要先设置
add_version(2,4,0,0)

#自定义宏
DEFINES += QQT_VERSION=$$APP_VERSION

#user can use app_version.pri to modify app version once, once is all. DEFINES += APP_VERSION=0.0.0 is very good.
#unix:VERSION = $${QQT_VERSION}
#bug?:open this macro, TARGET will suffixed with major version.
#win32:VERSION = $${QQT_VERSION4}

#################################################################
##project header
#################################################################
#qqt_header.pri不再使用，而是直接修改multi-link里的add_library_QQtBase.pri
#方便链接者跟随最新的QQt变动，方便编辑者不必重复操作include代码。
#include ($$PWD/qqt_header.pri)

#使用add_library_XXX.pri导出include和defines
#对这个pri的调用，使用add_export_manager()
add_export_manager($$add_target_name())

#################################################################
##project source
#################################################################
include ($$PWD/qqt_source.pri)

#################################################################
#发布SDK 必要
#所有App都依赖QQt的这个步骤
#################################################################
#可选修饰函数
#add_project_name(QQtCore)
#add_source_dir($$PWD)
#add_build_dir($$DESTDIR)

#导出include和library
#目标
#源代码目录
#编译在相对编译目录
add_sdk(QQt, $$add_target_name())

#额外做点事情 拷贝头文件 没有后缀的头文件
add_sdk_header(QQt, $$add_target_name(), QQtApplication, frame)

#################################################################
#其他设置
#################################################################
QMAKE_TARGET_FILE = "$${TARGET}"
QMAKE_TARGET_PRODUCT = "$${TARGET}"
QMAKE_TARGET_COMPANY = "www.$${TARGET}.com"
QMAKE_TARGET_DESCRIPTION = "$${TARGET} Foundation Class"
QMAKE_TARGET_COPYRIGHT = "Copyright 2017-2042 $${TARGET} Co., Ltd. All rights reserved"

win32 {
    #common to use upload, this can be ignored.
    #open this can support cmake config.h.in
    #configure_file(qqtversion.h.in, qqtversion.h) control version via cmake.
    #qmake version config and cmake version config is conflicted
    #RC_FILE += qqt.rc
    #RC_ICONS=
    RC_LANG=0x0004
    RC_CODEPAGE=
}

################################################
##project resource
################################################
RESOURCES += \
    $${PWD}/qqt.qrc

#################################################################
##QQt Lib工程持续编译
#################################################################
#如果不touch一下,资源文件改变不会引发编译,可是我们需要编译一下,不开持续编译,岂不是漏失?
#修改pro,如果不需要编译源文件,还是编译了一下,岂不是多余?
#权衡利弊,在qqt工程里开启开关.保证用户在编译源代码的时候,任何改动一定持续生效.
#依赖touch命令 :|
#QQt持续编译配置开关
#QQt用户请注意，在这里我开启了持续编译，以保证用户对QQt本身的修改生效
CONFIG += continue_build
contains(CONFIG, continue_build){
    system("touch $${PWD}/frame/qqtapplication.cpp")
}

#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})
message ($${TARGET} pre link $${QMAKE_PRE_LINK})
message ($${TARGET} post link $${QMAKE_POST_LINK})
