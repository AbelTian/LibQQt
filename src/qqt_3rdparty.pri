##-------------------------------------------------------
##exquisite widget dependence
##-------------------------------------------------------
contains (DEFINES, __EXQUISITE__) {
    #qrencode widgets
    #DEFINES += __QRENCODE__
    contains (DEFINES, __QRENCODE__) {
        include ($$PWD/exquisite/qrcode/qrencode/qrencode.pri)

        HEADERS += \
            $$PWD/exquisite/qrcode/qqtcustomqrencodewidget.h
        SOURCES += \
            $$PWD/exquisite/qrcode/qqtcustomqrencodewidget.cpp
    }

    #qrdecode widget
    #DEFINES += __QRDECODE__
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

    #gumbo widget
    #DEFINES += __GUMBOSUPPORT__
    contains (DEFINES, __GUMBOSUPPORT__) {
        include ($$PWD/exquisite/gumbo/parser/gumbo-parser.pri)
        include ($$PWD/exquisite/gumbo/query/gumbo-query.pri)
    }

}
