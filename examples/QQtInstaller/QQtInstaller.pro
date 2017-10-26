#-------------------------------------------------
#
# Project created by QtCreator 2017-10-27T00:14:05
#
#-------------------------------------------------
#include QQt's header (add QQt header to includepath)
include(../../src/qqt_header.pri)

#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    #include(../../src/qqt.pri)
} else {
    #if you want to link QQt library
    include(../qqt_library.pri)
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQtInstaller
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui



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
