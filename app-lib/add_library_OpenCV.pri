#----------------------------------------------------------------
#add_library_OpenCV.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
LIBRARYVER = 231
DEBUG = d
contains(BUILD, Release) {
    DEBUG=
}


#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_path_OpenCV){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_path_OpenCV(path) requires one arguments.")

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

defineTest(add_include_path_OpenCV){
    #包含OpenCV头文件的过程
    header_path = $$get_add_include_path(OpenCV)
    INCLUDEPATH += $$get_add_include_path_OpenCV($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_OpenCV){
    add_library_path(OpenCV)
    #链接Library
    add_library(opencv_calib3d$${LIBRARYVER}$${DEBUG})
    add_library(opencv_contrib$${LIBRARYVER}$${DEBUG})
    add_library(opencv_core$${LIBRARYVER}$${DEBUG})
    add_library(opencv_features2d$${LIBRARYVER}$${DEBUG})
    add_library(opencv_flann$${LIBRARYVER}$${DEBUG})
    add_library(opencv_gpu$${LIBRARYVER}$${DEBUG})
    add_library(opencv_highgui$${LIBRARYVER}$${DEBUG})
    add_library(opencv_imgproc$${LIBRARYVER}$${DEBUG})
    add_library(opencv_legacy$${LIBRARYVER}$${DEBUG})
    add_library(opencv_ml$${LIBRARYVER}$${DEBUG})
    add_library(opencv_objdetect$${LIBRARYVER}$${DEBUG})
    add_library(opencv_video$${LIBRARYVER}$${DEBUG})
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
    add_include_path_OpenCV()
    #这样包含也很好，简洁明了
    #add_include_path(OpenCV, opencv)
    #add_include_path(OpenCV, opencv2)
    #add_include_path(OpenCV, opencv2/core)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_OpenCV) {
    add_deploy_library(OpenCV, libopencv_calib3d$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_contrib$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_core$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_features2d$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_flann$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_gpu$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_highgui$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_imgproc$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_legacy$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_ml$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_objdetect$${LIBRARYVER}$${DEBUG})
    add_deploy_library(OpenCV, libopencv_video$${LIBRARYVER}$${DEBUG})
    return (1)
}

defineTest(add_dependent_library_OpenCV) {
    add_link_library_OpenCV()
    add_deploy_library_OpenCV()
    return (1)
}
