#--------------------------------------------------------------------------------
#multi_link_technology.pri
#提供所有multi link技术的功能函数
#包括设定必需目录的要求
#--------------------------------------------------------------------------------

################################################################################
#多链接技术的路径依赖
################################################################################
CONFIG_PATH =
CONFIG_FILE =

equals(QMAKE_HOST.os, Windows) {
    #>=v2.4
    CONFIG_PATH = $$user_home()\\.qmake
    #CONFIG_PATH = $$user_config_path()\\qmake
    CONFIG_FILE = $${CONFIG_PATH}\\app_configure.pri
} else {
    CONFIG_PATH = $$user_config_path()/.qmake
    CONFIG_FILE = $${CONFIG_PATH}/app_configure.pri
}

!exists($${CONFIG_FILE}) {
    mkdir("$${CONFIG_PATH}")
    empty_file($${CONFIG_FILE})
    ret = $$system(echo APP_BUILD_ROOT = >> $${CONFIG_FILE})
    ret = $$system(echo APP_DEPLOY_ROOT = >> $${CONFIG_FILE})
    ret = $$system(echo LIB_SDK_ROOT = > $${CONFIG_FILE})
}

#your must config this file! following readme!
include ($${CONFIG_FILE})

#qqt build root, build station root
#link_from_build will need this path.
isEmpty(APP_BUILD_ROOT)|isEmpty(LIB_SDK_ROOT)|isEmpty(APP_DEPLOY_ROOT){
    message($${TARGET} multiple linking config file: $${CONFIG_FILE})
    message("APP_BUILD_ROOT = is required, please modify $${CONFIG_FILE}")
    message("APP_DEPLOY_ROOT = is required [optional]")
    message("LIB_SDK_ROOT = is required")
    message("[linux platform, ]this pri is under multi_link_technology.pri")
    error("please check $$CONFIG_FILE")
}

#message($${TARGET} build root: $$APP_BUILD_ROOT)
#message($${TARGET} deploy root: $$APP_DEPLOY_ROOT)
#equals(TEMPLATE, app):message($${TARGET} use sdk root: $$LIB_SDK_ROOT)
#else:message($${TARGET} deploy sdk root: $$LIB_SDK_ROOT)

isEmpty(APP_BUILD_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(APP_BUILD_ROOT = /user/set/path is required, please modify app_configure.pri )
    error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
}
#deploy root
isEmpty(APP_DEPLOY_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(APP_DEPLOY_ROOT = /user/set/path is required, please modify app_configure.pri )
    error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
}
isEmpty(LIB_SDK_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(LIB_SDK_ROOT = /user/set/path is required, please modify app_configure.pri )
    error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
}
