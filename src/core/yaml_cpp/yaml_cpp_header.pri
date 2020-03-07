##############################################################
#编译 yaml_cpp
#为用户编译本库提供头文件包含集、宏控制集方便。
##############################################################
#头文件
defineTest(add_include_yaml_cpp) {
    header_path=$${PWD}

    command =
    command += $${header_path}

    add_include_path($$command)
    return (1)
}

#本库使用的定义
defineTest(add_defines_yaml_cpp) {
    #--------------------------------------------
    #留意 yaml_cpp 使用的控制宏
    #--------------------------------------------

    #--------------------------------------------
    #Multi-link 提供 Template 的自有控制宏，
    #留意 Template 使用的控制宏
    #--------------------------------------------

    #--------------------------------------------
    #根据 yaml_cpp 使用的控制宏，修改 yaml_cpp 编译时、链接时的不同的宏配置。编译时，修改前两个判断分支；链接时，修改后两个判断分支。
    #可以用于转换使用不同宏、两套宏控制的链接库。
    #--------------------------------------------
    #需要移动到qqt_header.pri里面

    win32 {

        contains (DEFINES, QQT_LIBRARY) {
            DEFINES += YAML_CPP_LIBRARY
        } else:contains(DEFINES, QQT_STATIC_LIBRARY) {
            DEFINES += YAML_CPP_STATIC_LIBRARY
        }

        contains(DEFINES, YAML_CPP_LIBRARY) {
            #yaml_cpp 动态编译时
            message(build yaml_cpp dynamic library)
            DEFINES += YAML_CPP_BUILD_CONTRIB
            DEFINES += YAML_CPP_DLL yaml_cpp_EXPORTS
        } else:contains(DEFINES, YAML_CPP_STATIC_LIBRARY) {
            #yaml_cpp 静态编译、链接时
            message(build-link yaml_cpp static library)
        } else:!contains(DEFINES, YAML_CPP_LIBRARY) {
            #yaml_cpp 动态链接时
            message(link yaml_cpp dynamic library)
            DEFINES += YAML_CPP_DLL
        }

    }

    #只要用户不在应用程序中使用YAML的头文件，放在这里也没关系。

    #--------------------------------------------
    #添加库的宏配置信息，编译时、链接时通用，需要注意区分不同宏控制
    #建议先写动态编译、链接时的通用配置，然后增加对动态编译、链接，对静态编译、链接时的兼容处理。处理多个子模块时特别好用。
    #--------------------------------------------


    export(QT)
    export(DEFINES)
    export(CONFIG)
    return (1)
}

add_include_yaml_cpp()
add_defines_yaml_cpp()
