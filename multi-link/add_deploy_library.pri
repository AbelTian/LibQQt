#-------------------------------------------------------------
#add_deploy_library.pri
#提供app发布library函数，只是app工程使用
#-------------------------------------------------------------

################################################################################
#内部用函数
#获取命令
################################################################################
THIS_PRI_PWD = $${PWD}

###############################################################
#app的发布library命令函数
###############################################################
#app发布lib到自己的目标里，必须先发布app，如果没有先发布app会出错（macOS）。
#lib发布lib，没有的事情
#解释，过去从sdk到build到deploy，现在从sdk到build，从sdk到deploy
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
    #build的地方调试需要.lib等其他文件
    command += $$COPY_DIR $${LIB_LIB_PWD}\\*$${librealname}.* $${APP_BUILD_PWD} $$CMD_SEP
    #拷贝sdk到build
    command += $$COPY_DIR $${LIB_BIN_PWD}\\$${librealname}.* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}\\$${librealname}.* $$CMD_SEP
    #deploy的地方不需要.lib等文件
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_BIN_PWD}\\$${librealname}.* $${APP_DEPLOY_PWD}
    #经过调试发现，如果DLL引用了Qt库，App却没有引用，windeployqt不会发布那些库，在这里发布。
    #command += windeployqt $${APP_DEPLOY_PWD}\\$${librealname}.dll $${APP_DEPLOY_PWD}

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_linux) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_on_linux(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_on_linux(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    command =

    command += $$RM $${APP_BUILD_PWD}/lib$${libname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}/lib$${libname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_DEPLOY_PWD}
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_android) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_on_android(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_on_android(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    LIB_ANDROID_PATH = $${LIB_LIB_PWD}/lib$${librealname}.so
    equals(QMAKE_HOST.os, Windows) {
        LIB_ANDROID_PATH~=s,/,\\,g
    }
    message(Android target $${ANDROID_TARGET_ARCH})
    message($${TARGET} deploy library $${LIB_ANDROID_PATH})

    command =
    command += $${LIB_ANDROID_PATH}
    #message($$command)

    return ($$command)
}

################################################################################
#外部用函数
################################################################################
defineTest(add_deploy_library) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    #deploy root
    isEmpty(APP_DEPLOY_ROOT){
        message($${TARGET} $${CONFIG_FILE})
        message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
        error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
    }
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
    LIB_BIN_PWD = $${LIB_SDK_PWD}/bin
    LIB_LIB_PWD = $${LIB_SDK_PWD}/lib
    equals(QMAKE_HOST.os, Windows) {
        LIB_STD_DIR~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
        LIB_BIN_PWD~=s,/,\\,g
        LIB_LIB_PWD~=s,/,\\,g
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_add_deploy_library_on_windows($${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_library_on_mac($${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_library_on_android($${libname}, $${librealname})
    } else {
        ##发布linux、e-linux，这个是一样的。GG
        QMAKE_POST_LINK += $$get_add_deploy_library_on_linux($${libname}, $${librealname})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed library $${librealname}.")
    return (1)
}

#判断某个lib是否已经发布
#避免二次发布，拷贝浪费时间。
defineTest(has_deployed_library) {
    return(0)
}


################################################################################
#内部用函数
################################################################################
###############################################################
#app的发布librarys命令函数
###############################################################
defineReplace(get_add_deploy_libraries_on_mac) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_add_deploy_libraries_on_mac(libname) requires one argument")

    command =

    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD}
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_libraries_on_windows) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_add_deploy_libraries_on_windows(libname) requires one argument")

    command =
    #build 需要.lib .exp等文件
    command += $$COPY_DIR $${LIB_LIB_PWD}\\* $${APP_BUILD_PWD} $$CMD_SEP
    #拷贝sdk到build
    command += $$COPY_DIR $${LIB_BIN_PWD}\\* $${APP_BUILD_PWD} $$CMD_SEP

    #deploy不需要.lib .exp等文件
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_BIN_PWD}\\* $${APP_DEPLOY_PWD}

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_libraries_on_linux) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_add_deploy_libraries_on_linux(libname) requires one argument")

    command =

    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD}
    #message($$command)

    return ($$command)
}

#这个?
defineReplace(get_add_deploy_libraries_on_android) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    isEmpty(1)|!isEmpty(2): error("get_add_deploy_libraries_on_android(libname) requires one argument")

    LIB_ANDROID_PATH = $${LIB_LIB_PWD}/lib$${libname}.so
    equals(QMAKE_HOST.os, Windows) {
        LIB_ANDROID_PATH~=s,/,\\,g
    }
    message(Android target $${ANDROID_TARGET_ARCH})

    command =
    command += $${LIB_ANDROID_PATH}
    #message($$command)

    return ($$command)
}

################################################################################
#外部用函数
################################################################################
defineTest(add_deploy_libraries) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    #deploy root
    isEmpty(APP_DEPLOY_ROOT){
        message($${TARGET} $${CONFIG_FILE})
        message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
        error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
    }
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
    isEmpty(1)|!isEmpty(2): error("add_deploy_libraries(libname) requires one argument")

    LIB_STD_DIR = $${libname}/$${QSYS_STD_DIR}
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    LIB_BIN_PWD = $${LIB_SDK_PWD}/bin
    LIB_LIB_PWD = $${LIB_SDK_PWD}/lib
    equals(QMAKE_HOST.os, Windows) {
        LIB_STD_DIR~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
        LIB_BIN_PWD~=s,/,\\,g
        LIB_LIB_PWD~=s,/,\\,g
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_add_deploy_libraries_on_windows($${libname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_libraries_on_mac($${libname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_libraries_on_android($${libname})
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$get_add_deploy_libraries_on_linux($${libname})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed all libraries under $${libname}.")
    return (1)
}

################################################################################
#内部用函数
#获取命令
################################################################################
###############################################################
#app的发布library命令函数
###############################################################
#这个的作用很简单，对发布的Library进行xxxdeployqt，这些函数是对使用了Qt库的library在跟随app发布的时候用的，
#使用方法:
#不仅跟随app发布库，而且还会对其执行xxxdeployqt。
#Qt库跟随App Qt库跟随Lib。这两边的发布是分开的。
defineReplace(get_add_deploy_library_Qt_on_mac) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_Qt_on_mac(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_Qt_on_mac(libname, librealname) requires at most two argument")
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

defineReplace(get_add_deploy_library_Qt_on_windows) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_Qt_on_windows(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_Qt_on_windows(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    command =
    command += $$RM $${APP_BUILD_PWD}\\$${librealname}.* $$CMD_SEP
    #build的地方调试需要.lib等其他文件
    command += $$COPY_DIR $${LIB_LIB_PWD}\\*$${librealname}.* $${APP_BUILD_PWD} $$CMD_SEP
    #拷贝sdk到build
    command += $$COPY_DIR $${LIB_BIN_PWD}\\$${librealname}.* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}\\$${librealname}.* $$CMD_SEP
    #deploy的地方不需要.lib等文件
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_BIN_PWD}\\$${librealname}.* $${APP_DEPLOY_PWD} $$CMD_SEP

    #经过调试发现，如果Lib引用了Qt库，App却没有引用，windeployqt不会发布那些库，在这里发布。
    DEPLOYTYPE =
    equals(BUILD, Debug):DEPLOYTYPE = --debug
    else:equals(BUILD, Release):DEPLOYTYPE = --release
    else:DEPLOYTYPE = --release
    command += windeployqt $${APP_DEPLOY_PWD}\\$${librealname}.dll $${DEPLOYTYPE} -verbose=1

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_Qt_on_linux) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_Qt_on_linux(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_Qt_on_linux(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    command =

    command += $$RM $${APP_BUILD_PWD}/lib$${libname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}/lib$${libname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_DEPLOY_PWD}
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_Qt_on_android) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_deploy_library_Qt_on_android(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_deploy_library_Qt_on_android(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    LIB_ANDROID_PATH = $${LIB_LIB_PWD}/lib$${librealname}.so
    equals(QMAKE_HOST.os, Windows) {
        LIB_ANDROID_PATH~=s,/,\\,g
    }
    message(Android target $${ANDROID_TARGET_ARCH})
    message($${TARGET} deploy library $${LIB_ANDROID_PATH})

    command =
    command += $${LIB_ANDROID_PATH}
    #message($$command)

    return ($$command)
}

################################################################################
#外部用函数
################################################################################
defineTest(add_deploy_library_Qt) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    #deploy root
    isEmpty(APP_DEPLOY_ROOT){
        message($${TARGET} $${CONFIG_FILE})
        message(APP_DEPLOY_ROOT = /user/set/path is required, please modify .qmake/app_configure.pri )
        error(please check $$CONFIG_FILE under add_multi_link_technology.pri)
    }
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
    isEmpty(1): error("add_deploy_library_Qt(libname, librealname) requires at last one argument")
    !isEmpty(3): error("add_deploy_library_Qt(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    LIB_STD_DIR = $${libname}/$${QSYS_STD_DIR}
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    LIB_BIN_PWD = $${LIB_SDK_PWD}/bin
    LIB_LIB_PWD = $${LIB_SDK_PWD}/lib
    equals(QMAKE_HOST.os, Windows) {
        LIB_STD_DIR~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
        LIB_BIN_PWD~=s,/,\\,g
        LIB_LIB_PWD~=s,/,\\,g
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_add_deploy_library_Qt_on_windows($${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_library_Qt_on_mac($${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_library_Qt_on_android($${libname}, $${librealname})
    } else {
        ##发布linux、e-linux，这个是一样的。GG
        QMAKE_POST_LINK += $$get_add_deploy_library_Qt_on_linux($${libname}, $${librealname})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed library Qt based $${librealname}.")
    return (1)
}
