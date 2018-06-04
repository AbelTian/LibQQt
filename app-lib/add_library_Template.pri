#----------------------------------------------------------------
#add_library_Template.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------
#_bundle的取舍，在于macOS系统下，使用的library为bundle形式，还是dylib形式。

#######################################################################################
#初始化设置
#######################################################################################
#1.0.0
LIBRARYVER =

#######################################################################################
#定义内部函数
#######################################################################################
#修改
#defineReplace(get_add_include_Template){
#    isEmpty(1)|!isEmpty(2) : error("get_add_include_Template(path) requires one arguments.")

#    path = $$1

#    command =
#    #basic
#    command += $${path}
#    #这里添加$${path}下的子文件夹

#    return ($$command)
#}

#这里，[get_]add_include_bundle，代表macOS下，Library的头文件在bundle里
defineTest(add_include_Template){
    #包含Template头文件的过程
    #header_path = $$get_add_include(Template)
    #INCLUDEPATH += $$get_add_include_Template($$header_path)
    #export(INCLUDEPATH)
    
    #不用上边这种，这样包含也很好，简洁明了
    #add_include_bundle(Template, Template, xxx)
    #add_include(Template, Template, xxx)
    #添加子路径
    add_include(Template, Template)

    return (1)
}

#这个地方add_library_bundle代表包括macOS下，lib在bundle里。
#修改
defineTest(add_library_Template){
    #添加这个SDK里的library
    add_library(Template, Template$${LIBRARYVER})

    return (1)
}

defineTest(add_defines_Template){
    #添加这个SDK里的library
    #add_defines(Template)

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
    add_include_Template()
    #添加宏定义
    add_defines_Template()
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_Template) {
    add_deploy_library(Template, Template$${LIBRARYVER})
    #add_deploy_libraryes(Template)
    return (1)
}

defineTest(add_dependent_library_Template) {
    add_link_library_Template()
    add_deploy_library_Template()
    return (1)
}
