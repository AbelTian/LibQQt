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

message (build $${TARGET} $${QT_KIT} library)

equals(QT_KIT, macOS) {
    CONFIG += dll
    CONFIG += lib_bundle
}

############
##install
############
#CONFIG += can_install

can_install:equals(QT_KIT, macOS) {
    ###if install product to same path,use this.
    target.path = /System/Library/Frameworks
    INSTALLS += target
}
