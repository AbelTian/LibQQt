#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
#windows: C:\Users\[userName]\AppData\Roaming\qmake\app_configure.pri
#linux: /home/[usrName]/.qmake/app_configure.pri
#macOS: /Users/[userName]/.qmake/app_configure.pri

#example（in /user/conf/path/.qmake/app_configure.pri）
#APP_DEPLOY_ROOT = /where/app/wants/to/deploy/app/root

defineReplace(deploy_app_on_mac) {
    #need QQT_BUILD_PWD
    command = &&
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app &&
    command += $$COPY_DIR $${APP_DEST_DIR}/$${TARGET}.app $${APP_DEPLOY_PWD}/$${TARGET}.app
    #message($$command)
    return ($$command)
}

defineReplace(deploy_app_on_win) {
    #need QQT_BUILD_PWD
    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    command += $$COPY $${QQT_BUILD_PWD}\\QQt.dll $${APP_DEPLOY_PWD}\\QQt.dll $$CMD_SEP
    command += $$COPY $${APP_DEST_DIR}\\$${TARGET}.exe $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
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
    command += $$COPY $${APP_DEST_DIR}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET}
    #message($$command)
    return ($$command)
}

defineReplace(deploy_app_for_android) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/libQQt.so* &&
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so $${APP_DEPLOY_PWD} &&
    command += $$RM $${APP_DEPLOY_PWD}/$${TARGET} &&
    command += $$COPY $${APP_DEST_DIR}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET}
    #message($$command)
    return ($$command)
}

##-------------------------------------------------
##work flow
##-------------------------------------------------
#set app deploy pwd
#APP_DEPLOY_PWD is here.
APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET}/$${QKIT_STD_DIR}
contains(QKIT_PRIVATE, WIN32||WIN64) {
    APP_DEPLOY_PWD~=s,/,\\,g
}

APP_DEST_DIR=$${DESTDIR}
isEmpty(APP_DEST_DIR):APP_DEST_DIR=.

#deploy root
isEmpty(APP_DEPLOY_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
    error(  please check $$CONFIG_FILE under link_qqt_library.pri)
}
message($${TARGET} deploy root: $$APP_DEPLOY_ROOT)

#如果 配置文件里 没有配置 APP_DEPLOY_ROOT 那么返回，不拷贝发布任何应用
#不会走到。
isEmpty(APP_DEPLOY_ROOT) {
    message("$${TARGET} hasn't deploied any app files")
    greaterThan(QT_MAJOR_VERSION, 5):return()
}

##4.8 qmake arm32 return() 函数无效
!isEmpty(APP_DEPLOY_ROOT) {
    CONFIG += deploy_app
    message("$${TARGET} has deploied some app files")
}


contains(CONFIG, deploy_app) {
    contains(QKIT_PRIVATE, WIN32||WIN64) {
        QMAKE_POST_LINK += $$deploy_app_on_win()
    } else: contains(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$deploy_app_on_mac()
    } else: contains(QKIT_PRIVATE, ANDROID||ANDROIDX86) {
        QMAKE_POST_LINK += $$deploy_app_on_android()
    } else {
        QMAKE_POST_LINK += $$deploy_app_on_linux()
    }
}
