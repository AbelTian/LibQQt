TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro
SUBDIRS += examples/framelesshelperwidget
SUBDIRS += examples/qqtframe
SUBDIRS += examples/qqtframe2
SUBDIRS += examples/animationframe
SUBDIRS += examples/cmdwidget
SUBDIRS += examples/qqtnetworkexample
SUBDIRS += examples/exquisite
SUBDIRS += examples/QtBuildTool
SUBDIRS += examples/QtSdkManager
SUBDIRS += examples/QQtInstaller

#need QQt installed to Qt library
SUBDIRS += examples/qqtframe3

#need bluetooth library
#SUBDIRS += examples/qqtbluetoothfiletransferserver

#need vlcQt libvlc library
#SUBDIRS += examples/qqtliveplayer

#need ffmpeg library
#SUBDIRS += examples/qqtffmpegplayer

#need webkitwidgets - WebSupport
#SUBDIRS += examples/qqtftpclient
#SUBDIRS += examples/qqthttpclient
#SUBDIRS += examples/qqtwebkit
#need QtSoap - WebSupport
#SUBDIRS += examples/easter
#SUBDIRS += examples/soapQQtOnline
