set( 

	PYMAKE_COMPILER_PATH 
	
	"C:/Users/Administrator/Qt/Tools/mingw530_32/bin"
	"g++.exe" 
)

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

set(
	CMAKE_C_FLAGS 
	"-g -Wall -O3 -m32"
)
set(
	CMAKE_CX_FLAGS 
	"-g -Wall -O3 -m32"
)
set( 
	CMAKE_CXX_FLAGS 
	"-g -Wall -O3 -m32"
)

set(
	CMAKE_COMPILER_IS_GNUCXX
	TRUE
)

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


set(
	PYMAKE_MAKE_PATH
	"C:/Users/Administrator/Qt/Tools/mingw530_32/bin"
	"mingw32-make.exe"
)

#make program
set(
	CMAKE_MAKE_PROGRAM
	"C:/Users/Administrator/Qt/Tools/mingw530_32/bin/mingw32-make.exe"
)


set( 
	PYMAKE_SDK_BIN_PATH 
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin"
	"qmake.exe"
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


set( 
	QT_QMAKE_EXECUTABLE 
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/qmake.exe"
)

set( 
	QT_UIC_EXECUTABLE 
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/uic.exe"
)

set( 
	QT_MOC_EXECUTABLE 
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/moc.exe"
)

set( 
	QT_RCC_EXECUTABLE 
	"C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/rcc.exe"
)


