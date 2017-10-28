#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
#################################################################
##project name
#################################################################
TARGET = QQt
TEMPLATE = lib

##default build dll but some occasion
CONFIG += dll
#QQt library export (DLL) static lib is not needed
DEFINES += QQT_LIBRARY
##special lib lib_bundle/staticlib
equals(QKIT_, macOS) {
    CONFIG += lib_bundle
} else:equals(QKIT_, iOS) {
    DEFINES -= QQT_LIBRARY
    CONFIG -= dll
    CONFIG += staticlib
} else:equals(QKIT_, WIN) {
    #when Qt is static by mingw32 building 5.9.1
    equals(QT_VERSION, 5.9.1){
        DEFINES -= QQT_LIBRARY
        CONFIG -= dll
        CONFIG += staticlib
    }
}
#create prl
CONFIG += create_prl
CONFIG += build_pass
build_pass:CONFIG(debug, debug|release) {
    #troublesome
    #win32: TARGET = $$join(TARGET,,,d)
}
#CONFIG += debug_and_release
#CONFIG += build_all

#################################################################
##project version
#################################################################
TARGET_MAJOR_VERSION = 1
TARGET_MINOR_VERSION = 5
TARGET_PATCH_VERSION = 0
TARGET_BUILD_VERSION = 0
TARGET_VERSION = $${TARGET_MAJOR_VERSION}.$${TARGET_MINOR_VERSION}.$${TARGET_PATCH_VERSION}
TARGET_VERSION4 = $${TARGET_MAJOR_VERSION}.$${TARGET_MINOR_VERSION}.$${TARGET_PATCH_VERSION}.$${TARGET_BUILD_VERSION}
unix:VERSION = $${TARGET_VERSION}
#bug?:open this macro, TARGET will suffixed with major version.
#win32:VERSION = $${TARGET_VERSION4}
message (QQt version: $$VERSION)
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


#################################################################
##project source
#################################################################
include ($$PWD/qqt_header.pri)
include ($$PWD/qqt_source.pri)

################################################
##install to Qt library
################################################
#if you want to use QQt with QT += QQtCore please open this feature
include ($$PWD/qqt_install.pri)

################################################
##project resource
################################################
RESOURCES += \
    qqt.qrc

#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})
