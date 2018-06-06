##-----------------------------------------------------------------
##LibQQt主工程入口
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##-----------------------------------------------------------------
TEMPLATE = subdirs
CONFIG += ordered

#这几个选项，自行决定，QQt一次编译完成两个版本。
#用户自行选择release还是debug版本使用即可。
#比较方便
#不会影响subdirs。
#CONFIG += debug_and_release
#CONFIG += build_all
#CONFIG += silent

#注意，这里用include，保证了路径直接在QQt.pro下边
#如果用SUBDIRS+=，会在子目录src里！
#但是，这里必须用subdirs，include有个特点，pro或者pri的PWD不是pro的路径，而是调用者的路径。
SUBDIRS += src/qqt.pro
