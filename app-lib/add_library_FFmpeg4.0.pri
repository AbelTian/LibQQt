#----------------------------------------------------------------
#add_library_FFmpeg4.0.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------


#######################################################################################
#初始化设置
#######################################################################################
#4.0
LIBRARYVER =

#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_FFmpeg4.0){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_FFmpeg4.0(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    command += $${path}/..
    command += $${path}/libavcodec
    command += $${path}/libavdevice
    command += $${path}/libavfilter
    command += $${path}/libavformat
    command += $${path}/libavutil
    command += $${path}/libpostproc
    command += $${path}/libswresample
    command += $${path}/libswscale

    return ($$command)
}

defineTest(add_include_FFmpeg4.0){
    #包含FFmpeg4.0头文件的过程
    header_path = $$get_add_include(FFmpeg4.0)
    INCLUDEPATH += $$get_add_include_FFmpeg4.0($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_FFmpeg4.0) {
    #链接Library
    add_library(FFmpeg4.0, avcodec.58)
    add_library(FFmpeg4.0, avdevice.58)
    add_library(FFmpeg4.0, avfilter.7)
    add_library(FFmpeg4.0, avformat.58)
    add_library(FFmpeg4.0, avutil.56)
    add_library(FFmpeg4.0, postproc.55)
    add_library(FFmpeg4.0, swresample.3)
    add_library(FFmpeg4.0, swscale.5)

    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接FFmpeg4.0的WorkFlow
defineTest(add_link_library_FFmpeg4.0) {
    #链接Library
    add_library_FFmpeg4.0()

    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_FFmpeg4.0()
    #这样包含也很好，简洁明了
    #add_include(FFmpeg4.0, FFmpeg4.0QtCore)
    #add_include(FFmpeg4.0, FFmpeg4.0QtWidgets)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library的函数
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_FFmpeg4.0) {
    add_deploy_library(FFmpeg4.0, avcodec.58)
    add_deploy_library(FFmpeg4.0, avdevice.58)
    add_deploy_library(FFmpeg4.0, avfilter.7)
    add_deploy_library(FFmpeg4.0, avformat.58)
    add_deploy_library(FFmpeg4.0, avutil.56)
    add_deploy_library(FFmpeg4.0, postproc.55)
    add_deploy_library(FFmpeg4.0, swresample.3)
    add_deploy_library(FFmpeg4.0, swscale.5)
    return (1)
}

defineTest(add_dependent_library_FFmpeg4.0) {
    add_link_library_FFmpeg4.0()
    add_deploy_library_FFmpeg4.0()
    return (1)
}
