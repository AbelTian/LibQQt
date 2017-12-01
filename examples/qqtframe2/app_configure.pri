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

contains(QKIT_PRIVATE, ANDROID|ANDROIDX86) {
    CONFIG += mobility
    MOBILITY =
    DISTFILES += \
        android/AndroidManifest.xml

    ANDROID_PACKAGE_SOURCE_DIR = $${PWD}/android
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
include(../../src/link_qqt_library.pri)

################################################################
##link Other library
################################################################

#-------------------------------------------------
##project environ print
#-------------------------------------------------
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})
