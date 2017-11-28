#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
#deploy root
equals(QMAKE_HOST.os, Darwin) {
    APP_DEPLOY_ROOT = $$PWD/../../../deployer
} else: equals(QMAKE_HOST.os, Linux) {
    APP_DEPLOY_ROOT = $$PWD/../../../deployer
} else: equals(QMAKE_HOST.os, Windows) {
    APP_DEPLOY_ROOT = $$PWD/../../../deployer
}

defineReplace(deploy_app_on_mac) {
    #need QQT_BUILD_PWD
    command = &&
    command += rm -fr $${APP_DEPLOY_ROOT}/$${TARGET}.app &&
    command += cp -fa $${DESTDIR}/$${TARGET}.app $${APP_DEPLOY_ROOT}
    message($$command)
    return ($$command)
}

CONFIG += deploy_app
contains(CONFIG, deploy_app) {
    contains(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$deploy_app_on_mac()
    }
}
