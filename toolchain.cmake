#compiler
set( 
CMAKE_C_COMPILER 
"C:/Users/Administrator/Qt/Tools/mingw530_32/bin/gcc.exe" 
)
set( 
CMAKE_CXX_COMPILER 
"C:/Users/Administrator/Qt/Tools/mingw530_32/bin/g++.exe" 
)
set(
CMAKE_RC_COMPILER
"C:/Users/Administrator/Qt/Tools/mingw530_32/bin/windres.exe"
)

set (
	ENV{PATH}
	"C:/Users/Administrator/Qt/Tools/mingw530_32/bin"
)

set(
CMAKE_C_FLAGS 
"-g -Wall -O3 -m32"
)
set( 
CMAKE_CXX_FLAGS 
"-g -Wall -O3 -m32"
)


#cmake cross build find_library to find in this directory 
set(
	CMAKE_COMPILER_IS_GNUCXX
	TRUE
)
set( 
	CMAKE_MAKE_PROGRAM 
	"C:/Users/Administrator/Qt/Tools/mingw530_32/bin/mingw32-make.exe" 
)
set(
CMAKE_PROGRAM_PATH
"C:/Users/Administrator/Qt/Tools/mingw530_32"
)
set( 
CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
"C:/Users/Administrator/Qt/5.9.1/mingw53_32" 
"C:/Users/Administrator/Qt/Tools/mingw530_32"
)
set( 
CMAKE_FIND_ROOT_PATH 
"C:/Users/Administrator/Qt/5.9.1/mingw53_32" 
)
set( 
CMAKE_MODULE_PATH 
"C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin"
)
set( 
CMAKE_FIND_ROOT_PATH_MODE_PROGRAM 
NEVER
)
set( 
CMAKE_FIND_ROOT_PATH_MODE_LIBRARY 
ONLY
)
set( 
CMAKE_FIND_ROOT_PATH_MODE_INCLUDE 
ONLY
)


#Qt Tools
set( 
CMAKE_AUTOMOC 
ON
)
set( 
CMAKE_AUTOUIC 
ON
)
set( 
CMAKE_AUTORCC 
ON
)


#others
set( 
CMAKE_INCLUDE_CURRENT_DIR 
ON
)
set(  
CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE 
ON
)
set(  
CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS 
ON
)
set(  
BUILD_SHARED_LIBS 
ON
)
set(  
CMAKE_VERBOSE_MAKEFILE 
OFF 
)
set(  
CMAKE_BUILD_TYPE 
Debug
)
