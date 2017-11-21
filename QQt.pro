TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro

#-----------------------------------------------------------------
#basic example
#-----------------------------------------------------------------
#SUBDIRS += examples/qqtframe
#SUBDIRS += examples/qqtframe2
#SUBDIRS += examples/qqtframe3
#SUBDIRS += examples/animationframe

#-----------------------------------------------------------------
#QQt installed to Qt library or
#QQt installed to sdk or
#QQt is build
#-----------------------------------------------------------------
#
SUBDIRS += examples/exquisite
#SUBDIRS += examples/tabwidgetexamples
#SUBDIRS += examples/qrcodeexample
#SUBDIRS += examples/qqtnetworkexample
#SUBDIRS += examples/QtBuildTool
#SUBDIRS += examples/QtSdkManager
#SUBDIRS += examples/QQtInstaller

#can't support ios
#SUBDIRS += examples/qqtprintsupportexample

#-----------------------------------------------------------------
#need vlcQt libvlc library
#-----------------------------------------------------------------
#SUBDIRS += examples/qqtliveplayer

#-----------------------------------------------------------------
#need ffmpeg library
#-----------------------------------------------------------------
#SUBDIRS += examples/qqtffmpegplayer

#need bluetooth library
#SUBDIRS += examples/qqtbluetoothfiletransferserver

#-----------------------------------------------------------------
#need QtSoap - WebSupport
#-----------------------------------------------------------------
#SUBDIRS += examples/easter
#SUBDIRS += examples/soapQQtOnline

#-----------------------------------------------------------------
#need webkitwidgets - WebSupport
#webkit webengine
#-----------------------------------------------------------------
#SUBDIRS += examples/qqtwebkit

#-----------------------------------------------------------------
#need webwork - WebSupport
#-----------------------------------------------------------------
#SUBDIRS += examples/qqtftpclient
#SUBDIRS += examples/qqthttpclient

#-----------------------------------------------------------------
#some example project
#maybe demo
#-----------------------------------------------------------------
#SUBDIRS += demo/VegeTablesPrice
#SUBDIRS += demo/cmdwidget

#-----------------------------------------------------------------
#some test project
#maybe demo
#-----------------------------------------------------------------
#SUBDIRS += test/gumbo_query_test
#SUBDIRS += test/svgtest
#SUBDIRS += test/framelesshelperwidget
#SUBDIRS += test/treeviewtest
