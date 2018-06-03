#---------------------------------------------------------------------
#add_deploy_config.pri
#用于发布app的配置文件。只是app工程使用

#这个目录一般在源代码目录里
#add_deploy_config(<config_path>, <dest_path>)
#add_deploy_config_bundle(<config_path>, <dest_path>) #这个mac下bundle一定会发布到bundle里面
#---------------------------------------------------------------------

################################################################################
#内部用函数
################################################################################
defineReplace(get_add_deploy_config) {
    isEmpty(1): error("get_add_deploy_config(app_config_pwd, app_target_pwd) requires at least one argument")
    !isEmpty(3): error("get_add_deploy_config(app_config_pwd, app_target_pwd) requires at most two argument")

    source_config_path = $$1
    target_config_path = $$2

    command =
    #目标路径不为空，则拷贝配置文件过去。
    !isEmpty(target_config_path) {
        command += $$MK_DIR $${target_config_path} $$CMD_SEP
        command += $$COPY_DIR $${source_config_path} $${target_config_path} $$CMD_SEP
    } else {
        contains(QMAKE_HOST.os, Darwin):contains(CONFIG, app_bundle){
            target_config_path=$${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS
            command += $$COPY_DIR $${source_config_path} $${target_config_path} $$CMD_SEP

            target_config_path=$${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS
            command += $$COPY_DIR $${source_config_path} $${target_config_path} $$CMD_SEP
        } else {
            target_config_path=$${APP_BUILD_PWD}
            command += $$COPY_DIR $${source_config_path} $${target_config_path} $$CMD_SEP

            target_config_path=$${APP_DEPLOY_PWD}
            command += $$COPY_DIR $${source_config_path} $${target_config_path} $$CMD_SEP
        }
    }
    command += echo .
    #message($$command)

    return ($$command)
}

################################################################################
#外部用函数
################################################################################
defineTest(add_deploy_config) {
    isEmpty(1): error("add_deploy_config(app_config_pwd, app_target_pwd) requires at least one argument")
    !isEmpty(3): error("add_deploy_config(app_config_pwd, app_target_pwd) requires at most two argument")

    APP_CONFIG_PWD = $$1
    APP_TARGET_PWD = $$2
    isEmpty(APP_TARGET_PWD):APP_TARGET_PWD =
    equals(QMAKE_HOST.os, Windows) {
        APP_CONFIG_PWD~=s,/,\\,g
        APP_TARGET_PWD~=s,/,\\,g
    }

    #起始位置 编译位置 中间目标位置
    APP_BUILD_PWD=$${DESTDIR}
    isEmpty(APP_BUILD_PWD):APP_BUILD_PWD=.

    #set app deploy pwd
    #APP_DEPLOY_PWD is here.
    #lib project会发布配置文件吗？
    APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET_NAME}/$${QSYS_STD_DIR}
    #不仅仅发布目标为Windows的时候，才需要改变路径
    #开发机为Windows就必须改变。
    #contains(QKIT_PRIVATE, WIN32||WIN64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_DEPLOY_PWD~=s,/,\\,g
    }

    #如果 TARGET 没有配置 APP_CONFIG_PWD 那么返回，不拷贝任何配置
    #qmake 或逻辑为 | 或者 ||
    isEmpty(APP_CONFIG_PWD):isEmpty(APP_DEPLOY_PWD) {
        message("$${TARGET} hasn't deployed any config files")
        return(0)
    }

    ##4.8 qmake arm32 return() 函数无效
    ##qmake 与逻辑为 :
    !isEmpty(APP_CONFIG_PWD):!isEmpty(APP_DEPLOY_PWD) {
        message("$${TARGET} has deployed some config files")
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        QMAKE_POST_LINK += $$get_add_deploy_config("$${APP_CONFIG_PWD}\\*", $${APP_TARGET_PWD})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        #分为Host为Windows和类Unix两种情况。
        #Android下使用qrc，无法发布配置文件。
        equals(QMAKE_HOST.os, Windows){
        } else {
        }
    } else {
        #macOS linux都走这里
        QMAKE_POST_LINK += $$get_add_deploy_config("$${APP_CONFIG_PWD}/*", $${APP_TARGET_PWD})
    }

    export(QMAKE_POST_LINK)

    return (1)
}
