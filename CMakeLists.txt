cmake_minimum_required(VERSION 2.8.12)

set (CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/extra/toolchain-mingw32.cmake 
	CACHE FILEPATH "" FORCE)

set( CMAKE_INCLUDE_CURRENT_DIR ON)
set( CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
set( BUILD_SHARED_LIBS ON)
SET( CMAKE_VERBOSE_MAKEFILE ON )
SET( CMAKE_BUILD_TYPE Debug|Release)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_definitions(
  -D__QT5__
  -D__WIN__
  -DUNICODE
  -DQT_DEFINITIONS
)


project(App0OnQQt)
set( ${PROJECT_NAME}_VERSION_MAJOR 0)
set( ${PROJECT_NAME}_VERSION_MINOR 1)


add_subdirectory( src )
#add_subdirectory( examples/qqtframe )
#add_subdirectory( examples/animationframe )
#add_subdirectory( examples/cmdwidget )
#add_subdirectory( examples/console )
#add_subdirectory( examples/ffmpegplayer )
#add_subdirectory( examples/ftpclient )
#add_subdirectory( examples/httpclient )
#add_subdirectory( examples/liveplayer )
add_subdirectory( examples/webkit )


set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../../b1-Product/a0-qqtbased/linux/install/Application)
