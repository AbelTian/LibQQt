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
##in this section, I use QMAKE_PRE_LINK QMAKE_POST_LINK, it won't work until project source changed
##on windows, I use touch.exe, you need download it and put it in system dir.
################################################
#QMAKE_POST_LINK won't work until source changed
#qmake pro pri prf change won't effect to QMAKE_POST_LINK
#but I need it before I complete this pri.
#debug.
system("touch $${PWD}/frame/qqtapplication.cpp")
include ($$PWD/qqt_install.pri)
#QQT_SDK_ROOT QQT_SDK_PWD QQT_LIB_PWD

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

defineReplace(copy_qqt_on_mac) {
    #need QQT_BUILD_PWD
    create_command = $$create_mac_sdk()

    command += rm -rf bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += mkdir -p bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += cd bin/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += $${create_command} &&
    command += cd $${OUT_PWD} &&
    #Qt Creator create framework but use absolute path to make link
    #QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
    #        bin/$${TARGET}.app/Contents/Frameworks &&
    command += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         bin/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    command += macdeployqt bin/$${TARGET}.app -verbose=1
    message($$command)
    return ($$command)
}


################################################
##link qqt work flow
################################################
#-------module name QQt
MODULE_NAME=QQt
module_name = $$lower($${MODULE_NAME})

#-------define the all path
#create platform sdk need this
QQT_SRC_PWD=$${PWD}
#need use qqt subdir proj
QQT_BUILD_PWD=$${QQT_BUILD_ROOT}/$${QQT_STD_DIR}/$${QQT_DST_DIR}
#sdk path
QQT_SDK_PWD = $${QQT_SDK_ROOT}/$${QQT_STD_DIR}
#message(QQt sdk install here:$${QQT_SDK_PWD})

contains(CONFIG, link_from_sdk) {
    #create sdk first
    QMAKE_PRE_LINK = $$create_qqt_sdk()
    equals(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$copy_qqt_on_mac()
    }
    #private struct
    QQT_LIB_PWD = $${QQT_SDK_ROOT}/$${QQT_STD_DIR}/lib
}

contains(CONFIG, link_from_build) {
    equals(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$copy_qqt_on_mac()
    }
    QQT_LIB_PWD = $${QQT_BUILD_ROOT}/$${QQT_STD_DIR}/$${QQT_DST_DIR}
}

message (Link QQt from: $$QQT_LIB_PWD)
LIBS += $$link_qqt_library()

