#---------------------------------------------------------------------
#应用程序配置文件拷贝qmake文件。通过qmake与编译调用。
#如果需要修改拷贝到发布目录里的配置文件，修改配置PWD下的文件，即可引起编译PWD和发布PWD配置文件的改变。
#这个pri会拷贝配置PWD下的所有文件、文件夹到编译PWD和发布PWD下。
#依赖 APP_CONFIG_PWD(in app pro) APP_DEPLOY_PWD(in app deploy)
#---------------------------------------------------------------------
#example（in app's pro file）
#APP_CONFIG_PWD = $${PWD}/../SysRoot
#win32 {
#    APP_CONFIG_PWD ~=s,/,\\,g
#}

defineReplace(copy_config_on_mac) {
    #need QQT_BUILD_PWD
    dirs = $$1
    !isEmpty(2): error("copy_config_on_mac(dirs) requires one argument")
    isEmpty(1): error("copy_config_on_mac(dirs) requires one argument")

    command =
    command += $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEST_DIR}/$${TARGET}.app/Contents/MacOS/ $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/
    #message($$command)
    return ($$command)
}


defineReplace(copy_config) {
    #need QQT_BUILD_PWD
    dirs = $$1
    !isEmpty(2): error("copy_config(dirs) requires one argument")
    isEmpty(1): error("copy_config(dirs) requires one argument")
    command =
    command += $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEST_DIR} $$CMD_SEP
    command += $$COPY_DIR $${dirs} $${APP_DEPLOY_PWD}
    #message($$command)
    return ($$command)
}

##-------------------------------------------------
##work flow
##-------------------------------------------------
#如果 TARGET 没有配置 APP_CONFIG_PWD 那么返回，不拷贝任何配置
isEmpty(APP_CONFIG_PWD) | isEmpty(APP_DEPLOY_PWD) {
    message("$${TARGET} hasn't deploied any cofig files")
    greaterThan(QT_MAJOR_VERSION, 5):return()
}

##4.8 qmake arm32 return() 函数无效
!isEmpty(APP_CONFIG_PWD) & !isEmpty(APP_DEPLOY_PWD) {
    CONFIG += app_copy_config
    message("$${TARGET} has deploied some cofig files")
}

contains(CONFIG, app_copy_config) {
    APP_DEST_DIR=$${DESTDIR}
    isEmpty(APP_DEST_DIR):APP_DEST_DIR=.
    contains(QKIT_PRIVATE, WIN32||WIN64) {
        QMAKE_POST_LINK += $$copy_config("$${APP_CONFIG_PWD}\\*")
    } else: contains(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$copy_config_on_mac("$${APP_CONFIG_PWD}/*")
    } else {
        QMAKE_POST_LINK += $$copy_config("$${APP_CONFIG_PWD}/*")
    }
}
