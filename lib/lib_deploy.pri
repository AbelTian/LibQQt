#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
#windows: C:\Users\[userName]\.qmake\app_configure.pri
#linux: /home/[usrName]/.qmake/app_configure.pri
#macOS: /Users/[userName]/.qmake/app_configure.pri

#example（in /user/conf/path/.qmake/app_configure.pri）
#QQT_SDK_ROOT = /where/lib/wants/to/deploy/lib/sdk/root

defineReplace(deploy_lib_on_mac) {
    #need QQT_BUILD_PWD
    command += $$MK_DIR $${LIB_DEPLOY_PWD} $$CMD_SEP
    command += $$RM_DIR $${LIB_DEPLOY_PWD}/$${TARGET}.framework $$CMD_SEP
    command += $$COPY_DIR $${LIB_DEST_DIR}/$${TARGET}.framework $${LIB_DEPLOY_PWD}/$${TARGET}.framework
    #message($$command)
    return ($$command)
}

defineReplace(deploy_lib_on_win) {
    #need QQT_BUILD_PWD
    command =
    command += $$MK_DIR $${LIB_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${LIB_DEPLOY_PWD}\\$${TARGET}.* $$CMD_SEP
    command += $$COPY_DIR $${LIB_DEST_DIR}\\$${TARGET}.* $${LIB_DEPLOY_PWD}\\ $$CMD_SEP
    #message($$command)
    return ($$command)
}

defineReplace(deploy_lib_on_linux) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${LIB_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${LIB_DEPLOY_PWD}/$${TARGET}.* $$CMD_SEP
    command += $$COPY_DIR $${LIB_DEST_DIR}/$${TARGET}.* $${LIB_DEPLOY_PWD}/
    #message($$command)
    return ($$command)
}

defineReplace(deploy_lib_on_android) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${LIB_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${LIB_DEPLOY_PWD}/$${TARGET}.* $$CMD_SEP
    command += $$COPY_DIR $${LIB_DEST_DIR}/$${TARGET}.* $${LIB_DEPLOY_PWD}/
    #message($$command)
    return ($$command)
}

##-------------------------------------------------
##work flow
##-------------------------------------------------
#set app deploy pwd
#LIB_DEPLOY_PWD is here.
LIB_DEPLOY_PWD = $${QQT_SDK_ROOT}/$${TARGET}/$${QKIT_STD_DIR}
#不仅仅发布目标为Windows的时候，才需要改变路径
#开发机为Windows就必须改变。
#contains(QKIT_PRIVATE, WIN32||WIN64) {
equals(QMAKE_HOST.os, Windows) {
    LIB_DEPLOY_PWD~=s,/,\\,g
}

LIB_DEST_DIR=$${DESTDIR}
isEmpty(LIB_DEST_DIR):LIB_DEST_DIR=.

#deploy root
isEmpty(QQT_SDK_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(QQT_SDK_ROOT = /user/set/path is required, please modify user/config/path/.qmake/app_configure.pri )
    error(please check $$CONFIG_FILE under lib_multi_link_technology.pri)
}
message($${TARGET} sdk root: $$QQT_SDK_ROOT/$${TARGET}/$$QKIT_STD_DIR)

#如果 配置文件里 没有配置 QQT_SDK_ROOT 那么返回，不拷贝发布任何应用
#不会走到
isEmpty(QQT_SDK_ROOT) {
    message("$${TARGET} hasn't deploied any lib files")
    greaterThan(QT_MAJOR_VERSION, 5):return()
}

##4.8 qmake arm32 return() 函数无效
!isEmpty(QQT_SDK_ROOT) {
    CONFIG += deploy_lib
    message("$${TARGET} has deploied some lib files")
}


contains(CONFIG, deploy_lib) {
    contains(QKIT_PRIVATE, WIN32||WIN64) {
        #发布windows版本
        QMAKE_POST_LINK += $$deploy_lib_on_win()
    } else: contains(QKIT_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
        QMAKE_POST_LINK += $$deploy_lib_on_mac()
    } else: contains(QKIT_PRIVATE, ANDROID||ANDROIDX86) {
        #发布Android版本，这个分为开发Host为windows和类Unix两种情况。
        #Android下Qt Creator自动使用androidDeployQt，无法发布应用。
        equals(QMAKE_HOST.os, Windows){
            #
        } else { }
        #QMAKE_POST_LINK += $$deploy_lib_on_android()
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$deploy_lib_on_linux()
    }
}
