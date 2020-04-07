CONFIG *= qt
QT *= core

INCLUDEPATH += $$PWD $$PWD/include

SOURCES += \
    $$PWD/sources/writer.cpp \
    $$PWD/sources/variantdata.cpp \
    $$PWD/sources/stringdata.cpp \
    $$PWD/sources/reader.cpp \
    $$PWD/sources/contentiterator.cpp

HEADERS += \
    $$PWD/include/qtcsv/qtcsv_global.h \
    $$PWD/include/qtcsv/writer.h \
    $$PWD/include/qtcsv/variantdata.h \
    $$PWD/include/qtcsv/stringdata.h \
    $$PWD/include/qtcsv/reader.h \
    $$PWD/include/qtcsv/abstractdata.h \
    $$PWD/sources/filechecker.h \
    $$PWD/sources/contentiterator.h \
    $$PWD/sources/symbols.h
