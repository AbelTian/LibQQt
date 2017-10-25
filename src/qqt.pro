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
#CONFIG += debug_and_release
#CONFIG += build_all

#################################################################
##project version
#################################################################
TARGET_MAJOR_VERSION = 1
TARGET_MINOR_VERSION = 3
TARGET_PATCH_VERSION = 0
TARGET_BUILD_VERSION = 0
TARGET_VERSION = $${TARGET_MAJOR_VERSION}.$${TARGET_MINOR_VERSION}.$${TARGET_PATCH_VERSION}
TARGET_VERSION4 = $${TARGET_MAJOR_VERSION}.$${TARGET_MINOR_VERSION}.$${TARGET_PATCH_VERSION}.$${TARGET_BUILD_VERSION}
unix:VERSION = $${TARGET_VERSION}
#bug?:open this macro, TARGET will suffixed with major version.
#win32:VERSION = $${TARGET_VERSION4}

QMAKE_TARGET_FILE = "$${TARGET}"
QMAKE_TARGET_PRODUCT = "$${TARGET}"
QMAKE_TARGET_COMPANY = "www.qqt.com"
QMAKE_TARGET_DESCRIPTION = "QQt Foundation Class"
QMAKE_TARGET_COPYRIGHT = "Copyright 2015-2020 QQT Co., Ltd. All rights reserved"

win32 {
    #common to use upload, this can be ignored.
    #RC_FILE += qqt.rc
    #RC_ICONS=
    RC_LANG=0x0004
    RC_CODEPAGE=
}

#################################################################
##project environ
#################################################################
#default
greaterThan(QT_MAJOR_VERSION, 4): {
    for (cc, CONFIG) {
        message($${TARGET} configed $${cc})
    }
    for (cc, DEFINES) {
        message($${TARGET} defined $${cc})
    }
} else {
    message ($${TARGET} configed $${CONFIG})
    message ($${TARGET} defined $${DEFINES})
}

#################################################################
##project source
#################################################################
include ($$PWD/qqt_header.pri)
include ($$PWD/qqt_source.pri)


################################################
##install
################################################
#CONFIG += can_install
can_install:equals(QKIT_, macOS) {
    ###if install product to same path,use this.
    target.path = /System/Library/Frameworks
    INSTALLS += target
}

################################################
##project resource
################################################
RESOURCES += \
    qqt.qrc
