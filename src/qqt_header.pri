#---------------------------------------------------------------
#qqt_header.pri
#Project link: https://gitee.com/drabel/LibQQt
#if you succeed with LibQQt, please thumb up.
#2017年11月10日18:53:56
##Don't modify this file outside QQt project
##this is QQt feature pri you can modify QQt feature at this pri in QQt project
#---------------------------------------------------------------

#################################################################
##definition and configration
##need QSYS
#################################################################
defineTest(add_defines_QQt){
    ##Qt version
    QT += core sql network gui xml
    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

    # release open debug output
    CONFIG(debug, debug|release) {
    } else {
        DEFINES -= QT_NO_DEBUG_OUTPUT
    }

    #compatible old version QQt (deperated)
    greaterThan(QT_MAJOR_VERSION, 4): DEFINES += __QT5__

    #defined in qqtcore.h
    #lessThan(QT_MAJOR_VERSION, 5):DEFINES += nullptr=0

    #mingw要加速编译，make -j20，-j参数是最好的解决办法。

    #close win32 no using fopen_s warning
    win32:DEFINES += _CRT_SECURE_NO_WARNINGS #fopen fopen_s

    #msvc支持设置
    msvc {
        MSVC_CCFLAGS =
        #this three pragma cause mingw errors
        msvc:MSVC_CCFLAGS += /wd"4819" /wd"4244" /wd"4100"

        #UTF8编码
        DEFINES += __MSVC_UTF8_SUPPORT__
        msvc:MSVC_CCFLAGS += /execution-charset:utf-8
        msvc:MSVC_CCFLAGS += /source-charset:utf-8
        #msvc:MSVC_CCFLAGS += /utf-8 #这一个是快捷方式，顶上边两个。

        #指定/mp编译选项，编译器将使用并行编译，同时起多个编译进程并行编译不同的cpp
        msvc:MSVC_CCFLAGS += /MP
        #指出：这个FLAG只能用于MSVC
        #指出：DLL导入错误，是因为环境变量设置错误不是这里引起的。修改设置，重新编译还是错误，build目录clean不干净，手动删除干净。如果还是不行，对源代码进行touch，无法区分import和export的dll，是编译器的错误。

        msvc:QMAKE_CFLAGS += $${MSVC_CCFLAGS}
        msvc:QMAKE_CXXFLAGS += $${MSVC_CCFLAGS}

        #指定stable.h这个头文件作为编译预处理文件，MFC里这个文件一般叫stdafx.h 然后在 stable.h里 包含你所用到的所有 Qt 头文件
        #在.pro 文件中加入一行, 加在这里，加速编译。
        #msvc:PRECOMPILED_HEADER = $${PWD}/qqt-qt.h
        #指出：precompiler header只能用于MSVC
        #这个功能可用，可是编译问题比较多，不方便，所以默认不开开。
    }

    #################################################################
    ##build qqt or link qqt
    #################################################################
    ##different target:
    ##-----------------------------------------------
    ##win platform:
    ##build qqt dll + QQT_LIBRARY
    ##build qqt lib + QQT_STATIC_LIBRARY
    ##link qqt lib + QQT_STATIC_LIBRARY
    ##link qqt dll + ~~
    ##- - - - - - - - - - - - - - - - - - - - -
    ##*nix platform:
    ##build and link qqt dll or lib + ~~
    ##-----------------------------------------------
    #link QQt static library in some occation on windows
    #when link QQt    static library, if no this macro, headers can't be linked on windows.
    #Qt is static by mingw32 building ?
    ios{
        #on my computer, Qt library are all static library?
        DEFINES += QQT_STATIC_LIBRARY
        message(Build $${TARGET} QQT_STATIC_LIBRARY is defined. build and link)
    }

    #link and build all need this macro
    #现在Multi-link v2里面，已经有LIB_STATIC_LIBRARY，这个宏多余了，可是由于内部逻辑复杂，更改也不简单，所以留着了。用户静态编译LibQQt，记得定义QQT_STATIC_LIBRARY，build and link。
    contains(DEFINES, QQT_STATIC_LIBRARY) {
    }

    ################################################################
    ##QQt Functions Macro
    ################################################################
    #You need switch these more macro according to your needs when you build this library
    #You can tailor QQt  with these macro.
    #Default: macroes is configed, some open, some close, compatibled to special accotation.
    ##App希望裁剪LibQQt，开关这个文件里的组件宏，用户有必要读懂这个头文件。up to so.

    ##################C++11 Module###############################
    #if you use C++11, open this annotation. suggest: ignore
    #DEFINES += __CPP11__
    contains (DEFINES, __CPP11__) {
        #macOS gcc Qt4.8.7
        #qobject.h fatal error: 'initializer_list' file not found,
        #Qt4.8.7 can't support c++11 features
        #QMAKE_CXXFLAGS += "-std=c++11"
        #QMAKE_CXXFLAGS += "-std=c++0x"

        #below: gcc version > 4.6.3
        #Open this Config, Why in Qt4 works? see qmake config auto ignored this feature.
        #In Qt5? don't need open this config, qmake auto add c++11 support on linux plat.
        #on windows mingw32? need test
        #CONFIG += c++11

        #compile period
        #LibQQt need c++11 support. Please ensure your compiler version.
        #LibQQt used override identifier
        #lambda also need c++11
    }

    ##################MultiMedia Module###############################
    DEFINES += __MULTIMEDIA__
    #on mac qt4 has no multimedia
    contains(QSYS_PRIVATE, macOS) {
        lessThan(QT_MAJOR_VERSION, 5):DEFINES-=__MULTIMEDIA__
    }
    contains (DEFINES, __MULTIMEDIA__) {
        QT += multimedia
    }

    ##################PluginSupport Module###############################
    #used in windows linux e-linux android, mac ios not support exactly
    #plugin notifer, and plugin device managament.
    #if you use DeviceWatcher , open this annotation
    DEFINES += __PLUGINSUPPORT__
    contains(QSYS_PRIVATE, iOS||iOSSimulator||macOS) {
        DEFINES -= __PLUGINSUPPORT__
    }
    contains (DEFINES, __PLUGINSUPPORT__) {
        contains(QSYS_PRIVATE, Win32|Windows|Win64 || MSVC32|MSVC|MSVC64) {
            contains (DEFINES, QQT_STATIC_LIBRARY) {
                DEFINES += BUILD_QDEVICEWATCHER_STATIC
            }
        }
    }

    ##################PrintSupport Module###############################
    #if you use printsupport , open this annotation
    DEFINES += __PRINTSUPPORT__
    #Qt 5.9.1, ios and android can't support this feature, because Qt 5.9.1, broken
    equals(QT_VERSION, 5.9.1) {
        contains(QSYS_PRIVATE, iOS||iOSSimulator||Android||AndroidX86) {
            DEFINES -= __PRINTSUPPORT__
        }
    }
    #Qt 5.9.2, android support this feature
    #Qt 5.9.2, ios can't use printsupport
    contains(QSYS_PRIVATE, iOS||iOSSimulator) {
        DEFINES -= __PRINTSUPPORT__
    }
    contains (DEFINES, __PRINTSUPPORT__) {
        #qtHaveModule(printsupport) : message(qqt use module printsupport)
        greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
    }

    ##################Charts Module###############################
    #if you use QQtCharts, open this annotation
    DEFINES += __QQTCHARTS__
    contains(DEFINES, __QQTCHARTS__) {
        #默认打开Qt Charts
        DEFINES += __QT_CHARTS__
        #Qt小于5.7没有charts模块
        #Qt Embedded，没有charts模块
        #对于这两种情况，默认删除去。如果用户自己编译了Charts，手动添加charts模块。
        lessThan(QT_VERSION, 5.7):DEFINES-=__QT_CHARTS__
        contains(QSYS_PRIVATE, Arm32|Armhf32 || Mips32 || Embedded):DEFINES-=__QT_CHARTS__
        #based on QtCharts, need charts module
        contains(DEFINES, __QT_CHARTS__ ): QT += charts

        #if you use qcustomplot, open this annotation
        #qcustomplot use QPrinter to export pdf file, QChart haven't use it, I fix it, now compiler ok.
        #in ios qcustomplot can't call savePdf now, no result but a log no printer error.
        #默认打开customplot
        DEFINES += __CUSTOMPLOT__
        contains (DEFINES, __CUSTOMPLOT__) {
            win32 {
                contains (DEFINES, QQT_STATIC_LIBRARY) {
                    #build static library - qcustomplot
                    DEFINES += QCUSTOMPLOT_STATIC_LIBRARY
                }
            }
        }
    }

    ##################QQtLogSystem Module###############################
    DEFINES += __QQTLOGSYSTEMSUPPORT__

    ###########################################################################
    ###QQtSocketClient多组功能组件。
    ############
    ##################QQt Network Module##################################
    #包括SerialPort Bluetooth TcpUdp
    #包括HttpFtp 多路的HttpFtp，QQtAccessManager WebService WebSocket Gumbo
    #包括WebKit WebEngine
    DEFINES += __NETWORKSUPPORT__
    contains (DEFINES, __NETWORKSUPPORT__) {
        ##################SerialPort Module##################################
        #if you use qextserialport, open the annotation
        #suggest: Qt5 use factory-packed, Qt4 use forming Qt5, extra use this.
        #DEFINES += __QEXTSERIALPORT__
        #if compiler QtSerialPort module manual, note this line is a good idea. default: qt4 qextserialport
        lessThan(QT_MAJOR_VERSION, 5): DEFINES += __QEXTSERIALPORT__
        #to ios, use qextserialport
        #android qt5 support serialport default?
        contains (DEFINES, __IOS__): DEFINES += __QEXTSERIALPORT__
        contains (DEFINES, __QEXTSERIALPORT__) {
            CONFIG += thread
            unix:DEFINES += _TTY_POSIX_
            win32:DEFINES += _TTY_WIN_
            #Qt4 is not a very good Cross Qt version, Qt5 suggest.
            win32:LIBS += -lsetupapi -ladvapi32
            #message ( __QEXTSERIALPORT__ Defined in $${TARGET})
        } else {
            #message ( __QSERIALPORT__ Defined in $${TARGET})
            greaterThan(QT_MAJOR_VERSION, 4): QT += serialport
            lessThan(QT_MAJOR_VERSION, 5): CONFIG += serialport
            unix {
                DEFINES += _TTY_POSIX_
            } else {
                DEFINES += _TTY_WIN_
            }
        }

        ##################Bluetooth Module###############################
        #if you use qtbluetooth, open this annotation
        DEFINES += __BLUETOOTH__
        #if you compiler QtBluetooth module manual, note this line is a good idea. default qt4 doesn't use bluetooth
        lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __BLUETOOTH__
        #condation
        contains (DEFINES, __BLUETOOTH__) {
            greaterThan(QT_MAJOR_VERSION, 4): QT += bluetooth
            lessThan(QT_MAJOR_VERSION, 5): CONFIG += bluetooth
        }

        ##################Nfc Module###############################
        #if you use QtNfc, open this annotation
        DEFINES += __NFC__
        #if you compiler QtNfc module manual, note this line is a good idea. default <qt5.2 doesn't use bluetooth
        lessThan(QT_VERSION, 5.2): DEFINES -= __NFC__
        DEFINES -= __NFC__
        #condation
        contains (DEFINES, __NFC__) {
            QT += nfc
        }

        ##################RawSocket Module###############################
        #raw socket, 这个是常用的，不要关，dont close。...
        DEFINES += __TCPUDPSOCKET__

        ##################WebService Module###############################
        #if you use Qt Service Support ( QtSoap ), open this annotation
        DEFINES += __WEBSERVICESUPPORT__
        contains (DEFINES, __WEBSERVICESUPPORT__) {
            win32 {
                contains (DEFINES, QQT_STATIC_LIBRARY) {
                    DEFINES += QT_QTSOAP_STATIC_LIBRARY
                }
            }
        }

        #One Ftp Http 单工...
        #Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
        #QNetworkAccessManager 提供多路并发 HTTP session。
        #if you use QNetworkAccessManagerSupport , open this annotation
        DEFINES += __WEBACCESSSUPPORT__
        lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __WEBACCESSSUPPORT__
        contains(QSYS_PRIVATE, Arm32|Armhf32 || Mips32 || Embedded):DEFINES -= __WEBACCESSSUPPORT__
        contains (DEFINES, __WEBACCESSSUPPORT__) {
            #QSslError not found, you need recompiler Qt4
        }

        DEFINES += __WEBKITSUPPORT__
        contains (DEFINES, __WEBKITSUPPORT__) {
            #TODO: QT += webkit
        }

        DEFINES += __WEBENGINESUPPORT__
        contains (DEFINES, __WEBENGINESUPPORT__) {
        }

        ##################WebSocket Module###############################
        #Multi New Protocol 全双工 QWebSocket
        #if you use QWebSocketSupport , open this annotation
        DEFINES += __WEBSOCKETSUPPORT__
        #equals(QSYS_PRIVATE, macOS):DEFINES += __WEBSOCKETSUPPORT__
        lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __WEBSOCKETSUPPORT__
        contains (DEFINES, __WEBSOCKETSUPPORT__) {
            QT += websockets
            #Qt4 QSslError not found, you need recompiler Qt4
            #TODO: QT += webkit
        }

        #c++ html parser query
        #if you use Gumbo parser query, open this annotation
        #这个组件用于解析网页，获得网页数据。
        #gumbo属于网络模块，中高级工具，经常用于写爬虫。
        DEFINES += __GUMBOSUPPORT__
        contains (DEFINES, __GUMBOSUPPORT__) {
            #Gumbo need std support, c99...
            QMAKE_CFLAGS += -std=c99
            win32 {
                contains (DEFINES, QQT_STATIC_LIBRARY) {
                    DEFINES += QT_GUMBO_STATIC_LIBRARY
                }
            }
        }

    }


    ##################Exquisite Widgets Module###############################
    #if you use Exquisite widgets, open this annotation
    #精美模块，包含不少的精美组件，这个模块可以集中开关。
    #依赖基础控件
    DEFINES += __EXQUISITE__
    contains (DEFINES, __EXQUISITE__) {
        #if you use QR encode, open this annotation
        DEFINES += __QRENCODE__

        #if you use QR decode, open this annotation
        #QZXing isnan_z function error. fixed
        #QZxing delegating constructors used. need c++11,but qt4.8.7 dont support c++11,compiler gcc 5.4.0 20160609 support....
        #DEFINES += __QRDECODE__
        contains(DEFINES, __QRDECODE__) {
            #lessThan(QT_MAJOR_VERSION, 5): QT += declarative
            greaterThan(QT_MAJOR_VERSION, 4): QT += quick
            contains(QSYS_PRIVATE, Win32|Windows|Win64 || MSVC32|MSVC|MSVC64) {
                #ignore: QZXing has no need to export
                contains (DEFINES, QQT_STATIC_LIBRARY) {
                    DEFINES += QZXING_STATIC_LIBRARY
                }
            }
        }

        #if you use gif widgets, open this annotation
        DEFINES += __GIFWIDGETS__

        #if you use Svg widgets, open this annotation
        DEFINES += __SVGWIDGETS__
        contains(QSYS_PRIVATE, macOS) {
            lessThan(QT_MAJOR_VERSION, 5):DEFINES-=__SVGWIDGETS__
        }
        contains (DEFINES, __SVGWIDGETS__) {
            QT += svg
        }

        ##################Mathes Module###############################
        DEFINES += __MATHWIDGETSUPPORT__
        contains (DEFINES, __MATHWIDGETSUPPORT__) {
            contains(QSYS_PRIVATE, Win32|Windows|Win64 || MSVC32|MSVC|MSVC64) {
                contains (DEFINES, QQT_STATIC_LIBRARY) {
                    DEFINES += QT_QTMMLWIDGET_STATIC_LIBRARY
                }
            }
        }
        #LOGIC CAMERA PREVIEW
        #depend on dmmu
        DEFINES += __LOGICCAMERAMODULE__

        #opengl module
        DEFINES += __OPENGLWIDGETS__
        contains(QSYS_PRIVATE, Arm32|Armhf32 || Mips32 || Embedded):DEFINES-=__OPENGLWIDGETS__
        contains (DEFINES, __OPENGLWIDGETS__) {
            QT += opengl
        }

        #single color only widget
        DEFINES += __COLORWIDGETS__

        #click widgets
        DEFINES += __CLICKWIDGETS__

        #click sound widgets
        DEFINES += __CLICKSOUNDWIDGETS__

        #on screen display widget
        DEFINES += __OSDWIDGETS__
    }

    ########################################################################
    ###这个模块名为高级模块。
    ###如果初中级工程师能使用这个模块完成App，那么必定是高分实现力学员。
    ###建议中级以上工程师尝试。2018年4月22日 星期天 11点08分
    ############
    ##################HighGrade Module###############################
    #if you use HighGrade module, open this annotation
    #高级模块，包含不少的高级功能组件，这个模块可以集中开关。
    DEFINES += __HIGHGRADE__
    contains (DEFINES, __HIGHGRADE__) {
        DEFINES += __QQT_COMMUNICATION_SUPPORT__
        contains(DEFINES, __QQT_COMMUNICATION_SUPPORT__) {
            ##################Shared Memory Module###############################
            DEFINES += __SHAREDMEMORY_SUPPORT__

            ##################Message Queue Module###############################
            DEFINES += __MESSAGEQUEUE_SUPPORT__

            ##################Local RawSocket Module###############################
            DEFINES += __NAMEDPIPE_SUPPORT__
            #local socket依赖network support
            !contains(DEFINES, __NETWORKSUPPORT__):DEFINES-=__NAMEDPIPE_SUPPORT__
        }
    }

    #################################################################
    ##library
    ##################################################################
    equals (QSYS_PRIVATE, iOSSimulator):{
        #error need
        #QMAKE_CXXFLAGS +=-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk
    }

    win32 {
        LIBS += -luser32
        contains (DEFINES, __OPENGLWIDGETS__) {
            LIBS += -lopengl32 -lglu32
        }
    }else: unix {
        equals(QSYS_PRIVATE, macOS) {
            #min macosx target
            QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
            #deperated
            #QMAKE_MAC_SDK=macosx10.12
            #MACOSXSDK = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX$${QMAKE_MACOSX_DEPLOYMENT_TARGET}.sdk
            #QMAKE_LIBDIR = $${MACOSXSDK}
            #LIBS += -F$${MACOSXSDK}/System/Library/Frameworks
            #LIBS += -L$${MACOSXSDK}/usr/lib
            LIBS += -framework DiskArbitration -framework Cocoa -framework IOKit
            export(QMAKE_MACOSX_DEPLOYMENT_TARGET)
            export(LIBS)
        }else:contains(QSYS_PRIVATE, iOS|iOSSimulator){
            QMAKE_LFLAGS += -ObjC -lsqlite3 -lz
            QMAKE_IOS_DEPLOYMENT_TARGET = 8
            export(QMAKE_LFLAGS)
            export(QMAKE_IOS_DEPLOYMENT_TARGET)
        }
    }

    export(QMAKE_CFLAGS)
    export(QMAKE_CXXFLAGS)

    export(CONFIG)
    export(DEFINES)

    export(LIBS)
    export(QT)

    return (1)
}

##################################################################
##include directories
##################################################################
#把QQt 源代码头文件路径加入进来 为搜索头文件而添加
defineTest(add_include_QQt){
    #不为空，肯定是源码里的路径。 用于导出头文件
    header_path = $$1
    #如果参数1为空，那么是用SDK里的路径 用于链接时包含头文件
    #此处_bundle代表 mac下头文件在bundle里。 留意
    isEmpty(header_path):header_path=$$PWD

    command =
    #basic
    command += $${header_path}
    #这里添加$${path}下的子文件夹
    #...
    command += $${header_path}/core
    command += $${header_path}/gui
    command += $${header_path}/widgets
    command += $${header_path}/multimedia
    command += $${header_path}/sql
    command += $${header_path}/frame
    command += $${header_path}/printsupport

    #charts
    command += $${header_path}/charts
    command += $${header_path}/charts/qcustomplot

    #network
    command += $${header_path}/network
    command += $${header_path}/network/qextserialport

    ##soap (web service)
    command += $${header_path}/network/soap

    ##gumbo library
    command += $${header_path}/network/gumbo/query/src
    command += $${header_path}/network/gumbo/parser/src
    win32{
        command += $${header_path}/network/gumbo/parser/visualc/include
    }

    #plugin support
    command += $${header_path}/pluginsupport
    command += $${header_path}/pluginsupport/devicewatcher

    #exquisite widgets
    command += $${header_path}/exquisite
    command += $${header_path}/exquisite/clicksoundwidgets
    command += $${header_path}/exquisite/clickwidgets
    command += $${header_path}/exquisite/svgwidgets
    command += $${header_path}/exquisite/gifwidgets
    command += $${header_path}/exquisite/openglwidgets
    command += $${header_path}/exquisite/colorwidgets
    command += $${header_path}/exquisite/osdwidgets
    command += $${header_path}/exquisite/mathml
    command += $${header_path}/exquisite/dmmu

    ##qr code library
    command += $${header_path}/exquisite/qrcode/qrencode
    command += $${header_path}/exquisite/qrcode/qrdecode
    command += $${header_path}/exquisite/qrcode/qrdecode/zxing
    win32-g++{
        command += $${header_path}/exquisite/qrcode/qrdecode/zxing/win32/zxing
    }
    win32-msvc*{
        command += $${header_path}/exquisite/qrcode/qrdecode/zxing/win32/zxing \
                    $${header_path}/exquisite/qrcode/qrdecode/zxing/win32/zxing/msvc
    }

    #highgrade module
    command += $${header_path}/highgrade
    command += $${header_path}/highgrade/network

    INCLUDEPATH += $$add_host_path($$command)
    export(INCLUDEPATH)
    return (1)
}

##################################################################
##header work flow
##################################################################
#添加源代码里的头文件路径 为搜索头文件而添加
add_include_QQt()
add_defines_QQt()
