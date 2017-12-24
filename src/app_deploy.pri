#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
#deploy root
isEmpty(APP_DEPLOY_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
    error(  please check $$CONFIG_FILE under qqt_library.pri)
}
message($${TARGET} deploy root: $$APP_DEPLOY_ROOT)

#set app deploy pwd
APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET}/$${QKIT_STD_DIR}
contains(QKIT_PRIVATE, WIN32||WIN64) {
    APP_DEPLOY_PWD~=s,/,\\,g
}

defineReplace(deploy_app_on_mac) {
    #need QQT_BUILD_PWD
    command = &&
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app &&
    command += $$COPY_DIR $${DESTDIR}/$${TARGET}.app $${APP_DEPLOY_PWD}/$${TARGET}.app
    #message($$command)
    return ($$command)
}

defineReplace(deploy_app_on_win) {
    #need QQT_BUILD_PWD
    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    command += $$COPY $${QQT_BUILD_PWD}\\QQt.dll $${APP_DEPLOY_PWD}\\QQt.dll $$CMD_SEP
    command += $$COPY $${DESTDIR}\\$${TARGET}.exe $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    #all windows need deploy release version?
    equals(BUILD, Debug) {
        #command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --debug -verbose=1
    } else: equals(BUILD, Release) {
        #command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --release -verbose=1
    }
    command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --release -verbose=1
    #message($$command)
    return ($$command)
}

defineReplace(deploy_app_on_linux) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/libQQt.so* &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION3} $${APP_DEPLOY_PWD} &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION2} $${APP_DEPLOY_PWD} &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION1} $${APP_DEPLOY_PWD} &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so $${APP_DEPLOY_PWD} &&
    command += $$RM $${APP_DEPLOY_PWD}/$${TARGET} &&
    command += $$COPY $${DESTDIR}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET}
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
