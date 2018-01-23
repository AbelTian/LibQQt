#################################################################
##project QQt version pri
##please don't modify this pri
#################################################################
##qqt_library qqt_install all need this pri
defineReplace(get_version_string_1) {
    major_version = $$1
    !isEmpty(2): error("get_version_string_1(major) requires one arguments")
    isEmpty(1): error("get_version_string_1(major) requires one arguments")
    command = $${major_version}
    return ($$command)
}
defineReplace(get_version_string_2) {
    major_version = $$1
    minor_version = $$2
    !isEmpty(3): error("get_version_string_2(major, minor) requires two arguments")
    isEmpty(2): error("get_version_string_2(major, minor) requires two arguments")
    command = $${major_version}.$${minor_version}
    return ($$command)
}
defineReplace(get_version_string_3) {
    major_version = $$1
    minor_version = $$2
    patch_version = $$3
    !isEmpty(4): error("get_version_string_3(major, minor, patch) requires three arguments")
    isEmpty(3): error("get_version_string_3(major, minor, patch) requires three arguments")
    command = $${major_version}.$${minor_version}.$${patch_version}
    return ($$command)
}
defineReplace(get_version_string_4) {
    major_version = $$1
    minor_version = $$2
    patch_version = $$3
    build_version = $$4
    !isEmpty(5): error("get_version_string_4(major, minor, patch, build) requires four arguments")
    isEmpty(4): error("get_version_string_4(major, minor, patch, build) requires four arguments")
    command = $${major_version}.$${minor_version}.$${patch_version}.$${build_version}
    return ($$command)
}

#-------------------------------------------------------------------------------
#QQt Make Version Flow
#-------------------------------------------------------------------------------
QQT_MAJOR_VERSION = 2
QQT_MINOR_VERSION = 1
QQT_PATCH_VERSION = 6
QQT_BUILD_VERSION = 0

QQT_VERSION1 = $$get_version_string_1( $${QQT_MAJOR_VERSION} )
QQT_VERSION2 = $$get_version_string_2( $${QQT_MAJOR_VERSION}, $${QQT_MINOR_VERSION} )
QQT_VERSION3 = $$get_version_string_3( $${QQT_MAJOR_VERSION}, $${QQT_MINOR_VERSION}, $${QQT_PATCH_VERSION} )
QQT_VERSION4 = $$get_version_string_4( $${QQT_MAJOR_VERSION}, $${QQT_MINOR_VERSION}, $${QQT_PATCH_VERSION}, $${QQT_BUILD_VERSION} )
#这两个变量赋值是什么关系？
QQT_VERSION = $${QQT_VERSION3}
DEFINES += QQT_VERSION=$${QQT_VERSION}
message (Build QQt version: $$QQT_VERSION4)
