
#Gumbo Parser的源文件和YAML的源文件冲突，需要用到编译目录的相对路径设置
#CONFIG += object_parallel_to_source
#CONFIG += object_with_source
#CONFIG += no_fixpath subdir_first_pro cd_change_global slient
#通过修改YAML源文件解决问题 parser.cpp -> parser_copy.cpp

include($${PWD}/yaml_cpp_header.pri)
include($${PWD}/yaml_cpp_source.pri)
#include ($$PWD/yaml-cpp-0.6.0.pri)
