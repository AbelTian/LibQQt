message(Link QQt to $${TARGET} $${QKIT_} from $${SYSNAME} $${BUILD} on $${QMAKE_HOST.os})
equals(QMAKE_HOST.os, Darwin) {
    equals(QKIT_, macOS) {
        LIBS += -F/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
        LIBS += -framework QQt
    } else: equals(QKIT_, Android) {
        LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
        LIBS += -lQQt
    } else: equals(QKIT_, ANDROIDX86) {
        LIBS += -L/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
        LIBS += -lQQt
    }
} else: equals(QMAKE_HOST.os, Linux) {
    LIBS += -L/home/abel/Develop/c0-buildstation/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
    LIBS += -lQQt
} else: equals(QMAKE_HOST.os, Windows) {
    LIBS += -LC:/Users/Administrator/Develop/c0-build/a0-qqtfoundation/$${SYSNAME}/$${BUILD}/src/bin
    LIBS += -lQQt
}

############
##install
############
#CONFIG += can_install
can_install:equals(QKIT_, EMBEDDED) {
    target.path = /Application
    INSTALLS += target
} else: unix {
    equals(QKIT_, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

equals(QKIT_, macOS) {
    CONFIG += app_bundle
}
equals(QKIT_, Android) {
    CONFIG += mobility
    MOBILITY =
    #DISTFILES += \
    #    android/AndroidManifest.xml

    #ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}
