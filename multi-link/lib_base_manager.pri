#---------------------------------------------------------------------------------
#app_base_manager.pri
#应用程序和Library的基础管理器，统一使用这个管理器。
#
#---------------------------------------------------------------------------------

################################################################################
#包含这个pri依赖的pri
################################################################################
include ($${PWD}/add_platform.pri)
include ($${PWD}/add_function.pri)

################################################################################
#多链接技术入口
################################################################################
include($${PWD}/add_multi_link_technology.pri)

################################################################################
#这里的pri提供multi link的全部函数
################################################################################
#app发布所需要的函数
#include ($${PWD}/add_deploy.pri)

#app发布配置项需要的函数
#include ($${PWD}/add_deploy_config.pri)

#链接lib所需要的函数
include ($${PWD}/add_link.pri)

#lib version
include ($${PWD}/add_version.pri)

#lib发布sdk所需要的函数
include ($${PWD}/add_sdk.pri)

####################################################################################
#lib base manager 都做了一下这些事情
####################################################################################

#################################################################
##definition and configration
##need QSYS
#################################################################
##Qt version
QT += core sql network gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# release open debug output
CONFIG(debug, debug|release) {
} else {
    DEFINES -= QT_NO_DEBUG_OUTPUT
}

#mingw要加速编译，make -j20，-j参数是最好的解决办法。

#close win32 no using fopen_s warning
win32:DEFINES += _CRT_SECURE_NO_WARNINGS #fopen fopen_s

#msvc支持设置
msvc {
    MSVC_CCFLAGS =
    #this three pragma cause mingw errors
    msvc:MSVC_CCFLAGS += /wd"4819" /wd"4244" /wd"4100"

    #UTF8编码
    DEFINES += __MSVC_UTF8_SUPPORT__
    msvc:MSVC_CCFLAGS += /execution-charset:utf-8
    msvc:MSVC_CCFLAGS += /source-charset:utf-8
    #msvc:MSVC_CCFLAGS += /utf-8 #这一个是快捷方式，顶上边两个。

    #指定/mp编译选项，编译器将使用并行编译，同时起多个编译进程并行编译不同的cpp
    msvc:MSVC_CCFLAGS += /MP
    #指出：这个FLAG只能用于MSVC

    msvc:QMAKE_CFLAGS += $${MSVC_CCFLAGS}
    msvc:QMAKE_CXXFLAGS += $${MSVC_CCFLAGS}

    #指定stable.h这个头文件作为编译预处理文件，MFC里这个文件一般叫stdafx.h 然后在 stable.h里 包含你所用到的所有 Qt 头文件
    #在.pro 文件中加入一行, 加在这里，加速编译。
    #msvc:PRECOMPILED_HEADER = $${PWD}/qqt-qt.h
    #指出：precompiler header只能用于MSVC
    #这个功能可用，可是编译问题比较多，不方便，所以默认不开开。
}

CONFIG += create_prl
#################################################################
##build qqt or link qqt
#################################################################
##different target:
##-----------------------------------------------
##win platform:
##build qqt dll + QQT_LIBRARY
##build qqt lib + QQT_STATIC_LIBRARY
##link qqt lib + QQT_STATIC_LIBRARY
##link qqt dll + ~~
##- - - - - - - - - - - - - - - - - - - - -
##*nix platform:
##build and link qqt dll or lib + ~~
##-----------------------------------------------
#link QQt static library in some occation on windows
#when link QQt    static library, if no this macro, headers can't be linked on windows.
contains(QSYS_PRIVATE, Win32|Win64 || iOS|iOSSimulator) {
    #Qt is static by mingw32 building
    mingw|ios{
        #on my computer, Qt library are all static library?
        DEFINES += LIB_STATIC_LIBRARY
        message(Build $${TARGET} LIB_STATIC_LIBRARY is defined. build and link)
    }

    #link and build all need this macro
    contains(DEFINES, QQT_STATIC_LIBRARY) {
    }
}

################################################################
##build cache (此处为中间目标目录，对用户并不重要)
##此处加以干涉，使目录清晰。
##此处关于DESTDIR的设置，导致用户必须把这个文件的包含，提前到最前边的位置，才能进行App里的目录操作。
##删除干涉?
##用户注意：(done in app_base_manager), 首先include(app_link_qqt_library.pri)，然后做app的工作，和include其他pri，包括LibQQt提供的其他pri，保证这个顺序就不会出错了。
##对编译目标目录进行干涉管理，显得更加细腻。
##用户注意：这里相当于给编译中间目录加了一个自动校准，属于校正范畴。
################################################################
isEmpty(OBJECTS_DIR):OBJECTS_DIR = obj
isEmpty(MOC_DIR):MOC_DIR = obj/moc.cpp
isEmpty(UI_DIR):UI_DIR = obj/ui.h
isEmpty(RCC_DIR):RCC_DIR = qrc
#这样做保持了App工程和LibQQt工程中间目录的一致性，但是并不必要。
isEmpty(DESTDIR):DESTDIR = bin

################################################################
##QQt Functions Macro
################################################################
#You need switch these more macro according to your needs when you build this library
#You can tailor QQt  with these macro.
#Default: macroes is configed, some open, some close, compatibled to special accotation.
##App希望裁剪LibQQt，开关这个文件里的组件宏，用户有必要读懂这个头文件。up to so.

##################C++11 Module###############################
#if you use C++11, open this annotation. suggest: ignore
#DEFINES += __CPP11__
contains (DEFINES, __CPP11__) {
    #macOS gcc Qt4.8.7
    #qobject.h fatal error: 'initializer_list' file not found,
    #Qt4.8.7 can't support c++11 features
    #QMAKE_CXXFLAGS += "-std=c++11"
    #QMAKE_CXXFLAGS += "-std=c++0x"

    #below: gcc version > 4.6.3
    #Open this Config, Why in Qt4 works? see qmake config auto ignored this feature.
    #In Qt5? don't need open this config, qmake auto add c++11 support on linux plat.
    #on windows mingw32? need test
    #CONFIG += c++11

    #compile period
    #LibQQt need c++11 support. Please ensure your compiler version.
    #LibQQt used override identifier
    #lambda also need c++11
}

#################################################################
##library
##################################################################
equals (QKIT_PRIVATE, iOSSimulator):{
    #error need
    #QMAKE_CXXFLAGS +=-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk
}

win32 {
    LIBS += -luser32
}else: unix {
    equals(QSYS_PRIVATE, macOS) {
        #min macosx target
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
        #deperated
        #QMAKE_MAC_SDK=macosx10.12
        #MACOSXSDK = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX$${QMAKE_MACOSX_DEPLOYMENT_TARGET}.sdk
        #QMAKE_LIBDIR = $${MACOSXSDK}
        #LIBS += -F$${MACOSXSDK}/System/Library/Frameworks
        #LIBS += -L$${MACOSXSDK}/usr/lib
        LIBS += -framework DiskArbitration -framework Cocoa -framework IOKit
    }else:contains(QSYS_PRIVATE, iOS|iOSSimulator){
        QMAKE_LFLAGS += -ObjC -lsqlite3 -lz
        QMAKE_IOS_DEPLOYMENT_TARGET = 8
    }
}


#用户有必要设置APP_VERSION
#add_version(1,0,0,0)

#用户有必要发布SDK 给其他APP用
#add_sdk()

#add_link(QQt)
#add_include(QQt)
