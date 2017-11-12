#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
#Project link: https://gitee.com/drabel/LibQt
#if you succeed with LibQQt, please thumb up.
#2017年11月10日18:53:56

#################################################################
##Usage
#################################################################
#please dont use Qt 5.9.1, it is broken with android and ios.

#################################################################
##project name
#################################################################
TARGET = QQt
TEMPLATE = lib

################################################
##project config definition
##need QKIT to compitible with some occasion
################################################
include ($$PWD/qqt_kit.pri)

##different target:
##win link qqt dll + ..
##win link qqt static + QQT_STATIC_LIBRARY
##win build qqt dll + QQT_LIBRARY
##win build qqt lib + QQT_STATIC_LIBRARY
##*nix build and link qqt dll or lib + ..
##some target, special lib lib_bundle/staticlib
equals(QKIT_PRIVATE, WIN32) {
    #when Qt is static by mingw32 building 5.9.1
    equals(QT_VERSION, 5.9.1){
        CONFIG += staticlib
        DEFINES += QQT_STATIC_LIBRARY
    } else {
        CONFIG += dll
        DEFINES += QQT_LIBRARY
    }
} else:equals(QKIT_PRIVATE, macOS) {
    CONFIG += dll
    CONFIG += lib_bundle
} else:equals(QKIT_PRIVATE, iOS) {
    CONFIG += staticlib
} else {
    ##default build dll
    CONFIG += dll
    #*nix no need this macro
    #DEFINES += QQT_LIBRARY
}
#create prl
CONFIG += create_prl
#CONFIG += build_pass
build_pass:CONFIG(debug, debug|release) {
    #troublesome
    #win32: TARGET = $$join(TARGET,,,d)
}
#CONFIG += debug_and_release
#CONFIG += build_all
#if some bug occured, maybe this help me, close some warning
CLFLAGS = -Wno-unused-parameter -Wno-reorder -Wno-c++11-extensions -Wno-c++11-long-long
QMAKE_CFLAGS +=  $${CLFLAGS}
QMAKE_CXXFLAGS +=  $${CLFLAGS}
#debug.
#QMAKE_POST_LINK won't work until source changed
#qmake pro pri prf change won't effect to QMAKE_POST_LINK
#but I need it before I complete this pri.
system("touch $${PWD}/widgets/qqtapplication.cpp")
#################################################################
##project Headers
#################################################################
include ($$PWD/qqt_header.pri)

#################################################################
##project source
#################################################################
include ($$PWD/qqt_source.pri)

#################################################################
##project version
#################################################################
include ($$PWD/qqt_version.pri)
unix:VERSION = $${QQT_VERSION}
#bug?:open this macro, TARGET will suffixed with major version.
#win32:VERSION = $${QQT_VERSION4}

QMAKE_TARGET_FILE = "$${TARGET}"
QMAKE_TARGET_PRODUCT = "$${TARGET}"
QMAKE_TARGET_COMPANY = "www.qqt.com"
QMAKE_TARGET_DESCRIPTION = "QQt Foundation Class"
QMAKE_TARGET_COPYRIGHT = "Copyright 2015-2020 QQT Co., Ltd. All rights reserved"

win32 {
    #common to use upload, this can be ignored.
    #open this can support cmake config.h.in
    #configure_file(qqtversion.h.in, qqtversion.h) control version via cmake.
    #qmake version config and cmake version config is conflicted
    #RC_FILE += qqt.rc
    #RC_ICONS=
    RC_LANG=0x0004
    RC_CODEPAGE=
}




################################################
##project resource
################################################
RESOURCES += \
    qqt.qrc


################################################
##install to Qt library
##in this section, I use QMAKE_POST_LINK, it won't work until project source changed
################################################
!contains(QKIT_PRIVATE, WIN32|WIN64) {
    CONFIG += qqt_create_sdk
}
include ($$PWD/qqt_install.pri)


#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})

