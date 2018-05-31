#----------------------------------------------------------------
#add_library_VLC.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#1.1.0
LIBRARYVER =
DEBUG = d
#这个地方，mingw比较特殊必须发布release版本，其他平台不清楚。
mingw:DEBUG=
contains(BUILD, Release) {
    DEBUG=
}

#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_header_VLC){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_header_VLC(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    command += $${path}/VLCQtCore
    command += $${path}/VLCQtWidgets

    return ($$command)
}

defineTest(add_header_VLC){
    #包含VLC头文件的过程
    header_path = $$get_add_header(VLC)
    INCLUDEPATH += $$get_add_header_VLC($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_VLC) {
    #链接Library
    add_library(VLC, VLCQtCore$${LIBRARYVER}$${DEBUG})
    add_library(VLC, VLCQtWidgets$${LIBRARYVER}$${DEBUG})
    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接VLC的WorkFlow
defineTest(add_link_library_VLC) {
    #链接Library
    add_library_VLC()

    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_header_VLC()
    #这样包含也很好，简洁明了
    #add_header(VLC, VLCQtCore)
    #add_header(VLC, VLCQtWidgets)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library的函数
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_VLC) {
    add_deploy_libraries(VLC)
    return (1)
}

defineTest(add_dependent_library_VLC) {
    add_link_library_VLC()
    add_deploy_library_VLC()
    return (1)
}