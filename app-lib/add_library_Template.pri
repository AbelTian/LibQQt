#----------------------------------------------------------------
#add_library_Template.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#1.0.0
LIBRARYVER =
DEBUG = d
contains(BUILD, Release) {
    DEBUG=
}


#######################################################################################
#定义内部函数
#######################################################################################
#修改
defineReplace(get_add_header_Template){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_header_Template(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    #这里添加$${path}下的子文件夹

    return ($$command)
}

defineTest(add_header_Template){
    #包含Template头文件的过程
    header_path = $$get_add_header(Template)
    INCLUDEPATH += $$get_add_header_Template($$header_path)
    export(INCLUDEPATH)
    
    #不用上边这种，这样包含也很好，简洁明了
    #add_header(Template)
    #add_header(Template, Template)
    #add_header(Template, Template/core)
    #...

    return (1)
}

#这个地方add_library_no_bundle代表包括macOS下，都不使用bundle，只是动态库或者静态库。
#修改
defineTest(add_library_Template){
    #链接Library
    add_library(Template, Template$${LIBRARYVER}$${DEBUG})
    #添加这个SDK下的其他的library
    
    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接Template的WorkFlow
#留意
defineTest(add_link_library_Template){
    #链接Library
    add_library_Template()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_header_Template()

    #添加宏定义
    #add_define(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
#_Qt 代表这个lib是基于Qt的 依赖Qt
#留意
defineTest(add_deploy_library_Template) {
    add_deploy_library_Qt(Template, Template$${LIBRARYVER}$${DEBUG})
    return (1)
}

defineTest(add_dependent_library_Template) {
    add_link_library_Template()
    add_deploy_library_Template()
    return (1)
}
