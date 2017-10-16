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


include ($$PWD/qqt.pri)

equals(QT_KIT, macOS) {
    message (build $${TARGET} $${QT_KIT} bundle)
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
