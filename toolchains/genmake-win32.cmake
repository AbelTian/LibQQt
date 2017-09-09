set ( 
	PYMAKE_GENMAKE_PATH
	"Z:/abel/Develop/b0-toolskits/a1-QQtToolsKits-Windows/compliers/cmake3.9.1_64/bin"
	"cmake.exe"
)

#cmake cross build find_library to find in this directory 
set(
	CMAKE_SYSTEM_NAME
	"Windows"
)

#generator name
set(
	CMAKE_GENERATOR
	"MinGW Makefiles"
)
#find program
set(
	CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH}
	"C:/Users/Administrator/Qt/Tools/mingw530_32"
)
#find library e.g
set( 
	CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32" 
	"C:/Users/Administrator/Qt/Tools/mingw530_32"
)
#find path
set( 
	CMAKE_FIND_ROOT_PATH 
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32" 
)
#find module
set( 
	CMAKE_MODULE_PATH 
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32"
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


#cmake comm
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
