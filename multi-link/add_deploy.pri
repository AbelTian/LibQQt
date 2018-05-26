#-------------------------------------------------------------
#add_deploy.pri
#提供app发布函数，只是app工程使用
#-------------------------------------------------------------
#Multi-link技术 add_deploy部分只能应用于Qt5，Qt4没有windeployqt程序，如果用户为Qt4编译了windeployqt那么也可以用于Qt4。

################################################################################
#内部用函数
#获取命令
################################################################################
THIS_PRI_PWD = $${PWD}

##########################################
#app的发布函数命令
##########################################
defineReplace(get_add_deploy_on_mac) {
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app $$CMD_SEP
    command += $$COPY_DIR $${APP_BUILD_PWD}/$${TARGET}.app $${APP_DEPLOY_PWD}/$${TARGET}.app
    #message($$command)
    return ($$command)
}

defineReplace(get_add_deploy_on_windows) {
    #need QQT_BUILD_PWD
    command =
    command += $$MK_DIR $${APP_DEPLOY_PWD} $$CMD_SEP
    command += $$RM $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    command += $$COPY $${APP_BUILD_PWD}\\$${TARGET}.exe $${APP_DEPLOY_PWD}\\$${TARGET}.exe $$CMD_SEP
    #msvc 在deploy lib上有点区别，mingw不发布依赖lib，在编译区也能运行，msvc却不能。
    #在运行区，都必须发布依赖lib。
    #add_deploy 仅仅发布app，不管依赖的lib。

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

##########################################
#app的发布lib函数命令
##########################################
#app发布lib到自己的目标里，必须先发布app，如果没有先发布app会出错。
#lib发布lib，没有的事情
#解释，从app build目录里拷贝是有原因的，在Creator编译完成后，我把依赖库拷贝过去了，add_library()实现的。
defineReplace(get_add_deploy_library_on_mac) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_on_mac(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_on_mac(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    #这里有个bug，用户删除了SDK以后，App qmake阶段读取这个SDK，结果读到这个位置，为0...bug，其实不应该为0，应该为用户设置的SDK版本号。
    #解决方法一：忽略第一遍编译。也就是什么SDK都没有的时候，编译一遍，lib生成了SDK，可是不管他，再qmake后编译一遍。能解决。
    libmajorver = $$system(readlink $${LIB_LIB_PWD}/$${librealname}.framework/Versions/Current)
    #这里是以防万一lib不存在 但是不能退出？如果是subdirs包含Library的工程，就不能退出。
    isEmpty(libmajorver){
        libmajorver=0
        message($$TARGET link $$libname, unexisted lib.)
    }
    command =
    command += $$MK_DIR $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
    #拷贝sdk到build
    command += $$COPY_DIR $${LIB_LIB_PWD}/$${librealname}.framework $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
    #更改app bundle链接Lib的位置。
    command += install_name_tool -change $${librealname}.framework/Versions/$${libmajorver}/$${librealname} \
         @rpath/$${librealname}.framework/Versions/$${libmajorver}/$${librealname} \
         $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    command += macdeployqt $${APP_BUILD_PWD}/$${TARGET}.app -verbose=1 &&
    lessThan(QT_MAJOR_VERSION, 5){
        command += chmod +x $${THIS_PRI_PWD}/mac_deploy_qt4.sh &&
        command += $${THIS_PRI_PWD}/mac_deploy_qt4.sh $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    }

    command += $$MK_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_LIB_PWD}/$${librealname}.framework $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
    #更改app bundle链接Lib的位置。
    command += install_name_tool -change $${librealname}.framework/Versions/$${libmajorver}/$${librealname} \
         @rpath/$${librealname}.framework/Versions/$${libmajorver}/$${librealname} \
         $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    command += macdeployqt $${APP_DEPLOY_PWD}/$${TARGET}.app -verbose=1
    lessThan(QT_MAJOR_VERSION, 5){
        command += &&
        command += chmod +x $${THIS_PRI_PWD}/mac_deploy_qt4.sh &&
        command += $${THIS_PRI_PWD}/mac_deploy_qt4.sh $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET}
    }

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_windows) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_on_windows(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_on_windows(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    command =
    command += $$RM $${APP_BUILD_PWD}\\$${librealname}.* $$CMD_SEP
    #拷贝sdk到build
    command += $$COPY_DIR $${LIB_LIB_PWD}\\$${librealname}.* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}\\$${librealname}.* $$CMD_SEP
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_LIB_PWD}\\$${librealname}.* $${APP_DEPLOY_PWD} $$CMD_SEP

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_linux) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_on_windows(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_on_windows(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    command =

    command += $$RM $${APP_BUILD_PWD}/lib$${libname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}/lib$${libname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_DEPLOY_PWD} $$CMD_SEP
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_android) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_on_windows(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_on_windows(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    command =
    command += $${LIB_LIB_PWD}/lib$${librealname}.so
    #message($$command)

    return ($$command)
}

################################################################################
#外部用函数
################################################################################
defineTest(add_deploy) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    #deploy root
    isEmpty(APP_DEPLOY_ROOT){
        message($${TARGET} $${CONFIG_FILE})
        message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
        error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
    }
    message($${TARGET} is deployed to $$APP_DEPLOY_ROOT/$${TARGET}/$$QSYS_STD_DIR)

    #起始位置 编译位置 中间目标位置
    APP_DEST_PWD=$${DESTDIR}
    isEmpty(APP_DEST_PWD):APP_DEST_PWD=.
    APP_BUILD_PWD = $$APP_DEST_PWD

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
        ANDROID_EXTRA_LIBS += $$get_add_deploy_on_android()
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$get_add_deploy_on_linux()
    }

    export(QMAKE_POST_LINK)

    return (1)
}

defineTest(add_deploy_library) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    #deploy root
    isEmpty(APP_DEPLOY_ROOT){
        message($${TARGET} $${CONFIG_FILE})
        message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
        error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
    }
    message(Deploy $${TARGET} to $$APP_DEPLOY_ROOT/$${TARGET}/$$QSYS_STD_DIR)
    isEmpty(LIB_SDK_ROOT){
        message($${TARGET} $${CONFIG_FILE})
        message(LIB_SDK_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
        error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
    }

    #起始位置 编译位置 中间目标位置
    APP_DEST_PWD=$${DESTDIR}
    isEmpty(APP_DEST_PWD):APP_DEST_PWD=.
    APP_BUILD_PWD = $$APP_DEST_PWD

    #set app deploy pwd
    #APP_DEPLOY_PWD is here.
    APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET}/$${QSYS_STD_DIR}
    #不仅仅发布目标为Windows的时候，才需要改变路径
    #开发机为Windows就必须改变。
    #contains(QKIT_PRIVATE, WIN32||WIN64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_DEPLOY_PWD~=s,/,\\,g
    }

    libname = $$1
    librealname = $$2
    isEmpty(1): error("add_deploy_library(libname, librealname) requires at last one argument")
    !isEmpty(3): error("add_deploy_library(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    LIB_STD_DIR = $${libname}/$${QSYS_STD_DIR}
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    LIB_LIB_PWD = $${LIB_SDK_PWD}/lib
    equals(QMAKE_HOST.os, Windows) {
        LIB_LIB_PWD~=s,/,\\,g
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_add_deploy_library_on_windows($${libname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_library_on_mac($${libname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_library_on_android($${libname})
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$get_add_deploy_library_on_linux($${libname})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed lib $${libname}.")
    return (1)
}

#判断某个lib是否已经发布
#避免二次发布，拷贝浪费时间。
defineTest(has_deployed_lib) {
    return(0)
}
