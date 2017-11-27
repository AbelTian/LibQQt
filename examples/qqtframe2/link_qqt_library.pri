#here is all your app common defination and configration
#you can modify this pri to link qqt_library

#this link need Qt Creator set default build directory, replace
#%{JS: Util.asciify("/your/local/path/to/build/root/%{CurrentProject:Name}/%{Qt:Version}/%{CurrentKit:FileSystemName}/%{CurrentBuild:Name}")}

#auto link QQt when build source
#auto copy QQt when deploy app

#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
equals(QMAKE_HOST.os, Darwin) {
    QQT_SOURCE_ROOT = $$PWD/../..
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_SOURCE_ROOT = $$PWD/../..
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_SOURCE_ROOT = $$PWD/../..
}

equals(QMAKE_HOST.os, Darwin) {
    QQT_BUILD_ROOT = /Users/abel/Develop/c0-buildstation
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_BUILD_ROOT = /home/abel/Develop/c0-buildstation
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_BUILD_ROOT = C:/Users/Administrator/Develop/c0-build
}

#default sdk path is qqt-source/../qqt-std-dir
#user can modify this path
equals(QMAKE_HOST.os, Darwin) {
    QQT_SDK_ROOT = $${QQT_SOURCE_ROOT}/..
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_SDK_ROOT = $${QQT_SOURCE_ROOT}/..
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_SDK_ROOT = $${QQT_SOURCE_ROOT}/..
}

#-------------------------------------------------------------
#include qqt's pri
#-------------------------------------------------------------
#qqt qkit
include($${QQT_SOURCE_ROOT}/src/qqt_qkit.pri)

#qqt version
include($${QQT_SOURCE_ROOT}/src/qqt_version.pri)

#qqt header
include($${QQT_SOURCE_ROOT}/src/qqt_header.pri)

#-------------------------------------------------------------
#link qqt settings: use source or link library?
#-------------------------------------------------------------
#if you want to build qqt source open this annotation
#CONFIG += LINK_QQT_SOURCE
contains (CONFIG, LINK_QQT_SOURCE) {
    #if you want to build src but not link QQt lib in your project
    #if you don't want to modify Qt Creator's default build directory, this maybe a choice.
    include($${QQT_SOURCE_ROOT}/src/qqt_source.pri)
} else {
    #if you want to link QQt library
    #qqt will install sdk to sdk path you set, then link it, or link from build station
    #qqt also can install sdk to qt library path, then to do that.
    #need QQT_BUILD_ROOT
    #need QKIT_PRIVATE from qqt_qkit.pri
    #you can open one or more macro to make sdk or link from build.
    #link from sdk is default setting
    CONFIG += link_from_sdk
    #CONFIG += link_from_build
    #especially some occations need some sure macro.
    contains(QKIT_PRIVATE, iOS|iOSSimulator) {
        #mac ios .framework .a 里面的快捷方式必须使用里面的相对路径，不能使用绝对路径
        #但是qtcreator生成framework的时候用了绝对路径，所以导致拷贝后链接失败，库不可用。
        #qqt_install.pri 里面解决了framework的拷贝问题，但是对于ios里.a的没做，而.a被拷贝了竟然也不能用！
        #在build的地方link就可以了
        CONFIG += link_from_build
    }

    include($${QQT_SOURCE_ROOT}/src/qqt_library.pri)
}

