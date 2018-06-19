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
#use LibQQt you need change Qt Creator default build directory: your-pc-build-station/%{CurrentProject:Name}/%{Qt:Version}/%{CurrentKit:FileSystemName}/%{CurrentBuild:Name}
#in Qt kit page, set kit's File System Name. (Creator Ver.>v3.5)
#in project build page, def env QKIT
#in app_configure.pri (auto createed) define QQT_BUILD_ROOT= and QQT_SDK_ROOT= and or APP_DEPLOY_ROOT

#################################################################
##project name
#################################################################
TARGET = QQt
TEMPLATE = lib

#in theory, this should not be limited to 4.8.0, no limit is good.
lessThan(QT_VERSION, 4.8.0) {
    message(A. ensure your compiler support c++11 feature)
    message(B. suggest Qt version >= 4.8.0)
    #error(  error occured!)
}

################################################
##project config and definition
##need QKIT to compitible with some occasion
################################################
include ($$PWD/qqt_qkit.pri)


isEmpty(QKIT_PRIVATE) {
    message(1. you should change qt default build directory to your-pc-build-station/%{CurrentProject:Name}/%{Qt:Version}/%{CurrentKit:FileSystemName}/%{CurrentBuild:Name})
    message(2. env variable QKIT is required! pleace check qqt_qkit.pri)
    error(error occured! please check build output panel.)
}

################################################
##project function
##support some commonly used function
################################################
include ($$PWD/qqt_function.pri)


##win platform: some target, special lib lib_bundle staticlib
##only deal dynamic is ok, static all in headers dealing.
##define macro before header.
contains(QKIT_PRIVATE, WIN32|WIN64) {
    #Qt is static by mingw32 building
    mingw {
        #on my computer , Qt library are all static library?
        #create static lib (important, only occured at builder pro)
        CONFIG += staticlib
        #in qqt_header.pri
        #DEFINES += QQT_STATIC_LIBRARY
    } else {
        #create dynamic lib (important, only occured at builder pro)
        CONFIG += dll
        #no other one deal this, define it here, right here.
        DEFINES += QQT_LIBRARY
    }
#*nux platform: no macro
} else {
    equals(QKIT_PRIVATE, macOS) {
        CONFIG += dll
        CONFIG += lib_bundle
    } else:contains(QKIT_PRIVATE, iOS|iOSSimulator) {
        CONFIG += static
    } else {
        ##default build dll
        CONFIG += dll
        #*nix no need this macro
        #DEFINES += QQT_LIBRARY
    }
}

#create prl
CONFIG += create_prl
#CONFIG += build_pass
build_pass:CONFIG(debug, debug|release) {
    #troublesome
    #win32: TARGET = $$join(TARGET,,,d)
}
#CONFIG += debug_and_release
#CONFIG += build_all
#if some bug occured, maybe this help me, close some warning
CCFLAG =
!win32:CCFLAGS = -Wno-unused-parameter -Wno-reorder -Wno-c++11-extensions -Wno-c++11-long-long -Wno-comment
QMAKE_CFLAGS +=  $${CCFLAGS}
QMAKE_CXXFLAGS +=  $${CCFLAGS}

#################################################################
##build cache
#################################################################
#LibQQt工程里，这个值是不允许改变的，但是再App工程里可以改变。
DESTDIR = bin

#################################################################
##project Headers
#################################################################
include ($$PWD/qqt_header.pri)

#################################################################
##project source
#################################################################
include ($$PWD/qqt_source.pri)

#################################################################
##project version
#################################################################
include ($$PWD/qqt_version.pri)

#user can use app_version.pri to modify app version once, once is all. DEFINES += APP_VERSION=0.0.0 is very good.
unix:VERSION = $${QQT_VERSION}
#bug?:open this macro, TARGET will suffixed with major version.
#win32:VERSION = $${QQT_VERSION4}

QMAKE_TARGET_FILE = "$${TARGET}"
QMAKE_TARGET_PRODUCT = "$${TARGET}"
QMAKE_TARGET_COMPANY = "www.qqt.com"
QMAKE_TARGET_DESCRIPTION = "QQt Foundation Class"
QMAKE_TARGET_COPYRIGHT = "Copyright 2015-2020 QQt Co., Ltd. All rights reserved"

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
DISTFILES += \
    qqt.qrc \
    linux_cp_files.sh \
    linux_cur_path.sh \
    linux_cd_path.sh \
    linux_read_ini.sh \
    linux_write_ini.sh \
    win_read_ini.bat

#################################################################
##QQt Lib工程持续编译
#################################################################
#如果不touch一下,资源文件改变不会引发编译,可是我们需要编译一下,不开持续编译,岂不是漏失?
#修改pro,如果不需要编译源文件,还是编译了一下,岂不是多余?
#权衡利弊,在qqt工程里开启开关.保证用户在编译源代码的时候,任何改动一定持续生效.
#依赖touch命令 :|
#QQt持续编译配置开关
CONFIG += continued_build
contains(CONFIG, continued_build){
    system("touch $${PWD}/frame/qqtapplication.cpp")
}

#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})
