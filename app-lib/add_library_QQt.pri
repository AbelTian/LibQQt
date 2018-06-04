################################################################
##add_library_QQt.pri
##link QQt
################################################################
#简介
#add link library 链接过程 用于源代码编写的时候。包括头文件和添加库
#add deploy library 编译过程 用于源代码编译的时候。发布库
#add dependent library 包括以上两个过程
#一般app才会使用add dependent library, lib使用add link library。
#到这里用户必须明白，链接概念到不了app，lib里才有链接概念。
#依赖概念才会在app里出现。
#这是重点。

#######################################################################################
#初始化设置
#######################################################################################
#2.4
LIBRARYVER =

#######################################################################################
#定义内部函数
#######################################################################################

##################################################################
##defines and configures
##################################################################
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
    contains(DEFINES, QQT_STATIC_LIBRARY) {
        DEFINES += QCUSTOMPLOT_STATIC_LIBRARY
        DEFINES += QZXING_STATIC_LIBRARY
        DEFINES += QT_QTSOAP_STATIC_LIBRARY
        DEFINES += BUILD_QDEVICEWATCHER_STATIC
        DEFINES += QT_QTMMLWIDGET_STATIC_LIBRARY
        DEFINES += QT_GUMBO_STATIC_LIBRARY
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
    lessThan(QT_MAJOR_VERSION, 5):DEFINES-=__QQTCHARTS__
    contains(QSYS_PRIVATE, Arm32||Mips32||Embedded):DEFINES-=__QQTCHARTS__
    #based on QtCharts, need charts module
    contains(DEFINES, __QQTCHARTS__) {
        QT += charts

        #if you use qcustomplot, open this annotation
        #qcustomplot use QPrinter to export pdf file, QChart haven't use it, I fix it, now compiler ok.
        #in ios qcustomplot can't call savePdf now, no result but a log no printer error.
        DEFINES += __CUSTOMPLOT__
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

        #One Ftp Http 单工...
        #Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
        #QNetworkAccessManager 提供多路并发 HTTP session。
        #if you use QNetworkAccessManagerSupport , open this annotation
        DEFINES += __WEBACCESSSUPPORT__
        lessThan(QT_MAJOR_VERSION, 5): DEFINES -= __WEBACCESSSUPPORT__
        contains(QSYS_PRIVATE, Arm32||Mips32||Embedded):DEFINES -= __WEBACCESSSUPPORT__
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

        #LOGIC CAMERA PREVIEW
        #depend on dmmu
        DEFINES += __LOGICCAMERAMODULE__

        #opengl module
        DEFINES += __OPENGLWIDGETS__
        contains(QSYS_PRIVATE, Mips32||Arm32||Embedded):DEFINES-=__OPENGLWIDGETS__
        contains (DEFINES, __OPENGLWIDGETS__) {
            QT += opengl
        }

        #single color only widget
        DEFINES += __COLORWIDGETS__

        #click widgets
        DEFINES += __CLICKWIDGETS__

        #click sound widgets
        DEFINES += __CLICKSOUNDWIDGETS__
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
    #依赖网络模块
    !contains (DEFINES, __NETWORKSUPPORT__): DEFINES -= __HIGHGRADE__
    contains (DEFINES, __HIGHGRADE__) {

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
defineReplace(get_add_include_QQt){
    path = $$1
    !isEmpty(2) : error("get_add_include_QQt(path) requires one arguments.")
    isEmpty(1) : error("get_add_include_QQt(path) requires one arguments.")

    #basic
    command += $${path}
    command += $${path}/core
    command += $${path}/gui
    command += $${path}/widgets
    command += $${path}/multimedia
    command += $${path}/sql
    command += $${path}/frame
    command += $${path}/printsupport

    #charts
    command += $${path}/charts
    command += $${path}/charts/qcustomplot

    #network
    command += $${path}/network
    command += $${path}/network/qextserialport

    ##soap (web service)
    command += $${path}/network/soap

    ##gumbo library
    command += $${path}/network/gumbo/query/src
    command += $${path}/network/gumbo/parser/src
    win32{
        command += $${path}/network/gumbo/parser/visualc/include
    }

    #plugin support
    command += $${path}/pluginsupport
    command += $${path}/pluginsupport/devicewatcher

    #exquisite widgets
    command += $${path}/exquisite
    command += $${path}/exquisite/clicksoundwidgets
    command += $${path}/exquisite/clickwidgets
    command += $${path}/exquisite/svgwidgets
    command += $${path}/exquisite/gifwidgets
    command += $${path}/exquisite/openglwidgets
    command += $${path}/exquisite/colorwidgets
    command += $${path}/exquisite/mathml
    command += $${path}/exquisite/dmmu

    ##qr code library
    command += $${path}/exquisite/qrcode/qrencode
    command += $${path}/exquisite/qrcode/qrdecode
    command += $${path}/exquisite/qrcode/qrdecode/zxing
    win32-g++{
        command += $${path}/exquisite/qrcode/qrdecode/zxing/win32/zxing
    }
    win32-msvc*{
        command += $${path}/exquisite/qrcode/qrdecode/zxing/win32/zxing \
                    $${path}/exquisite/qrcode/qrdecode/zxing/win32/zxing/msvc
    }

    #highgrade module
    command += $${path}/highgrade

    return ($$command)
}

#把QQt SDK头文件路径加入进来 为搜索头文件而添加
#其实过去做的自动添加QQt头文件就是这个功能
#用户包含QQt头文件，就不必加相对路径了，方便了很多
defineTest(add_include_QQt){
    #包含QQt头文件的过程
    header_path = $$get_add_include_bundle(QQt)
    INCLUDEPATH += $$get_add_include_QQt($$header_path)
    export(INCLUDEPATH)
    return (1)
}


defineTest(add_library_QQt){
    #链接QQt
    add_library_bundle(QQt)
}

#######################################################################################
#定义外部函数
#######################################################################################
#链接QQt
#用户只需要调用这个函数，一个，就能开启链接QQt 包含QQt 跟随App发布QQt三个步骤的App生产线工位。
defineTest(add_link_library_QQt){
    #细心的用户会发现，QQt的头文件包含了两次，一个在源代码目录里，一个在SDK目录里，两个并不冲突。系统只要搜索到一个目录里的就可以使用了。
    #当然，我们确信，SDK目录里的头文件服从于源代码目录里的头文件。
    #包含QQt的头文件
    add_include_QQt()
    #包含QQt的宏定义
    add_defines_QQt()
    #链接（lib)
    add_library_QQt()
    return (1)
}

#以上代码只完成了链接libQQt 包含libQQt头文件 包含libQQt宏文件(在宏文件控制下Library的头文件才有精确的意义)
#没有发布libQQt
#App在开发中，调用发布App以后 必然需要调用add_deploy_library(QQt)发布QQt到运行时。强大的：从sdk发布到build和deploy位置。
#调试，正常；发布运行，正常。
#:) 方便函数
defineTest(add_deploy_library_QQt){
    add_deploy_library_bundle(QQt)
    return (1)
}

defineTest(add_dependent_library_QQt){
    add_link_library_QQt()
    add_deploy_library_QQt()
    return (1)
}
