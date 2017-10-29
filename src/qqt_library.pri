################################################
##qqt_library.pri
##QQt based app contains qqt library
##need qqt_version.pri
##don't modify this pri file, if you cache any issure, please make issure
##https://gitee.com/drabel/LibQt/issues/new?issue%5Bassignee_id%5D=0&issue%5Bmilestone_id%5D=0
##2017年10月29日08:54:28
################################################

message(Link QQt to $${TARGET} $${QKIT_PRIVATE} \
    at $${QT_VERSION} $${SYSNAME} $${BUILD} \
    on $${QMAKE_HOST.os})

QQT_LIB_PWD = $$PWD/../sdk/lib
message (Linke QQt from: $$QQT_LIB_PWD)

contains(DEFINES, __DARWIN__) {
    lessThan(QT_MAJOR_VERSION, 5):{
        LIBS += -L$${QQT_LIB_PWD}
        LIBS += -l QQt
    } else {
        LIBS += -F$${QQT_LIB_PWD}
        LIBS += -framework QQt
    }
} else {
    LIBS += -L$${QQT_LIB_PWD}
    LIBS += -l QQt
}

equals(QKIT_PRIVATE, macOS) {
    QMAKE_POST_LINK += rm -rf bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    QMAKE_POST_LINK += cp -af $${QQT_LIB_PWD}/QQt.framework \
            bin/$${TARGET}.app/Contents/Frameworks &&
    QMAKE_POST_LINK += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         bin/$${TARGET}.app/Contents/MacOS/$$TARGET &&
    QMAKE_POST_LINK += macdeployqt bin/$${TARGET}.app -verbose=1
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
