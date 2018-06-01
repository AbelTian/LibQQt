##-----------------------------------------------------------------
##LibQQt主工程入口
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##-----------------------------------------------------------------
#TEMPLATE = subdirs
#CONFIG += ordered

#这几个选项，自行决定，QQt一次编译完成两个版本。
#用户自行选择release还是debug版本使用即可。
#比较方便
CONFIG += debug_and_release
CONFIG += build_all
#CONFIG += silent

include(src/qqt.pri)
