################################################################
##add_library_QQt.pri
##link QQt
################################################################
#包含QQt的宏。
#头文件其实没多大作用。只是提供路劲
include ($${PWD}/../src/qqt_header.pri)

#把QQt SDK头文件路径加入进来 为搜索头文件而添加
#其实过去做的自动添加QQt头文件就是这个功能
#用户包含QQt头文件，就不必加相对路径了，方便了很多
defineTest(add_qqt_header){
    #包含QQt头文件的过程
    header_path = $$get_add_header(QQt)
    INCLUDEPATH += $$get_qqt_header($$header_path)
    export(INCLUDEPATH)
    return (1)
}

#包含QQt的头文件
add_qqt_header()

#细心的用户会发现，QQt的头文件包含了两次，一个在源代码目录里，一个在SDK目录里，两个并不冲突。系统只要搜索到一个目录里的就可以使用了。
#当然，我们确信，SDK目录里的头文件服从于源代码目录里的头文件。

#链接QQt
add_library(QQt)

#以上代码只完成了链接libQQt 包含libQQt头文件 包含libQQt宏文件(在宏文件控制下Library的头文件才有精确的意义)
#没有发布libQQt
#App在开发中，调用发布App以后 必然需要调用add_deploy_library(QQt)发布QQt到运行时。强大的：从sdk发布到build和deploy位置。
#调试，正常；发布运行，正常。
#:) 方便函数
defineTest(add_deploy_library_QQt){
    add_deploy_library(QQt)
    return (1)
}
