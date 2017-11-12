TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro
#-----------------------------------------------------------------
#basic example
#-----------------------------------------------------------------
#SUBDIRS += examples/framelesshelperwidget
#SUBDIRS += examples/qqtframe
#SUBDIRS += examples/animationframe
#SUBDIRS += examples/cmdwidget
#SUBDIRS += examples/qqtnetworkexample
#
SUBDIRS += examples/exquisite
#SUBDIRS += examples/QtBuildTool
#SUBDIRS += examples/QtSdkManager
#SUBDIRS += examples/QQtInstaller
#SUBDIRS += examples/qqtframe2

#-----------------------------------------------------------------
#need QQt installed to Qt library or
#need QQt installed to sdk
#-----------------------------------------------------------------
#SUBDIRS += examples/qqtframe3
#SUBDIRS += examples/VegeTablesPrice
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
#open SUBDIRS += examples/qqtbluetoothfiletransferserver

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
