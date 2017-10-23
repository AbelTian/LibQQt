#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------
TARGET = QQt
TEMPLATE = lib

#QQT LIBRARY (DLL)
#DEFINES += QQT_LIBRARY
DEFINES += QQT_LIBRARY

include ($$PWD/qqt_header.pri)
include ($$PWD/qqt_source.pri)

message (build $${TARGET} $${QKIT_} library)

equals(QKIT_, macOS) {
    CONFIG += dll
    CONFIG += lib_bundle
} else:equals(QKIT_, iOS) {
    #DEFINES -= QQT_LIBRARY
    CONFIG -= dll
    CONFIG -= lib_bundle
    CONFIG += staticlib
}
CONFIG += debug_and_release
CONFIG += build_all
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
############
##install
############
#CONFIG += can_install

can_install:equals(QKIT_, macOS) {
    ###if install product to same path,use this.
    target.path = /System/Library/Frameworks
    INSTALLS += target
}
