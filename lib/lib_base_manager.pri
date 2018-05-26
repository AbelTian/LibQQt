#------------------------------------------------------------------
#工程组织管理器
#包含：link libqqt；deploy lib；deploy lib config files；
#Lib翻译 Lib版本 由Lib工程自行管理
#用于帮助用户基于LibQQt编写Lib程序
#------------------------------------------------------------------
################################################################
##lib 的 config defination 先一步设置好
################################################################
contains(CONFIG, mac) {
    CONFIG += lib_bundle
}

################################################################
##administrator policy
##如果用户Lib需要管理员权限，那么打开这个CONFIG
################################################################
#CONFIG += administrator
contains(CONFIG, administrator){
    win32 {
        QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
    }
}

################################################################
##build cache (此处为中间目标目录，对用户并不重要)
##此处加以干涉，使目录清晰。
##此处关于DESTDIR的设置，导致用户必须把这个文件的包含，提前到最前边的位置，才能进行App里的目录操作。
##删除干涉?
##用户注意：(done in lib_base_manager), 首先include(lib_link_qqt_library.pri)，然后做lib的工作，和include其他pri，包括LibQQt提供的其他pri，保证这个顺序就不会出错了。
##对编译目标目录进行干涉管理，显得更加细腻。
##用户注意：这里相当于给编译中间目录加了一个自动校准，属于校正范畴。
################################################################
OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
#这样做保持了Lib工程和LibQQt工程目录的一致性，但是并不必要。
DESTDIR = bin

################################################################
##Multi-link technology
################################################################
include($$PWD/lib_multi_link_technology.pri)

################################################################
##link QQt
################################################################
include($${PWD}/lib_link_qqt_library.pri)

################################################################
##用户lib链接其他Library的函数库
################################################################
include ($$PWD/lib_multi_link_function.pri)

################################################################
##deploy lib to sdk path
##config defination
##依赖 QQT_SDK_ROOT DESTDIR(can set)
################################################################
#Qt4 is not a very good Cross Qt version, Qt5 suggest.
#if you have this request, include this pri in your app pro
include($${PWD}/lib_deploy.pri)

################################################################
##deploy lib config files to config path
##config defination
##in sdk path root/libname/xx/xx/xx/config 与include、lib目录平行
#依赖 QQT_SDK_ROOT DESTDIR(can set)
################################################################
#if you have this request, include this pri in your app pro
#include($${PWD}/lib_deploy_config.pri)


#-------------------------------------------------
#install lib
#-------------------------------------------------
contains(QKIT_PRIVATE, Embedded||Mips32||Arm32) {
    target.path = /Application
    INSTALLS += target
}

#-------------------------------------------------
##project environ print
#-------------------------------------------------
#default ignore
message ($${TARGET} config $${CONFIG})
message ($${TARGET} define $${DEFINES})

message ($${TARGET} QMAKE_PRE_LINK $${QMAKE_PRE_LINK})
message ($${TARGET} QMAKE_POST_LINK $${QMAKE_POST_LINK})


