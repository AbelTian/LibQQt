#------------------------------------------------------------------------------------
#app_multi_link_function.pri
#App多链接技术函数库
#用户app从这里调用关于app link的函数
#------------------------------------------------------------------------------------
################################################################################
#app获取功能命令函数
#一般不会拿出去用，除非你懂得LIBS+= INCLUDEPATH+= 语法
################################################################################
defineReplace(get_app_link) {
    libname = $$1
    isEmpty(1): error("get_app_link(libname) requires one argument")
    !isEmpty(2): error("get_app_link(libname) requires one argument")

    CUR_LIB_PWD = $${QQT_SDK_ROOT}/$${libname}/$${QKIT_STD_DIR}/lib
    equals(QMAKE_HOST.os, Windows) {
        CUR_LIB_PWD~=s,/,\\,g
    }

    contains(DEFINES, __DARWIN__) {
        LINK += -F$${CUR_LIB_PWD}
        LINK += -framework $${libname}
    } else {
        LINK += -L$${CUR_LIB_PWD}
        #win can't with the blank! error: -l QQt
        LINK += -l$${libname}
    }
    return ($${LINK})
}

defineReplace(get_app_include) {
    libname = $$1
    isEmpty(1): error("get_app_include(libname) requires one argument")
    !isEmpty(2): error("get_app_include(libname) requires one argument")

    INCLUDE =
    contains(DEFINES, __DARWIN__) {
        CUR_INC_PWD = $${QQT_SDK_ROOT}/$${libname}/$${QKIT_STD_DIR}/$${libname}.framework/Headers
        INCLUDE += $${CUR_INC_PWD}
    } else {
        CUR_INC_PWD = $${QQT_SDK_ROOT}/$${libname}/$${QKIT_STD_DIR}/include
        equals(QMAKE_HOST.os, Windows) {
            CUR_INC_PWD~=s,/,\\,g
        }

        INCLUDE += $${CUR_INC_PWD}
    }

    return ($${INCLUDE})
}

defineReplace(get_app_add_library) {
    libname = $$1
    lib_real_name = $$2
    isEmpty(2): error("get_app_add_library(libname, lib_real_name) requires two argument")
    !isEmpty(3): error("get_app_add_library(libname, lib_real_name) requires two argument")

    CUR_LIB_PWD = $${QQT_SDK_ROOT}/$${libname}/$${QKIT_STD_DIR}/lib
    equals(QMAKE_HOST.os, Windows) {
        CUR_LIB_PWD~=s,/,\\,g
    }

    contains(DEFINES, __DARWIN__) {
        LINK += -F$${CUR_LIB_PWD}
        LINK += -framework $${lib_real_name}
    } else {
        LINK += -L$${CUR_LIB_PWD}
        #win can't with the blank! error: -l QQt
        LINK += -l$${lib_real_name}
    }
    return ($${LINK})
}

defineReplace(get_app_add_header) {
    libname = $$1
    lib_inc_name = $$2
    isEmpty(2): error("get_app_add_library(libname, lib_inc_name) requires two argument")
    !isEmpty(3): error("get_app_add_library(libname, lib_inc_name) requires two argument")

    INCLUDE =
    contains(DEFINES, __DARWIN__) {
        CUR_INC_PWD = $${QQT_SDK_ROOT}/$${libname}/$${QKIT_STD_DIR}/$${lib_inc_name}.framework/Headers
        INCLUDE += $${CUR_INC_PWD}
    } else {
        CUR_INC_PWD = $${QQT_SDK_ROOT}/$${libname}/$${QKIT_STD_DIR}/include/$${lib_inc_name}
        equals(QMAKE_HOST.os, Windows) {
            CUR_INC_PWD~=s,/,\\,g
        }

        INCLUDE += $${CUR_INC_PWD}
    }

    return ($${INCLUDE})
}

################################################################################
#app link 功能函数
#app通过调用这些函数实现从SDK标准路径加载各种lib
################################################################################
#从QQT_SDK_ROOT按照标准路径QKIT_STD_DIR链接 [libname/5.9.2/macOS/Debug/lib/libname.framework]
defineTest(app_link) {
    libname = $$1
    isEmpty(1): error("app_link(libname) requires one argument")
    !isEmpty(2): error("app_link(libname) requires one argument")
    command = $$get_app_link($${libname})
    #message ($$command)
    LIBS += $${command}
    return (1)
}


#从QQT_SDK_ROOT按照标准路径QKIT_STD_DIR包含 [libname/5.9.2/macOS/Debug/lib/libname.framework/Headers]
defineTest(app_include) {
    libname = $$1
    isEmpty(1): error("app_include(libname) requires one argument")
    !isEmpty(2): error("app_include(libname) requires one argument")
    command = $$get_app_include($${libname})
    #message ($$command)
    INCLUDEPATH += $${command}
    return (1)
}

#从QQT_SDK_ROOT按照Lib标准路径QKIT_STD_DIR链接Lib2 [libname/5.9.2/macOS/Debug/lib/librealname.framework]
defineTest(app_add_library) {
    libname = $$1
    lib_real_name = $$1
    isEmpty(2): error("app_add_library(libname) requires two argument")
    !isEmpty(3): error("app_add_library(libname) requires two argument")

    command = $$get_app_add_library($${libname}, $${lib_real_name})
    #message ($$command)
    LIBS += $${command}
    return (1)
}


#从QQT_SDK_ROOT按照Lib标准路径QKIT_STD_DIR包含sub_inc [libname/5.9.2/macOS/Debug/lib/libincname.framework/Headers]
defineTest(app_add_header) {
    libname = $$1
    lib_inc_name = $$2
    isEmpty(2): error("app_add_header(libname, lib_inc_name) requires two argument")
    !isEmpty(3): error("app_add_header(libname, lib_inc_name) requires two argument")

    command = $$get_app_add_header($${libname}, $${lib_inc_name})
    #message ($$command)
    INCLUDEPATH += $${command}
    return (1)
}
