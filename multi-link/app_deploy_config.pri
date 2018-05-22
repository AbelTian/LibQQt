#---------------------------------------------------------------------
#app_deploy_config.pri
#用于发布app的配置文件。
#---------------------------------------------------------------------

defineReplace(app_deploy_config_on_mac) {
    dirs = $$1
    !isEmpty(2): error("app_deploy_config_on_mac(dirs) requires one argument")
    isEmpty(1): error("app_deploy_config_on_mac(dirs) requires one argument")

    command =
    command += $$COPY_DIR $${dirs} $${APP_DEST_PWD}/$${TARGET}.app/Contents/MacOS/ $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/
    #message($$command)
    return ($$command)
}


defineReplace(app_deploy_config_on_linux) {
    #need QQT_BUILD_PWD
    dirs = $$1
    !isEmpty(2): error("app_deploy_config_on_linux(dirs) requires one argument")
    isEmpty(1): error("app_deploy_config_on_linux(dirs) requires one argument")
    command =
    command += $$COPY_DIR $${dirs} $${APP_DEST_PWD} $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEPLOY_PWD}
    #message($$command)
    return ($$command)
}

defineTest(app_deploy_config) {

    APP_CONFIG_PWD = $$1
    isEmpty(1)|!isEmpty(2): error("app_deploy_config(APP_CONFIG_PWD) requires one argument")

    #如果 TARGET 没有配置 APP_CONFIG_PWD 那么返回，不拷贝任何配置
    #qmake 或逻辑为 | 或者 ||
    isEmpty(APP_CONFIG_PWD)|isEmpty(APP_DEPLOY_PWD) {
        message("$${TARGET} hasn't deployed any config files")
        greaterThan(QT_MAJOR_VERSION, 5):return()
    }

    ##4.8 qmake arm32 return() 函数无效
    ##qmake 与逻辑为 :
    !isEmpty(APP_CONFIG_PWD):!isEmpty(APP_DEPLOY_PWD) {
        CONFIG += app_deploy_config
        message("$${TARGET} has deploied some config files")
    }

    isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32||Win64) {
        QMAKE_POST_LINK += $$app_deploy_config_on_linux("$${APP_CONFIG_PWD}\\*")
    } else: contains(QSYS_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$app_deploy_config_on_mac("$${APP_CONFIG_PWD}/*")
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        #分为Host为Windows和类Unix两种情况。
        #Android下使用qrc，无法发布配置文件。
        equals(QMAKE_HOST.os, Windows){
        } else {
        }
    } else {
        QMAKE_POST_LINK += $$app_deploy_config_on_linux("$${APP_CONFIG_PWD}/*")
    }

    return (1)
}

################################################################################
##work flow
################################################################################
APP_DEST_DIR=$${DESTDIR}
isEmpty(APP_DEST_DIR):APP_DEST_DIR=.

#这个需要用户手动调用.这个目录一般在源代码目录里
#app_deploy_config(<config_path>)
