##-----------------------------------------------------------------
##LibQQt主工程入口
##LibQQt R2只有QQt一个库,没有任何额外辅助库,建议仅仅用于嵌入式开发.
##
##不能随便编译，初始设置要求比较严格，请按照规程设置完整。
##-----------------------------------------------------------------
TEMPLATE = subdirs
CONFIG += ordered

#警告：如果发现编译面板里链接成功了，App程序死活说找不到-lLibName，去那个源文件，改一改源文件，只要有一点改动就可以链接成功。
#Windows系统里有这种bug，不确定是mingw编译器的还是系统的。

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
SUBDIRS += src/QQt.pro
