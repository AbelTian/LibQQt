#-------------------------------------------------------------
#add_library.pri
#提供app链接library函数，app lib工程通用
#-------------------------------------------------------------
#add_include
#add_include_bundle
#add_library
#add_library_bundle
#add_link_library
#add_link_library_bundle

#固定SDK结构！请参照add_sdk.pri

################################################################################
#内部用函数
#获取命令
################################################################################
#添加链接库路径 Only 路径
defineReplace(get_add_library_path) {
    isEmpty(1)|!isEmpty(3): error("get_add_library_path(libgroupname) requires one argument")

    libgroupname = $$1
    CUR_LIB_PWD = $${LIB_SDK_ROOT}/$${libgroupname}/$${QSYS_STD_DIR}/lib
    equals(QMAKE_HOST.os, Windows) {
        CUR_LIB_PWD~=s,/,\\,g
    }

    LINK =
    contains(DEFINES, __DARWIN__) {
        LINK += -F$${CUR_LIB_PWD}
    }

    LINK += -L$${CUR_LIB_PWD}
    message(add library path $$CUR_LIB_PWD)

    return ($${LINK})
}

defineTest(add_library_path) {
    isEmpty(1)|!isEmpty(3): error("add_library_path(libgroupname) requires one argument")

    libgroupname = $$1
    command = $$get_add_library_path($${libgroupname})
    LIBS += $$command
    export(LIBS)

    return ($${LINK})
}

#链接库的命令
#从LIB_SDK_ROOT按照标准路径QSYS_STD_DIR链接
#mac下使用bundle
defineReplace(get_add_library_bundle) {
    isEmpty(1): error("get_add_library(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_library(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)

    CUR_LIB_PWD = $${LIB_SDK_ROOT}/$${libgroupname}/$${QSYS_STD_DIR}/lib
    equals(QMAKE_HOST.os, Windows) {
        CUR_LIB_PWD~=s,/,\\,g
    }

    LINK =
    contains(DEFINES, __DARWIN__) {
        LINK += -F$${CUR_LIB_PWD}
        LINK += -framework $${libname}
    } else {
        LINK += -L$${CUR_LIB_PWD}
        #win can't with the blank! error: -l QQt
        LINK += -l$${librealname}
    }

    message(link $${libname} from $$CUR_LIB_PWD)
    return ($${LINK})
}

#忽略mac bundle的add_library
#建议不设置第三个参数
defineReplace(get_add_library) {
    isEmpty(1): error("get_add_library(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("get_add_library(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)

    CUR_LIB_PWD = $${LIB_SDK_ROOT}/$${libgroupname}/$${QSYS_STD_DIR}/lib
    equals(QMAKE_HOST.os, Windows) {
        CUR_LIB_PWD~=s,/,\\,g
    }

    LINK =
    #注意：macOS下使用-L -l...也就是链接.dylib .a
    LINK += -L$${CUR_LIB_PWD}
    #win can't with the blank! error: -l QQt
    LINK += -l$${librealname}

    message(link $${libname} from $$CUR_LIB_PWD)

    return ($${LINK})
}


defineReplace(get_add_include_bundle) {
    isEmpty(1): error("get_add_include_bundle(libgroupname, libname, libincsubpath) requires at least one argument")
    !isEmpty(4): error("get_add_include_bundle(libgroupname, libname, libincsubpath) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    libincsubpath = $$3

    isEmpty(libname): libname = $${libgroupname}

    CUR_INC_PWD =
    contains(DEFINES, __DARWIN__) {
        CUR_INC_PWD = $${LIB_SDK_ROOT}/$${libgroupname}/$${QSYS_STD_DIR}/lib/$${libname}.framework/Headers
        !isEmpty(libincsubpath):CUR_INC_PWD=$${CUR_INC_PWD}/$${libincsubpath}
    } else {
        CUR_INC_PWD = $${LIB_SDK_ROOT}/$${libgroupname}/$${QSYS_STD_DIR}/include/$${libname}
        !isEmpty(libincsubpath):CUR_INC_PWD=$${CUR_INC_PWD}/$${libincsubpath}
        equals(QMAKE_HOST.os, Windows) {
            CUR_INC_PWD~=s,/,\\,g
        }
    }

    INCLUDE =
    INCLUDE += $${CUR_INC_PWD}
    message (include $${CUR_INC_PWD})

    return ($${INCLUDE})
}

#获取头文件路径
defineReplace(get_add_include) {
    isEmpty(1): error("get_add_include(libgroupname, libname, libincsubpath) requires at least one argument")
    !isEmpty(4): error("get_add_include(libgroupname, libname, libincsubpath) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    libincsubpath = $$3

    isEmpty(libname): libname = $${libgroupname}

    CUR_INC_PWD = $${LIB_SDK_ROOT}/$${libgroupname}/$${QSYS_STD_DIR}/include/$${libname}
    !isEmpty(libincsubpath):CUR_INC_PWD=$${CUR_INC_PWD}/$${libincsubpath}
    equals(QMAKE_HOST.os, Windows) {
        CUR_INC_PWD~=s,/,\\,g
    }

    INCLUDE =
    INCLUDE += $${CUR_INC_PWD}
    message (include $${CUR_INC_PWD})

    return ($${INCLUDE})
}


################################################################################
#公开给外部用函数
#执行命令
################################################################################
#包含路径
#包含library
defineTest(add_library) {
    isEmpty(1): error("add_library(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("add_library(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)

    command =
    command += $$get_add_library($${libgroupname}, $${libname}, $${librealname})
    LIBS += $${command}
    export(LIBS)
    #message (LIBS += $$command)

    return (1)
}

defineTest(add_library_bundle) {
    isEmpty(1): error("add_library_bundle(libgroupname, libname, librealname) requires at least one argument")
    !isEmpty(4): error("add_library_bundle(libgroupname, libname, librealname) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    librealname = $$3

    isEmpty(libname): libname = $${libgroupname}
    #建议使用默认值
    isEmpty(librealname): librealname = $$add_decorate_target_name($$libname)

    command =
    command += $$get_add_library_bundle($${libgroupname}, $${libname}, $${librealname})
    LIBS += $${command}
    export(LIBS)
    #message (LIBS += $$command)

    return (1)
}

defineTest(add_include_bundle) {
    isEmpty(1): error("add_include_bundle(libgroupname, libname, libincsubpath) requires at least one argument")
    !isEmpty(4): error("add_include_bundle(libgroupname, libname, libincsubpath) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    libincsubpath = $$3

    isEmpty(libname): libname = $${libgroupname}

    command = $$get_add_include_bundle($$libgroupname, $$libname, $$libincsubpath)
    INCLUDEPATH += $${command}
    export(INCLUDEPATH)
    #message (INCLUDEPATH += $$command)

    return (1)
}

defineTest(add_include) {
    isEmpty(1): error("add_include(libgroupname, libname, libincsubpath) requires at least one argument")
    !isEmpty(4): error("add_include(libgroupname, libname, libincsubpath) requires at most three argument")

    libgroupname = $$1
    libname = $$2
    libincsubpath = $$3

    isEmpty(libname): libname = $${libgroupname}

    command = $$get_add_include($$libgroupname, $$libname, $$libincsubpath)
    INCLUDEPATH += $${command}
    export(INCLUDEPATH)
    #message (INCLUDEPATH += $$command)

    return (1)
}


#提供方便
#链接标准SDK
defineTest(add_link_library) {
    isEmpty(1): error("add_link_library(libgroupname, libname) requires at least one argument")
    !isEmpty(3): error("add_link_library(libgroupname, libname) requires at most two argument")

    libgroupname = $$1
    libname = $$2

    isEmpty(libname): libname = $${libgroupname}

    add_include($${libgroupname}, $$libname)
    add_library($$libgroupname, $$libname)

    return (1)
}

defineTest(add_link_library_bundle) {
    isEmpty(1): error("add_link_library_bundle(libgroupname, libname) requires at least one argument")
    !isEmpty(3): error("add_link_library_bundle(libgroupname, libname) requires at most two argument")

    libgroupname = $$1
    libname = $$2

    isEmpty(libname): libname = $${libgroupname}

    add_include_bundle($${libgroupname}, $$libname)
    add_library_bundle($$libgroupname, $$libname)

    return (1)
}
