
CONFIG                 += debug_and_release
CONFIG                 += qt
CONFIG                 += warn_on
CONFIG                 += thread


OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
#user directory
DESTDIR = bin

DEPENDPATH               += $$PWD
INCLUDEPATH              += $$PWD
HEADERS                 += $$PWD/qextserialbase.h \
                          $$PWD/qextserialport.h \
                          $$PWD/qextserialenumerator.h
SOURCES                 += $$PWD/qextserialbase.cpp \
                          $$PWD/qextserialport.cpp \
                          $$PWD/qextserialenumerator.cpp

unix:HEADERS           += $$PWD/posix_qextserialport.h
unix:SOURCES           += $$PWD/posix_qextserialport.cpp
unix:DEFINES           += _TTY_POSIX_


win32:HEADERS          += $$PWD/win_qextserialport.h
win32:SOURCES          += $$PWD/win_qextserialport.cpp
win32:DEFINES          += _TTY_WIN_
win32:LIBS             += -lsetupapi

