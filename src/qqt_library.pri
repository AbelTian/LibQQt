################################################
##qqt_library.pri
##QQt based app please include this pri to link qqt library
##dependence qqt_version.pri qqt_header.pri
##don't modify this pri file, if you catch any issure, please make issure
##https://gitee.com/drabel/LibQt/issues/new?issue%5Bassignee_id%5D=0&issue%5Bmilestone_id%5D=0
##2017年10月29日08:54:28
################################################

message(Link QQt to $${TARGET} $${QKIT_PRIVATE} \
    at $${QT_VERSION} $${SYSNAME} $${BUILD} \
    on $${QMAKE_HOST.os})

QQT_LIB_PWD = $$PWD/../sdk/lib
message (Link QQt from: $$QQT_LIB_PWD)

contains(DEFINES, __DARWIN__) {
    LIBS += -F$${QQT_LIB_PWD}
    LIBS += -framework QQt
} else {
    LIBS += -L$${QQT_LIB_PWD}
    LIBS += -l QQt
}

equals(QKIT_PRIVATE, macOS) {
    MODULE_NAME = QQt
    CMD_SEP = &&
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
    command += mkdir -p $$QQT_BUNDLE_VER_DIR $$CMD_SEP
    command += mkdir -p $$QQT_BUNDLE_INC_DIR $$CMD_SEP
    #copy lib
    command += cp -rf $$QQT_LIB_PWD/$${MODULE_NAME}.framework/$${QQT_BUNDLE_VER_DIR}/* $$QQT_BUNDLE_VER_DIR $$CMD_SEP
    #link header current resources
    command += cd Versions $$CMD_SEP
    command += ln -sf $${QQT_MAJOR_VERSION} $${QQT_BUNDLE_CUR_LINK} $$CMD_SEP
    command += cd .. $$CMD_SEP
    command += ln -sf $$QQT_BUNDLE_CUR_INC_DIR  $${QQT_BUNDLE_INC_LINK} $$CMD_SEP
    command += ln -sf $$QQT_BUNDLE_CUR_RES_DIR  $${QQT_BUNDLE_RES_LINK} $$CMD_SEP
    command += ln -sf $$QQT_BUNDLE_CUR_EXE_FILE $${QQT_BUNDLE_EXE_LINK}

    QMAKE_POST_LINK += rm -rf bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    QMAKE_POST_LINK += mkdir -p bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    QMAKE_POST_LINK += cd bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    QMAKE_POST_LINK += $${command} &&
    QMAKE_POST_LINK += cd $${OUT_PWD} &&
    #QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
    #        bin/$${TARGET}.app/Contents/Frameworks &&
    QMAKE_POST_LINK += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         bin/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    QMAKE_POST_LINK += macdeployqt bin/$${TARGET}.app -verbose=1
    message($$QMAKE_POST_LINK)
}

############
##config defination
############
equals(QKIT_PRIVATE, macOS) {
    CONFIG += app_bundle
}
equals(QKIT_PRIVATE, ANDROID) {
    CONFIG += mobility
    MOBILITY =
}
