#here is all your app common defination and configration
#you can modify this pri to link qqt_library

equals(QMAKE_HOST.os, Darwin) {
    QQT_SOURCE_ROOT = $$PWD/../../
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_SOURCE_ROOT = $$PWD/../../
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_SOURCE_ROOT = $$PWD/../../
}

#qqt qkit
include($${QQT_SOURCE_ROOT}/src/qqt_kit.pri)

#qqt version
include($${QQT_SOURCE_ROOT}/src/qqt_version.pri)

#link QQt static library in some occation
equals(QKIT_PRIVATE, WIN32) {
    #when Qt is static by mingw32 building 5.9.1
    equals(QT_VERSION, 5.9.1){
        DEFINES += QQT_STATIC_LIBRARY
    }
}

contains(DEFINES, QQT_STATIC_LIBRARY) {
    DEFINES += QCUSTOMPLOT_STATIC_LIBRARY
    DEFINES += QZXING_STATIC_LIBRARY
    DEFINES += QT_QTSOAP_STATIC_LIBRARY
    DEFINES += BUILD_QDEVICEWATCHER_STATIC
}

#qqt header
include($${QQT_SOURCE_ROOT}/src/qqt_header.pri)

#qqt library or qqt source
#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in your project
    include($${QQT_SOURCE_ROOT}/src/qqt_source.pri)
} else {
    #QKIT_PRIVATE from qqt_header.pri
    contains(QKIT_PRIVATE, WIN32|WIN64) {
        CONFIG += link_from_build
    } else:contains(QKIT_PRIVATE, iOS|iOSSimulator) {
        #mac ios .framework .a 里面的快捷方式必须使用里面的相对路径，不能使用绝对路径
        #但是qtcreator生成framework的时候用了绝对路径，所以导致拷贝后链接失败，库不可用。
        #qqt_install.pri 里面解决了framework的拷贝问题，但是对于ios里.a的没做，而.a被拷贝了竟然也不能用！
        #在build的地方link就可以了
        CONFIG += link_from_build
    } else{
        #default
        CONFIG += link_from_sdk
    }

    contains(CONFIG, link_from_build) {
        equals(QMAKE_HOST.os, Darwin) {
            QQT_BUILD_ROOT = /Users/abel/Develop/c0-buildstation
        } else: equals(QMAKE_HOST.os, Linux) {
            QQT_BUILD_ROOT = /home/abel/Develop/c0-buildstation
        } else: equals(QMAKE_HOST.os, Windows) {
            QQT_BUILD_ROOT = C:/Users/Administrator/Develop/c0-build
        }
    }

    #if you want to link QQt library
    include($${QQT_SOURCE_ROOT}/src/qqt_library.pri)
}
