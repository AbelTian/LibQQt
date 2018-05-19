#------------------------------------------------------------------
#工程组织管理器
#包含：link libqqt；deploy app；deploy config files；
#App翻译 App版本 由App工程自行管理
#------------------------------------------------------------------

################################################################
##build cache (此处为中间目标目录，对用户并不重要)
##此处加以干涉，使目录清晰。
##此处关于DESTDIR的设置，导致用户必须把这个文件的包含，提前到最前边的位置，才能进行App里的目录操作。
##删除干涉?
##用户注意：(done in app_base_manager), 首先include(app_link_qqt_library.pri)，然后做app的工作，和include其他pri，包括LibQQt提供的其他pri，保证这个顺序就不会出错了。
##对编译目标目录进行干涉管理，显得更加细腻。
##用户注意：这里相当于给编译中间目录加了一个自动校准，属于校正范畴。
################################################################
OBJECTS_DIR = obj
MOC_DIR = obj/moc.cpp
UI_DIR = obj/ui.h
RCC_DIR = qrc
#这样做保持了App工程和LibQQt工程目录的一致性，但是并不必要。
DESTDIR = bin

################################################################
##administrator policy
##如果用户App需要管理员权限，那么打开这个CONFIG
################################################################
#CONFIG += administrator
contains(CONFIG, administrator){
    win32 {
        QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
    }
}

################################################################
##Multi-link technology
################################################################
include($$PWD/app_multi_link_technology.pri)

################################################################
##link QQt
################################################################
include($${PWD}/app_link_qqt_library.pri)

################################################################
##deploy app for install update deploy
##config defination
##依赖：DESTDIR APP_DEPLOY_ROOT
################################################################
#Qt4 is not a very good Cross Qt version, Qt5 suggest.
#if you have this request, include this pri in your app pro
include($${PWD}/app_deploy.pri)

################################################################
##deploy app config files for install update deploy
##config defination
#依赖 APP_CONFIG_PWD(in app pro) APP_DEPLOY_PWD(in app deploy)
################################################################
#if you have this request, include this pri in your app pro
include($${PWD}/app_deploy_config.pri)

################################################################
##config defination
################################################################
equals(QKIT_PRIVATE, macOS) {
    CONFIG += app_bundle
}

#-------------------------------------------------
#install app
#-------------------------------------------------
contains(QKIT_PRIVATE, EMBEDDED||MIPS32||ARM32) {
    target.path = /Application
    INSTALLS += target
}

#CONFIG += can_install
can_install: unix {
    equals(QKIT_PRIVATE, macOS) {
        target.path = /Applications
        INSTALLS += target
    }
}

#-------------------------------------------------
##project environ print
#-------------------------------------------------
#default ignore
#message ($${TARGET} config $${CONFIG})
#message ($${TARGET} define $${DEFINES})


