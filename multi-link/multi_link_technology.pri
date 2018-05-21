#--------------------------------------------------------------------------------
#multi_link_technology.pri
#提供所有multi link技术的功能函数
#包括设定必需目录的要求
#--------------------------------------------------------------------------------

################################################################################
#包含这个pri依赖的pri
################################################################################
include ($${PWD}/app_platform.pri)
include ($${PWD}/app_function.pri)

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
isEmpty(APP_BUILD_ROOT)|isEmpty(LIB_SDK_ROOT) {
    message($${TARGET} multiple linking config file: $${CONFIG_FILE})
    message("APP_BUILD_ROOT = is required, please modify $${CONFIG_FILE}")
    message("APP_DEPLOY_ROOT = is required [optional]")
    message("LIB_SDK_ROOT = is required")
    message("[linux platform, ]this pri is under multi_link_technology.pri")
    error("please check $$CONFIG_FILE")
}

message($${TARGET} build root: $$APP_BUILD_ROOT)
message($${TARGET} deploy root: $$APP_DEPLOY_ROOT)
equals(TEMPLATE, app):message($${TARGET} use sdk root: $$LIB_SDK_ROOT)
else:message($${TARGET} deploy sdk root: $$LIB_SDK_ROOT)

################################################################################
#这里的pri提供multi link的全部函数
################################################################################
#app发布所需要的函数
include ($${PWD}/app_deploy.pri)

#app链接所需要的函数
include ($${PWD}/app_link.pri)
