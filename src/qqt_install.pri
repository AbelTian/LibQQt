################################################
##install to Qt library
################################################
#return
equals(QKIT_, macOS) {
    ###if install product to same path,use this.
    target.path = /System/Library/Frameworks
    INSTALLS += target
    include( qqt_install.pri )
}
message ($$QMAKE_)
message ($$OUT_PWD)
