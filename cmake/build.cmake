#compiler

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
