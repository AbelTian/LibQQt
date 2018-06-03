#----------------------------------------------------------------
#add_library_GoogleTest.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#1.0.0
LIBRARYVER =
DEBUG =
contains(BUILD, Release) {
    DEBUG=
}


#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_GoogleTest){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_GoogleTest(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    #这里添加$${path}下的子文件夹
    command += $${path}/gtest
    command += $${path}/gtest/internal
    command += $${path}/gtest/internal/custom
    command += $${path}/gmock
    command += $${path}/gmock/internal
    command += $${path}/gmock/internal/custom

    return ($$command)
}

defineTest(add_include_GoogleTest){
    #包含GoogleTest头文件的过程
    header_path = $$get_add_include(GoogleTest)
    INCLUDEPATH += $$get_add_include_GoogleTest($$header_path)
    export(INCLUDEPATH)
    
    #不用上边这种，这样包含也很好，简洁明了
    #add_include(GoogleTest)
    #add_include(GoogleTest, GoogleTest)
    #add_include(GoogleTest, GoogleTest/core)
    #...

    return (1)
}

defineTest(add_library_GoogleTest){
    #链接Library
    add_library(GoogleTest, gtest$${LIBRARYVER}$${DEBUG})
    #添加这个SDK下的其他的library
    add_library(GoogleTest, gtest_main$${LIBRARYVER}$${DEBUG})
    add_library(GoogleTest, gmock$${LIBRARYVER}$${DEBUG})
    add_library(GoogleTest, gmock_main$${LIBRARYVER}$${DEBUG})

    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接GoogleTest的WorkFlow
defineTest(add_link_library_GoogleTest){
    #链接Library
    add_library_GoogleTest()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_GoogleTest()

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_GoogleTest) {
    add_deploy_library_Qt(GoogleTest, GoogleTest$${LIBRARYVER}$${DEBUG})
    return (1)
}

defineTest(add_dependent_library_GoogleTest) {
    add_link_library_GoogleTest()
    add_deploy_library_GoogleTest()
    return (1)
}
