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
DEBUG = 
contains(BUILD, Release) {
    DEBUG=
}


#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_header_FMOD){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_header_FMOD(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    #这里添加$${path}下的子文件夹
    command += $${path}/fsbank/inc
    command += $${path}/studio/inc
    command += $${path}/lowlevel/inc

    return ($$command)
}

defineTest(add_header_FMOD){
    #包含FMOD头文件的过程
    header_path = $$get_add_header(FMOD)
    INCLUDEPATH += $$get_add_header_FMOD($$header_path)
    export(INCLUDEPATH)
    
    #不用上边这种，这样包含也很好，简洁明了
    #add_header(FMOD)
    #add_header(FMOD, FMOD)
    #add_header(FMOD, FMOD/core)
    #...

    return (1)
}

#这个地方add_library_no_bundle代表包括macOS下，都不使用bundle，只是动态库或者静态库。
defineTest(add_library_FMOD){
    #链接Library
    add_library_at_subdir(FMOD, fsbank$${LIBRARYVER}$${DEBUG}, fsbank/lib)
    add_library_at_subdir(FMOD, fsbank64$${LIBRARYVER}$${DEBUG}, fsbank/lib)
    add_library_at_subdir(FMOD, fsbvorbis$${LIBRARYVER}$${DEBUG}, fsbank/lib)
    add_library_at_subdir(FMOD, fsbvorbis64$${LIBRARYVER}$${DEBUG}, fsbank/lib)

    add_library_at_subdir(FMOD, fmod$${LIBRARYVER}$${DEBUG}, lowlevel/lib)
    add_library_at_subdir(FMOD, fmod64$${LIBRARYVER}$${DEBUG}, lowlevel/lib)
    add_library_at_subdir(FMOD, fmodL$${LIBRARYVER}$${DEBUG}, lowlevel/lib)
    add_library_at_subdir(FMOD, fmodL64$${LIBRARYVER}$${DEBUG}, lowlevel/lib)
    #添加这个SDK下的其他的library

    add_library_at_subdir(FMOD, fmodstudio$${LIBRARYVER}$${DEBUG}, studio/lib)
    add_library_at_subdir(FMOD, fmodstudio64$${LIBRARYVER}$${DEBUG}, studio/lib)
    add_library_at_subdir(FMOD, fmodstudioL$${LIBRARYVER}$${DEBUG}, studio/lib)
    add_library_at_subdir(FMOD, fmodstudioL64$${LIBRARYVER}$${DEBUG}, studio/lib)

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
    add_header_FMOD()

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
#_Qt 代表这个lib是基于Qt的 依赖Qt
defineTest(add_deploy_library_FMOD) {
    add_deploy_library(FMOD, FMOD$${LIBRARYVER}$${DEBUG})
    return (1)
}

defineTest(add_dependent_library_FMOD) {
    add_link_library_FMOD()
    add_deploy_library_FMOD()
    return (1)
}
