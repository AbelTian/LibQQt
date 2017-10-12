TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS +=  \
 src/qqt.pro \
 examples/qqtframe \
# examples/animationframe \
# examples/cmdwidget \
# examples/qqtliveplayer \
# examples/qqtffmpegplayer \
# examples/qqtftpclient \
# examples/qqthttpclient \
# examples/qqtwebkit
    examples/qqtframe2

#include(src/qqt.pri)
