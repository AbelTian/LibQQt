##SOURCES

set(SUBPROJECT_NAME webkit)

file(GLOB SOURCES "*.cpp")
add_executable(${SUBPROJECT_NAME} ${SOURCES})

include_directories( 
	${PROJECT_SOURCE_DIR}/src 
	${PROJECT_SOURCE_DIR}/src/core 
	${PROJECT_SOURCE_DIR}/src/sql 
	${PROJECT_SOURCE_DIR}/src/network 
	${PROJECT_SOURCE_DIR}/src/qcustomplot
	${PROJECT_SOURCE_DIR}/src/gui 
	${PROJECT_SOURCE_DIR}/src/widgets 
	${PROJECT_SOURCE_DIR}/src/frame
	${PROJECT_SOURCE_DIR}/src/pluginwatcher 
	${PROJECT_SOURCE_DIR}/src/printsupport 
)

target_link_libraries(${SUBPROJECT_NAME} QQt)

#set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "Z:/abel/Develop/b0-toolskits/a1-QQtToolsKits-Windows/QtLibrary/4.8.7/mingw482_32")
#set(QT_QMAKE_EXECUTABLE "Z:/abel/Develop/b0-toolskits/a1-QQtToolsKits-Windows/QtLibrary/4.8.7/mingw482_32/bin/qmake.exe")
#set(CMAKE_FIND_ROOT_PATH "Z:/abel/Develop/b0-toolskits/a1-QQtToolsKits-Windows/QtLibrary/4.8.7/mingw482_32" )

include_directories(
	"Z:/abel/Develop/b0-toolskits/a1-QQtToolsKits-Windows/QtLibrary/4.8.7/mingw482_32/include"
)
link_directories(
	"Z:/abel/Develop/b0-toolskits/a1-QQtToolsKits-Windows/QtLibrary/4.8.7/mingw482_32/lib"
)
target_link_libraries(${SUBPROJECT_NAME} QtCore4 QtGui4 QtWebkit4)

##BUILDING
#load qt5 libraries
set(Qt5Libs Core Widgets Gui Xml Sql Network)
foreach(loop_var ${Qt5Libs})
    #message(Qt5${loop_var})
	#find_package(Qt5${loop_var})
    #target_link_libraries(${SUBPROJECT_NAME} Qt5::${loop_var})
endforeach(loop_var)

install( TARGETS ${SUBPROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
