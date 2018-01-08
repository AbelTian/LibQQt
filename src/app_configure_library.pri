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
include($${PWD}/app_link_qqt_library.pri)

################################################################
##link Other library
################################################################

################################################################
##config defination
################################################################
equals(QKIT_PRIVATE, macOS) {
    CONFIG += app_bundle
}

#-------------------------------------------------
#install app
#-------------------------------------------------
contains(QKIT_PRIVATE, EMBEDDED||MIPS32||ARM32) {
    target.path = /Application
    INSTALLS += target
}

#CONFIG += can_install
can_install: unix {
    equals(QKIT_PRIVATE, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

#-------------------------------------------------
##project environ print
#-------------------------------------------------
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})


