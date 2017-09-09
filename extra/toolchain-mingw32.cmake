#SET(CMAKE_SYSTEM_NAME Windows)
#toolchain
set(CMAKE_C_COMPILER "C:/Users/Administrator/Qt/Tools/mingw530_32/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Users/Administrator/Qt/Tools/mingw530_32/bin/g++.exe")
set(CMAKE_RC_COMPILER "C:/Users/Administrator/Qt/Tools/mingw530_32/bin/windres.exe")

set(CMAKE_C_FLAGS "-g -Wall -O3 -m32")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -m32")

set(CMAKE_MAKE_PROGRAM "C:/Users/Administrator/Qt/Tools/mingw530_32/bin/mingw32-make.exe" CACHE FILEPATH "" FORCE)
set(CMAKE_PROGRAM_PATH "Z:/abel/Develop/b0-toolskits/a1-QQtToolsKits-Windows/compliers/cmake3.9.1_64/bin/cmake.exe" CACHE FILEPATH "" FORCE)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
SET(CMAKE_FIND_ROOT_PATH "C:/Users/Administrator/Qt/5.9.1/mingw53_32" )

set(QT_MOC_EXECUTABLE "C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/rcc.exe" CACHE INTERNAL "" FORCE)
set(QT_MOC_EXECUTABLE "C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/moc.exe" CACHE INTERNAL "" FORCE)
set(QT_UIC_EXECUTABLE "C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/uic.exe" CACHE INTERNAL "" FORCE)
set(QT_QMAKE_EXECUTABLE "C:/Users/Administrator/Qt/5.9.1/mingw53_32/bin/qmake.exe" CACHE FILEPATH "" FORCE)

