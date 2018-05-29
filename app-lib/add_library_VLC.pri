#----------------------------------------------------------------
#add_library_VLC.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#添加依赖library
LIBRARYVER =
DEBUG = d
#这个地方，mingw比较特殊必须发布release版本，其他平台不清楚。
mingw:DEBUG=
contains(BUILD, Release) {
    DEBUG=
}

add_library(VLC, VLCQtCore$${LIBRARYVER}$${DEBUG})
add_library(VLC, VLCQtWidgets$${LIBRARYVER}$${DEBUG})

#添加头文件 （如果头文件目录扩展了，就改这个函数）
defineReplace(get_vlc_header){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_vlc_header(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    command += $${path}/VLCQtCore
    command += $${path}/VLCQtWidgets

    return ($$command)
}

defineTest(add_vlc_header){
    #包含VLC头文件的过程
    header_path = $$get_add_header(VLC)
    INCLUDEPATH += $$get_vlc_header($$header_path)
    export(INCLUDEPATH)
    return (1)
}

add_vlc_header()

#这样包含也很好，简洁明了
#add_header(VLC, VLCQtCore)
#add_header(VLC, VLCQtWidgets)
#...

#添加宏定义
#add_defines(xx)

#发布依赖library
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_VLC) {
    add_deploy_libraries(VLC)
}
