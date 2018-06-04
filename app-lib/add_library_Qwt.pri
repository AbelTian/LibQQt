#----------------------------------------------------------------
#add_library_Qwt.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#6.1.3
LIBRARYVER =


#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_Qwt){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_Qwt(path) requires one arguments.")

    command =
    #basic
    command += $${path}

    return ($$command)
}

defineTest(add_include_Qwt){
    #包含Qwt头文件的过程
    header_path = $$get_add_include(Qwt)
    INCLUDEPATH += $$get_add_include_Qwt($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_Qwt){
    #链接Library
    add_library(Qwt, Qwt$${LIBRARYVER})
    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接Qwt的WorkFlow
defineTest(add_link_library_Qwt){
    #链接Library
    add_library_Qwt()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_Qwt()
    #这样包含也很好，简洁明了
    #add_include(Qwt, opencv)
    #add_include(Qwt, opencv2)
    #add_include(Qwt, opencv2/core)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_Qwt) {
    add_deploy_library(Qwt, Qwt$${LIBRARYVER})
    return (1)
}

defineTest(add_dependent_library_Qwt) {
    add_link_library_Qwt()
    add_deploy_library_Qwt()
    return (1)
}
