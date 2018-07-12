##-----------------------------------------------------------------
##LibQQt样例工程入口
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##Example要编译，必须先编译完LibQQt
##本Library基于Multi-link技术，Example也是
##Example工程也就是App工程和Library工程不能放在一起编译，否则会引发 first time bug (add_deploy_library_on_mac).
##Library工程组和App工程组分开编译，不会引发这个bug。
##-----------------------------------------------------------------
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += test/singletonapptest
#SUBDIRS += demo/QQtClientCreator
#SUBDIRS += demo/QQtServerCreator
#SUBDIRS += test/sharedmemorytest
#SUBDIRS += test/QQtCustomTitleBarMainFormTest
#SUBDIRS += demo/QQtRoseMonitor
#SUBDIRS += examples/exquisite
#SUBDIRS += test/voicetest
#SUBDIRS += test/giftest
