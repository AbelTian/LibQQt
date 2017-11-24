TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro

##-----------------------------------------------------------------
##basic example
##-----------------------------------------------------------------
#SUBDIRS += examples/qqtframe
#SUBDIRS += examples/qqtframe2
#SUBDIRS += examples/qqtframe3
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
#SUBDIRS += examples/QtBuildTool
#SUBDIRS += examples/QtSdkManager
#SUBDIRS += examples/QQtInstaller
#SUBDIRS += examples/qqtnetworkexample

#
##can't support ios
#SUBDIRS += examples/qqtprintsupportexample
#
##-----------------------------------------------------------------
##need vlcQt libvlc library
##-----------------------------------------------------------------
##SUBDIRS += examples/qqtliveplayer
#
##-----------------------------------------------------------------
##need ffmpeg library
##-----------------------------------------------------------------
##SUBDIRS += examples/qqtffmpegplayer
#
##need bluetooth library
#SUBDIRS += examples/qqtbluetoothfiletransferserver
#

##-----------------------------------------------------------------
##need QtSoap - WebSupport
##-----------------------------------------------------------------
#SUBDIRS += examples/easter
#SUBDIRS += examples/soapQQtOnline
#
##-----------------------------------------------------------------
##need webkit webkitwidgets - WebSupport
##webengine
##-----------------------------------------------------------------
##SUBDIRS += examples/qqtwebkit
##SUBDIRS += examples/qqthttpclient
#
##-----------------------------------------------------------------
##need webaccessmanager - WebSupport
##need GumoQuery
##-----------------------------------------------------------------
#SUBDIRS += examples/qqtftpclient
#
greaterThan(QT_MAJOR_VERSION, 4):SUBDIRS += examples/qqthttpdownload
#greaterThan(QT_MAJOR_VERSION , 4):SUBDIRS += demo/VegeTablesPrice
#
##-----------------------------------------------------------------
##some example project
##maybe demo
##-----------------------------------------------------------------
#
#
#SUBDIRS += demo/cmdwidget
#
##-----------------------------------------------------------------
##some test project
##maybe demo
##-----------------------------------------------------------------
#SUBDIRS += test/gumbo_query_test
#SUBDIRS += test/svgtest
#SUBDIRS += test/framelesshelperwidget
#SUBDIRS += test/treeviewtest
