#-------------------------------------------------------
#qqt_3rdparty.pri
#这个文件用于指示版权。
#-------------------------------------------------------
#inifile
#注释：在qqt_header.pri打开 DEFINES += __INICONTENTSUPPORT__
DEFINES += __INICONTENTSUPPORT__
contains (DEFINES, __INICONTENTSUPPORT__) {
    INCLUDEPATH += $$PWD/core/inifile
    SOURCES += $$PWD/core/inifile/inifile.cpp \
            $$PWD/core/inifile/qqtiniparser.cpp
    HEADERS += $$PWD/core/inifile/inifile.h \
            $$PWD/core/inifile/qqtiniparser.h
}

#yaml
#注释：在qqt_header.pri打开 DEFINES += __YAMLSUPPORT__
DEFINES += __YAMLSUPPORT__
contains (DEFINES, __YAMLSUPPORT__) {
    include($$PWD/core/yaml_cpp/yaml_cpp.pri)
}

#pluginsupport
#注释：在qqt_header.pri打开 DEFINES += __PLUGINSUPPORT__
#TODO: macOS runtime crash
contains (DEFINES, __PLUGINSUPPORT__) {
    #MinGW64 doesn't support contains(||) and contains(|) 任何层pro、pri都不支持。
    #contains(QSYS_PRIVATE, Win32|Windows|Win64|MSVC32|MSVC|MSVC64) {
    win32{
        wince*: SOURCES += $$PWD/pluginsupport/devicewatcher/qdevicewatcher_wince.cpp
        else:  SOURCES += $$PWD/pluginsupport/devicewatcher/qdevicewatcher_win32.cpp
    }else:contains(QSYS_PRIVATE, macOS) {
        SOURCES += $$PWD/pluginsupport/devicewatcher/qdevicewatcher_mac.cpp
    }else {
        SOURCES += $$PWD/pluginsupport/devicewatcher/qdevicewatcher_linux.cpp
    }
    SOURCES += $$PWD/pluginsupport/devicewatcher/qdevicewatcher.cpp
    HEADERS += $$PWD/pluginsupport/devicewatcher/qdevicewatcher.h \
                $$PWD/pluginsupport/devicewatcher/qdevicewatcher_p.h

    SOURCES += $$PWD/pluginsupport/qqtpluginwatcher.cpp
    HEADERS += $$PWD/pluginsupport/qqtpluginwatcher.h
}

contains(DEFINES, __QQTCHARTS__) {
    #qcustomplot
    #注释：在qqt_header.pri打开 DEFINES += __CUSTOMPLOT__
    contains (DEFINES, __CUSTOMPLOT__) {
        #message (qcustomplot is used in $${TARGET})
        SOURCES += $$PWD/charts/qcustomplot/qcpdocumentobject.cpp \
                    $$PWD/charts/qcustomplot/qcustomplot.cpp
        HEADERS += $$PWD/charts/qcustomplot/qcpdocumentobject.h \
                    $$PWD/charts/qcustomplot/qcustomplot.h
    }
}

contains (DEFINES, __NETWORKSUPPORT__) {
    #qextserialport support
    #if you use qextserialport, open the two annotation
    #注释：在qqt_header.pri打开 DEFINES += __QEXTSERIALPORT__
    contains (DEFINES, __QEXTSERIALPORT__) {
        #include ( $$PWD/network/qextserialport/qextserialport.pri )
        HEADERS += $$PWD/network/qextserialport/qextserialbase.h \
                  $$PWD/network/qextserialport/qextserialport.h \
                  $$PWD/network/qextserialport/qextserialenumerator.h
        SOURCES += $$PWD/network/qextserialport/qextserialbase.cpp \
                  $$PWD/network/qextserialport/qextserialport.cpp \
                  $$PWD/network/qextserialport/qextserialenumerator.cpp
        unix:HEADERS += $$PWD/network/qextserialport/posix_qextserialport.h
        unix:SOURCES += $$PWD/network/qextserialport/posix_qextserialport.cpp
        win32:HEADERS += $$PWD/network/qextserialport/win_qextserialport.h
        win32:SOURCES += $$PWD/network/qextserialport/win_qextserialport.cpp
    }

    #Qt soap, webservice
    contains(DEFINES, __WEBSERVICESUPPORT__) {
        SOURCES += \
            $$PWD/network/soap/qtsoap.cpp
        HEADERS += \
            $$PWD/network/soap/qtsoap.h
    }

    #gumbo support
    #注释：在qqt_header.pri打开 DEFINES += __GUMBOSUPPORT__
    contains (DEFINES, __GUMBOSUPPORT__) {
        #mingw 如果以前编译过mingw，然后编译+MSVC支持的版本，这个模块可能符号未导出。
        #这个问题，我也不知道原因，通过手动修改(touch)一下gumbo.h可以解决。
        #如果还是不对，那么需要为 gumbo parser 添加 gumbo_global.h。
        #如果有用户需要导出 gumbo parser的函数，那么必须加gumbo_global.h控制
        #gumbo query默认已经导出。
        include ($$PWD/network/gumbo/parser/gumbo-parser.pri)
        include ($$PWD/network/gumbo/query/gumbo-query.pri)
    }
}

##-------------------------------------------------------
##exquisite widget dependence
##-------------------------------------------------------
contains (DEFINES, __EXQUISITE__) {
    #qrencode widgets
    #注释：在qqt_header.pri打开 DEFINES += __QRENCODE__
    contains (DEFINES, __QRENCODE__) {
        include ($$PWD/exquisite/qrcode/qrencode/qrencode.pri)

        HEADERS += \
            $$PWD/exquisite/qrcode/qqtcustomqrencodewidget.h
        SOURCES += \
            $$PWD/exquisite/qrcode/qqtcustomqrencodewidget.cpp
    }

    #qrdecode widget
    #注释：在qqt_header.pri打开 DEFINES += __QRDECODE__
    contains (DEFINES, __QRDECODE__) {
        include ($$PWD/exquisite/qrcode/qrdecode/qrdecode.pri)

        HEADERS += \
            $$PWD/exquisite/qrcode/qqtcustomqrdecodewidget.h
        SOURCES += \
            $$PWD/exquisite/qrcode/qqtcustomqrdecodewidget.cpp

    }

    #mathml widget
    #注释：在qqt_header.pri打开 DEFINES += __MATHWIDGETSUPPORT__
    contains (DEFINES, __MATHWIDGETSUPPORT__) {
        SOURCES += $$PWD/exquisite/mathml/qtmmlwidget.cpp
        HEADERS += $$PWD/exquisite/mathml/qtmmlwidget.h
    }

    #dialog
    SOURCES += \
        $$PWD/exquisite/qqtpopupdialog.cpp
    HEADERS += \
        $$PWD/exquisite/qqtpopupdialog.h

    #widget
    SOURCES += \
        $$PWD/exquisite/qqtmaskwidget.cpp \
        $$PWD/exquisite/qqtfadewidget.cpp \
        $$PWD/exquisite/qqtninepatchwidget.cpp \
        $$PWD/exquisite/qqtshadowwidget.cpp \
        $$PWD/exquisite/qqtflipstackedwidget.cpp
    HEADERS += \
        $$PWD/exquisite/qqtmaskwidget.h \
        $$PWD/exquisite/qqtninepatchwidget.h \
        $$PWD/exquisite/qqtfadewidget.h \
        $$PWD/exquisite/qqtshadowwidget.h \
        $$PWD/exquisite/qqtflipstackedwidget.h

    #校验码生成器
    SOURCES += \
        $$PWD/exquisite/qqtcustomverificationcode.cpp
    HEADERS += \
        $$PWD/exquisite/qqtcustomverificationcode.h

    #progressbar
    SOURCES += \
        $$PWD/exquisite/qqtcustomprogressbar.cpp
    HEADERS += \
        $$PWD/exquisite/qqtcustomprogressbar.h

    #pushbutton
    SOURCES += \
        $$PWD/exquisite/qqtripplepushbutton.cpp
    HEADERS += \
        $$PWD/exquisite/qqtripplepushbutton.h

    #label
    SOURCES += \
        $$PWD/exquisite/qqtledbannerlabel.cpp \
        $$PWD/exquisite/qqtmarqueelabel.cpp
    HEADERS += \
        $$PWD/exquisite/qqtmarqueelabel.h \
        $$PWD/exquisite/qqtledbannerlabel.h
}

#multimedia
contains (DEFINES, __MULTIMEDIA__) {
    contains (DEFINES, __LOGICCAMERAMODULE__) {
        #dmmu support
        #arm mips
        #TODO: +wince +android +ios +macOS +win +linux
        equals(QSYS_PRIVATE, Embedded) {
            SOURCES += $$PWD/multimedia/dmmu/dmmu.c
            HEADERS += $$PWD/multimedia/dmmu/dmmu.h \
                        $$PWD/multimedia/dmmu/jz_cim.h \
                        $$PWD/multimedia/dmmu/graphics.h \
                        $$PWD/multimedia/dmmu/hal.h

            #logic video manager
            SOURCES += $$PWD/multimedia/qqtlogicvideomanager.cpp
            HEADERS += $$PWD/multimedia/qqtlogicvideomanager.h

            SOURCES += $$PWD/multimedia/qqtlogicpreviewwidget.cpp
            HEADERS += $$PWD/multimedia/qqtlogicpreviewwidget.h
            FORMS += $$PWD/multimedia/qqtlogicpreviewwidget.ui
        }
    }
}



