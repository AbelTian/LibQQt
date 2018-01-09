#################################################################
##project QQt version pri
##please don't modify this pri
#################################################################
##qqt_library qqt_install all need this pri

QQT_MAJOR_VERSION = 2
QQT_MINOR_VERSION = 1
QQT_PATCH_VERSION = 6
QQT_BUILD_VERSION = 0

QQT_VERSION1 = $${QQT_MAJOR_VERSION}
QQT_VERSION2 = $${QQT_MAJOR_VERSION}.$${QQT_MINOR_VERSION}
QQT_VERSION3 = $${QQT_MAJOR_VERSION}.$${QQT_MINOR_VERSION}.$${QQT_PATCH_VERSION}
QQT_VERSION4 = $${QQT_MAJOR_VERSION}.$${QQT_MINOR_VERSION}.$${QQT_PATCH_VERSION}.$${QQT_BUILD_VERSION}
QQT_VERSION = $${QQT_VERSION3}

message (Build QQt version: $$QQT_VERSION4)
