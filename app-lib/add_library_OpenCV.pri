#----------------------------------------------------------------
#add_library_OpenCV.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#添加依赖library
add_library(OpenCV, opencv_java3)

#添加头文件 （如果头文件目录扩展了，就改这个函数）
defineReplace(get_opencv_header){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_opencv_header(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    command += $${path}/opencv
    command += $${path}/opencv2

    return ($$command)
}

defineTest(add_opencv_header){
    #包含OpenCV头文件的过程
    header_path = $$get_add_header(OpenCV)
    INCLUDEPATH += $$get_opencv_header($$header_path)
    export(INCLUDEPATH)
    return (1)
}

add_opencv_header()

#这样包含也很好，简洁明了
#add_header(OpenCV, opencv)
#add_header(OpenCV, opencv2)

#添加宏定义
#add_defines(xx)

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
add_deploy_library(OpenCV, opencv_java3)
