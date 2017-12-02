#-------------------------------------------------
#install app
#-------------------------------------------------
#CONFIG += can_install
can_install:equals(QKIT_PRIVATE, EMBEDDED) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    equals(QKIT_PRIVATE, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

############
##config defination
############
equals(QKIT_PRIVATE, macOS) {
    CONFIG += app_bundle
}

################################################################
##build cache
################################################################
OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
DESTDIR = bin

################################################################
##link QQt
################################################################
include($${PWD}/link_qqt_library.pri)

################################################################
##link Other library
################################################################

################################################################
##deploy app for install update deploy
################################################################
#optional
#if you have this request, include this pri in your app pro
#include($${PWD}/app_deploy.pri)

#-------------------------------------------------
##project environ print
#-------------------------------------------------
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})
