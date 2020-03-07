#需要移动到qqt_header.pri里面
win32 {
    contains (DEFINES, QQT_LIBRARY) {
        DEFINES += YAML_CPP_LIBRARY
    } else:contains(DEFINES, QQT_STATIC_LIBRARY) {
        DEFINES += YAML_CPP_STATIC_LIBRARY
    } else { }
    #yaml_cpp 动态编译时
    contains(DEFINES, YAML_CPP_LIBRARY){
        #message(build yaml_cpp dynamic library)
        DEFINES += YAML_CPP_BUILD_CONTRIB
        DEFINES += YAML_CPP_DLL yaml_cpp_EXPORTS
    }
    #yaml_cpp 静态编译、链接时
    else:contains(DEFINES, YAML_CPP_STATIC_LIBRARY){
        #message(build-link yaml_cpp static library)
    }
    #yaml_cpp 动态链接时
    else:!contains(DEFINES, YAML_CPP_LIBRARY){
        #message(link yaml_cpp dynamic library)
        DEFINES += YAML_CPP_DLL
    }
}
#只要用户不在应用程序中使用YAML的头文件，放在这里也没关系。

#Gumbo Parser的源文件和YAML的源文件冲突，需要用到编译目录的相对路径设置
#CONFIG += object_parallel_to_source
#CONFIG += object_with_source
#CONFIG += no_fixpath subdir_first_pro cd_change_global slient
#通过修改YAML源文件解决问题 parser.cpp -> parser_copy.cpp

#include($${PWD}/yaml_cpp_header.pri)
#include($${PWD}/yaml_cpp_source.pri)
include ($$PWD/yaml-cpp-0.6.0.pri)
