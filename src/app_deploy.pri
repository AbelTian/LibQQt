#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
#deploy root
isEmpty(APP_DEPLOY_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(APP_DEPLOY_ROOT = /user/set/path is required )
    error(  please check $$CONFIG_FILE under qqt_library.pri)
}
message($${TARGET} deploy root: $$APP_DEPLOY_ROOT)

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
    command =
    command += $$RM $${APP_DEPLOY_ROOT}\\$${TARGET}.exe $$CMD_SEP
    command += $$COPY $${QQT_BUILD_PWD}\\QQt.dll $${APP_DEPLOY_ROOT}\\QQt.dll $$CMD_SEP
    command += $$COPY $${DESTDIR}\\$${TARGET}.exe $${APP_DEPLOY_ROOT}\\$${TARGET}.exe $$CMD_SEP
    command += windeployqt $${APP_DEPLOY_ROOT}\\$${TARGET}.exe --release -verbose=1
    #message($$command)
    return ($$command)
}

defineReplace(deploy_app_on_linux) {
    #need QQT_BUILD_PWD
    command =
    command += $$RM $${APP_DEPLOY_ROOT}/libQQt.so* &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION3} $${APP_DEPLOY_ROOT} &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION2} $${APP_DEPLOY_ROOT} &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION1} $${APP_DEPLOY_ROOT} &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so $${APP_DEPLOY_ROOT} &&
    command += $$RM $${APP_DEPLOY_ROOT}/$${TARGET} &&
    command += $$COPY $${DESTDIR}/$${TARGET} $${APP_DEPLOY_ROOT}/$${TARGET}
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
