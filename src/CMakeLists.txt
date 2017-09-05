include (${CMAKE_SOURCE_DIR}/cmake/function.cmake)

set ( SUBLIBRARY_NAME QQt)

##SOURCES
file(GLOB_RECURSE SOURCES "*.cpp")
msglist("${SOURCES}")

if(UNIX)
	file(GLOB_RECURSE DMMUSOURCES "dmmu/*.c")
	set(SOURCE ${SOURCES} ${DMMUSOURCES})
endif(UNIX)

if(NOT UNIX)
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
	customplot gui widgets frame
	pluginwatcher printsupport )

add_library(${SUBLIBRARY_NAME} ${SOURCES})
SET_TARGET_PROPERTIES(${SUBLIBRARY_NAME} PROPERTIES OUTPUT_NAME ${SUBLIBRARY_NAME})
GET_TARGET_PROPERTY(OUTPUT_VALUE ${SUBLIBRARY_NAME} OUTPUT_NAME)
MESSAGE(STATUS "${OUTPUT_VALUE} ${CMAKE_SHARED_LIBS}")

SET_TARGET_PROPERTIES(${SUBLIBRARY_NAME} PROPERTIES VERSION 1.2 SOVERSION 1)

set(Qt5Libs Core Widgets Gui Xml Sql Network PrintSupport SerialPort)
foreach(loop_var ${Qt5Libs})
    #message(Qt5${loop_var})
    find_package(Qt5${loop_var})
    target_link_libraries(${SUBLIBRARY_NAME} Qt5::${loop_var})
endforeach(loop_var)

install(TARGETS ${SUBLIBRARY_NAME} 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install ( FILES ${MOC_HEADERS}
	DESTINATION include
)
