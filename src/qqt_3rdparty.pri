#-------------------------------------------------------
#qqt_3rdparty.pri
#这个文件用于指示版权。
#-------------------------------------------------------
#pluginsupport
#注释：在qqt_header.pri打开 DEFINES += __PLUGINSUPPORT__
#TODO: macOS runtime crash
contains (DEFINES, __PLUGINSUPPORT__) {
    contains(QKIT_PRIVATE, WIN32|WIN64) {
        contains (DEFINES, QQT_LIBRARY) {
            DEFINES += BUILD_QDEVICEWATCHER_LIB
        } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
            DEFINES += BUILD_QDEVICEWATCHER_STATIC
        }
        wince*: SOURCES += $$PWD/pluginsupport/devicewatcher/qdevicewatcher_wince.cpp
        else:  SOURCES += $$PWD/pluginsupport/devicewatcher/qdevicewatcher_win32.cpp
    }else:contains(QKIT_PRIVATE, macOS) {
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
        win32 {
            contains (DEFINES, QQT_LIBRARY) {
                DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY
            } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
                #build static library - qcustomplot
                DEFINES += QCUSTOMPLOT_STATIC_LIBRARY
            }
        }
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
        win32 {
            contains (DEFINES, QQT_LIBRARY) {
                DEFINES += QT_QTSOAP_LIBRARY
            } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
                DEFINES += QT_QTSOAP_STATIC_LIBRARY
            }
        }
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
        #如果还是不对，那么需要为 gumbo parser 添加 gumbolocal.h。
        #如果有用户需要到处 gumbo parser的函数，那么必须加gumbolocal.h控制
        #gumbo query默认已经导出。
        win32 {
            contains (DEFINES, QQT_LIBRARY) {
                DEFINES += QT_GUMBO_LIBRARY
            } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
                DEFINES += QT_GUMBO_STATIC_LIBRARY
            }
        }
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
        contains(QKIT_PRIVATE, WIN32|WIN64) {
            #ignore: QZXing has no need to export
            contains (DEFINES, QQT_LIBRARY) {
                DEFINES += QZXING_LIBRARY
            } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
                DEFINES += QZXING_STATIC_LIBRARY
            }
        }
        include ($$PWD/exquisite/qrcode/qrdecode/qrdecode.pri)

        HEADERS += \
            $$PWD/exquisite/qrcode/qqtcustomqrdecodewidget.h
        SOURCES += \
            $$PWD/exquisite/qrcode/qqtcustomqrdecodewidget.cpp

    }

    #mathml widget
    #注释：在qqt_header.pri打开 DEFINES += __MATHWIDGETSUPPORT__
    contains (DEFINES, __MATHWIDGETSUPPORT__) {
        contains(QKIT_PRIVATE, WIN32|WIN64) {
            #mathml
            contains (DEFINES, QQT_LIBRARY) {
                DEFINES += QT_QTMMLWIDGET_LIBRARY
            } else: contains (DEFINES, QQT_STATIC_LIBRARY) {
                DEFINES += QT_QTMMLWIDGET_STATIC_LIBRARY
            }
        }
        SOURCES += $$PWD/exquisite/mathml/qtmmlwidget.cpp
        HEADERS += $$PWD/exquisite/mathml/qtmmlwidget.h
    }

    contains (DEFINES, __LOGICCAMERAMODULE__) {
        #dmmu support
        #arm mips
        #TODO: +wince +android +ios +macOS +win +linux
        equals(QKIT_PRIVATE, EMBEDDED) {
            SOURCES += $$PWD/exquisite/dmmu/dmmu.c
            HEADERS += $$PWD/exquisite/dmmu/dmmu.h \
                        $$PWD/exquisite/dmmu/jz_cim.h \
                        $$PWD/exquisite/dmmu/graphics.h \
                        $$PWD/exquisite/dmmu/hal.h
            SOURCES += $$PWD/exquisite/qqtpreviewwidget.cpp
            HEADERS += $$PWD/exquisite/qqtpreviewwidget.h
            FORMS += $$PWD/exquisite/qqtpreviewwidget.ui
        }
    }
}
