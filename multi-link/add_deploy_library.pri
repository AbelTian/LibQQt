#-------------------------------------------------------------
#add_deploy_library.pri
#提供app发布library函数，只是app工程使用
#-------------------------------------------------------------
#add_deploy_library
#add_deploy_libraryes

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

#这个参数很复杂。
#主模块名
#真实模块名
#子目录
#是否为bundle 否则为空 是则为bundle
#是否使用Qt版本路径 否则为空 是则为use
#是否依赖Qt 否则为空 是则为yes
defineReplace(get_add_deploy_library_on_mac) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_library_on_mac(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_library_on_mac(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

    #这里有个bug，用户删除了SDK以后，App qmake阶段读取这个SDK，结果读到这个位置，为0...bug，其实不应该为0，应该为用户设置的SDK版本号。
    #解决方法一：忽略第一遍编译。也就是什么SDK都没有的时候，编译一遍，lib生成了SDK，可是不管他，再qmake后编译一遍。能解决。
    libmajorver =
    !isEmpty(libusebundle){
        libmajorver = $$system(readlink $${LIB_LIB_PWD}/$${libname}.framework/Versions/Current)
        #这里是以防万一lib不存在 但是不能退出？如果是subdirs包含Library的工程，就不能退出。
        isEmpty(libmajorver){
            libmajorver=0
            message($$TARGET deploy $$libname"," unexisted lib.)
            return ("echo unexisted lib $$libname .")
        }
    }

    command =

    !isEmpty(libusebundle) {
        contains(TEMPLATE, app_bundle) {
            command += $$MK_DIR $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
        }
    }

    #拷贝sdk到build
    isEmpty(libusebundle) {
        contains(TEMPLATE, app_bundle) {
            command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
        } else {
            command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} &&
        }
    } else {
        contains(TEMPLATE, app_bundle) {
            command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_BUILD_PWD}/$${TARGET}.app/Contents/Frameworks &&
        } else {
            command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_BUILD_PWD} &&
        }
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
    isEmpty(libusebundle) {
        contains(TEMPLATE, app_bundle) {
            command += install_name_tool -change $${libname}.dylib \
                 @rpath/$${librealname}.dylib \
                 $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
        } else {
            command += install_name_tool -change $${libname}.dylib \
                 @rpath/$${librealname}.dylib \
                 $${APP_BUILD_PWD}/$${TARGET} &&
        }
    } else {
        contains(TEMPLATE, app_bundle) {
            command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
                 @rpath/$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
                 $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
        } else {
            command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
                 @executable_path/../../../$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
                 $${APP_BUILD_PWD}/$${TARGET} &&
        }
    }

    #这个似乎多余，add deploy已经做了
    #command += macdeployqt $${APP_BUILD_PWD}/$${TARGET}.app -verbose=1 &&
    #lessThan(QT_MAJOR_VERSION, 5){
    #    command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/mac_deploy_qt4.sh &&
    #    command += $${ADD_DEPLOY_LIBRARY_PRI_PWD}/mac_deploy_qt4.sh $${APP_BUILD_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    #}

    !isEmpty(libusebundle) {
        contains(TEMPLATE, app_bundle) {
            command += $$MK_DIR $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
        }
    }

    #拷贝sdk到build
    isEmpty(libusebundle) {
        contains(TEMPLATE, app_bundle) {
            command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
        } else {
            command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD} &&
        }
    } else {
        contains(TEMPLATE, app_bundle) {
            command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/Frameworks &&
        } else {
            command += $$COPY_DIR $${LIB_LIB_PWD}/$${libname}.framework $${APP_DEPLOY_PWD} &&
        }
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
    isEmpty(libusebundle) {
        contains(TEMPLATE, app_bundle) {
            command += install_name_tool -change $${libname}.dylib \
                 @rpath/$${librealname}.dylib \
                 $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
        } else {
            command += install_name_tool -change $${libname}.dylib \
                 @rpath/$${librealname}.dylib \
                 $${APP_DEPLOY_PWD}/$${TARGET} &&
        }
    } else {
        contains(TEMPLATE, app_bundle) {
            command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
                 @rpath/$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
                 $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
        } else {
            command += install_name_tool -change $${libname}.framework/Versions/$${libmajorver}/$${libname} \
                 @executable_path/../../../$${libname}.framework/Versions/$${libmajorver}/$${librealname} \
                 $${APP_DEPLOY_PWD}/$${TARGET} &&
        }
    }

    #command += macdeployqt $${APP_DEPLOY_PWD}/$${TARGET}.app -verbose=1
    #lessThan(QT_MAJOR_VERSION, 5){
    #    command += &&
    #    command += chmod +x $${ADD_DEPLOY_LIBRARY_PRI_PWD}/mac_deploy_qt4.sh &&
    #    command += $${ADD_DEPLOY_LIBRARY_PRI_PWD}/mac_deploy_qt4.sh $${APP_DEPLOY_PWD}/$${TARGET}.app/Contents/MacOS/$${TARGET}
    #}
    command += echo . #app deploy library $$librealname progressed.

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_windows) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD

    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_library_on_windows(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_library_on_windows(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

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

    !isEmpty(libdeployqt) {
        #经过调试发现，如果DLL引用了Qt库，App却没有引用，windeployqt不会发布那些库，在这里发布。
        #command += windeployqt $${APP_BUILD_PWD}\\$${librealname}.dll $${DEPLOYTYPE} -verbose=1 $$CMD_SEP
    }

    command += $$RM $${APP_DEPLOY_PWD}\\*$${librealname}.* $$CMD_SEP
    #deploy的地方不需要.lib等文件
    #拷贝sdk到deploy
    command += $$COPY_DIR $${LIB_BIN_PWD}\\$${librealname}.* $${APP_DEPLOY_PWD} $$CMD_SEP

    !isEmpty(libdeployqt) {
        #经过调试发现，如果DLL引用了Qt库，App却没有引用，windeployqt不会发布那些库，在这里发布。
        command += windeployqt $${APP_DEPLOY_PWD}\\$${librealname}.dll $${DEPLOYTYPE} -verbose=1 $$CMD_SEP
    }

    command += echo . #app deploy library $$librealname progressed.

    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_linux) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_library_on_linux(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_library_on_linux(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

    command =

    command += $$RM $${APP_BUILD_PWD}/lib$${librealname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_BUILD_PWD} $$CMD_SEP

    command += $$RM $${APP_DEPLOY_PWD}/lib$${librealname}.so* $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/lib$${librealname}.so* $${APP_DEPLOY_PWD}
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_library_on_android) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_library_on_linux(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_library_on_linux(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

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
#内部用函数
################################################################################
###############################################################
#app的发布librarys命令函数
###############################################################
#发布所有的library
defineReplace(get_add_deploy_libraryes_on_mac) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_libraryes_on_mac(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_libraryes_on_mac(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

    command =

    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD}
    #message($$command)

    return ($$command)
}

defineReplace(get_add_deploy_libraryes_on_windows) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_libraryes_on_windows(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_libraryes_on_windows(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

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

defineReplace(get_add_deploy_libraryes_on_linux) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_libraryes_on_linux(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_libraryes_on_linux(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

    command =

    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_BUILD_PWD} $$CMD_SEP
    command += $$COPY_DIR $${LIB_LIB_PWD}/* $${APP_DEPLOY_PWD}
    #message($$command)

    return ($$command)
}

#这个?
defineReplace(get_add_deploy_libraryes_on_android) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("get_add_deploy_libraryes_on_android(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("get_add_deploy_libraryes_on_android(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

    LIB_ANDROID_PATH = $${LIB_LIB_PWD}/lib$${librealname}.so
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
################################################################################
#外部用函数
################################################################################
defineTest(add_deploy_libraryes) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("add_deploy_library(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("add_deploy_library(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname =
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

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
    APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET_PRIVATE}/$${QSYS_STD_DIR}
    #不仅仅发布目标为Windows的时候，才需要改变路径
    #开发机为Windows就必须改变。
    #contains(QKIT_PRIVATE, WIN32||WIN64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_DEPLOY_PWD~=s,/,\\,g
    }

    LIB_STD_DIR =
    isEmpty(libuseqtversion):LIB_STD_DIR = $${libname}/$${QSYS_NOQT_STD_DIR}
    else:LIB_STD_DIR = $${libname}/$${QSYS_STD_DIR}
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    LIB_BIN_PWD = $${LIB_SDK_PWD}/bin
    LIB_LIB_PWD = $${LIB_SDK_PWD}/lib
    !isEmpty(libsubname):LIB_LIB_PWD = $${LIB_LIB_PWD}/$${libsubname}

    equals(QMAKE_HOST.os, Windows) {
        LIB_STD_DIR~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
        LIB_BIN_PWD~=s,/,\\,g
        LIB_LIB_PWD~=s,/,\\,g
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_add_deploy_libraryes_on_windows($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_libraryes_on_mac($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_libraryes_on_android($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
    } else {
        #发布linux、e-linux，这个是一样的。
        QMAKE_POST_LINK += $$get_add_deploy_libraryes_on_linux($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
    }

    export(QMAKE_POST_LINK)

    message("$${TARGET} has deployed all libraries under $${libname}.")
    return (1)
}

defineTest(add_deploy_library) {
    #APP_DEPLOY_PWD
    #APP_DEST_PWD
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libusebundle = $$4
    libuseqtversion = $$5
    libdeployqt = $$6
    isEmpty(1): error("add_deploy_library(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at least one argument")
    !isEmpty(7): error("add_deploy_library(libname, librealname, libsubname, libusebundle, libuseqtversion, libdeployqt) requires at most six argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libusebundle = lib_use_bundle
    !isEmpty(5): libuseqtversion = lib_use_qt_version
    !isEmpty(6): libdeployqt = lib_deploy_qt

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
    APP_DEPLOY_PWD = $${APP_DEPLOY_ROOT}/$${TARGET_PRIVATE}/$${QSYS_STD_DIR}
    #不仅仅发布目标为Windows的时候，才需要改变路径
    #开发机为Windows就必须改变。
    #contains(QKIT_PRIVATE, WIN32||WIN64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_DEPLOY_PWD~=s,/,\\,g
    }

    LIB_STD_DIR =
    isEmpty(libuseqtversion):LIB_STD_DIR = $${libname}/$${QSYS_NOQT_STD_DIR}
    else:LIB_STD_DIR = $${libname}/$${QSYS_STD_DIR}
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    LIB_BIN_PWD = $${LIB_SDK_PWD}/bin
    LIB_LIB_PWD = $${LIB_SDK_PWD}/lib

    !isEmpty(libsubname):LIB_LIB_PWD = $${LIB_LIB_PWD}/$${libsubname}

    equals(QMAKE_HOST.os, Windows) {
        LIB_STD_DIR~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
        LIB_BIN_PWD~=s,/,\\,g
        LIB_LIB_PWD~=s,/,\\,g
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows||Win64) {
        #发布windows版本
        QMAKE_POST_LINK += $$get_add_deploy_library_on_windows($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
    } else: contains(QSYS_PRIVATE, macOS) {
        #发布苹果版本，iOS版本也是这个？
        QMAKE_POST_LINK += $$get_add_deploy_library_on_mac($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
    } else: contains(QSYS_PRIVATE, Android||AndroidX86) {
        ANDROID_EXTRA_LIBS += $$get_add_deploy_library_on_android($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
    } else {
        ##发布linux、e-linux，这个是一样的。GG
        QMAKE_POST_LINK += $$get_add_deploy_library_on_linux($${libname}, $${librealname}, $${libsubname}, $${libusebundle}, $${libuseqtversion}, $${libdeployqt})
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
