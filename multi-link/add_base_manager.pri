#---------------------------------------------------------------------------------
#add_base_manager.pri
#应用程序和Library的基础管理器，统一使用这个管理器。
#---------------------------------------------------------------------------------

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
#公共的基础header.pri
#包含基本的Qt工程设置 qqt_header.pri里的设置更详细
include ($${PWD}/add_base_header.pri)

#################################################################
##definition and configration
##need QSYS
#################################################################
##win platform: some target, special lib lib_bundle staticlib
##only deal dynamic is ok, static all in headers dealing.
##define macro before header.
equals(TEMPLATE, lib) {
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
}

#lib 必须创建prl
contains(TEMPLATE, lib) {
    #create sdk need
    CONFIG += create_prl
}

#macOS下必须开开bundle
contains(QSYS_PRIVATE, macOS){
    contains(TEMPLATE, app) {
        CONFIG += app_bundle
    } else: contains(TEMPLATE, lib) {
        #仅仅用这个 这个是lib用的pri
        CONFIG += lib_bundle
    }
}

#################################################################
##此处代码完成包含(链接)libQQt
#################################################################
include ($${PWD}/../src/qqt_header.pri)

#把QQt SDK头文件路径加入进来 为搜索头文件而添加
#其实过去做的自动添加QQt头文件就是这个功能
#用户包含QQt头文件，就不必加相对路径了，方便了很多
defineTest(add_qqt_header){
    #包含QQt头文件的过程
    header_path = $$get_add_header(QQt)
    INCLUDEPATH += $$get_qqt_header($$header_path)
    export(INCLUDEPATH)
    return (1)
}

#包含QQt的头文件
add_qqt_header()

#细心的用户会发现，QQt的头文件包含了两次，一个在源代码目录里，一个在SDK目录里，两个并不冲突。系统只要搜索到一个目录里的就可以使用了。
#当然，我们确信，SDK目录里的头文件服从于源代码目录里的头文件。

#链接QQt
!equals(TARGET, QQt) {
    add_library(QQt)
}

#以上代码只完成了链接libQQt 包含libQQt头文件 包含libQQt宏文件(在宏文件控制下Library的头文件才有精确的意义)
#没有发布libQQt
#App在开发中，调用发布App以后 必然需要调用app_deploy_library(QQt)发布QQt到运行时。强大的：从sdk发布到build和deploy位置。
#调试，正常；发布运行，正常。
