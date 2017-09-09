cmake_minimum_required(VERSION 2.8.12)

set ( 
CMAKE_TOOLCHAIN_FILE  
${CMAKE_SOURCE_DIR}/toolchains/build.cmake 
)

project(App0OnQQt)
set( ${PROJECT_NAME}_VERSION_MAJOR 0)
set( ${PROJECT_NAME}_VERSION_MINOR 1)

add_definitions(
  -D__QT5__
  -D__WIN__
  -DUNICODE
  -DQT_DEFINITIONS
)

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

set ( 
CMAKE_INSTALL_PREFIX
${CMAKE_SOURCE_DIR}/../temp
)