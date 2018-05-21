#-------------------------------------------------------------
#app_link.pri
#提供app链接函数，app lib工程通用
#-------------------------------------------------------------

################################################################################
#内部用函数
#获取命令
################################################################################
defineReplace(get_add_link) {
    libname = $$1
    librealname = $$2
    isEmpty(1): error("get_add_link(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_link(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    CUR_LIB_PWD = $${LIB_SDK_ROOT}/$${libname}/$${QSYS_STD_DIR}/lib
    equals(QMAKE_HOST.os, Windows) {
        CUR_LIB_PWD~=s,/,\\,g
    }

    LINK =
    contains(DEFINES, __DARWIN__) {
        LINK += -F$${CUR_LIB_PWD}
        LINK += -framework $${librealname}
    } else {
        LINK += -L$${CUR_LIB_PWD}
        #win can't with the blank! error: -l QQt
        LINK += -l$${librealname}
    }
    return ($${LINK})
}

defineReplace(get_add_include) {
    incname = $$1
    increalname = $$2
    isEmpty(1): error("get_add_include(incname, increalname) requires at last one argument")
    !isEmpty(3): error("get_add_include(incname, increalname) requires at most two argument")

    INCLUDE =
    contains(DEFINES, __DARWIN__) {
        CUR_INC_PWD = $${LIB_SDK_ROOT}/$${incname}/$${QSYS_STD_DIR}/$${incname}.framework/Headers
        !isEmpty(2):CUR_INC_PWD=$${CUR_INC_PWD}/$${increalname}
        INCLUDE += $${CUR_INC_PWD}
    } else {
        CUR_INC_PWD = $${LIB_SDK_ROOT}/$${incname}/$${QSYS_STD_DIR}/include
        !isEmpty(2):CUR_INC_PWD=$${CUR_INC_PWD}/$${increalname}
        equals(QMAKE_HOST.os, Windows) {
            CUR_INC_PWD~=s,/,\\,g
        }

        INCLUDE += $${CUR_INC_PWD}
    }

    return ($${INCLUDE})
}

defineReplace(get_add_deploy) {
    #APP_DEPLOY_ROOT
    #DESTDIR
    incname = $$1
    increalname = $$2
    isEmpty(1): error("get_add_include(incname, increalname) requires at last one argument")
    !isEmpty(3): error("get_add_include(incname, increalname) requires at most two argument")

    INCLUDE =
    contains(DEFINES, __DARWIN__) {
        CUR_INC_PWD = $${LIB_SDK_ROOT}/$${incname}/$${QSYS_STD_DIR}/$${incname}.framework/Headers
        !isEmpty(2):CUR_INC_PWD=$${CUR_INC_PWD}/$${increalname}
        INCLUDE += $${CUR_INC_PWD}
    } else {
        CUR_INC_PWD = $${LIB_SDK_ROOT}/$${incname}/$${QSYS_STD_DIR}/include
        !isEmpty(2):CUR_INC_PWD=$${CUR_INC_PWD}/$${increalname}
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
#从LIB_SDK_ROOT按照标准路径QSYS_STD_DIR链接
#[libname/5.9.2/macOS/Debug/lib/librealname.framework]
#[libname/5.9.2/macOS/Debug/lib/librealname.dll]
#[libname/5.9.2/macOS/Debug/lib/lib<librealname>.so.*]
#librealname可以为空
defineTest(add_link) {
    libname = $$1
    librealname = $$2
    isEmpty(1): error("add_link(libname, librealname) requires at last one argument")
    !isEmpty(3): error("add_link(libname, librealname) requires at most two argument")
    isEmpty(2): librealname = $${libname}

    command = $$get_add_link($${libname}, $${librealname})
    #message ($$command)
    LIBS += $${command}

    return (1)
}


#从LIB_SDK_ROOT按照标准路径QSYS_STD_DIR包含
#[incname/5.9.2/macOS/Debug/lib/incname.framework/Headers/increalname]
#[incname/5.9.2/macOS/Debug/include/increalname]
#increalname可以为空
defineTest(add_include) {
    incname = $$1
    increalname = $$2
    isEmpty(1): error("add_include(incname, increalname) requires at last one argument")
    !isEmpty(3): error("add_include(incname, increalname) requires at most two argument")

    command = $$get_add_include($${incname}, $${increalname})
    #message ($$command)
    INCLUDEPATH += $${command}

    return (1)
}

