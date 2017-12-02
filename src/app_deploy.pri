#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
#deploy root
CONFIG_PATH =
CONFIG_FILE =

win32 {
    CONFIG_PATH = $$user_config_path()\\QQt
    CONFIG_FILE = $${CONFIG_PATH}\\app.ini
} else {
    CONFIG_PATH = $$user_config_path()/.QQt
    CONFIG_FILE = $${CONFIG_PATH}/app.ini
}

message($${TARGET} config path: $$CONFIG_PATH config file: $${CONFIG_FILE})

!exists($${CONFIG_FILE}) {
    empty_file($${CONFIG_FILE})
    #qt4 need this ret, why?
    ret = $$system(echo [$${TARGET}] >> $${CONFIG_FILE})
    ret = $$system(echo APP_DEPLOY_ROOT =  >> $${CONFIG_FILE})
}

APP_DEPLOY_ROOT = $$read_ini("$${CONFIG_FILE}", "$${TARGET}", "APP_DEPLOY_ROOT")
isEmpty(APP_DEPLOY_ROOT){
    message([$${TARGET}])
    message(APP_DEPLOY_ROOT = is required )
    error(  please check app.ini at $$CONFIG_PATH)
}
message($${TARGET} deploy root: $$APP_DEPLOY_ROOT)
isEmpty(APP_DEPLOY_ROOT):error(APP_DEPLOY_ROOT required please check app.ini at $$CONFIG_PATH)

defineReplace(deploy_app_on_mac) {
    #need QQT_BUILD_PWD
    command = &&
    command += rm -fr $${APP_DEPLOY_ROOT}/$${TARGET}.app &&
    command += cp -fa $${DESTDIR}/$${TARGET}.app $${APP_DEPLOY_ROOT}/$${TARGET}.app
    #message($$command)
    return ($$command)
}

defineReplace(deploy_app_on_win) {
    #need QQT_BUILD_PWD
    #message($$command)
    return ($$command)
}

defineReplace(deploy_app_on_linux) {
    #need QQT_BUILD_PWD
    #message($$command)
    return ($$command)
}

CONFIG += deploy_app
contains(CONFIG, deploy_app) {
    contains(QKIT_PRIVATE, WIN32||WIN64) {
        QMAKE_POST_LINK += $$deploy_app_on_win()
    } else: contains(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$deploy_app_on_mac()
    } else {
        QMAKE_POST_LINK += $$deploy_app_on_linux()
    }
}
