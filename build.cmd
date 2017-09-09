@echo off

cd /d ./build

del /f CMakeCache.txt

:qmake
set Path=C:\Users\Administrator\Qt\5.9.1\mingw53_32\bin;%Path%
:cmake
set Path="Z:\abel\Develop\b0-toolskits\a1-QQtToolsKits-Windows\compliers\cmake3.9.1_64\bin";%Path%
:make
set Path=C:\Users\Administrator\Qt\Tools\mingw530_32\bin;%Path%

:Z:\abel\Develop\b0-toolskits\a1-QQtToolsKits-Windows\compliers\cmake3.9.1_64\bin\cmake.exe -G"MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=Z:\abel\Develop\a0-Developworkspace\temp ..

cmake.exe -G"MinGW Makefiles" ../

:mingw32-make.exe -j4 install

cd /d ../