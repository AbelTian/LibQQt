#-------------------------------------------------------------
#add_library.pri
#提供app链接library函数，app lib工程通用
#-------------------------------------------------------------
#add_include_path
#add_library_path
#add_library
#add_link_library

#解释每个函数最后两个参数：
#macOS下library的bundle形态决定了是否使用bundle参数
#SDKROOT/模块目录/平台/下是否有Qt版本号，决定了是否使用qtversionpath

################################################################################
#内部用函数
#获取命令
################################################################################
#链接库的命令
#ModuleName
#subdirName
#第三个参数 为空则不使用bundle 输入任何内容都代表使用bundle
#第四个参数 为空则不使用+Qt版本的路径 输入任何内容都代表使用加Qt版本的路径
#LIB_SDK_ROOT/主目录名/Platform/[QtVersion]/lib/子目录
#subdirName可以为空，就是lib根目录。
defineReplace(get_add_library_path) {
    libname = $$1
    librealname = $$2
    libtemplate = $$3
    libqtpath = $$4
    isEmpty(1): error("get_add_library_path(libname, librealname, libtemplate, libqtpath) requires at least one argument")
    !isEmpty(5): error("get_add_library_path(libname, librealname, libtemplate, libqtpath) requires at most four argument")
    isEmpty(2): librealname =
    !isEmpty(3): libtemplate = lib_bundle
    !isEmpty(4): libqtpath = lib_use_qt_version

    CUR_LIB_PWD =
    isEmpty(4):CUR_LIB_PWD = $${LIB_SDK_ROOT}/$${libname}/$${QSYS_STD_DIR}/lib
    else:CUR_LIB_PWD = $${LIB_SDK_ROOT}/$${libname}/$${QSYS_NOQT_STD_DIR}/lib
    !isEmpty(2):CUR_LIB_PWD=$${CUR_LIB_PWD}/$${librealname}
    equals(QMAKE_HOST.os, Windows) {
        CUR_LIB_PWD~=s,/,\\,g
    }
    message(add library path $$CUR_LIB_PWD)

    LINK =
    contains(DEFINES, __DARWIN__):equals(libtemplate, lib_bundle) {
        LINK += -F$${CUR_LIB_PWD}
    } else {
        LINK += -L$${CUR_LIB_PWD}
    }
    return ($${LINK})
}

################################################################################
#公开给外部用函数
#执行命令
################################################################################
#从LIB_SDK_ROOT按照标准路径QSYS_STD_DIR链接
defineTest(add_library_path) {
    libname = $$1
    librealname = $$2
    libtemplate = $$3
    libqtpath = $$4
    isEmpty(1): error("add_library_path(libname, librealname, libtemplate, libqtpath) requires at least one argument")
    !isEmpty(5): error("add_library_path(libname, librealname, libtemplate, libqtpath) requires at most four argument")
    isEmpty(2): librealname =
    !isEmpty(3): libtemplate = lib_bundle
    !isEmpty(4): libqtpath = lib_use_qt_version

    command = $$get_add_library_path($${libname}, $${librealname}, $${libtemplate}, $${libqtpath})
    #message (LIBS += $$command)
    LIBS += $${command}
    export(LIBS)

    return (1)
}

################################################################################
#内部用函数
#获取命令
################################################################################
#直接输入lib的名字即可 libxxx.so 则输入xxx。
defineReplace(get_add_library) {
    libname = $$1
    libtemplate = $$2
    isEmpty(1): error("get_add_library(libname, libtemplate) requires at last one argument")
    !isEmpty(3): error("get_add_library(libname, libtemplate) requires at most two argument")
    !isEmpty(2): libtemplate = lib_bundle

    message(link $${libname})

    LINK =
    contains(DEFINES, __DARWIN__):equals(libtemplate, lib_bundle) {
        LINK += -framework $${libname}
    } else {
        #win can't with the blank! error: -l QQt
        LINK += -l$${libname}
    }
    return ($${LINK})
}

################################################################################
#公开给外部用函数
#执行命令
################################################################################
defineTest(add_library) {
    libname = $$1
    libtemplate = $$2
    isEmpty(1): error("add_library(libname, libtemplate) requires at last one argument")
    !isEmpty(3): error("add_library(libname, libtemplate) requires at most two argument")

    command = $$get_add_library($${libname}, $${libtemplate})
    #message (LIBS += $$command)
    LIBS += $${command}

    export(LIBS)

    return (1)
}


################################################################################
#内部用函数
#获取命令
################################################################################
#获取头文件路径
#模块名，就是SDKROOT根目录里的子文件夹名
#子模块名，就是模块/平台/[QtVersion]/include里的子文件夹名 这个用来切换子文件夹 默认在和主文件夹同名的子文件夹里。 使用其他子模块一般要换这个value。
#子文件夹名，就是上边这个目录里边的文件夹目录
#模板，默认为mac不使用捆绑，可以设置使用。如果设置使用，那么目录为 模块/平台/[QtVersion]/子模块.framework/Headers/子目录
#sdkRoot/ModuleName/Platform/[QtVersion]/include/SubModuleName/subdirName
#这个函数初级工程师能看懂吗？ 这个函数里对include目录制定了标准。
defineReplace(get_add_include_path) {
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libtemplate = $$4
    libqtpath = $$5
    isEmpty(1): error("get_add_include_path(libname, librealname, libsubname, libtemplate) requires at last one argument")
    !isEmpty(6): error("get_add_include_path(libname, librealname, libsubname, libtemplate) requires at most five argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libtemplate = lib_bundle
    !isEmpty(5): libqtpath = lib_use_qt_version

    INCLUDE =
    contains(DEFINES, __DARWIN__):equals(libtemplate, lib_bundle) {
        CUR_INC_PWD =
        isEmpty(5):CUR_INC_PWD = $${LIB_SDK_ROOT}/$${libname}/$${QSYS_NOQT_STD_DIR}/lib/$${librealname}.framework/Headers
        else:CUR_INC_PWD = $${LIB_SDK_ROOT}/$${libname}/$${QSYS_STD_DIR}/lib/$${librealname}.framework/Headers
        !isEmpty(3):CUR_INC_PWD=$${CUR_INC_PWD}/$${libsubname}
        INCLUDE += $${CUR_INC_PWD}
    } else {
        CUR_INC_PWD =
        isEmpty(5):CUR_INC_PWD = $${LIB_SDK_ROOT}/$${libname}/$${QSYS_NOQT_STD_DIR}/include/$${librealname}
        else:CUR_INC_PWD = $${LIB_SDK_ROOT}/$${libname}/$${QSYS_STD_DIR}/include/$${librealname}
        !isEmpty(3):CUR_INC_PWD=$${CUR_INC_PWD}/$${libsubname}
        equals(QMAKE_HOST.os, Windows) {
            CUR_INC_PWD~=s,/,\\,g
        }

        INCLUDE += $${CUR_INC_PWD}
    }

    return ($${INCLUDE})
}


################################################################################
#公开给外部用函数
#执行命令
################################################################################
#从LIB_SDK_ROOT按照标准路径QSYS_STD_DIR包含
#[incname/5.9.2/macOS/Debug/lib/incname.framework/Headers/increalname]
#[incname/5.9.2/macOS/Debug/include/incname/increalname]
#increalname可以为空
defineTest(add_include_path) {
    libname = $$1
    librealname = $$2
    libsubname = $$3
    libtemplate = $$4
    libqtpath = $$5
    isEmpty(1): error("get_add_include_path(libname, librealname, libsubname, libtemplate) requires at last one argument")
    !isEmpty(6): error("get_add_include_path(libname, librealname, libsubname, libtemplate) requires at most five argument")
    isEmpty(2): librealname = $$libname
    isEmpty(3): libsubname =
    !isEmpty(4): libtemplate = lib_bundle
    !isEmpty(5): libqtpath = lib_use_qt_version

    command = $$get_add_include_path($$libname, $$librealname, $$libsubname, $$libtemplate, $${libqtpath})
    #message (INCLUDEPATH += $$command)
    INCLUDEPATH += $${command}
    export(INCLUDEPATH)
    return (1)
}

#提供方便
#链接标准SDK
#添加包含路径 libName/.../include
#添加库路径 libName/.../lib
#链接库 libRealName
defineTest(add_link_library) {
    libname = $$1
    librealname = $$2
    libtemplate = $$3
    libqtpath = $$4
    isEmpty(1): error("add_link_library(libname, librealname, libtemplate, libqtpath) requires at least one argument")
    !isEmpty(5): error("add_link_library(libname, librealname, libtemplate, libqtpath) requires at most four argument")
    isEmpty(2): librealname =
    !isEmpty(3): libtemplate = lib_bundle
    !isEmpty(4): libqtpath = lib_use_qt_version

    add_include_path($${libname}, $$librealname, , $$libtemplate, $$libqtpath)
    add_library_path($${libname}, $$librealname, $$libtemplate, $$libqtpath)
    add_library($${librealname})

    return (1)
}
