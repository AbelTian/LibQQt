TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS =
SUBDIRS += src/qqt.pro
SUBDIRS += examples/framelesshelperwidget
SUBDIRS += examples/qqtframe
SUBDIRS += examples/qqtframe2
SUBDIRS += examples/animationframe
SUBDIRS += examples/cmdwidget
SUBDIRS += examples/qqtbluetoothfiletransferserver
SUBDIRS += examples/qqtnetworkexample
SUBDIRS += examples/exquisite
SUBDIRS += examples/QtBuildTool
SUBDIRS += examples/QtSdkManager

#need vlcQt libvlc library
#SUBDIRS += examples/qqtliveplayer

#need ffmpeg library
#SUBDIRS += examples/qqtffmpegplayer

#need webkitwidgets
#SUBDIRS += examples/qqtftpclient
#SUBDIRS += examples/qqthttpclient
#SUBDIRS += examples/qqtwebkit
