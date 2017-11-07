#here is all your app common defination and configration
#you can modify this pri to link qqt_library

equals(QMAKE_HOST.os, Darwin) {
    QQT_SOURCE_ROOT = /Users/abel/Develop/a0-develop/a0-qqtfoundation
} else: equals(QMAKE_HOST.os, Linux) {
    QQT_SOURCE_ROOT = /home/abel/Develop/a0-develop/LibQt
} else: equals(QMAKE_HOST.os, Windows) {
    QQT_SOURCE_ROOT = C:/Users/Administrator/Develop/a0-develop/LibQt
}

#qqt version
include($${QQT_SOURCE_ROOT}/src/qqt_version.pri)

#qqt header
include($${QQT_SOURCE_ROOT}/src/qqt_header.pri)

#qqt library or qqt source
#CONFIG += BUILD_SRC
contains (CONFIG, BUILD_SRC) {
    #if you want to build src but not link QQt in this project
    include($${QQT_SOURCE_ROOT}/src/qqt_source.pri)
} else {
    #QKIT_PRIVATE from qqt_header.pri
    !contains(QKIT_PRIVATE, WIN32|WIN64) {
        #default
        CONFIG += link_from_sdk
    } else {
        CONFIG += link_from_build
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

