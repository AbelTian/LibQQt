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

##-----------------------------------------------------------------
##Q1级别 V1 第一版、第一代
##-----------------------------------------------------------------
#古老的链接LibQQt的方式废弃。
#App管理Application句柄的方式废弃。
#
SUBDIRS += examples/qqtframe

#
SUBDIRS += examples/animationframe
#
#need vlcQt libvlc library
#SUBDIRS += test/qqtliveplayer
#need ffmpeg library
#SUBDIRS += test/qqtffmpegplayer

#need webkit webkitwidgets - WebSupport
#webengine
#ignored
#lessThan(QT_MAJOR_VERSION , 5):SUBDIRS += test/qqtwebkittest
#lessThan(QT_MAJOR_VERSION , 5):SUBDIRS += test/qqtwebclient

#-----------------------------------------------------------------
#Q3级别 V2 第二版、第二代
#QQt installed to Qt library or
#QQt installed to sdk or
#QQt is build
#-----------------------------------------------------------------
#第二种引用LibQQt的方式
#方法：include(.../LibQQt/multi-link/multi-link/add_base_manager.pri)
#QQt提供QQtApplication帮助App管理Application句柄。
#
SUBDIRS += examples/qqtframe2
#必看
#
SUBDIRS += examples/exquisite
#
SUBDIRS += examples/tabwidgetexamples
#need QZXing, default closed.
#SUBDIRS += examples/qrcodeexample

#
SUBDIRS += examples/qqtchartexample
#
#
SUBDIRS += examples/console_app
#-----------------------------------------------------------------
#need webaccessmanager - WebSupport
#need QSsl
#need GumoQuery
#-----------------------------------------------------------------
#
greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += demo/QtSdkManager
#
greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += demo/VegeTablesPrice
#
SUBDIRS += demo/GuiBuildTool
#
SUBDIRS += demo/LearnCookieTest
#-----------------------------------------------------------------
#some test project
#
SUBDIRS += test/gumbo_query_test
#
SUBDIRS += test/customqvariant
#
SUBDIRS += test/framelesshelperwidget
#
SUBDIRS += test/treeviewtest
#
SUBDIRS += test/bytearraytest
#
!contains(QSYS_PRIVATE, iOS|iOSSimulator){
#
    SUBDIRS += test/cmdwidget
#
}
#
SUBDIRS += test/coretest
#不要开
#SUBDIRS += test/tmpproj

#
#need QtSoap - WebSupport
##
SUBDIRS += test/easter
#
SUBDIRS += demo/soapQQtOnline
#
##need bluetooth library
#
greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += test/qqtbtfileserver

#0000
#
SUBDIRS += test/svgtest
#
SUBDIRS += test/qqtdicttest
#必开
#
SUBDIRS += test/qqtdicttest2
#必开
#
SUBDIRS += test/giftest

#必开 这两个例子是关于QQtAudio的最好展示
#
SUBDIRS += examples/qqtaudioexample
#111111
#
greaterThan(QT_VERSION, 4.6.0):SUBDIRS += test/voicetest
#
mac:lessThan(QT_MAJOR_VERSION , 5):SUBDIRS -= test/voicetest

#网络创建工具
#
SUBDIRS += demo/QQtClientCreator
#
SUBDIRS += demo/QQtServerCreator
#这边是个组合项，客户端和服务器一起的。必看
#
SUBDIRS += examples/qqtclientexample
#
SUBDIRS += examples/qqtserverexample
#通信协议的复杂的例子
#
SUBDIRS += examples/qqtnetworkexample

#udp 嵌入式linux，Qt编译了udp支持，默认是支持的
#
SUBDIRS += examples/qqtudpexample
#
lessThan(QT_VERSION , 5.8.0):SUBDIRS -= examples/qqtudpexample

#-----------------------------------------------------------------
#Q5级别 V2 第三版、第二代
#和QQt脱离开的Multi-link技术
#默认链接QQt，但是可以容易的脱开。
#-----------------------------------------------------------------
#
SUBDIRS += test/openglwidgettest
#
SUBDIRS += test/osdtest
#
SUBDIRS += test/inputtest
#
SUBDIRS += demo/SysInfoNotify

#
SUBDIRS += test/QQtWidgetClickHelperTest
#
SUBDIRS += test/QQtWidgetClickSoundHelperTest

