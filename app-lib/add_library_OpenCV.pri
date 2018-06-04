#----------------------------------------------------------------
#add_library_OpenCV.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
LIBRARYVER = 231


#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_OpenCV){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_OpenCV(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    command += $${path}/opencv
    command += $${path}/opencv2
    command += $${path}/opencv2/calib3d
    command += $${path}/opencv2/contrib
    command += $${path}/opencv2/core
    command += $${path}/opencv2/features2d
    command += $${path}/opencv2/flann
    command += $${path}/opencv2/gpu
    command += $${path}/opencv2/highgui
    command += $${path}/opencv2/imgproc
    command += $${path}/opencv2/legacy
    command += $${path}/opencv2/ml
    command += $${path}/opencv2/objdetect
    command += $${path}/opencv2/video

    return ($$command)
}

defineTest(add_include_OpenCV){
    #包含OpenCV头文件的过程
    header_path = $$get_add_include(OpenCV)
    INCLUDEPATH += $$get_add_include_OpenCV($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_OpenCV){
    #链接Library
    add_library(OpenCV, opencv_calib3d$${LIBRARYVER})
    add_library(OpenCV, opencv_contrib$${LIBRARYVER})
    add_library(OpenCV, opencv_core$${LIBRARYVER})
    add_library(OpenCV, opencv_features2d$${LIBRARYVER})
    add_library(OpenCV, opencv_flann$${LIBRARYVER})
    add_library(OpenCV, opencv_gpu$${LIBRARYVER})
    add_library(OpenCV, opencv_highgui$${LIBRARYVER})
    add_library(OpenCV, opencv_imgproc$${LIBRARYVER})
    add_library(OpenCV, opencv_legacy$${LIBRARYVER})
    add_library(OpenCV, opencv_ml$${LIBRARYVER})
    add_library(OpenCV, opencv_objdetect$${LIBRARYVER})
    add_library(OpenCV, opencv_video$${LIBRARYVER})
    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接OpenCV的WorkFlow
defineTest(add_link_library_OpenCV){
    #链接Library
    add_library_OpenCV()
    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_OpenCV()
    #这样包含也很好，简洁明了
    #add_include(OpenCV, opencv)
    #add_include(OpenCV, opencv2)
    #add_include(OpenCV, opencv2/core)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_OpenCV) {
    add_deploy_library(OpenCV, libopencv_calib3d$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_contrib$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_core$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_features2d$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_flann$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_gpu$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_highgui$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_imgproc$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_legacy$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_ml$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_objdetect$${LIBRARYVER})
    add_deploy_library(OpenCV, libopencv_video$${LIBRARYVER})
    return (1)
}

defineTest(add_dependent_library_OpenCV) {
    add_link_library_OpenCV()
    add_deploy_library_OpenCV()
    return (1)
}
