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
    command = $$app_deploy_with_lib_on_mac($${APP_DEST_DIR})
    return ($$command)
}

##########################################
#app的发布函数命令
##########################################
defineReplace(get_app_deploy_on_mac) {
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app $$CMD_SEP
    command += $$COPY_DIR $${APP_DEST_DIR}/$${TARGET}.app $${APP_DEPLOY_PWD}/$${TARGET}.app
    #message($$command)
    return ($$command)
}

defineReplace(get_app_deploy_on_win) {
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

defineReplace(get_app_deploy_on_linux) {
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

defineReplace(get_app_deploy_on_android) {
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

##########################################
#app的发布lib函数命令
##########################################
#app发布lib到自己的目标里，必须先发布app，如果没有先发布app会出错。
#lib发布lib，没有的事情
#解释，从app build目录里拷贝是有原因的，在Creator编译完成后，我把依赖库拷贝过去了，add_link()实现的。
defineReplace(get_app_deploy_lib_on_mac) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_app_deploy_lib_on_mac(libname) requires one argument")

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$COPY_DIR $${APP_DEST_PWD}/$${TARGET}.app/Contents/Frameworks/$${libname}.framework $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks
    #message($$command)

    return ($$command)
}

defineReplace(get_app_deploy_lib_on_windows) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_app_deploy_lib_on_windows(libname) requires one argument")

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    msvc:command += $$COPY_DIR $${APP_DEST_PWD}\\$${libname}.* $${APP_DEPLOY_PWD} $$CMD_SEP
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

defineReplace(get_app_deploy_lib_on_linux) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_app_deploy_lib_on_linux(libname) requires one argument")

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/lib$${libname}.so* $$CMD_SEP
    command += $$COPY_DIR $${APP_DEST_PWD}/lib$${libname}.so* $${APP_DEPLOY_PWD} $$CMD_SEP
    #message($$command)

    return ($$command)
}

defineReplace(get_app_deploy_lib_on_android) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_app_deploy_lib_on_android(libname) requires one argument")

    command =
    command += $${APP_DEST_PWD}/lib$${libname}.so
    #message($$command)

    return ($$command)
}

################################################################################
#外部用函数
################################################################################
defineTest(app_deploy) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_app_deploy_on_win()
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_app_deploy_on_mac()
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_app_deploy_on_android()
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$get_app_deploy_on_linux()
    }

    return (1)
}

defineTest(app_deploy_lib) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    libname = $$1
    isEmpty(1)|!isEmpty(2): error("app_deploy_lib(libname) requires one argument")

    message("$${TARGET} has deployed lib $${libname}.")

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_app_deploy_lib_on_win($${libname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_app_deploy_lib_on_mac($${libname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_app_deploy_lib_on_android($${libname})
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$get_app_deploy_lib_on_linux($${libname})
    }

    return (1)
}

#判断某个lib是否已经发布
#避免二次发布，拷贝浪费时间。
defineTest(has_deployed_lib) {
    return(0)
}

##-------------------------------------------------
##work flow
##-------------------------------------------------
#deploy root
isEmpty(APP_DEPLOY_ROOT){
    message($${TARGET} $${CONFIG_FILE})
    message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
    error(please check $$CONFIG_FILE under multi_link_technology.pri)
}
message(Deploy $${TARGET} to $$APP_DEPLOY_ROOT/$${TARGET}/$$QSYS_STD_DIR)

#起始位置 编译位置 中间目标位置
APP_DEST_PWD=$${DESTDIR}
isEmpty(APP_DEST_PWD):APP_DEST_PWD=.

#set app deploy pwd
#APP_DEPLOY_PWD is here.
APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET}/$${QSYS_STD_DIR}
#不仅仅发布目标为Windows的时候，才需要改变路径
#开发机为Windows就必须改变。
#contains(QKIT_PRIVATE, WIN32||WIN64) {
equals(QMAKE_HOST.os, Windows) {
    APP_DEPLOY_PWD~=s,/,\\,g
}

#如果 配置文件里 没有配置 APP_DEPLOY_ROOT 那么返回，不拷贝发布任何应用
#不会走到
isEmpty(APP_DEPLOY_ROOT) {
    message("$${TARGET} hasn't deployed any app files")
    greaterThan(QT_MAJOR_VERSION, 5):return()
}

##4.8 qmake arm32 return() 函数无效
!isEmpty(APP_DEPLOY_ROOT) {
    CONFIG += app_deploy
    message("$${TARGET} has deployed some app files")
}

##########
#注意，此处强制发布App 不需要用户手动调用。
#注意，此处强制依赖LibQQt，不需要用户手动发布LibQQt。
##########
contains(CONFIG, app_deploy) {
    app_deploy_lib(QQt)
    app_deploy()
    #如果用户依赖了其他的lib，便可以用app_deploy_lib进行拷贝依赖到app发布区域。
    #并且这个工作，后续持续收到app_deploy配置开关的控制。
    #note: app_deploy 一个配置开关 一个函数 两个都有效使用
    #注意，用户必须先发布lib 再发布app
}
