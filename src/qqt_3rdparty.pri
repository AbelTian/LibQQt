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
