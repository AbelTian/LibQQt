##SOURCES
include (${CMAKE_SOURCE_DIR}/cmake/function.cmake)

set(SUBPROJECT_NAME qqtframe)

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

##BUILDING
#load qt5 librariess
link_qt_libraries(${SUBPROJECT_NAME})

install( TARGETS ${SUBPROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
