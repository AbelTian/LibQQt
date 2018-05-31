#----------------------------------------------------------------
#add_custom_manager.pri
#这个文件用于给用户自定义管理内容，随意添加自己所需要的library、defines、config等等。
#拷贝到用户app工程目录里使用用
#----------------------------------------------------------------
THIS_PRI_PWD = $${PWD}

################################################################
##基础使用方法
################################################################
#添加app版本
#add_version (1,0,0,0)

#添加依赖library
#add_library(xx)
#add_header(xx)
#add_defines(xx)

#先发布App
#app从build到deploy
#add_deploy()

#后发布依赖
#lib从sdk到build和deploy
#add_deploy_library(xx)

############################################################################################################
#对产品线的控制结构Multi-link下命令 开启产品线
############################################################################################################
#管理内置依赖的函数
#用户可以依照模板增加内置依赖，这样使用更方便。

#################################################################
##此处代码完成包含(链接+发布)libQQt的函数
#include(add_library_QQt.pri)
#add_dependent
##这里是对QQt的lib的支持。
##这个支持是有条件的：如果用户移动了Multi-link技术文件夹，那么不再自动加入支持，用户需要手动include(add_library_QQt.pri)，和使用其他的lib一样。
##这个支持有个特点，因为LibQQt是开源的，所以这个pri依赖了qqt_header.pri，所以这个pri不能移动，一旦移动就会失去效果。
#如此支持。使用函数
#后续会脱离qqt_header.pri
#################################################################
defineTest(add_dependent_manager_QQt){
    !equals(TARGET_PRIVATE, QQt):
        exists($${THIS_PRI_PWD}/../app-lib/add_library_QQt.pri):
        exists($${THIS_PRI_PWD}/../src/core/qqtcore.cpp) {
        include ($${THIS_PRI_PWD}/../app-lib/add_library_QQt.pri)
        contains(TEMPLATE, app):add_dependent_library_QQt()
        else:contains(TEMPLATE, lib):add_link_library_QQt()
        else:add_link_library_QQt()
    }
    return (1)
}

defineTest(add_dependent_manager_Qwt){
    !equals(TARGET_PRIVATE, Qwt):
        exists($${THIS_PRI_PWD}/../app-lib/add_library_Qwt.pri){
        include ($${THIS_PRI_PWD}/../app-lib/add_library_Qwt.pri)
        contains(TEMPLATE, app):add_dependent_library_Qwt()
        else:contains(TEMPLATE, lib):add_link_library_Qwt()
        else:add_link_library_Qwt()
    }
    return (1)
}

defineTest(add_dependent_manager_OpenCV){
    !equals(TARGET_PRIVATE, OpenCV):
        exists($${THIS_PRI_PWD}/../app-lib/add_library_OpenCV.pri){
        include ($${THIS_PRI_PWD}/../app-lib/add_library_OpenCV.pri)
        contains(TEMPLATE, app):add_dependent_library_OpenCV()
        else:contains(TEMPLATE, lib):add_link_library_OpenCV()
        else:add_link_library_OpenCV()
    }
    return (1)
}

defineTest(add_dependent_manager_OpenSceneGraph){
    !equals(TARGET_PRIVATE, OpenSceneGraph):
        exists($${THIS_PRI_PWD}/../app-lib/add_library_OpenSceneGraph.pri){
        include ($${THIS_PRI_PWD}/../app-lib/add_library_OpenSceneGraph.pri)
        contains(TEMPLATE, app):add_dependent_library_OpenSceneGraph()
        else:contains(TEMPLATE, lib):add_link_library_OpenSceneGraph()
        else:add_link_library_OpenSceneGraph()
    }
    return (1)
}
