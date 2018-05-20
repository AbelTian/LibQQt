#-------------------------------------------------------------
#app_deploy.pri
#提供app发布函数，只是app工程使用
#-------------------------------------------------------------
#Multi-link技术 app_deploy部分只能应用于Qt5，Qt4没有windeployqt程序，如果用户为Qt4编译了windeployqt那么也可以用于Qt4。

################################################################################
#内部用函数
#获取命令
################################################################################

#在build path修复app (macOS专有)
#copy lib
#fix bundle路径链接
defineReplace(app_deploy_with_lib_on_mac) {
    #need QQT_BUILD_PWD
    deploy_path = $$1
    isEmpty(1): error("app_deploy_with_lib_on_mac(deploy_path) requires one argument")
    create_command = $$create_mac_sdk()
    APP_DEST_DIR=$${deploy_path}
    isEmpty(APP_DEST_DIR):APP_DEST_DIR=.
    command =
    command += chmod +x $${PWD}/linux_cur_path.sh &&
    command += . $${PWD}/linux_cur_path.sh &&
    command += rm -rf $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    #拷贝QQt.framework到app bundle里。其实，是直接在app里执行的。这个会移动走。
    command += mkdir -p $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += cd $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    #修复QQt.framework里的快捷方式
    command += $${create_command} &&
    command += chmod +x $${PWD}/linux_cd_path.sh &&
    command += . $${PWD}/linux_cd_path.sh &&

    #Qt Creator create framework but use absolute path to make link
    #QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
    #        $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks &&
    #更改app bundle链接QQt的位置。
    command += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         $${APP_DEST_DIR}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    command += macdeployqt $${APP_DEST_DIR}/$${TARGET}.app -verbose=1

    lessThan(QT_MAJOR_VERSION, 5){
        command += &&
        command += chmod +x $${PWD}/mac_deploy_qt4.sh &&
        command += $${PWD}/mac_deploy_qt4.sh $${APP_DEST_DIR}/$${TARGET}.app/Contents/MacOS/$${TARGET}
    }
    #message($$command)
    return ($${command})
}

defineReplace(fix_app_bundle_with_qqt_in_building_path_on_mac) {
    #need QQT_BUILD_PWD
    APP_DEST_DIR=$${DESTDIR}
    isEmpty(APP_DEST_DIR):APP_DEST_DIR=.
    command = $$deploy_qqt_to_app_deploy_path_on_mac($${APP_DEST_DIR})
    return ($$command)
}

defineReplace(app_deploy_on_mac) {
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app $$CMD_SEP
    command += $$COPY_DIR $${APP_DEST_DIR}/$${TARGET}.app $${APP_DEPLOY_PWD}/$${TARGET}.app
    #message($$command)
    return ($$command)
}

defineReplace(app_deploy_on_win) {
    #need QQT_BUILD_PWD
    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    command += $$COPY $${QQT_BUILD_PWD}\\QQt.dll $${APP_DEPLOY_PWD}\\QQt.dll $$CMD_SEP
    msvc:command += $$COPY_DIR $${QQT_BUILD_PWD}\\QQt.* $${APP_DEST_DIR} $$CMD_SEP
    command += $$COPY $${APP_DEST_DIR}\\$${TARGET}.exe $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    #all windows need deploy release version?
    equals(BUILD, Debug) {
        #command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --debug -verbose=1
        msvc{
            command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --debug -verbose=1
        } else {
            command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --release -verbose=1
        }
    } else: equals(BUILD, Release) {
        #command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --release -verbose=1
        command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --release -verbose=1
    }
    #message($$command)
    return ($$command)
}

defineReplace(app_deploy_on_linux) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/libQQt.so* $$CMD_SEP
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION3} $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION2} $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so.$${QQT_VERSION1} $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/$${TARGET} $$CMD_SEP
    command += $$COPY $${APP_DEST_DIR}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET}
    #message($$command)
    return ($$command)
}

defineReplace(app_deploy_on_android) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/libQQt.so* $$CMD_SEP
    command += $$COPY_DIR $${QQT_BUILD_PWD}/libQQt.so $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/$${TARGET} $$CMD_SEP
    command += $$COPY $${APP_DEST_DIR}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET}
    #message($$command)
    return ($$command)
}

##-------------------------------------------------
##work flow
##-------------------------------------------------
#set app deploy pwd
#APP_DEPLOY_PWD is here.
APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET}/$${QSYS_STD_DIR}
#不仅仅发布目标为Windows的时候，才需要改变路径
#开发机为Windows就必须改变。
#contains(QKIT_PRIVATE, WIN32||WIN64) {
equals(QMAKE_HOST.os, Windows) {
    APP_DEPLOY_PWD~=s,/,\\,g
}

APP_DEST_DIR=$${DESTDIR}
isEmpty(APP_DEST_DIR):APP_DEST_DIR=.

#deploy root
isEmpty(APP_DEPLOY_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
    error(please check $$CONFIG_FILE under app_multi_link_technology.pri)
}
message(Deploy $${TARGET} to $$APP_DEPLOY_ROOT/$${TARGET}/$$QKIT_STD_DIR)

#如果 配置文件里 没有配置 APP_DEPLOY_ROOT 那么返回，不拷贝发布任何应用
#不会走到
isEmpty(APP_DEPLOY_ROOT) {
    message("$${TARGET} hasn't deploied any app files")
    greaterThan(QT_MAJOR_VERSION, 5):return()
}

##4.8 qmake arm32 return() 函数无效
!isEmpty(APP_DEPLOY_ROOT) {
    CONFIG += app_deploy
    message("$${TARGET} has deploied some app files")
}


contains(CONFIG, app_deploy) {
    contains(QKIT_PRIVATE, WIN32||WIN64) {
        #发布windows版本
        QMAKE_POST_LINK += $$app_deploy_on_win()
    } else: contains(QKIT_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$CMD_SEP $$app_deploy_on_mac()
    } else: contains(QKIT_PRIVATE, ANDROID||ANDROIDX86) {
        #发布Android版本，这个分为开发Host为windows和类Unix两种情况。
        #Android下Qt Creator自动使用androidDeployQt，无法发布应用。
        equals(QMAKE_HOST.os, Windows){
            #
        } else { }
        #QMAKE_POST_LINK += $$app_deploy_on_android()
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$app_deploy_on_linux()
    }
}
