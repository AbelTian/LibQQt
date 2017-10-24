#here is all your app common defination and configration
#change these path on your computer
message(Link QQt to $${TARGET} $${QKIT_} at $${QT_VERSION} $${SYSNAME} $${BUILD} on $${QMAKE_HOST.os})
equals(QMAKE_HOST.os, Darwin) {
    LIBS += -F/Users/abel/Develop/c0-buildstation/a0-qqtfoundation/$${QT_VERSION}/$${SYSNAME}/$${BUILD}/src/bin
    contains(DEFINES, __DARWIN__) {
        LIBS += -framework QQt
    } else: contains(DEFINES, __IOS__) {
        LIBS += -framework QQt
    } else{
        LIBS += -lQQt
    }
} else: equals(QMAKE_HOST.os, Linux) {
    LIBS += -L/home/abel/Develop/c0-buildstation/a0-qqtfoundation/$${QT_VERSION}/$${SYSNAME}/$${BUILD}/src/bin
    LIBS += -lQQt
} else: equals(QMAKE_HOST.os, Windows) {
    LIBS += -LC:/Users/Administrator/Develop/c0-build/a0-qqtfoundation/$${QT_VERSION}/$${SYSNAME}/$${BUILD}/src/bin
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

############
##config defination
############
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

#equals(QKIT_, macOS) {
#    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
#    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
#    msgpacklib.path = Contents/Frameworks
#    msgpacklib.files = ../myapp/3rd/msgpack-0.5.4/src/.libs/libmsgpack.3.dylib
#    evlib.path = Contents/Frameworks
#    evlib.files = ../myapp/3rd/libev-4.11/.libs/libev.4.dylib
#    QMAKE_BUNDLE_DATA += msgpacklib evlib
#    QMAKE_POST_LINK = install_name_tool -change /usr/local/lib/libmsgpack.3.dylib \
#         @executable_path/../Frameworks/libmsgpack.3.dylib \
#         myapp.app/Contents/MacOs/myapp & \
#         install_name_tool -change /usr/local/lib/libev.4.dylib \
#         @executable_path/../Frameworks/libev.4.dylib \
#         myapp.app/Contents/MacOs/myapp
#}
