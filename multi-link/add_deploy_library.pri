#-------------------------------------------------------------
#add_deploy_library.pri
#提供app发布library函数，只是app工程使用
#-------------------------------------------------------------
#add_deploy_library
#add_deploy_library_bundle
#add_deploy_libraryes
#has_deployed_library

################################################################################
#内部用函数
#获取命令
################################################################################
ADD_DEPLOY_LIBRARY_PRI_PWD = $${PWD}

###############################################################
#app的发布library命令函数
###############################################################
#app发布lib到自己的目标里，必须先发布app，如果没有先发布app会出错（macOS）。
#lib发布lib，没有的事情
#解释，过去从sdk到build到deploy，现在从sdk到build，从sdk到deploy
defineReplace(get_add_deploy_library_on_mac) {
    isEmpty(1): error("get_add_deploy_library_on_mac(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_deploy_library_on_mac(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)


    command =

    contains(CONFIG, app_bundle) {
        command += $$MK_DIR $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
    }

    #拷贝sdk到build
    contains(CONFIG, app_bundle) {
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
    } else {
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} &&
    }
    #一条代码总是拷贝实例
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += $$CD $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks $$CMD_SEP
    #command += $$MK_DIR $${libname}.framework $$CMD_SEP
    #command += $$CD $${libname}.framework $$CMD_SEP
    #command += $$get_add_mac_sdk($${libname}, $${librealname}, $${libmajorver}) $$CMD_SEP
    #command += $$CD .. $$CMD_SEP
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP

    #更改app bundle链接Lib的位置。
    contains(CONFIG, app_bundle) {
        command += install_name_tool -change @loader_path/lib$${librealname}.dylib \
             @rpath/lib$${librealname}.dylib \
             $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    } else {
        command += install_name_tool -change @loader_path/lib$${librealname}.dylib \
             @executable_path/lib$${librealname}.dylib \
             $${APP_BUILD_PWD}/$${TARGET} &&
    }


    contains(CONFIG, app_bundle) {
        command += $$MK_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
    }

    #拷贝sdk到build
    contains(CONFIG, app_bundle) {
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
    } else {
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD} &&
    }
    #一条代码总是拷贝实例
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += $$CD $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks $$CMD_SEP
    #command += $$MK_DIR $${libname}.framework $$CMD_SEP
    #command += $$CD $${libname}.framework $$CMD_SEP
    #command += $$get_add_mac_sdk($${libname}, $${librealname}, $${libmajorver}) $$CMD_SEP
    #command += $$CD .. $$CMD_SEP
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP

    #更改app bundle链接Lib的位置。
    contains(CONFIG, app_bundle) {
        command += install_name_tool -change @loader_path/lib$${librealname}.dylib \
             @rpath/lib$${librealname}.dylib \
             $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    } else {
        command += install_name_tool -change @loader_path/lib$${librealname}.dylib \
             @executable_path/lib$${librealname}.dylib \
             $${APP_DEPLOY_PWD}/$${TARGET} &&
    }

    command += echo . #app deploy library $$librealname progressed.
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_bundle_on_mac) {
    isEmpty(1): error("get_add_deploy_library_bundle_on_mac(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_deploy_library_bundle_on_mac(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)


    #这里有个bug，用户删除了SDK以后，App qmake阶段读取这个SDK，结果读到这个位置，为0...bug，其实不应该为0，应该为用户设置的SDK版本号。
    #解决方法一：忽略第一遍编译。也就是什么SDK都没有的时候，编译一遍，lib生成了SDK，可是不管他，再qmake后编译一遍。能解决。
    libmajorver =
    libmajorver = $$system(readlink $${LIB_LIB_PWD}/$${libname}.framework/Versions/Current)
    #这里是以防万一lib不存在 但是不能退出？如果是subdirs包含Library的工程，就不能退出。
    isEmpty(libmajorver){
        libmajorver=0
        message($$TARGET deploy $$libname"," unexisted lib.)
        return ("echo unexisted lib $$libname .")
    }

    command =

    contains(CONFIG, app_bundle) {
        command += $$MK_DIR $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
    }

    #拷贝sdk到build
    contains(CONFIG, app_bundle) {
        command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
    } else {
        command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_BUILD_PWD} &&
    }
    #一条代码总是拷贝实例
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += $$CD $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks $$CMD_SEP
    #command += $$MK_DIR $${libname}.framework $$CMD_SEP
    #command += $$CD $${libname}.framework $$CMD_SEP
    #command += $$get_add_mac_sdk($${libname}, $${librealname}, $${libmajorver}) $$CMD_SEP
    #command += $$CD .. $$CMD_SEP
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP

    #更改app bundle链接Lib的位置。
    contains(CONFIG, app_bundle) {
        command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
             @rpath/$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
             $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    } else {
        command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
             @executable_path/$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
             $${APP_BUILD_PWD}/$${TARGET} &&
    }


    contains(CONFIG, app_bundle) {
        command += $$MK_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
    }

    #拷贝sdk到 deploy
    contains(CONFIG, app_bundle) {
        command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
    } else {
        command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_DEPLOY_PWD} &&
    }
    #一条代码总是拷贝实例
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cur_path.sh $$CMD_SEP
    #command += $$CD $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks $$CMD_SEP
    #command += $$MK_DIR $${libname}.framework $$CMD_SEP
    #command += $$CD $${libname}.framework $$CMD_SEP
    #command += $$get_add_mac_sdk($${libname}, $${librealname}, $${libmajorver}) $$CMD_SEP
    #command += $$CD .. $$CMD_SEP
    #command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP
    #command += . $${ADD_DEPLOY_LIBRARY_PRI_PWD}/linux_cd_path.sh $$CMD_SEP

    #更改app bundle链接Lib的位置。
    contains(CONFIG, app_bundle) {
        command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
             @rpath/$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
             $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    } else {
        command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
             @executable_path/$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
             $${APP_DEPLOY_PWD}/$${TARGET} &&
    }

    command += echo . #app deploy library $$librealname progressed.
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_windows) {
    isEmpty(1): error("get_add_deploy_library_on_windows(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_deploy_library_on_windows(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)

    DEPLOYTYPE =
    equals(BUILD, Debug):DEPLOYTYPE = --debug
    else:equals(BUILD, Release):DEPLOYTYPE = --release
    else:DEPLOYTYPE = --release

    command =
    command += $$RM $${APP_BUILD_PWD}\\*$${librealname}.* $$CMD_SEP
    #build的地方调试需要.lib等其他文件
    command += $$COPY_DIR $${LIB_LIB_PWD}\\*$${librealname}.* $${APP_BUILD_PWD} $$CMD_SEP
    #拷贝sdk到build
    command += $$COPY_DIR $${LIB_BIN_PWD}\\$${librealname}.* $${APP_BUILD_PWD} $$CMD_SEP


    command += $$RM $${APP_DEPLOY_PWD}\\*$${librealname}.* $$CMD_SEP
    #deploy的地方不需要.lib等文件
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_BIN_PWD}\\$${librealname}.* $${APP_DEPLOY_PWD} $$CMD_SEP

    #经过调试发现，如果DLL引用了Qt库，App却没有引用，windeployqt不会发布那些库，在这里发布。
    command += windeployqt $${APP_DEPLOY_PWD}\\$${librealname}.dll $${DEPLOYTYPE} -verbose=1 $$CMD_SEP

    command += echo . #app deploy library $$librealname progressed.

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_linux) {
    isEmpty(1): error("get_add_deploy_library_on_windows(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_deploy_library_on_windows(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)


    command =

    command += $$RM $${APP_BUILD_PWD}/lib$${librealname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}/lib$${librealname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_DEPLOY_PWD} $$CMD_SEP

    command += echo . #app deploy library $$librealname progressed.

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_android) {
    isEmpty(1): error("get_add_deploy_library_on_windows(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_deploy_library_on_windows(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)

    LIB_ANDROID_PATH = $${LIB_LIB_PWD}/lib$${librealname}.so
    equals(QMAKE_HOST.os, Windows) {
        LIB_ANDROID_PATH~=s,/,\\,g
    }
    message(Android target $${ANDROID_TARGET_ARCH})
    message(Android $${TARGET} deploy library $${LIB_ANDROID_PATH})

    command =
    command += $${LIB_ANDROID_PATH}
    #message($$command)

    return ($$command)
}

###############################################################
#app的发布librarys命令函数
###############################################################
#发布所有的library
defineReplace(get_add_deploy_libraryes_on_mac) {

    command =

    contains(CONFIG, app_bundle) {
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks $$CMD_SEP
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks $$CMD_SEP
    } else {
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} $$CMD_SEP
        command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD} $$CMD_SEP
    }
    command += echo . #app deploy library $$librealname progressed.
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_libraryes_on_windows) {

    command =
    #build 需要.lib .exp等文件
    command += $$COPY_DIR $${LIB_LIB_PWD}\\* $${APP_BUILD_PWD} $$CMD_SEP
    #拷贝sdk到build
    command += $$COPY_DIR $${LIB_BIN_PWD}\\* $${APP_BUILD_PWD} $$CMD_SEP

    #deploy不需要.lib .exp等文件
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_BIN_PWD}\\* $${APP_DEPLOY_PWD} $$CMD_SEP

    command += echo . #app deploy library $$librealname progressed.
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_libraryes_on_linux) {

    command =

    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD} $$CMD_SEP
    command += echo . #app deploy library $$librealname progressed.
    #message($$command)

    return ($$command)
}

#这个?
defineReplace(get_add_deploy_libraryes_on_android) {
    isEmpty(1): error("get_add_deploy_libraryes_on_android(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_deploy_libraryes_on_android(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)

    LIB_ANDROID_PATH = $${LIB_LIB_PWD}/lib$${librealname}.so
    equals(QMAKE_HOST.os, Windows) {
        LIB_ANDROID_PATH~=s,/,\\,g
    }
    message(Android target $${ANDROID_TARGET_ARCH})
    message(Android $${TARGET} deploy library $${LIB_ANDROID_PATH})

    command =
    command += $${LIB_ANDROID_PATH}
    #message($$command)

    return ($$command)
}


################################################################################
#外部用函数
################################################################################
defineTest(add_deploy_library) {
    isEmpty(1): error("add_deploy_library(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("add_deploy_library(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)


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

    LIB_STD_DIR =
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}
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
        QMAKE_POST_LINK += $$get_add_deploy_library_on_windows($${libgroupname}, $${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_library_on_mac($${libgroupname}, $${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_library_on_android($${libgroupname}, $${libname}, $${librealname})
    } else {
        ##发布linux、e-linux，这个是一样的。GG
        QMAKE_POST_LINK += $$get_add_deploy_library_on_linux($${libgroupname}, $${libname}, $${librealname})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed library $${libname} ")
    return (1)
}

defineTest(add_deploy_library_bundle) {
    isEmpty(1): error("add_deploy_library_bundle(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("add_deploy_library_bundle(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)


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

    LIB_STD_DIR =
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}
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
        QMAKE_POST_LINK += $$get_add_deploy_library_on_windows($${libgroupname}, $${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_library_bundle_on_mac($${libgroupname}, $${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_library_on_android($${libgroupname}, $${libname}, $${librealname})
    } else {
        ##发布linux、e-linux，这个是一样的。GG
        QMAKE_POST_LINK += $$get_add_deploy_library_on_linux($${libgroupname}, $${libname}, $${librealname})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed library $${libname}")
    return (1)
}

defineTest(add_deploy_libraryes) {
    isEmpty(1): error("add_deploy_library(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("add_deploy_library(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)


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

    LIB_STD_DIR =
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}
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
        QMAKE_POST_LINK += $$get_add_deploy_libraryes_on_windows($${libgroupname}, $${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_libraryes_on_mac($${libgroupname}, $${libname}, $${librealname})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_libraryes_on_android($${libgroupname}, $${libname}, $${librealname})
    } else {
        ##发布linux、e-linux，这个是一样的。GG
        QMAKE_POST_LINK += $$get_add_deploy_libraryes_on_linux($${libgroupname}, $${libname}, $${librealname})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed all libraries under $${libgroupname}")
    return (1)
}


#判断某个lib是否已经发布
#避免二次发布，拷贝浪费时间。
defineTest(has_deployed_library) {
    return(0)
}
