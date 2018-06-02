#----------------------------------------------------------------
#add_library_OpenSceneGraph.pri
#这是给用户提供的方便pri
#这个比较common，允许拷贝到用户工程中更改。
#----------------------------------------------------------------

#######################################################################################
#初始化设置
#######################################################################################
#3.4
LIBRARYVER =
DEBUG = d
contains(BUILD, Release) {
    DEBUG=
}

#######################################################################################
#定义内部函数
#######################################################################################
defineReplace(get_add_include_path_OpenSceneGraph){
    path = $$1
    isEmpty(1)|!isEmpty(2) : error("get_add_include_path_OpenSceneGraph(path) requires one arguments.")

    command =
    #basic
    command += $${path}
    command += $${path}/OpenThreads
    command += $${path}/osg
    command += $${path}/osgAnimation
    command += $${path}/osgDB
    command += $${path}/osgFX
    command += $${path}/osgGA
    command += $${path}/osgManipulator
    command += $${path}/osgParticle
    command += $${path}/osgPresentation
    command += $${path}/osgQt
    command += $${path}/osgShadow
    command += $${path}/osgSim
    command += $${path}/osgTerrain
    command += $${path}/osgText
    command += $${path}/osgUI
    command += $${path}/osgUtil
    command += $${path}/osgViewer
    command += $${path}/osgVolume
    command += $${path}/osgWidget

    return ($$command)
}

defineTest(add_include_path_OpenSceneGraph){
    #包含OpenSceneGraph头文件的过程
    header_path = $$get_add_include_path(OpenSceneGraph, , , , "qtversionpath")
    INCLUDEPATH += $$get_add_include_path_OpenSceneGraph($$header_path)
    export(INCLUDEPATH)
    return (1)
}

defineTest(add_library_OpenSceneGraph) {
    #添加Library路径
    add_library_path(OpenSceneGraph, , , "qtversionpath")
    #链接Library
    add_library(OpenThreads$${LIBRARYVER}$${DEBUG})
    add_library(osg$${LIBRARYVER}$${DEBUG})
    add_library(osgAnimation$${LIBRARYVER}$${DEBUG})
    add_library(osgDB$${LIBRARYVER}$${DEBUG})
    add_library(osgFX$${LIBRARYVER}$${DEBUG})
    add_library(osgGA$${LIBRARYVER}$${DEBUG})
    add_library(osgManipulator$${LIBRARYVER}$${DEBUG})
    add_library(osgParticle$${LIBRARYVER}$${DEBUG})
    add_library(osgPresentation$${LIBRARYVER}$${DEBUG})
    add_library(osgQt$${LIBRARYVER}$${DEBUG})
    add_library(osgShadow$${LIBRARYVER}$${DEBUG})
    add_library(osgSim$${LIBRARYVER}$${DEBUG})
    add_library(osgTerrain$${LIBRARYVER}$${DEBUG})
    add_library(osgText$${LIBRARYVER}$${DEBUG})
    add_library(osgUI$${LIBRARYVER}$${DEBUG})
    add_library(osgUtil$${LIBRARYVER}$${DEBUG})
    add_library(osgViewer$${LIBRARYVER}$${DEBUG})
    add_library(osgVolume$${LIBRARYVER}$${DEBUG})
    add_library(osgWidget$${LIBRARYVER}$${DEBUG})
    return (1)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接OpenSceneGraph的WorkFlow
defineTest(add_link_library_OpenSceneGraph) {
    #链接Library
    add_library_OpenSceneGraph()

    #添加头文件 （如果头文件目录扩展了，就改这个函数）
    add_include_path_OpenSceneGraph()
    #这样包含也很好，简洁明了
    #add_include_path(OpenSceneGraph, OpenSceneGraphQtCore)
    #add_include_path(OpenSceneGraph, OpenSceneGraphQtWidgets)
    #...

    #添加宏定义
    #add_defines(xx)
    return (1)
}

#发布依赖library的函数
#注意Android也需要这个函数，使用这个函数Android才会发布Library到运行时。上边的只是链接作用。
defineTest(add_deploy_library_OpenSceneGraph) {
    add_deploy_libraryes(OpenSceneGraph, , , , "qtversionpath")
    add_deploy_library(OpenSceneGraph, osgQt$${LIBRARYVER}$${DEBUG}, , , "qtversionpath", "deployqt")
    return (1)
}

defineTest(add_dependent_library_OpenSceneGraph) {
    add_link_library_OpenSceneGraph()
    add_deploy_library_OpenSceneGraph()
    return (1)
}
