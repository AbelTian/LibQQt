#----------------------------------------------------------------
#add_library_QwtPlot3d.pri
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
defineReplace(get_add_include_QwtPlot3d){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_QwtPlot3d(path) requires one arguments.")

    command =
    #basic
    command += $${path}

    return ($$command)
}

defineTest(add_include_QwtPlot3d){
    #包含QwtPlot3d头文件的过程
    header_path = $$get_add_include(QwtPlot3d)
    INCLUDEPATH += $$get_add_include_QwtPlot3d($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_QwtPlot3d){
    #链接Library
    add_library(QwtPlot3d, QwtPlot3d$${LIBRARYVER})
    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接QwtPlot3d的WorkFlow
defineTest(add_link_library_QwtPlot3d){
    #链接Library
    add_library_QwtPlot3d()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_QwtPlot3d()
    #这样包含也很好，简洁明了
    #add_include(QwtPlot3d, opencv)
    #add_include(QwtPlot3d, opencv2)
    #add_include(QwtPlot3d, opencv2/core)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_QwtPlot3d) {
    add_deploy_library(QwtPlot3d, QwtPlot3d$${LIBRARYVER})
    return (1)
}

defineTest(add_dependent_library_QwtPlot3d) {
    add_link_library_QwtPlot3d()
    add_deploy_library_QwtPlot3d()
    return (1)
}
