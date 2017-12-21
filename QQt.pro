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
#
SUBDIRS += test/svgtest
#SUBDIRS += test/framelesshelperwidget
#SUBDIRS += test/treeviewtest
#SUBDIRS += test/qqtdicttest
#!contains(QKIT_PRIVATE, iOS|iOSSimulator){
#    SUBDIRS += test/cmdwidget
#}
#SUBDIRS += test/coretest
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

