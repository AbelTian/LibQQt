
import os
import sys
import shutil
import argparse, re, os, traceback
import argparse

from pycore import PyConfig



config = PyConfig()
config.read("toolchains/toolchain-config.ini")
current_toolchain_name = config.get("compiler", "CMAKE_CURRENT_TOOLCHAIN")
with open("", 'r') as f:
    print ""

use_toolchain = "toolchains/toolchain-" + current_toolchain_name + ".cmake"

toolchain_using = "toolchains/toolchain.cmake"

