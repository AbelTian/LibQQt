
import os
import sys
import shutil
import argparse, re, os, traceback

import pycore

config = PyConfig()
config.read("toolchains/toolchain-config.ini")
current_toolchain_name = config.get("compiler", "CMAKE_CURRENT_TOOLCHAIN")

use_toolchain = "toolchains/toolchain-" + current_toolchain_name + ".cmake"

toolchain_using = "toolchains/toolchain.cmake"

shutil.copyfile(use_toolchain, toolchain_using)

toolchain_path=""
make_program=""
make_executable=""

qmake_path = ""
qmake_progam=""
qmake_executable = ""

cmake_path = ""
cmake_progam=""
cmake_exectable = ""
with open(toolchain_using, 'r') as f:
    target = 0
    for line in f.readlines():
        line = line.replace('\\', '/')
        line = line.replace('\n', '')
        line = line.replace('\r', '')
        if(target == 1):
            make_program = line
            toolchain_path = line.replace('\"', '').rsplit('/', 1)[0]
            make_executable = line.replace('\"', '').rsplit('/', 1)[1]
            target = 0
            continue
        if(target == 2):
            qmake_progam = line
            qmake_path = line.replace('\"', '').rsplit('/', 1)[0]
            qmake_executable = line.replace('\"', '').rsplit('/', 1)[1]
            target = 0
            continue
        if(target == 3 ) :
            cmake_progam = line
            cmake_path = line.replace('\"', '').rsplit('/', 1)[0]
            cmake_exectable = line.replace('\"', '').rsplit('/', 1)[1]
            target = 0
            continue

        if(line.find("CMAKE_MAKE_PROGRAM") is 0 ) :
            target = 1
        if(line.find("QT_QMAKE_EXECUTABLE") is 0 ) :
            target = 2
        if(line.find("CMAKE_PROGRAM_PATH") is 0 ) :
            target = 3

print " make program", make_program
print "cmake program", cmake_progam
print "qmake program", qmake_progam

env = os.environ
env["PATH"] = toolchain_path + ';' + cmake_path + ';' + qmake_path + ';' + env["PATH"]

os.chdir("./build")

cmd = cmake_exectable + " -G\"MinGW Makefiles\" ../ "
print cmd
#os.system(cmd)

#os.system("cmake.exe --help")

sys.argv