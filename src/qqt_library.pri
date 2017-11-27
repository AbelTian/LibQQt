################################################
##qqt_library.pri
##QQt based app please include this pri to link qqt library
##dependence qqt_version.pri qqt_header.pri
##don't modify this pri file, if you catch any issure, please make issure
##https://gitee.com/drabel/LibQt/issues/new?issue%5Bassignee_id%5D=0&issue%5Bmilestone_id%5D=0
##2017年10月29日08:54:28
################################################

################################################
##include qqt_install.pri using these function to install qqt
##install to Qt library
##install to SDK path
##in this section, I use QMAKE_POST_LINK, it won't work until project source changed
##on windows, I use touch.exe, you need download it and put it in system dir.
################################################
#QMAKE_POST_LINK won't work until source changed
#qmake pro pri prf change won't effect to QMAKE_POST_LINK
#but I need it before I complete this pri.
#debug.
system("touch $${PWD}/frame/qqtapplication.cpp")
include ($$PWD/qqt_install.pri)
#QQT_SDK_ROOT QQT_SDK_PWD QQT_LIB_PWD what?

#TARGET must be equals to pro name ? no, TARGET must be placeed before qqt_library.pri
#qmake pro pri is sequential
message(Link QQt to $${TARGET} $${QKIT_PRIVATE} \
    at $${QT_VERSION} $${SYSNAME} $${BUILD} \
    on $${QMAKE_HOST.os})


################################################
##link QQt logic function
################################################
defineReplace(link_qqt_library) {
    contains(DEFINES, __DARWIN__) {
        LINK += -F$${QQT_LIB_PWD}
        LINK += -framework QQt
    } else {
        LINK += -L$${QQT_LIB_PWD}
        #win can't with the blank! error: -l QQt
        LINK += -lQQt
    }
    return ($${LINK})
}

defineReplace(link_qqt_on_mac) {
    equals(QKIT_PRIVATE, macOS) {
        MODULE_NAME = QQt
        command = $$create_mac_sdk()

        post_link += rm -rf bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
        post_link += mkdir -p bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
        post_link += cd bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
        post_link += $${command} &&
        post_link += cd $${OUT_PWD} &&
        #Qt Creator create framework but use absolute path to make link
        #QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
        #        bin/$${TARGET}.app/Contents/Frameworks &&
        post_link += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
             @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
             bin/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
        post_link += macdeployqt bin/$${TARGET}.app -verbose=1
        message($$post_link)
        return ($$post_link)
    }
}


################################################
##link qqt work flow
################################################
contains(CONFIG, link_from_sdk) {
    QQT_LIB_PWD = $${QQT_SDK_ROOT}/$${QQT_STD_DIR}/lib
    message (Link QQt from: $$QQT_LIB_PWD)
    #create sdk first
    LIBS += $$link_qqt_library()
    QMAKE_PRE_LINK = $$create_qqt_sdk()
    QMAKE_POST_LINK += $$link_qqt_on_mac()
}
contains(CONFIG, link_from_build) {
    QQT_LIB_PWD = $${QQT_BUILD_ROOT}/$${QQT_STD_DIR}/src/bin
    message (Link QQt from: $$QQT_LIB_PWD)
    LIBS += $$link_qqt_library()
    QMAKE_POST_LINK = $$link_qqt_on_mac()
}


