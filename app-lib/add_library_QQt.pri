################################################################
##add_library_QQt.pri
##link QQt
################################################################
#简介
#add link library 连接过程 用于源代码编写的时候。包括头文件和添加库
#add deploy library 编译过程 用于源代码编译的时候。发布库
#add dependent library 包括以上两个过程
#一般app才会使用add dependent library, lib使用add link library。
#到这里用户必须明白，连接概念到不了app，lib里才有链接概念。
#依赖概念才会在app里出现。
#这是重点。

#######################################################################################
#初始化设置
#######################################################################################
#包含QQt的宏。
#头文件其实没多大作用。只是提供路劲
include ($${PWD}/../src/qqt_header.pri)

#######################################################################################
#定义内部函数
#######################################################################################
#把QQt SDK头文件路径加入进来 为搜索头文件而添加
#其实过去做的自动添加QQt头文件就是这个功能
#用户包含QQt头文件，就不必加相对路径了，方便了很多
defineTest(add_header_QQt){
    #包含QQt头文件的过程
    header_path = $$get_add_header(QQt)
    INCLUDEPATH += $$get_qqt_header($$header_path)
    export(INCLUDEPATH)
    return (1)
}


defineTest(add_library_QQt){
    #链接QQt
    add_library(QQt)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接QQt
#用户只需要调用这个函数，一个，就能开启链接QQt 包含QQt 跟随App发布QQt三个步骤的App生产线工位。
defineTest(add_link_library_QQt){
    #细心的用户会发现，QQt的头文件包含了两次，一个在源代码目录里，一个在SDK目录里，两个并不冲突。系统只要搜索到一个目录里的就可以使用了。
    #当然，我们确信，SDK目录里的头文件服从于源代码目录里的头文件。
    #包含QQt的头文件
    add_header_QQt()
    #链接（lib)
    add_library_QQt()
    return (1)
}

#以上代码只完成了链接libQQt 包含libQQt头文件 包含libQQt宏文件(在宏文件控制下Library的头文件才有精确的意义)
#没有发布libQQt
#App在开发中，调用发布App以后 必然需要调用add_deploy_library(QQt)发布QQt到运行时。强大的：从sdk发布到build和deploy位置。
#调试，正常；发布运行，正常。
#:) 方便函数
defineTest(add_deploy_library_QQt){
    add_deploy_library(QQt)
    return (1)
}

defineTest(add_dependent_library_QQt){
    add_link_library_QQt()
    add_deploy_library_QQt()
    return (1)
}
