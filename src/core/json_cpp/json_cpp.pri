JSONCPPROOT=$$PWD/jsoncpp

#DEFINES += JSON_DLL_BUILD JSON_DLL
QMAKE_CXXFLAGS += -std=c++11
android:DEFINES += JSONCPP_NO_LOCALE_SUPPORT

INCLUDEPATH += $${JSONCPPROOT}/include

HEADERS += \
        $${JSONCPPROOT}/include/json/allocator.h \
        $${JSONCPPROOT}/include/json/assertions.h \
        $${JSONCPPROOT}/include/json/config.h \
        $${JSONCPPROOT}/include/json/forwards.h \
        $${JSONCPPROOT}/include/json/json_features.h \
        $${JSONCPPROOT}/include/json/json.h \
        $${JSONCPPROOT}/include/json/reader.h \
        $${JSONCPPROOT}/include/json/value.h \
        $${JSONCPPROOT}/include/json/version.h \
        $${JSONCPPROOT}/include/json/writer.h

SOURCES += \
        $${JSONCPPROOT}/src/lib_json/json_reader.cpp \
        $${JSONCPPROOT}/src/lib_json/json_tool.h \
        $${JSONCPPROOT}/src/lib_json/json_value.cpp \
        $${JSONCPPROOT}/src/lib_json/json_valueiterator.inl \
        $${JSONCPPROOT}/src/lib_json/json_writer.cpp

use_custom_writer {
    #INCLUDEPATH += $$PWD
    #add_file($$PWD/json_mod_writer.cpp)
    #add_file($$PWD/json_mod_writer.h)
    #HEADERS += $$PWD/json_mod_writer.h
    #SOURCES += $$PWD/json_mod_writer.cpp
}
