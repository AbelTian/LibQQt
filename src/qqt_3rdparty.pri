##-------------------------------------------------------
##exquisite widget dependence
##-------------------------------------------------------
contains (DEFINES, __EXQUISITE__) {
    #qrencode widgets
    #DEFINES += __QRENCODE__
    contains (DEFINES, __QRENCODE__) {
        HEADERS += \
            $$PWD/exquisite/qqtcustomqrencodewidget.h
        SOURCES += \
            $$PWD/exquisite/qqtcustomqrencodewidget.cpp
        include ($$PWD/exquisite/qrcode/qrencode/qrencode.pri)
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
        HEADERS += \
            $$PWD/exquisite/qqtcustomqrdecodewidget.h
        SOURCES += \
            $$PWD/exquisite/qqtcustomqrdecodewidget.cpp

        include ($$PWD/exquisite/qrcode/qrdecode/qrdecode.pri)
    }
}

contains (DEFINES, __EXQUISITE__) {
    #gumbo widget
    #DEFINES += __GUMBOSUPPORT__
    contains (DEFINES, __GUMBOSUPPORT__) {
        include ($$PWD/exquisite/gumbo/parser/gumbo-parser.pri)
        include ($$PWD/exquisite/gumbo/query/gumbo-query.pri)
    }
}

contains (DEFINES, __EXQUISITE__) {
    #gumbo widget
    #DEFINES += __MATHSUPPORT__
    contains (DEFINES, __MATHSUPPORT__) {
        SOURCES += $$PWD/exquisite/mathml/qtmmlwidget.cpp
        HEADERS += $$PWD/exquisite/mathml/qtmmlwidget.h
    }
}
