"""PyMake 1.0.

Usage:
  pymake.py cmake <cmake-command-list> ...
  pymake.py command (generate|build|install) [--quiet=<hg>]
  pymake.py config toolchain <toolchain-name>
  pymake.py config genmake <genmake-name>
  pymake.py config make <make-name>
  pymake.py config sdk <sdk-path> [--included | --prepared ]
  pymake.py config source <source> [--build | --prepared ]
  pymake.py (-h | --help)
  pymake.py --version

Options:
  -h --help     Show this screen.
  --version     Show version.
  --quiet=<hg>  Quiet to execute command [default: safety].
  --included    Be sure to include this sdk.
  --prepared    Prepared to include these path or don't build them.
  --build       Add source to build
"""

# -*- coding: utf-8 -*-

import os
import sys
import shutil
import time

from pymake.pycore import *
from pymake.docopt import docopt

def readPyMakeConfig():

    global toolchain_file
    global genmake_file
    global make_file
    global pyMakeConfig


    conf = PyCMakeConfig()

    pyMakeConfig = conf.readPymakeSet("pymake.setting")

    toolchain_file = pyMakeConfig["toolchain"][0]["PYMAKE_CURRENT_TOOLCHAIN"]
    genmake_file = pyMakeConfig["make"][0]["PYMAKE_CURRENT_GENMAKE"]
    make_file = pyMakeConfig["make"][0]["PYMAKE_CURRENT_MAKE"]

    print toolchain_file
    print genmake_file
    print make_file
    
    return

def exportEnviron():
    #ENVIRONMENT
    global sdk_file
    global genmake_command

    env = os.environ
    cmakeConfig = PyCMakeConfig()

    temp = cmakeConfig.readSet("toolchains/" + toolchain_file + ".cmake", "PYMAKE_COMPILER_PATH")
    print temp
    toolchain_path = temp[1]
    print "toolchain path", toolchain_path
    env["PATH"] = toolchain_path + ';' + env["PATH"]

    temp = cmakeConfig.readSet("toolchains/" + genmake_file + ".cmake", "PYMAKE_GENMAKE_PATH")
    genmake_path = temp[1]
    genmake_command = temp[2]
    print "genmake program", genmake_path, genmake_command
    env["PATH"] = genmake_path + ';' + env["PATH"]

    temp = cmakeConfig.readSet("toolchains/" + make_file + ".cmake", "PYMAKE_MAKE_PATH")
    make_path = temp[1]
    make_command = temp[2]
    print "make program", make_path, make_command
    env["PATH"] = make_path + ';' + env["PATH"]


    if isinstance(pyMakeConfig["sdk"], dict):
        for sdk in range(len(pyMakeConfig["sdk"])):
            sdk_id = pyMakeConfig["sdk"].keys()[sdk]
            sdk_dict = pyMakeConfig["sdk"][sdk_id]
            #print "sdk_id, sdk_dict", sdk_id, sdk_dict

            sdk_file = sdk_dict["PYMAKE_SDK"]
            temp = cmakeConfig.readSet("toolchains/" + sdk_file + ".cmake", "PYMAKE_SDK_BIN_PATH")
            sdk_path = temp[1]
            print "sdk path", sdk_path
            env["PATH"] = sdk_path + ';' + env["PATH"]

    return


def buildToolChainFile():
    ##BUILD TOOL CMAKE
    with open("toolchains/build.cmake", "w") as file :
        with open("toolchains/" + toolchain_file + ".cmake" , "r") as f:
            for line in f.readlines():
                file.writelines(line)
        file.write('\n')
        with open("toolchains/" + genmake_file + ".cmake", "r") as f:
            for line in f.readlines():
                file.writelines(line)
        file.write('\n')
        with open("toolchains/" + make_file + ".cmake", "r") as f:
            for line in f.readlines():
                file.writelines(line)
        file.write('\n')
        with open("toolchains/" + sdk_file + ".cmake", "r") as f:
            for line in f.readlines():
                file.writelines(line)
        file.write('\n')

    return

def parseCommandLine():
    env = os.environ
    print env['PATH']

    ##COMMAND LINE
    arguments = docopt(__doc__, version='Pymake.py 1.0')
    #print(arguments)

    if(arguments['cmake'] == True):
        if(len(arguments['<cmake-command-list>']) > 0):
            cmd = arguments['<cmake-command-list>'][0]
            print cmd
            os.system(cmd)
        return

    if(arguments['command'] == True):
        build_path = pyMakeConfig['source'][1]['PYMAKE_BUILD_PATH']
        source_path = pyMakeConfig['source'][1]['PYMAKE_SOURCE_PATH']
        install_path = pyMakeConfig['source'][1]['PYMAKE_INSTALL_PATH']

        #build_path.replace('\\', '/')

        #bug: can't create blank in line
        make_dir_cmd = genmake_command + ' -E make_directory ' + build_path
        #os.system(make_dir_cmd)
        #success
        if( False == os.path.exists(build_path) ):
            os.makedirs(build_path)

        cmakeConfig = PyCMakeConfig()
        temp = cmakeConfig.readSet("toolchains/" + genmake_file + ".cmake", "CMAKE_GENERATOR")
        #print temp
        generator_name = temp[1]
        print "generator name", generator_name

        os.chdir(build_path)
        rel_source_path =  os.path.relpath(source_path)
        cmake_generate_cmd = genmake_command + ' -G\"' + generator_name + '\" -DCMAKE_INSTALL_PREFIX=' + install_path \
                             + ' ' + rel_source_path

        print "cmake_generate_cmd", cmake_generate_cmd

        cmake_build_cmd = genmake_command + ' --build .' + ' --target install'

        print "cmake_build_cmd", cmake_build_cmd

        if (arguments['generate'] == True):
            os.system(cmake_generate_cmd)
        elif (arguments['build'] == True):
            os.system(cmake_build_cmd)
        elif (arguments['install'] == True):
            os.system(cmake_build_cmd)

    return

def main_function():

    readPyMakeConfig()

    exportEnviron()

    buildToolChainFile()

    parseCommandLine()
    return

if __name__ == '__main__':

    main_function()
