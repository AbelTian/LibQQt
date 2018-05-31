#---------------------------------------------------------------------
#add_deploy_config.pri
#用于发布app的配置文件。只是app工程使用

#这个目录一般在源代码目录里
#add_deploy_config(<config_path>)
#---------------------------------------------------------------------

################################################################################
#内部用函数
################################################################################
defineReplace(add_deploy_config_on_mac) {
    dirs = $$1
    isEmpty(1)|!isEmpty(2): error("add_deploy_config_on_mac(dirs) requires one argument")

    command =
    command += $$COPY_DIR $${dirs} $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/ $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/
    #message($$command)
    return ($$command)
}


defineReplace(add_deploy_config_on_linux) {
    #need QQT_BUILD_PWD
    dirs = $$1
    isEmpty(1)|!isEmpty(2): error("add_deploy_config_on_linux(dirs) requires one argument")

    command =
    command += $$COPY_DIR $${dirs} $${APP_BUILD_PWD} $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEPLOY_PWD}
    #message($$command)
    return ($$command)
}

################################################################################
#外部用函数
################################################################################
defineTest(add_deploy_config) {
    APP_CONFIG_PWD = $$1
    isEmpty(1)|!isEmpty(2): error("add_deploy_config(app_config_pwd) requires one argument")

    equals(QMAKE_HOST.os, Windows) {
        APP_CONFIG_PWD~=s,/,\\,g
    }

    #起始位置 编译位置 中间目标位置
    APP_DEST_PWD=$${DESTDIR}
    isEmpty(APP_DEST_PWD):APP_DEST_PWD=.
    APP_BUILD_PWD = $$APP_DEST_PWD

    #deploy root
    isEmpty(APP_DEPLOY_ROOT){
        message($${TARGET} $${CONFIG_FILE})
        message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
        error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
    }

    #set app deploy pwd
    #APP_DEPLOY_PWD is here.
    #lib project会发布配置文件吗？
    APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET_PRIVATE}/$${QSYS_STD_DIR}
    #不仅仅发布目标为Windows的时候，才需要改变路径
    #开发机为Windows就必须改变。
    #contains(QKIT_PRIVATE, WIN32||WIN64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_DEPLOY_PWD~=s,/,\\,g
    }
    message($${TARGET} deployes config to $$APP_DEPLOY_PWD)

    #如果 TARGET 没有配置 APP_CONFIG_PWD 那么返回，不拷贝任何配置
    #qmake 或逻辑为 | 或者 ||
    isEmpty(APP_CONFIG_PWD)|isEmpty(APP_DEPLOY_PWD) {
        message("$${TARGET} hasn't deployed any config files")
        return(0)
    }

    ##4.8 qmake arm32 return() 函数无效
    ##qmake 与逻辑为 :
    !isEmpty(APP_CONFIG_PWD):!isEmpty(APP_DEPLOY_PWD) {
        message("$${TARGET} has deploied some config files")
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$add_deploy_config_on_mac("$${APP_CONFIG_PWD}/*")
    } else: contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        QMAKE_POST_LINK += $$add_deploy_config_on_linux("$${APP_CONFIG_PWD}\\*")
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        #分为Host为Windows和类Unix两种情况。
        #Android下使用qrc，无法发布配置文件。
        equals(QMAKE_HOST.os, Windows){
        } else {
        }
    } else {
        QMAKE_POST_LINK += $$add_deploy_config_on_linux("$${APP_CONFIG_PWD}/*")
    }

    export(QMAKE_POST_LINK)

    return (1)
}
