include (${CMAKE_SOURCE_DIR}/cmake/function.cmake)

set ( SUBLIBRARY_NAME QQt)

#文件版本
set( VER_FILEVERSION             1,0,0,0   )
set( VER_FILEVERSION_STR         "1.0.0.0" )

#产品版本
set( VER_PRODUCTVERSION          1.0 )
set( VER_PRODUCTVERSION_MAJOR          1 )
set( VER_PRODUCTVERSION_STR      "1.0"   )
set( VER_PRODUCTVERSION_MAJOR_STR      "1"   )

#产品名称
set( VER_PRODUCTNAME_STR         "QQT"  )
set( VER_ORIGINALFILENAME_STR    "QQT"  )
set( VER_INTERNALNAME_STR        "QQT"   )
set( VER_COMPANYNAME_STR         "QQT"   )
set( VER_COMPANYDOMAIN_STR       "www.qqt.com" )
#文件说明
set( VER_FILEDESCRIPTION_STR     "QQT"   )
#版权
set( VER_LEGALCOPYRIGHT_STR      "Copyright 2007-2017 QQT Co., Ltd."  )
set( VER_LEGALTRADEMARKS1_STR    "All rights reserved" )
set( VER_LEGALTRADEMARKS2_STR    ${VER_LEGALTRADEMARKS1_STR} )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/qqtversion.h.in ${CMAKE_CURRENT_SOURCE_DIR}/core/qqtversion.h)

##SOURCES
file(GLOB_RECURSE SOURCES "*.cpp")
msglist("${SOURCES}")

if(UNIX)
	file(GLOB_RECURSE DMMUSOURCES "dmmu/*.c")
	set(SOURCE ${SOURCES} ${DMMUSOURCES})
endif(UNIX)

if(APPLE OR WIN32 OR WINCE)
	file(GLOB FILTER "network/qqtethenetmanager.cpp")
	set(FILTERS ${FILTERS} ${FILTER})
	file(GLOB FILTER "frame/qqtpreviewwidget.cpp")
	set(FILTERS ${FILTERS} ${FILTER})
	file(GLOB FILTER "frame/qqtwifiwidget.cpp")
	set(FILTERS ${FILTERS} ${FILTER})
	msglist("${FILTERS}")
	filter_out("${FILTERS}" "${SOURCES}" SOURCES )
endif()

file(GLOB FILTERS "pluginwatcher/qdevicewatcher_*.cpp")
msglist("${FILTERS}")
filter_out("${FILTERS}" "${SOURCES}" SOURCES )
if(WIN32)
	set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/pluginwatcher/qdevicewatcher_win32.cpp)
elseif(APPLE)
	set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/pluginwatcher/qdevicewatcher_mac.cpp)
elseif(WINCE)
	set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/pluginwatcher/qdevicewatcher_wince.cpp)
elseif(UNIX)
	set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/pluginwatcher/qdevicewatcher_linux.cpp)
endif(WIN32)

#内部编译 解决头文件发现不了的问题
include_directories( core sql network
	qcustomplot gui widgets frame
	pluginwatcher printsupport )

add_library(${SUBLIBRARY_NAME} ${SOURCES})
SET_TARGET_PROPERTIES(${SUBLIBRARY_NAME} PROPERTIES OUTPUT_NAME ${SUBLIBRARY_NAME})
GET_TARGET_PROPERTY(OUTPUT_VALUE ${SUBLIBRARY_NAME} OUTPUT_NAME)
MESSAGE(STATUS "${OUTPUT_VALUE} ${CMAKE_SHARED_LIBS}")

SET_TARGET_PROPERTIES(${SUBLIBRARY_NAME} PROPERTIES VERSION ${VER_PRODUCTVERSION} SOVERSION ${VER_PRODUCTVERSION_MAJOR})

link_qt_libraries(${SUBLIBRARY_NAME})

if(APPLE)
    link_framework(${SUBLIBRARY_NAME})
    set_target_properties(${SUBLIBRARY_NAME} PROPERTIES AUTOMOC_MOC_OPTIONS "-DQ_OS_MAC")
    # qmake will do this automatically
    set_target_properties(${SUBLIBRARY_NAME} PROPERTIES COMPILE_FLAGS "-mmacosx-version-min=10.10")
endif()



install(TARGETS ${SUBLIBRARY_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install ( FILES ${MOC_HEADERS}
    DESTINATION include
)
