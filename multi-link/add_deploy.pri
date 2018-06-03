#-------------------------------------------------------------
#add_deploy.pri
#提供app发布函数，只是app工程使用
#-------------------------------------------------------------
#Multi-link技术 add_deploy部分只能应用于Qt5，Qt4没有windeployqt程序，如果用户为Qt4编译了windeployqt那么也可以用于Qt4。

################################################################################
#内部用函数
#获取命令
################################################################################
ADD_DEPLOY_PRI_PWD = $${PWD}

##########################################
#app的发布函数命令
##########################################
#终端程序，依赖Qt的必须修复Qt组件的rpath引用，或者加入rpath，并且Qt环境要加入路径。
#实用价值不高，所以在app_base_manager里面，我默认开启了app_bundle.
#如果不发布app，build位置的app也不能运行。单独给build一个fix吗？还是算了吧。
defineReplace(get_add_deploy_on_mac) {    
    #fix app in build pwd
    contains(CONFIG, app_bundle) {
        #这里或许需要加macdeployqt? build pwd 需要
        command += macdeployqt $${APP_BUILD_PWD}/$${TARGET}.app -verbose=1 $$CMD_SEP
        lessThan(QT_MAJOR_VERSION, 5){
            command += chmod +x $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $$CMD_SEP
            command += $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} $$CMD_SEP
        }
    } else {

        #这里或许需要加macdeployqt? build pwd 不需要
        command += macdeployqt $${APP_BUILD_PWD}/$${TARGET} -verbose=1 $$CMD_SEP
        lessThan(QT_MAJOR_VERSION, 5){
            command += chmod +x $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $$CMD_SEP
            command += $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $${APP_BUILD_PWD}/$${TARGET} $$CMD_SEP
        }
    }

    #deploy pwd
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    contains(CONFIG, app_bundle) {
        command += $$RM_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app $$CMD_SEP
        command += $$COPY_DIR $${APP_BUILD_PWD}/$${TARGET}.app $${APP_DEPLOY_PWD}/$${TARGET}.app $$CMD_SEP

        #这里或许需要加macdeployqt? deploy pwd 需要
        command += macdeployqt $${APP_DEPLOY_PWD}/$${TARGET}.app -verbose=1 $$CMD_SEP
        lessThan(QT_MAJOR_VERSION, 5){
            command += chmod +x $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $$CMD_SEP
            command += $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} $$CMD_SEP
        }
    } else {
        command += $$RM_DIR $${APP_DEPLOY_PWD}/$${TARGET} $$CMD_SEP
        command += $$COPY_DIR $${APP_BUILD_PWD}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET} $$CMD_SEP

        #这里或许需要加macdeployqt? deploy pwd 需要
        command += macdeployqt $${APP_DEPLOY_PWD}/$${TARGET} -verbose=1 $$CMD_SEP
        lessThan(QT_MAJOR_VERSION, 5){
            command += chmod +x $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $$CMD_SEP
            command += $${ADD_DEPLOY_PRI_PWD}/mac_deploy_qt4.sh $${APP_DEPLOY_PWD}/$${TARGET} $$CMD_SEP
        }
    }
    command += echo .


    #message($$command)
    return ($$command)
}

defineReplace(get_add_deploy_on_windows) {
    #need QQT_BUILD_PWD
    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    command += $$COPY $${APP_BUILD_PWD}\\$${TARGET}.exe $${APP_DEPLOY_PWD}\\$${TARGET}.exe
    #msvc 在deploy lib上有点区别，mingw不发布依赖lib，在编译区也能运行，msvc却不能。
    #在运行区，都必须发布依赖lib。
    #add_deploy 仅仅发布app，不管依赖的lib。

    #all windows need deploy release version?
    equals(BUILD, Debug) {
        command += $$CMD_SEP
        #command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --debug -verbose=1
        msvc{
            command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --debug -verbose=1
        } else {
            #过去you'yi'dua有一段时间，这里必须发布release版本，mingw的才能通过，现在debug的才能通过
            #必须release。编译dll可以，链接不成功。静态编译后，app必须发布release。
            #注意：链接库较多时候，windeployqt发布不全。dll用这些库，app不用，windeployqt不发布。在add_deploy_library里修复。
            command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --debug -verbose=1
        }
    } else: equals(BUILD, Release) {
        command += $$CMD_SEP
        #command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --release -verbose=1
        command += windeployqt $${APP_DEPLOY_PWD}\\$${TARGET}.exe --release -verbose=1
    }
    #message($$command)
    return ($$command)
}

defineReplace(get_add_deploy_on_linux) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/$${TARGET} $$CMD_SEP
    command += $$COPY $${APP_BUILD_PWD}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET}

    #message($$command)
    return ($$command)
}

defineReplace(get_add_deploy_on_android) {
    #need QQT_BUILD_PWD

    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}/$${TARGET} $$CMD_SEP
    command += $$COPY $${APP_BUILD_PWD}/$${TARGET} $${APP_DEPLOY_PWD}/$${TARGET}
    #message($$command)
    return ($$command)
}


################################################################################
#外部用函数
################################################################################
defineTest(add_deploy) {
    #起始位置 编译位置 中间目标位置
    APP_BUILD_PWD=$${DESTDIR}
    isEmpty(APP_BUILD_PWD):APP_BUILD_PWD=.

    #set app deploy pwd
    #APP_DEPLOY_PWD is here.
    APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET_NAME}/$${QSYS_STD_DIR}
    #不仅仅发布目标为Windows的时候，才需要改变路径
    #开发机为Windows就必须改变。
    #contains(QKIT_PRIVATE, WIN32||WIN64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_DEPLOY_PWD~=s,/,\\,g
    }
    message($${TARGET} is deployed to $$APP_DEPLOY_PWD)

    #如果 配置文件里 没有配置 APP_DEPLOY_ROOT 那么返回，不拷贝发布任何应用
    #不会走到
    isEmpty(APP_DEPLOY_ROOT) {
        message("$${TARGET} hasn't deployed any app files")
        return(0)
    }

    ##4.8 qmake arm32 return() 函数无效
    !isEmpty(APP_DEPLOY_ROOT) {
        message("$${TARGET} has deployed some app files")
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_add_deploy_on_windows()
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_on_mac()
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        #Qt做了
        #ANDROID_EXTRA_LIBS += $$get_add_deploy_on_android()
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$get_add_deploy_on_linux()
    }

    export(QMAKE_POST_LINK)

    return (1)
}
