#---------------------------------------------------------------------------------
#add_base_manager.pri
#应用程序和Library的基础管理器，统一使用这个管理器。
#---------------------------------------------------------------------------------
#简介
#在这个管理器里，App和Lib工程其实是区分开的。
#尤其动态编译 配置开关、宏定义 是在这里处理的，但是静态编译 配置开关在这里、宏定义在base_header里。这里需要加强理解。
#这是重点。

################################################################################
#包含这个pri依赖的pri
#设置目标平台 QSYS
################################################################################
include ($${PWD}/add_platform.pri)
include ($${PWD}/add_function.pri)

################################################################################
#多链接技术入口
#配置重要的三个路径 APP_BUILD_ROOT APP_DEPLOY_ROOT LIB_SDK_ROOT
################################################################################
include($${PWD}/add_multi_link_technology.pri)

################################################################################
#这里的pri提供multi link的全部函数
#增加发布
#增加发布配置
#增加链接库
#增加链接库头文件
#增加SDK (lib用)
#增加版本信息
################################################################################
#app发布所需要的函数
include ($${PWD}/add_deploy.pri)

#app发布library所需要的函数
include ($${PWD}/add_deploy_library.pri)

#app发布配置项需要的函数
include ($${PWD}/add_deploy_config.pri)

#链接lib所需要的函数 包含lib头文件所需要的函数 设置lib宏所需要的函数
include ($${PWD}/add_library.pri)

#lib发布sdk所需要的函数
include ($${PWD}/add_sdk.pri)

#program version
include ($${PWD}/add_version.pri)

#program language
include ($${PWD}/add_language.pri)

####################################################################################
#base manager 都做了以下这些事情
####################################################################################
#################################################################
##definition and configration
##need QSYS
#################################################################
#这个编译，build pane比较简洁
CONFIG += silent

contains(TEMPLATE, app) {
    #add base manager对App的处理很少，App通过函数基本上能解决所有的事情
    #macOS下必须开开bundle
    contains(QSYS_PRIVATE, macOS){
        CONFIG += app_bundle
    }
} else: contains(TEMPLATE, lib) {
    ##base manager 对lib的处理很重要
    ##区分了在不同目标下Qt library的不同形态，其实就是要求lib工程和Qt library保持一样的状态。
    ##尤其在windows平台下，还提供了LIB_STATIC_LIBRARY 和 LIB_LIBRARY两个宏的支持
    ##帮助用户区分lib的状态。
    ##注意：在app下，永远没有dll或者static字样，只有lib有

    ##win platform: some target, special lib lib_bundle staticlib
    ##only deal dynamic is ok, static all in headers dealing.
    ##define macro before header.
    #专门为lib工程设置
    contains(QSYS_PRIVATE, Win32|Windows|Win64) {
        #Qt is static by mingw32 building
        mingw {
            #on my computer , Qt library are all static library?
            #create static lib (important, only occured at builder pro)
            CONFIG += staticlib
            #在add_base_header里设置
            #DEFINES += LIB_STATIC_LIBRARY
            #在我电脑上编译别的lib mingw下是dll格式的。
            #CONFIG += dll
            #DEFINES += LIB_LIBRARY
            #mingw编译为静态有原因：动态库可以编译成功，但是无法链接成功。
            #message(Build $${TARGET} LIB_LIBRARY is defined. build)
        } else {
            #create dynamic lib (important, only occured at builder pro)
            CONFIG += dll
            #no other one deal this, define it here, right here.
            DEFINES += LIB_LIBRARY
            message(Build $${TARGET} LIB_LIBRARY is defined. build)
        }
    #*nux platform: no macro
    } else {
        contains(QSYS_PRIVATE, macOS) {
            CONFIG += dll
            #macOS下必须开开bundle
            CONFIG += lib_bundle
        } else:contains(QSYS_PRIVATE, iOS|iOSSimulator) {
            CONFIG += static
        } else {
            ##default build dll
            CONFIG += dll
            #*nix no need this macro
            #DEFINES += LIB_LIBRARY
        }
    }

    #CONFIG += build_pass
    build_pass:CONFIG(debug, debug|release) {
        #troublesome
        #win32: TARGET = $$join(TARGET,,,d)
    }

    #lib 必须创建prl
    #create sdk need
    CONFIG += create_prl
}

#################################################################
#公共的基础header.pri，这个的作用在于不需要区分app和lib的设置都在这里面。
#包含基本的编译设置 qqt_header.pri里的设置更详细
#################################################################
include ($${PWD}/add_base_header.pri)

#################################################################
##此处代码完成包含(链接+发布)libQQt的函数
##这里是对QQt的lib的支持。
##这个支持是有条件的：如果用户移动了Multi-link技术文件夹，那么不再自动加入支持，用户需要手动include(add_library_QQt.pri)，和使用其他的lib一样。
##这个支持有个特点，因为LibQQt是开源的，所以这个pri依赖了qqt_header.pri，所以这个pri不能移动，一旦移动就会失去效果。
#################################################################
!equals(TARGET, QQt):
    exists($${PWD}/../app-lib/add_library_QQt.pri):
    exists($${PWD}/../src/core/qqtcore.cpp) {
    include ($${PWD}/../app-lib/add_library_QQt.pri)
}

#message($$TARGET config $$CONFIG)
#message($$TARGET define $$DEFINES)
#message($$TARGET pre link $$QMAKE_PRE_LINK)
#message($$TARGET post link $$QMAKE_POST_LINK)
