#-------------------------------------------------
#
# Project created by QtCreator 2018-05-19T23:32:58
#
#-------------------------------------------------

QT       -= gui

TARGET = QQtBasedLibTest
TEMPLATE = lib

DEFINES += QQTBASEDLIBTEST_LIBRARY

#if defined(QQTBASEDLIBTEST_LIBRARY)
#  define QQTBASEDLIBTESTSHARED_EXPORT Q_DECL_EXPORT
#elif defined (QQTBASEDLIBTEST_STATIC_LIBRARY)
#define QQTBASEDLIBTESTSHARED_EXPORT
#else
#  define QQTBASEDLIBTESTSHARED_EXPORT Q_DECL_IMPORT
#endif

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
        qqtbasedlibtest.cpp

HEADERS += \
        qqtbasedlibtest.h \
        qqtbasedlibtest_global.h 

unix {
    #target.path = /usr/lib
    #INSTALLS += target
}

system(touch qqtbasedlibtest.cpp)
include (../../lib/lib_base_manager.pri)
