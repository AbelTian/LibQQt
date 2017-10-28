#don't modify this pri file.

message(Link QQt to $${TARGET} $${QKIT_} \
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

equals(QKIT_, macOS) {
    QMAKE_POST_LINK += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         bin/$${TARGET}.app/Contents/MacOS/$$TARGET &&
    QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
            bin/$${TARGET}.app/Contents/Frameworks &&
    QMAKE_POST_LINK += macdeployqt bin/$${TARGET}.app -verbose=1
}

############
##config defination
############
equals(QKIT_, macOS) {
    CONFIG += app_bundle
}
equals(QKIT_, ANDROID) {
    CONFIG += mobility
    MOBILITY =
}
