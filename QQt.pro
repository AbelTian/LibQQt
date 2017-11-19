TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro
#-----------------------------------------------------------------
#basic example
#-----------------------------------------------------------------
#SUBDIRS += examples/framelesshelperwidget
#SUBDIRS += examples/qqtframe
#SUBDIRS += examples/animationframe
#SUBDIRS += examples/qqtnetworkexample
#SUBDIRS += examples/qqtframe2

#-----------------------------------------------------------------
#QQt installed to Qt library or
#QQt installed to sdk or
#QQt is build
#-----------------------------------------------------------------
#SUBDIRS += examples/qqtframe3
#SUBDIRS += examples/exquisite
#can't support ios
#SUBDIRS += examples/qqtprintsupportexample
#
SUBDIRS += examples/tabwidgetexamples
#SUBDIRS += examples/svgtest
#SUBDIRS += examples/treeviewexample

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
#SUBDIRS += examples/qqtftpclient
#SUBDIRS += examples/qqthttpclient
#SUBDIRS += examples/qqtwebkit

#-----------------------------------------------------------------
#some example project
#maybe demo
#-----------------------------------------------------------------
#SUBDIRS += examples/cmdwidget
#SUBDIRS += examples/VegeTablesPrice
#SUBDIRS += examples/QtBuildTool
#SUBDIRS += examples/QtSdkManager
#SUBDIRS += examples/QQtInstaller
