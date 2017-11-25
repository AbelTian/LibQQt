include(../../examples/qqtframe2/link_qqt_library.pri)

############
##install
############
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

equals(QKIT_PRIVATE, ANDROID) {
    CONFIG += mobility
    MOBILITY =
}

#################################################################
##project environ
#################################################################
#default
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})

TEMPLATE = app
INCLUDEPATH += .
CONFIG += console

# Input
HEADERS += easter.h
SOURCES += main.cpp easter.cpp
