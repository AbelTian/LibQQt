##-----------------------------------------------------------------
##LibQQt样例工程入口
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##Example要编译，必须先编译完LibQQt
##本Library基于Multi-link技术，Example也是
##Example工程也就是App工程和Library工程不能放在一起编译，否则会引发 first time bug (add_deploy_library_on_mac).
##Library工程组和App工程组分开编译，不会引发这个bug。
##-----------------------------------------------------------------
TEMPLATE = subdirs

SUBDIRS =

#need webkit webkitwidgets - WebSupport
#webengine
#ignored
#lessThan(QT_MAJOR_VERSION , 5):SUBDIRS += test/qqtwebkittest
#lessThan(QT_MAJOR_VERSION , 5):SUBDIRS += test/qqtwebclient

#用于测试Multi-link对其他的lib的链接能力
#zh这个测试过程过于复杂。
#废弃
#SUBDIRS += test/QQtMultiLinkTest

#在subdirs里面添加一次add_base_manager.pri是否可以影响全部子工程？不会
#SUBDIRS += test/SubDirBaseManagerTest

########################################################################################
#支持添加开源的依赖项目
#这些工程用来测试添加依赖的成功与否
#所有的依赖添加pri都位于QQt/app-lib里，暂时除了QQt的不能移动，其他的pri都可以移动。
########################################################################################
########################################################################################
#Windows
#need OpenCV SDK
#SUBDIRS += examples/QQtOpenCVExample

#need OSG SDK
#need win SDK
#string is not a type?
#SUBDIRS += examples/QQtOpenSceneGraphExample

#need Qwt SDK
#SUBDIRS += test/QQtQwtTest

#need QwtPlot3D sdk
#SUBDIRS += test/QQtQwtPlot3DTest

#need FMOD lowlevel SDK
#SUBDIRS += test/QQtFMODTest

#need vlcQt libvlc library
#SUBDIRS += test/qqtliveplayer

########################################################################################
#macOS
#need log4cpp sdk
#macOS无故会记忆过去的链接位置，无解。
#SUBDIRS += test/qqtlog4cpptest

#need ffmpeg library
#SUBDIRS += test/qqtffmpegplayer

#测试libQQt的链接。
#
SUBDIRS += test/giftest

########################################################################################
#macOS Windows

