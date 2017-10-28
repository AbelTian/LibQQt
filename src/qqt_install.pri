################################################
##install to Qt library
################################################
contains(QMAKE_HOST.os,Windows) {
    SCRIPT_SUFFIX=bat
    CMD_SEP = &
    MOVE = move /y
    COPY = copy /y
    COPY_DIR = xcopy /s /q /y /i
    MK_DIR = mkdir
    RM = del
    RM_DIR = rd /s /q
} else {
    SCRIPT_SUFFIX=sh
    CMD_SEP = &&
    MOVE = mv
    COPY = cp -f
    COPY_DIR = $$COPY -R
    MK_DIR = mkdir -p
    RM = rm -f
    LN = ln -s
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


system("touch $${PWD}/exquisite/qqtcustomeffectprogressbar.cpp")


MODULE_NAME=qqtcore
MODULE_CNAME=QQtCore

QQT_BUILD_DIR=$$OUT_PWD/bin
QQT_TEMP_DIR=$$PWD/../install
#QQT_BASE_DIR=$$[QT_INSTALL_DATA]
QQT_BASE_DIR=$$QQT_TEMP_DIR
#QQT_BASE_DIR=$$[QT_INSTALL_DATA]
message(QQt sdk install here:$${QQT_BASE_DIR})

defineReplace(create_sdk_dirs) {
    return (cccccc)
}
#can be used in condition or values
#must $$ !
#return values. true is 'true', false is 'false', xx0, xx1 is list
defineReplace(create_sdk) {
    return (cccccc)
}

!equals(QQT_BASE_DIR , $$[QT_INSTALL_DATA]){
    QQT_INC_DIR=$${QQT_BASE_DIR}/include/$${MODULE_CNAME}
    QQT_LIB_DIR=$${QQT_BASE_DIR}/lib
    QQT_PRI_PATH=$${QQT_BASE_DIR}/mkspecs/modules
    QQT_PRI_FILEPATH=$${QQT_PRI_PATH}/qt_lib_$${MODULE_NAME}.pri
    QQT_CMAKE_DIR=$${QQT_BASE_DIR}/lib/cmake/$${MODULE_CNAME}
    #mac only
    contains(QKIT_, macOS) {
        QQT_INC_DIR=$${QQT_BASE_DIR}/lib/QQt.framework/Versions/$${TARGET_MAJOR_VERSION}/Headers
    }
}

#create base dir excide header
!equals(QQT_BASE_DIR , $$[QT_INSTALL_DATA]){
    QMAKE_POST_LINK += $$RM_DIR $$QQT_BASE_DIR $$CMD_SEP
    QMAKE_POST_LINK += $$MK_DIR $$QQT_BASE_DIR $$CMD_SEP
    QMAKE_POST_LINK += $$MK_DIR $$QQT_LIB_DIR $$CMD_SEP
    QMAKE_POST_LINK += $$MK_DIR $$QQT_PRI_PATH $$CMD_SEP
    QMAKE_POST_LINK += $$MK_DIR $$QQT_CMAKE_DIR $$CMD_SEP
}

#copy lib
contains(QKIT_, macOS) {
    QMAKE_POST_LINK += "$$COPY_DIR $$QQT_BUILD_DIR/QQt.framework $$QQT_LIB_DIR" $$CMD_SEP
} else {
    QMAKE_POST_LINK += "$$COPY_DIR $$QQT_BUILD_DIR/* $$QQT_LIB_DIR" $$CMD_SEP
}

#create header dir
!equals(QQT_BASE_DIR , $$[QT_INSTALL_DATA]){
    QMAKE_POST_LINK += $$MK_DIR $$QQT_INC_DIR $$CMD_SEP
}
QMAKE_POST_LINK += $$COPY $$HEADERS $$QQT_INC_DIR $$CMD_SEP

#link header
contains(QKIT_, macOS) {
    QMAKE_POST_LINK += "$$LN $$QQT_INC_DIR $$QQT_LIB_DIR/QQt.framework/Headers" $$CMD_SEP
}

##write qt_lib_qqtcore.pri
QMAKE_POST_LINK += $$get_empty_file($${QQT_PRI_FILEPATH}) $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.VERSION = $${TARGET_VERSION}" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.name = $${MODULE_CNAME}"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.module = $${MODULE_CNAME}"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.libs = '\$$QT_MODULE_LIB_BASE'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.bins = '\$$QT_MODULE_BIN_BASE'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
equals(QKIT_, macOS) {
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.includes = '\$$QT_MODULE_LIB_BASE/$${MODULE_CNAME}.framework/Headers'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.frameworks = '\$$QT_MODULE_LIB_BASE'" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.module_config = v2 lib_bundle" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
} else {
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.includes = '\$$QT_MODULE_INCLUDE_BASE \$$QT_MODULE_INCLUDE_BASE/$${MODULE_CNAME}'" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.frameworks = " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.module_config = v2 " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
}
greaterThan(QT_MAJOR_VERSION, 4):{
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.depends = core sql network gui xml widgets" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
} else {
    QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.depends = core sql network gui xml" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
}
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.uses =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.DEFINES = QQT_LIBRARY" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.enabled_features =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT.$${MODULE_NAME}.disabled_features =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT_CONFIG +=" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
QMAKE_POST_LINK += echo "QT_MODULES += $${MODULE_NAME}" >> $${QQT_PRI_FILEPATH}



