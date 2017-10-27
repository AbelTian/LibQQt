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
    $$system("echo . 2> $${filename}") | return(false)
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
        sdd = "echo $$value >> $$filename"
        $$system($$sdd) || return(false)
    }
}

QQT_BASE_DIR=$$[QT_INSTALL_DATA]
QQT_INC_DIR=$${QQT_BASE_DIR}/include/QQtCore
QQT_LIB_DIR=$${QQT_BASE_DIR}/lib
QQT_PRI_PATH=$${QQT_BASE_DIR}/mkspecs/modules/qt_lib_qqtcore.pri
QQT_CMAKE_DIR=$${QQT_BASE_DIR}/lib/cmake/QQtCore

QQT_PROJ_DIR=$$PWD

message($$QQT_BASE_DIR)
message($$QQT_INC_DIR)
message($$QQT_LIB_DIR)
message($$QQT_PRI_PATH)
message($$QQT_CMAKE_DIR)

MODULE_NAME=qqtcore
MODULE_CNAME=QQtCore
$$empty_file(qt_lib_$${MODULE_NAME}.pri)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.VERSION = $${TARGET_VERSION}")
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.name = $${MODULE_CNAME}", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.module = $${MODULE_CNAME}", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.libs = $$QT_MODULE_LIB_BASE", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.includes = $$QT_MODULE_LIB_BASE/$${MODULE_CNAME}.framework/Headers", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.frameworks = $$QT_MODULE_LIB_BASE", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.bins = $$QT_MODULE_BIN_BASE", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.depends = core sql network gui xml widgets", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.uses =", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.module_config = v2 lib_bundle", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.DEFINES = QQT_LIBRARY", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.enabled_features =", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT.$${MODULE_NAME}.disabled_features =", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT_CONFIG +=", append)
$$write_file(qt_lib_$${MODULE_NAME}.pri, "QT_MODULES += $${MODULE_NAME}", append)



#framework only
equals(QKIT_, macOS) {
    ###if install product to same path,use this.
    target.path = /System/Library/Frameworks
    INSTALLS += target
} else {
    qqt.files = j
}

