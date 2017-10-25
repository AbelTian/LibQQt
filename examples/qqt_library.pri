#here is all your app common defination and configration
#change these path on your computer
message(Link QQt to $${TARGET} $${QKIT_} \
    at $${QT_VERSION} $${SYSNAME} $${BUILD} \
    on $${QMAKE_HOST.os})

equals(QMAKE_HOST.os, Darwin) {
    BUILDROOT = /Users/abel/Develop/c0-buildstation
} else: equals(QMAKE_HOST.os, Linux) {
    BUILDROOT = /home/abel/Develop/c0-buildstation
} else: equals(QMAKE_HOST.os, Windows) {
    BUILDROOT = C:/Users/Administrator/Develop/c0-build
}

QQT_OUT_PWD = QQt/$${QT_VERSION}/$${SYSNAME}/$${BUILD}/src
QQT_OUT_BIN = $${QQT_OUT_PWD}/$${DESTDIR}
QQT_LIB_PWD = $$BUILDROOT/$$QQT_OUT_BIN
message (QQt Build: $$QQT_LIB_PWD)

contains(DEFINES, __DARWIN__) {
    lessThan(QT_MAJOR_VERSION, 5):{
        LIBS += -L$${QQT_LIB_PWD}
        LIBS += -l QQt
    } else {
        LIBS += -F$${QQT_LIB_PWD}
        LIBS += -framework QQt
    }
} else {
    LIBS += -L$${QQT_LIB_PWD}
    LIBS += -l QQt
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
