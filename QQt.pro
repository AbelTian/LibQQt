##-----------------------------------------------------------------
##LibQQt主工程入口
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##-----------------------------------------------------------------
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro

##-----------------------------------------------------------------
##Q1级别 V1 第一版、第一代
##-----------------------------------------------------------------
#古老的链接LibQQt的方式废弃。
#App管理Application句柄的方式废弃。
#SUBDIRS += examples/qqtframe

#SUBDIRS += examples/animationframe
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
#方法：include(.../LibQQt/src/app_base_manager.pri)
#QQt提供QQtApplication帮助App管理Application句柄。
#SUBDIRS += examples/qqtframe2
#SUBDIRS += examples/exquisite
#SUBDIRS += examples/tabwidgetexamples
#need QZXing, default closed.
#SUBDIRS += examples/qrcodeexample
#SUBDIRS += examples/qqtnetworkexample
#greaterThan(QT_VERSION, 4.6.0):SUBDIRS += test/voicetest
#mac:lessThan(QT_MAJOR_VERSION , 5):SUBDIRS -= test/voicetest

#udp 嵌入式linux，Qt编译了udp支持，默认是支持的
#SUBDIRS += examples/qqtudpexample
#lessThan(QT_VERSION , 5.8.0):SUBDIRS -= examples/qqtudpexample
#SUBDIRS += examples/qqtchartexample
#
#SUBDIRS += examples/console_app
#-----------------------------------------------------------------
#need webaccessmanager - WebSupport
#need QSsl
#need GumoQuery
#-----------------------------------------------------------------
#greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += examples/QtSdkManager
#greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += demo/VegeTablesPrice
#SUBDIRS += examples/GuiBuildTool
#SUBDIRS += test/LearnCookieTest
#-----------------------------------------------------------------
#some test project
#SUBDIRS += test/gumbo_query_test
#SUBDIRS += test/svgtest
#SUBDIRS += test/customqvariant
#SUBDIRS += test/framelesshelperwidget
#SUBDIRS += test/treeviewtest
#SUBDIRS += test/qqtdicttest
#
SUBDIRS += test/qqtdicttest2
#SUBDIRS += test/bytearraytest
#!contains(QKIT_PRIVATE, iOS|iOSSimulator){
#    SUBDIRS += test/cmdwidget
#}
#SUBDIRS += test/coretest
#SUBDIRS += test/giftest
#SUBDIRS += test/tmpproj
#
#need QtSoap - WebSupport
##SUBDIRS += test/easter
#SUBDIRS += test/soapQQtOnline
#
##need bluetooth library
#greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += test/qqtbtfileserver

