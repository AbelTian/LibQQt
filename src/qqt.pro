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

################################################
##project config definition
##need QKIT to compitible with some occasion
################################################
##default build dll but some occasion
CONFIG += dll
#QQt library export (DLL) static lib is not needed
DEFINES += QQT_LIBRARY
##special lib lib_bundle/staticlib
QKIT_PRIVATE = $$(QKIT)
equals(QKIT_PRIVATE, macOS) {
    CONFIG += lib_bundle
} else:equals(QKIT_PRIVATE, iOS) {
    DEFINES -= QQT_LIBRARY
    CONFIG -= dll
    CONFIG += staticlib
} else:equals(QKIT_PRIVATE, WIN) {
    #when Qt is static by mingw32 building 5.9.1
    equals(QT_VERSION, 5.9.1){
        DEFINES -= QQT_LIBRARY
        CONFIG -= dll
        CONFIG += staticlib
    }
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
include ($$PWD/qqt_install.pri)


#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})
