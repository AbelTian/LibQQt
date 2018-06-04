#----------------------------------------------------------------
#add_library_FMOD.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#1.10.05
LIBRARYVER =

#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_FMOD){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_FMOD(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    #这里添加$${path}下的子文件夹

    return ($$command)
}

defineTest(add_include_FMOD){
    #包含FMOD头文件的过程
    header_path = $$get_add_include(FMOD)
    INCLUDEPATH += $$get_add_include_FMOD($$header_path)
    export(INCLUDEPATH)
    
    #不用上边这种，这样包含也很好，简洁明了
    #add_include(FMOD)
    #add_include(FMOD, FMOD)
    #add_include(FMOD, FMOD/core)
    #...

    return (1)
}

#这个地方add_library_no_bundle代表包括macOS下，都不使用bundle，只是动态库或者静态库。
defineTest(add_library_FMOD){
    #链接Library
    add_library(FMOD, fmod$${LIBRARYVER})
    add_library(FMOD, fmodL$${LIBRARYVER})
    #添加这个SDK下的其他的library
    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接FMOD的WorkFlow
defineTest(add_link_library_FMOD){
    #链接Library
    add_library_FMOD()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_FMOD()

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_FMOD) {
    add_deploy_library(FMOD, fmod$${LIBRARYVER})
    add_deploy_library(FMOD, fmodL$${LIBRARYVER})
    return (1)
}

defineTest(add_dependent_library_FMOD) {
    add_link_library_FMOD()
    add_deploy_library_FMOD()
    return (1)
}
