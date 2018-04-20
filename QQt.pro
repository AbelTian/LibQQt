##-----------------------------------------------------------------
##LibQQt主工程入口
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##-----------------------------------------------------------------
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src/qqt.pro \
    test/openglwidgettest
SUBDIRS += QQtExample.pro
