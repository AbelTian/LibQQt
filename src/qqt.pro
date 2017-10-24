#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
#default
greaterThan(QT_MAJOR_VERSION, 4): {
    for (cc, $$CONFIG) {
        message($${TARGET} configed $${cc})
    }
    for (cc, $$DEFINES) {
        message($${TARGET} defined $${cc})
    }
} else {
    message ($${TARGET} configed $${CONFIG})
    message ($${TARGET} defined $${DEFINES})
}

TARGET = QQt
TEMPLATE = lib

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
win32:VERSION = $${TARGET_VERSION4}

QMAKE_TARGET_PRODUCT = "$${TARGET}"
QMAKE_TARGET_COMPANY = "www.qqt.com"
QMAKE_TARGET_DESCRIPTION = "QQt Foundation Class"
QMAKE_TARGET_COPYRIGHT = "Copyright 2015-2020 QQT Co., Ltd. All rights reserved"

win32 {
    #RC_FILE += qrc://qqt.rc
    #RC_ICONS=
    RC_LANG=0x0004
    RC_CODEPAGE=
}

#QQT LIBRARY (DLL)
#DEFINES += QQT_LIBRARY
DEFINES += QQT_LIBRARY

include ($$PWD/qqt_header.pri)
include ($$PWD/qqt_source.pri)

equals(QKIT_, macOS) {
    CONFIG += dll
    CONFIG += lib_bundle
} else:equals(QKIT_, iOS) {
    #DEFINES -= QQT_LIBRARY
    CONFIG -= dll
    CONFIG -= lib_bundle
    CONFIG += staticlib
}
#CONFIG += debug_and_release
#CONFIG += build_all


############
##install
############
#CONFIG += can_install
can_install:equals(QKIT_, macOS) {
    ###if install product to same path,use this.
    target.path = /System/Library/Frameworks
    INSTALLS += target
}

RESOURCES += \
    qqt.qrc
