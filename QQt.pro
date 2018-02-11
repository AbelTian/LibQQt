##-----------------------------------------------------------------
##LibQQt主工程入口
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##-----------------------------------------------------------------
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro

##-----------------------------------------------------------------
##basic example
##-----------------------------------------------------------------
#SUBDIRS += examples/qqtframe
#SUBDIRS += examples/qqtframe2
#SUBDIRS += examples/animationframe
#
##-----------------------------------------------------------------
##QQt installed to Qt library or
##QQt installed to sdk or
##QQt is build
##-----------------------------------------------------------------
#SUBDIRS += examples/exquisite
#SUBDIRS += examples/tabwidgetexamples
#SUBDIRS += examples/qrcodeexample
#SUBDIRS += examples/qqtnetworkexample
#udp 嵌入式linux，Qt编译了udp后支持
#SUBDIRS += examples/qqtudpexample
#SUBDIRS += examples/qqtchartexample
#
#
##-----------------------------------------------------------------
##need webaccessmanager - WebSupport
##need QSsl
##need GumoQuery
##-----------------------------------------------------------------
#greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += examples/QtSdkManager
#greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += demo/VegeTablesPrice
#SUBDIRS +=     examples/GuiBuildTool
##-----------------------------------------------------------------
##some test project
##-----------------------------------------------------------------
#SUBDIRS += test/gumbo_query_test
#SUBDIRS += test/svgtest
#SUBDIRS += test/customqvariant
#SUBDIRS += test/framelesshelperwidget
#SUBDIRS += test/treeviewtest
#SUBDIRS += test/qqtdicttest
#SUBDIRS += test/qqtdicttest2
#SUBDIRS += test/consoletest
#
SUBDIRS += test/voicetest

#!contains(QKIT_PRIVATE, iOS|iOSSimulator){
#    SUBDIRS += test/cmdwidget
#}
#SUBDIRS += test/coretest
#
SUBDIRS += test/giftest
#
##-----------------------------------------------------------------
##need webkit webkitwidgets - WebSupport
##webengine
##ignored
##-----------------------------------------------------------------
##lessThan(QT_MAJOR_VERSION , 5):SUBDIRS += test/qqtwebkittest
##lessThan(QT_MAJOR_VERSION , 5):SUBDIRS += test/qqtwebclient
##-----------------------------------------------------------------
##need QtSoap - WebSupport
##-----------------------------------------------------------------
#SUBDIRS += test/easter
#SUBDIRS += test/soapQQtOnline
##-----------------------------------------------------------------
##need vlcQt libvlc library
##-----------------------------------------------------------------
##SUBDIRS += test/qqtliveplayer
#
##-----------------------------------------------------------------
##need ffmpeg library
##-----------------------------------------------------------------
##SUBDIRS += test/qqtffmpegplayer
#
##need bluetooth library
#greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += test/qqtbtfileserver

