cmake_minimum_required(VERSION 2.8.12)

##tool chain file.cmake
#set(CMAKE_COMPILER_IS_GNUCXX TRUE)

# Skip the platform compiler checks for cross compiling
set (CMAKE_CXX_COMPILER_WORKS TRUE)
set (CMAKE_C_COMPILER_WORKS TRUE)

set( CMAKE_C_FLAGS "-g -Wall -O3 -m64" )
set( CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS}  )

#cmake cross build find_library to find in this directory
set(CMAKE_MACOSX_RPATH TRUE)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#Qt Tools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#others
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_VERBOSE_MAKEFILE OFF )
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#set ( CMAKE_TOOLCHAIN_FILE  ${CMAKE_SOURCE_DIR}/cmake/build.cmake )

project(App0OnQQt)
set( ${PROJECT_NAME}_VERSION_MAJOR 1)
set( ${PROJECT_NAME}_VERSION_MINOR 0)
set(QT5 TRUE)

add_definitions( -D__QT5__ -DUNICODE )
IF (WIN32)
    add_definitions( -D__WIN__ )
ELSEIF (APPLE)
    add_definitions( -D__DARWIN__ )
ELSEIF (UNIX)
    add_definitions( -D__LINUX__ )
ENDIF ()

add_subdirectory( src )
add_subdirectory( examples/qqtframe )
#add_subdirectory( examples/animationframe )
#add_subdirectory( examples/cmdwidget )
#add_subdirectory( examples/console )
#add_subdirectory( examples/ffmpegplayer )
#add_subdirectory( examples/ftpclient )
#add_subdirectory( examples/httpclient )
#add_subdirectory( examples/liveplayer )
#add_subdirectory( examples/webkit )

#set ( CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/../../b1-Product/a0-qqtbased/Application)

if(APPLE)
    set (CPACK_GENERATOR Bundle)
    set (CPACK_BUNDLE_NAME "QQtFrame")
    set (CPACK_BUNDLE_PLIST "info.plist")
    set (CPACK_BUNDLE_ICON "app.ico")
    INCLUDE (CPack)
endif(APPLE)

