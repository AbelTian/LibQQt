#----------------------------------------------------------------
#add_library_FFmpeg.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------
unix {
    equals(QKIT_, macOS){
    }
    else{
        INCLUDEPATH += /usr/include/x86_64-linux-gnu
        LIBS += -L/usr/lib/x86_64-linux-gnu -lavutil -lavcodec -lswscale -lswresample -lavformat
        LIBS += -lSDL2
    }
}
#未完成

#######################################################################################
#初始化设置
#######################################################################################
#4.0
LIBRARYVER =
DEBUG =
#这个地方，mingw比较特殊必须发布release版本，其他平台不清楚。
mingw:DEBUG=
contains(BUILD, Release) {
    DEBUG=
}

#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_path_FFmpeg){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_path_FFmpeg(path) requires one arguments.")

    command =
    #basic
    command += $${path}

    return ($$command)
}

defineTest(add_include_path_FFmpeg){
    #包含FFmpeg头文件的过程
    header_path = $$get_add_include_path(FFmpeg)
    INCLUDEPATH += $$get_add_include_path_FFmpeg($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_FFmpeg) {
    #链接Library
    add_library(FFmpeg, avcodec$${DEBUG}.58)
    add_library(FFmpeg, avdevice$${DEBUG}.58)
    add_library(FFmpeg, avfilter$${DEBUG}.7)
    add_library(FFmpeg, avformat$${DEBUG}.58)
    add_library(FFmpeg, avutil$${DEBUG}.56)
    add_library(FFmpeg, postproc$${DEBUG}.55)
    add_library(FFmpeg, swresample$${DEBUG}.3)
    add_library(FFmpeg, swscale$${DEBUG}.5)

    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接FFmpeg的WorkFlow
defineTest(add_link_library_FFmpeg) {
    #链接Library
    add_library_FFmpeg()

    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_path_FFmpeg()
    #这样包含也很好，简洁明了
    #add_include_path(FFmpeg, FFmpegQtCore)
    #add_include_path(FFmpeg, FFmpegQtWidgets)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library的函数
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_FFmpeg) {
    add_deploy_libraryes(FFmpeg)
    return (1)
}

defineTest(add_dependent_library_FFmpeg) {
    add_link_library_FFmpeg()
    add_deploy_library_FFmpeg()
    return (1)
}
