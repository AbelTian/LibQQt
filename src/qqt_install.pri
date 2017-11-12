################################################
##qqt_install.pri
##install to Qt library
##please don't modify this pri
##need qqt_version.pri qqt_header.pri qqt_source.pri
################################################
contains(QMAKE_HOST.os,Windows) {
    SCRIPT_SUFFIX=bat
    CMD_SEP = &
    MOVE = move /y
    COPY = copy /y
    COPY_DIR = xcopy /s /q /y /i
    MK_DIR = mkdir
    RM = del
    CD = cd /d
    RM_DIR = rd /s /q
} else {
    SCRIPT_SUFFIX=sh
    CMD_SEP = &&
    MOVE = mv
    COPY = cp -f
    COPY_DIR = cp -rf
    MK_DIR = mkdir -p
    RM = rm -f
    CD = cd
    LN = ln -sf
    RM_DIR = rm -rf
}
################################################
##get command string
################################################
defineReplace(get_mkdir) {
    filepath = $$1
    isEmpty(1): error("get_mkdir(filepath) requires one argument")
    command = $${MKDIR} $${filepath}
    return ($$command)
}
defineReplace(get_errcode) {
    command = $$1
    isEmpty(1): error("get_errcode(command) requires one argument")
    contains(QMAKE_HOST.os,Windows) {
        command = $${command} >nul & echo %errorlevel%
    } else {
        command = $${command} >/dev/null; echo $?
    }
    return ($$command)
}
defineReplace(get_empty_file) {
    filename = $$1
    isEmpty(1): error("get_empty_file(filename) requires one argument")
    command = echo . 2> $${filename}
    return ($$command)
}
defineReplace(get_write_file) {
    filename = $$1
    variable = $$2
    !isEmpty(3): error("get_write_file(name, [content]) requires one or two arguments.")
    isEmpty(2) {
        return ( $$get_empty_file($$filename) )
    }
    command = echo $$variable >> $$filename
    return ($$command)
}

################################################
##custom functions
################################################
# system is default a replace and test function, can be used in condition, but
# system execute succ return 1 fail return 0 it is not follow command error code.
# define test used in condition my impletement
# system_error return command errcode
# 如果自定义的这个函数和系统函数重名，会调用系统函数。
defineTest(system_errcode) {
    command = $$1
    isEmpty(1): error("system_errcode(command) requires one argument")
    #special process
    command = $$get_errcode($$command)
    ret = $$system("$${command}")
    #if eval configed ...
    #error: if(ret) : return (false)
    #erro : eval(ret = 0): return (false)
    #succ: equals(ret, 0):return (false)
    return ($$ret)
}

defineTest(mkdir) {
    filename = $$1
    isEmpty(1): error("mkdir(name) requires one argument")
    command = $$get_mkdir($$filename)
    system_error($${command}): return (true)
    return (false)
}

#can be used in condition or values
#must $$ !
#return values. true is 'true', false is 'false', xx0, xx1 is list
defineReplace(mkdir) {
    filename = $$1
    isEmpty(1): error("mkdir(name) requires one argument")
    command = $$get_mkdir($$filename)
    result = $$system($${command})
    return ($$result)
}


#only use in condition! return true is 1, false is 0
#refuse $$ !
#return only true(1) or false(0)
defineTest(empty_file) {
    filename = $$1
    isEmpty(1): error("empty_file(filename) requires one argument")
    command = $$get_empty_file($$filename)
    system_error($${command}) : return (true)
    return(false)
}

## but system write_file where ?
defineTest(write_file) {
    filename = $$1
    variable = $$2
    !isEmpty(3): error("write_file(name, [content]) requires one or two arguments.")
    isEmpty(2) {
        empty_file($$filename)
    }
    command = $$get_write_file($$filename, $$variable)
    system_error($$command) : return(true)
    return (false)
}

################################################
##QQt install functions
##variable can be private and default inherit
################################################
defineReplace(create_dir_struct) {
    #if it's qt library, don't create
    command =
    !equals(QQT_SDK_DIR , $$[QT_INSTALL_DATA]){
        !contains(QKIT_PRIVATE, macOS) {
            command += $$MK_DIR $$QQT_INC_DIR $$CMD_SEP
        }
        command += $$MK_DIR $$QQT_LIB_DIR $$CMD_SEP
        command += $$MK_DIR $$QQT_CMAKE_DIR $$CMD_SEP
        command += $$MK_DIR $$QQT_PRI_PATH $$CMD_SEP
    }
    return ($$command)
}

defineReplace(create_linux_sdk) {
    #need cd sdk root

    command =
    command += $$COPY $$HEADERS $${QQT_INC_DIR} $$CMD_SEP
    command += $$COPY_DIR $${QQT_BUILD_DIR}/* $${QQT_LIB_DIR}

    return ($$command)
}

defineReplace(create_mac_sdk){
    #need cd framework root
    #QQT_BUILD_DIR MODULE_NAME QQT_MAJOR_VERSION
    module_name = $$lower($$MODULE_NAME)
    QQT_BUNDLE_VER_DIR   = Versions/$${QQT_MAJOR_VERSION}
    QQT_BUNDLE_CUR_DIR   = Versions/Current
    QQT_BUNDLE_INC_DIR   = $${QQT_BUNDLE_VER_DIR}/Headers
    QQT_BUNDLE_RES_DIR   = $${QQT_BUNDLE_VER_DIR}/Resources
    QQT_BUNDLE_EXE_FILE  = $${QQT_BUNDLE_VER_DIR}/$${MODULE_NAME}

    QQT_BUNDLE_CUR_INC_DIR   = $${QQT_BUNDLE_CUR_DIR}/Headers
    QQT_BUNDLE_CUR_RES_DIR   = $${QQT_BUNDLE_CUR_DIR}/Resources
    QQT_BUNDLE_CUR_EXE_FILE  = $${QQT_BUNDLE_CUR_DIR}/$${MODULE_NAME}

    QQT_BUNDLE_CUR_LINK  = Current
    QQT_BUNDLE_INC_LINK  = Headers
    QQT_BUNDLE_RES_LINK  = Resources
    QQT_BUNDLE_EXE_LINK  = $${MODULE_NAME}

    command =
    command += $$MK_DIR $$QQT_BUNDLE_VER_DIR $$CMD_SEP
    command += $$MK_DIR $$QQT_BUNDLE_INC_DIR $$CMD_SEP
    #copy lib
    command += $$COPY_DIR $$QQT_BUILD_DIR/$${MODULE_NAME}.framework/$${QQT_BUNDLE_VER_DIR}/* $$QQT_BUNDLE_VER_DIR $$CMD_SEP
    #copy header
    command += $$COPY $$HEADERS $$QQT_BUNDLE_INC_DIR $$CMD_SEP
    #link header current resources
    command += $$CD Versions $$CMD_SEP
    command += $$LN $${QQT_MAJOR_VERSION} $${QQT_BUNDLE_CUR_LINK} $$CMD_SEP
    command += $$CD .. $$CMD_SEP
    command += $$LN $$QQT_BUNDLE_CUR_INC_DIR  $${QQT_BUNDLE_INC_LINK} $$CMD_SEP
    command += $$LN $$QQT_BUNDLE_CUR_RES_DIR  $${QQT_BUNDLE_RES_LINK} $$CMD_SEP
    command += $$LN $$QQT_BUNDLE_CUR_EXE_FILE $${QQT_BUNDLE_EXE_LINK}

    return ($$command)
}

defineReplace(create_qt_lib_pri){
    #need cd sdk root
    #QQT_BASE_DIR MODULE_NAME QQT_VERSION MODULE_CNAME
    ##write qt_lib_qqtcore.pri
    module_name = $$lower($$MODULE_NAME)
    QQT_PRI_PATH=mkspecs/modules
    QQT_PRI_FILEPATH=$${QQT_PRI_PATH}/qt_lib_$${module_name}.pri

    command =
    command += $$get_empty_file($${QQT_PRI_FILEPATH}) $$CMD_SEP
    command += echo "QT.$${module_name}.VERSION = $${QQT_VERSION}" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.name = $${MODULE_NAME}"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.module = $${MODULE_NAME}"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.libs = '\$$QT_MODULE_LIB_BASE'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.bins = '\$$QT_MODULE_BIN_BASE'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    equals(QKIT_PRIVATE, macOS) {
        command += echo "QT.$${module_name}.includes = '\$$QT_MODULE_LIB_BASE/$${MODULE_NAME}.framework/Headers'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.frameworks = '\$$QT_MODULE_LIB_BASE'" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.module_config = v2 lib_bundle" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${module_name}.includes = '\$$QT_MODULE_INCLUDE_BASE \$$QT_MODULE_INCLUDE_BASE/$${MODULE_NAME}'" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.frameworks = " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.module_config = v2 " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    }
    greaterThan(QT_MAJOR_VERSION, 4):{
        command += echo "QT.$${module_name}.depends = core sql network gui xml widgets" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${module_name}.depends = core sql network gui xml" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    }
    command += echo "QT.$${module_name}.uses =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.DEFINES = QQT_LIBRARY" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.enabled_features =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.disabled_features =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT_CONFIG +=" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT_MODULES += $${module_name}" >> $${QQT_PRI_FILEPATH}
    return ($$command)
}

################################################
##QQt install workflow
################################################
#use to output sdk
contains(CONFIG, qqt_create_sdk){
    MODULE_NAME=QQt
    module_name = $$lower($${MODULE_NAME})

    QQT_BUILD_DIR=$$OUT_PWD/bin
    #sdk path
    QQT_SDK_DIR = $$PWD/../sdk
    message(QQt sdk install here:$${QQT_SDK_DIR})

    QQT_INC_DIR = include/$${MODULE_NAME}
    QQT_LIB_DIR = lib
    QQT_CMAKE_DIR=lib/cmake/$${MODULE_NAME}
    QQT_PRI_PATH=mkspecs/modules
    QQT_PRI_FILEPATH=$${QQT_PRI_PATH}/qt_lib_$${module_name}.pri

    post_link =
    post_link += $$RM_DIR $$QQT_SDK_DIR $$CMD_SEP
    post_link += $$MK_DIR $$QQT_SDK_DIR $$CMD_SEP
    post_link += $$CD $$QQT_SDK_DIR $$CMD_SEP
    post_link += $$create_dir_struct()

    contains(QKIT_PRIVATE, macOS) {
        #message(create QQt mac bundle framework)
        post_link += $$MK_DIR lib/$${MODULE_NAME}.framework $$CMD_SEP
        post_link += $$CD lib/$${MODULE_NAME}.framework $$CMD_SEP
        post_link += $$create_mac_sdk() $$CMD_SEP
        post_link += $$CD ../../ $$CMD_SEP
        #create prl
        post_link += $$COPY $$QQT_BUILD_DIR/$${MODULE_NAME}.framework/$${MODULE_NAME}.prl lib/$${MODULE_NAME}.framework/$${MODULE_NAME}.prl $$CMD_SEP
    } else {
        #message(create QQt linux struct library)
        post_link += $$create_linux_sdk() $$CMD_SEP
        post_link += $$COPY $$QQT_BUILD_DIR/*.prl lib $$CMD_SEP
    }
    post_link += $$create_qt_lib_pri()
    QMAKE_POST_LINK += $${post_link}
    #message ($$post_link)
}

#if you want to use QQt with QT += QQt please open this feature
#unimplete: CONFIG += install_to_qt_library
contains(CONFIG, install_to_qt_library){
    MODULE_NAME=QQt
    QQT_BUILD_DIR=$$OUT_PWD/bin
    #sdk path
    QQT_SDK_DIR=$$[QT_INSTALL_DATA]
    message(QQt sdk install here:$${QQT_SDK_DIR})
}
