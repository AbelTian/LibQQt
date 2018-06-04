#----------------------------------------------------------------
#add_library_SDL2.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#2
LIBRARYVER =

#######################################################################################
#定义内部函数
#######################################################################################
#修改
#defineReplace(get_add_include_SDL2){
#    isEmpty(1)|!isEmpty(2) : error("get_add_include_SDL2(path) requires one arguments.")

#    path = $$1

#    command =
#    #basic
#    command += $${path}
#    #这里添加$${path}下的子文件夹

#    return ($$command)
#}

#这里，[get_]add_include_bundle，代表macOS下，Library的头文件在bundle里
defineTest(add_include_SDL2){
    #包含SDL2头文件的过程
    #header_path = $$get_add_include(SDL2)
    #INCLUDEPATH += $$get_add_include_SDL2($$header_path)
    #export(INCLUDEPATH)
    
    #不用上边这种，这样包含也很好，简洁明了
    #add_include_bundle(SDL2, SDL2, xxx)
    #add_include(SDL2, SDL2, xxx)
    #添加子路径
    add_include(SDL2, SDL2)
    add_include(SDL2, SDL2, ..)
    #这个是有点分歧，其实mac下SDL22 framwrok里的Headers就够用了，可是某些程序当中喜欢把头文件带SDL22字样，bundle里面没有，所以出现了下边这个inc和上边这个inc并存的情况。
    add_include_bundle(SDL2, SDL2)

    return (1)
}

#这个地方add_library_bundle代表包括macOS下，lib在bundle里。
#修改
defineTest(add_library_SDL2){
    #添加这个SDK里的library
    add_library_bundle(SDL2, SDL2$${LIBRARYVER})

    return (1)
}

defineTest(add_defines_SDL2){
    #添加这个SDK里的library
    #add_defines(SDL2)

    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接SDL2的WorkFlow
#留意
defineTest(add_link_library_SDL2){
    #链接Library
    add_library_SDL2()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_SDL2()
    #添加宏定义
    add_defines_SDL2()
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_SDL2) {
    add_deploy_library_bundle(SDL2, SDL2$${LIBRARYVER})
    #add_deploy_libraryes(SDL2)
    return (1)
}

defineTest(add_dependent_library_SDL2) {
    add_link_library_SDL2()
    add_deploy_library_SDL2()
    return (1)
}
