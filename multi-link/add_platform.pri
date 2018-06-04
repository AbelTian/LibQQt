#-----------------------------------------------------------------------------
#app_platform.pri
#这个pri决定编译目标平台
#-----------------------------------------------------------------------------
#从环境变量读取QSYS保存为qmake变量QSYS_PRIVATE
QSYS_PRIVATE = $$(QSYS)
contains(QSYS_PRIVATE, Embedded) {
    #embedded common macro
    DEFINES += __EMBEDDED_LINUX__
} else:contains(QSYS_PRIVATE, Arm32) {
    DEFINES += __EMBEDDED_LINUX__
    #arm32 private
    DEFINES += __ARM_LINUX__
} else:contains(QSYS_PRIVATE, Mips32) {
    DEFINES += __EMBEDDED_LINUX__
    #mips32 private
    DEFINES += __MIPS_LINUX__
} else:contains(QSYS_PRIVATE, Linux) {
    DEFINES += __LINUX__
} else:contains(QSYS_PRIVATE, Linux64) {
    DEFINES += __LINUX64__
} else:contains(QSYS_PRIVATE, Win32|Windows) {
    DEFINES += __WIN32__
} else:contains(QSYS_PRIVATE, Win64) {
    DEFINES += __WIN64__
} else:contains(QSYS_PRIVATE, macOS) {
    DEFINES += __DARWIN__
} else:contains(QSYS_PRIVATE, iOS) {
    DEFINES += __IOS__
} else:contains(QSYS_PRIVATE, iOSSimulator) {
    DEFINES += __IOS__
    #TODO:no qcustomplot word printer process
} else:contains(QSYS_PRIVATE, Android) {
    DEFINES += __ANDROID__
} else:contains(QSYS_PRIVATE, AndroidX86) {
    DEFINES += __ANDROID__
    DEFINES += __ANDROIDX86__ #可能废弃
}

BUILD=
CONFIG(debug, debug|profile|release):BUILD=Debug
CONFIG(profile, debug|profile|release):BUILD=Profile
CONFIG(release, debug|profile|release):BUILD=Release

QSYS_STD_DIR = $${QSYS_PRIVATE}/$${QT_VERSION}/$${BUILD}
QSYS_STD_DIR = $${QSYS_PRIVATE}/$${QT_VERSION}
QSYS_STD_DIR = $${QSYS_PRIVATE}

message(add_platform.pri)
message(Build $${TARGET} to $${QSYS_PRIVATE} \(QSYS=$${QSYS_PRIVATE} is configed in project build page.\) )
message(Build $${TARGET} at $${QSYS_STD_DIR} \(Qt Kit page FileSystem Name=$${QSYS_PRIVATE}\) )
message(Build $${TARGET} on $${QMAKE_HOST.os} \(Operating System=$${QMAKE_HOST.os}\) )
isEmpty(QSYS_PRIVATE) : message(Build $${TARGET} Qt Kit page FileSystem Name is decided by env variable QSYS. Please set it. )

isEmpty(QSYS_PRIVATE) {
    message(1. you should change qt default build directory to your-pc-build-station/%{CurrentProject:Name}/%{CurrentKit:FileSystemName})
    message(2. env variable QSYS is required! pleace check app_platform.pri)
    error(error occured! please check build output panel.)
}

isEmpty(QSYS_PRIVATE) {
    message(env variable QSYS is required!)
    message(pleace check app_platform.pri)
    error("error occured, please check build output panel.")
}


#in theory, this should not be limited to 4.8.0, no limit is good.
lessThan(QT_VERSION, 4.8.0) {
    message(A. ensure your compiler support c++11 feature)
    message(B. suggest Qt version >= 4.8.0)
    #error(  error occured!)
}
