#---------------------------------------------------------------------------------
#lib_base_manager.pri
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
#
include ($${PWD}/add_base_header.pri)

#app发布所需要的函数
include ($${PWD}/add_deploy.pri)

#app发布配置项需要的函数
include ($${PWD}/add_deploy_config.pri)

#链接lib所需要的函数 包含lib头文件所需要的函数 设置lib宏所需要的函数
include ($${PWD}/add_library.pri)

#program version
include ($${PWD}/add_version.pri)

#lib发布sdk所需要的函数
include ($${PWD}/add_sdk.pri)

####################################################################################
#base manager 都做了一下这些事情
####################################################################################

#################################################################
##definition and configration
##need QSYS
#################################################################
##win platform: some target, special lib lib_bundle staticlib
##only deal dynamic is ok, static all in headers dealing.
##define macro before header.
contains(QSYS_PRIVATE, Win32|Win64) {
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
        DEFINES += LIB_LIBRARY
    }
#*nux platform: no macro
} else {
    equals(QSYS_PRIVATE, macOS) {
        CONFIG += dll
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

