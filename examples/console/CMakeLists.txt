##SOURCES

set(SUBPROJECT_NAME qqtconsole)

file(GLOB SOURCES "*.cpp")
add_executable(${SUBPROJECT_NAME} ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${SUBPROJECT_NAME} QQt)

##BUILDING
#load qt5 librariess
set(Qt5Libs Core )
foreach(loop_var ${Qt5Libs})
    #message(Qt5${loop_var})
    find_package(Qt5${loop_var})
    target_link_libraries(${SUBPROJECT_NAME} Qt5::${loop_var})
endforeach(loop_var)

install( TARGETS ${SUBPROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
