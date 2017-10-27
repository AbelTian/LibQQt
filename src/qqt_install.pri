################################################
##install to Qt library
################################################
contains(QMAKE_HOST.os,Windows) {
    SCRIPT_SUFFIX=bat
    MOVE = move /y
    COPY = copy /y
    COPY_DIR = xcopy /s /q /y /i
    MKDIR = mkdir
    RM = del
    RM_DIR = rd /s /q
} else {
    SCRIPT_SUFFIX=sh
    MOVE = mv
    COPY = cp -f
    COPY_DIR = $$COPY -R
    MKDIR = mkdir -p
    RM = rm -f
    RM_DIR = rm -rf
}

defineReplace(empty_file) {
    filename = $$1
    isEmpty(1): error("empty_file(name) requires one argument")
    $$system("echo . 2> $${filename}") || return(false)
}

defineReplace(write_file) {
    filename = $$1
    variable = $$2
    append = $$3
    !isEmpty(4): error("write_file(name, [content var, [append]]) requires one to three arguments.")
    isEmpty(3)||!isEqual(3, append) {
        $$empty_file($$filename)
    }
    for(value, variable): {
        $$system("echo $$value >> $$filename")||return(false)
    }
}

defineReplace(mkdir) {
    filename = $$1
    isEmpty(1): error("mkdir(name) requires one argument")
    $$system("$${MKDIR} $${filename}") || return(false)
    return(true)
}


MODULE_NAME=qqtcore
MODULE_CNAME=QQtCore

QQT_BUILD_DIR=$$OUT_PWD/bin
QQT_TEMP_DIR=$$PWD/../install
#QQT_BASE_DIR=$$[QT_INSTALL_DATA]
QQT_BASE_DIR=$$absolute_path($$QQT_TEMP_DIR)

#framework only
contains(QKIT_, macOS) {
    message (laile?)
    ###if install product to same path,use this.
    QQT_BUNDLE_DIR=$${QQT_BASE_DIR}/lib/$${MODULE_CNAME}.framework

    QQT_RES_DIR=$${QQT_BUNDLE_DIR}/Versions/$${TARGET_MAJOR_VERSION}/Resources
    QQT_RES_LINK=$${QQT_BUNDLE_DIR}/Resources

    QQT_INC_DIR=$${QQT_BUNDLE_DIR}/Versions/$${TARGET_MAJOR_VERSION}/Headers
    QQT_INC_DIR=$${QQT_BUNDLE_DIR}/Headers

    QQT_LIB_DIR=$${QQT_BUNDLE_DIR}/Versions/$${TARGET_MAJOR_VERSION}
    QQT_LIB_FILEPATH=$${QQT_LIB_DIR}/$${MODULE_CNAME}
    QQT_LIB_FILEPATH_LINK=$${QQT_BUNDLE_DIR}/$${MODULE_CNAME}

    QQT_CURRENT_LINK=$${QQT_BUNDLE_DIR}/Versions/Current

    QMAKE_INFO_PLIST = $$QQT_RES_DIR/Info.plist
    ##how to set names

    QQT_PRI_PATH=$${QQT_BASE_DIR}/mkspecs/modules
    QQT_PRI_FILEPATH=$${QQT_PRI_PATH}/qt_lib_$${MODULE_NAME}.pri
    QQT_CMAKE_DIR=$${QQT_BASE_DIR}/lib/cmake/$${MODULE_CNAME}
} else {
    QQT_INC_DIR=$${QQT_BASE_DIR}/include/$${MODULE_CNAME}
    QQT_LIB_DIR=$${QQT_BASE_DIR}/lib
    QQT_PRI_PATH=$${QQT_BASE_DIR}/mkspecs/modules
    QQT_PRI_FILEPATH=$${QQT_PRI_PATH}/qt_lib_$${MODULE_NAME}.pri
    QQT_CMAKE_DIR=$${QQT_BASE_DIR}/lib/cmake/$${MODULE_CNAME}
    QQT_RES_DIR=
}

#QQT_BASE_DIR=$$[QT_INSTALL_DATA]

##create dest dirs
!equals(QQT_BASE_DIR , $$[QT_INSTALL_DATA]){
    message($$QQT_BASE_DIR)
    message($$QQT_INC_DIR)
    message($$QQT_LIB_DIR)
    message($$QQT_PRI_PATH)
    message($$QQT_CMAKE_DIR)
    QMAKE_POST_LINK += $$system($$RM_DIR $$QQT_BASE_DIR)
    QMAKE_POST_LINK += $$mkdir($$QQT_BASE_DIR)
    QMAKE_POST_LINK += $$mkdir($$QQT_INC_DIR)
    QMAKE_POST_LINK += $$mkdir($$QQT_PRI_PATH)
    QMAKE_POST_LINK += $$mkdir($$QQT_CMAKE_DIR)
}

##write qt_lib_qqtcore.pri
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.VERSION = $${TARGET_VERSION}")
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.name = $${MODULE_CNAME}", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.module = $${MODULE_CNAME}", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.libs = '\$$QT_MODULE_LIB_BASE'", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.bins = $$system_quote(\$$QT_MODULE_BIN_BASE)", append)
equals(QKIT_, macOS) {
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.includes = '\$$QT_MODULE_LIB_BASE/$${MODULE_CNAME}.framework/Headers'", append)
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.frameworks = '\$$QT_MODULE_LIB_BASE'", append)
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.module_config = v2 lib_bundle", append)
} else {
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.includes = '\$$QT_MODULE_INCLUDE_BASE \$$QT_MODULE_INCLUDE_BASE/$${MODULE_CNAME}'", append)
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.frameworks = ", append)
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.module_config = v2 ", append)
}
greaterThan(QT_MAJOR_VERSION, 4):{
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.depends = core sql network gui xml widgets", append)
} else {
    QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.depends = core sql network gui xml", append)
}
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.uses =", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.DEFINES = QQT_LIBRARY", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.enabled_features =", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT.$${MODULE_NAME}.disabled_features =", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT_CONFIG +=", append)
QMAKE_POST_LINK += $$write_file($${QQT_PRI_FILEPATH}, "QT_MODULES += $${MODULE_NAME}", append)

#write haeders and library
QMAKE_POST_LINK += $$system($$COPY $$HEADERS $$QQT_INC_DIR)
QMAKE_POST_LINK += $$system($$COPY $$QQT_BUILD_DIR/* $$QQT_LIB_DIR)


