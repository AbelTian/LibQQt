#----------------------------------------------------------------
#add_library_log4cpp.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#1.0.0
LIBRARYVER = .5


#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_log4cpp){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_log4cpp(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    #这里添加$${path}下的子文件夹
    command += $${path}/..
    command += $${path}/threading

    return ($$command)
}

defineTest(add_include_log4cpp){
    #包含log4cpp头文件的过程
    header_path = $$get_add_include(log4cpp)
    INCLUDEPATH += $$get_add_include_log4cpp($$header_path)
    export(INCLUDEPATH)
    
    #不用上边这种，这样包含也很好，简洁明了
    #add_include(log4cpp)
    #add_include(log4cpp, log4cpp)
    #add_include(log4cpp, log4cpp/core)
    #...

    return (1)
}

defineTest(add_library_log4cpp){
    add_library(log4cpp, log4cpp$${LIBRARYVER})

    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接log4cpp的WorkFlow
defineTest(add_link_library_log4cpp){
    #链接Library
    add_library_log4cpp()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_log4cpp()

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_log4cpp) {
    add_deploy_library(log4cpp, log4cpp$${LIBRARYVER})
    return (1)
}

defineTest(add_dependent_library_log4cpp) {
    add_link_library_log4cpp()
    add_deploy_library_log4cpp()
    return (1)
}
