#this configration need Qt Creator set default build directory
#%{CurrentProject:Name}/%{Qt:Version}/%{CurrentKit:FileSystemName}/%{CurrentBuild:Name}")}

#target arch type
#You need define a env variable QKIT=XX
QKIT_PRIVATE = $$(QKIT)
#处理文件内平台小差异
#EMBEDDED __EMBEDDED_LINUX__
#MIPS __MIPS_LINUX__
#ARM __ARM_LINUX__
#LINUX __LINUX__
#LINUX64 __LINUX64__
#WIN32 __WIN32__
#WIN64 __WIN64__
#macOS __DARWIN__
#ANDROID __ANDROID__
#ANDROIDX86 __ANDROIDX86__
equals(QKIT_PRIVATE, EMBEDDED) {
    #embedded common macro
    DEFINES += __EMBEDDED_LINUX__
} else:equals(QKIT_PRIVATE, ARM32) {
    DEFINES += __EMBEDDED_LINUX__
    #arm32 private
    DEFINES += __ARM_LINUX__
} else:equals(QKIT_PRIVATE, MIPS32) {
    DEFINES += __EMBEDDED_LINUX__
    #mips32 private
    DEFINES += __MIPS_LINUX__
} else:equals(QKIT_PRIVATE, LINUX) {
    DEFINES += __LINUX__
} else:equals(QKIT_PRIVATE, LINUX64) {
    DEFINES += __LINUX64__
} else:equals(QKIT_PRIVATE, WIN32) {
    DEFINES += __WIN32__
} else:equals(QKIT_PRIVATE, WIN64) {
    DEFINES += __WIN64__
} else:equals(QKIT_PRIVATE, macOS) {
    DEFINES += __DARWIN__
} else:equals(QKIT_PRIVATE, iOS) {
    DEFINES += __IOS__
} else:equals(QKIT_PRIVATE, iOSSimulator) {
    DEFINES += __IOS__
    #TODO:no customplot word printer process
} else:equals(QKIT_PRIVATE, ANDROID) {
    DEFINES += __ANDROID__
} else:equals(QKIT_PRIVATE, ANDROIDX86) {
    DEFINES += __ANDROID__
    DEFINES += __ANDROIDX86__
}

#QMAKESPEC_NAME = $${QMAKESPEC}
#QMAKESPEC_NAME ~= s@^/.*/([^/]+)/?@\1@g
#QMAKESPECS = $${QMAKESPEC}
#QMAKESPECS ~= s:/[^/]*$::p
#message (used spec: $$QMAKESPEC_NAME at here: $$QMAKESPECS )
#equals(QMAKESPEC_NAME, EMBEDDED) {
#    #embedded common macro
#    DEFINES += __EMBEDDED_LINUX__
#} else:equals(QMAKESPEC_NAME, *arm*) {
#    DEFINES += __EMBEDDED_LINUX__
#    #arm32 private
#    DEFINES += __ARM_LINUX__
#} else:equals(QMAKESPEC_NAME, *mips*) {
#    QT += multimedia
#    DEFINES += __EMBEDDED_LINUX__
#    #mips32 private
#    DEFINES += __MIPS_LINUX__
#} else:equals(QMAKESPEC_NAME, linux-g++-32) {
#    DEFINES += __LINUX__
#} else:equals(QMAKESPEC_NAME, linux-g++) {
#    DEFINES += __LINUX64__
#} else:equals(QMAKESPEC_NAME, win32-*) {
#    DEFINES += __WIN32__
#} else:equals(QMAKESPEC_NAME, win64-*) {
#    DEFINES += __WIN64__
#} else:equals(QMAKESPEC_NAME, macx-ios-*) {
#    DEFINES += __IOS__
#} else:equals(QMAKESPEC_NAME, iOSSimulator) {
#    DEFINES += __IOS__
#} else:equals(QMAKESPEC_NAME, macx-*) {
#    DEFINES += __DARWIN__
#} else:equals(QMAKESPEC_NAME, android-*) {
#    DEFINES += __ANDROID__
#} else:equals(QMAKESPEC_NAME, ANDROIDX86) {
#    DEFINES += __ANDROID__
#    #todo:no customplot word printer
#}

#################################################################
##variables
#################################################################
CONFIG(debug, debug|profile|release):BUILD=Debug
CONFIG(profile, debug|profile|release):BUILD=Profile
CONFIG(release, debug|profile|release):BUILD=Release
equals(QKIT_PRIVATE, EMBEDDED) {
    SYSNAME = Embedded
} else:equals(QKIT_PRIVATE, ARM32) {
    SYSNAME = Arm32
} else:equals(QKIT_PRIVATE, MIPS32) {
    SYSNAME = Mips32
} else:equals(QKIT_PRIVATE, LINUX) {
    SYSNAME = Linux
} else:equals(QKIT_PRIVATE, LINUX64) {
    SYSNAME = Linux64
} else:equals(QKIT_PRIVATE, WIN32) {
    SYSNAME = Windows
} else:equals(QKIT_PRIVATE, WIN64) {
    SYSNAME = Win64
} else:equals(QKIT_PRIVATE, macOS) {
    SYSNAME = MacOS
} else:equals(QKIT_PRIVATE, iOS) {
    SYSNAME = iOS
} else:equals(QKIT_PRIVATE, iOSSimulator) {
    SYSNAME = iOS-simulator
} else:equals(QKIT_PRIVATE, ANDROID) {
    SYSNAME = Android
} else:equals(QKIT_PRIVATE, ANDROIDX86) {
    SYSNAME = Android_x86
}

#if you dont modify Qt Creator default build directory, you may need mod this path variable.
#link operation all will need this variable
QKIT_STD_DIR = $${QT_VERSION}/$${SYSNAME}/$${BUILD}

message(qqt_qkit.pri)
message(Build $${TARGET} to $${QKIT_PRIVATE} \(QKIT=$${QKIT_PRIVATE} is configed in project build page.\) )
message(Build $${TARGET} at $${QKIT_STD_DIR} \(Qt Kit page FileSystem Name=$${SYSNAME}\) )
message(Build $${TARGET} on $${QMAKE_HOST.os} \(Operating System=$${QMAKE_HOST.os}\) )
message(Build $${TARGET} Qt Kit page FileSystem Name is decided by env variable QKIT. Please set it. )
