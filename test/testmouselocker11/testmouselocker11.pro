#-------------------------------------------------
#
# Project created by QtCreator 2018-10-06T08:16:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testmouselocker11
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
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

include($${PWD}/../../multi-link/add_base_manager.pri)

#-------------------------------------------------
#用户工程配置
#-------------------------------------------------
add_version(1,0,0,0)
add_deploy()
add_dependent_manager(QQt)
system(touch main.cpp)

add_file(mainwidget.h)
add_file(mainwidget.cpp)
HEADERS += \
    mainwidget.h
SOURCES += \
    mainwidget.cpp

add_file(qqtframemouselocker.h)
add_file(qqtframemouselocker.cpp)
HEADERS += \
    qqtframemouselocker.h
SOURCES += \
    qqtframemouselocker.cpp

add_file(qqtmouselocker.h)
add_file(qqtmouselocker.cpp)
add_file(qqtmouselocker_p.h)
add_file(qqtmouselocker_p.cpp)
add_file(qqtmouselocker_win.h)
add_file(qqtmouselocker_win.cpp)
add_file(qqtmouselocker_mac.h)
add_file(qqtmouselocker_mac.cpp)
add_file(qqtmouselocker_x11.h)
add_file(qqtmouselocker_x11.cpp)
add_file(qqtmouselocker_other.h)
add_file(qqtmouselocker_other.cpp)

HEADERS += \
    qqtmouselocker.h \
    qqtmouselocker_p.h
SOURCES += \
    qqtmouselocker.cpp \
    qqtmouselocker_p.cpp

win32:!cross_compile {
    HEADERS += \
        qqtmouselocker_win.h
    SOURCES += \
        qqtmouselocker_win.cpp
} else:mac:!cross_compile {
    HEADERS += \
        qqtmouselocker_mac.h
    SOURCES += \
        qqtmouselocker_mac.cpp
} else:linux:!cross_compile {
    LIBS += -lX11
    QT += x11extras
    HEADERS += \
        qqtmouselocker_x11.h
    SOURCES += \
        qqtmouselocker_x11.cpp
} else {
    HEADERS += \
        qqtmouselocker_other.h
    SOURCES += \
        qqtmouselocker_other.cpp
}

#add_file(qqtframebodymovehelper.h)
#add_file(qqtframebodymovehelper.cpp)

#-------------------------------------------------
#用户工程配置
#-------------------------------------------------
#嵌入式上不支持这个东西
QT-=opengl

equals(QSYS_PRIVATE, macOS) {
    CONFIG += app_bundle
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
    LIBS += -framework DiskArbitration -framework Cocoa -framework IOKit -framework CoreGraphics
}

contains(QSYS_PRIVATE, Android|AndroidX86) {
    CONFIG += mobility
    MOBILITY =
    DISTFILES += \
        android/AndroidManifest.xml

    ANDROID_PACKAGE_SOURCE_DIR = $${PWD}/android
}

message ($${TARGET} Qt $${QT})
message ($${TARGET} config $${CONFIG})
message ($${TARGET} DEFINE $${DEFINES})
message ($${TARGET} prelink $${QMAKE_PRE_LINK})
message ($${TARGET} postlink $${QMAKE_POST_LINK})
