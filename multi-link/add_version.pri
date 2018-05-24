#################################################################
##project $${TARGET} version pri
#################################################################
#拷贝到用户用户工程目录里使用用
##add_sdk need this pri

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
#User Make Version Flow
#-------------------------------------------------------------------------------
defineTest(add_version) {
    isEmpty(4):error(add_version(major, minor, patch, build) need four arguments.)

    APP_MAJOR_VERSION = $$1
    APP_MINOR_VERSION = $$2
    APP_PATCH_VERSION = $$3
    APP_BUILD_VERSION = $$4

    APP_VERSION1 = $$get_version_string_1( $${APP_MAJOR_VERSION} )
    APP_VERSION2 = $$get_version_string_2( $${APP_MAJOR_VERSION}, $${APP_MINOR_VERSION} )
    APP_VERSION3 = $$get_version_string_3( $${APP_MAJOR_VERSION}, $${APP_MINOR_VERSION}, $${APP_PATCH_VERSION} )
    APP_VERSION4 = $$get_version_string_4( $${APP_MAJOR_VERSION}, $${APP_MINOR_VERSION}, $${APP_PATCH_VERSION}, $${APP_BUILD_VERSION} )

    message ($${TARGET} version: V$$APP_VERSION4)

    #这两个变量赋值是什么关系？
    #qmake 域变量
    APP_VERSION = $${APP_VERSION3}
    #源代码 域宏
    DEFINES += VERSION=$${APP_VERSION}
    DEFINES += LIB_VERSION=$${APP_VERSION}
    DEFINES += APP_VERSION=$${APP_VERSION}

    #工程版本设置
    VERSION = $${APP_VERSION}
    VER_MAJ = $$APP_MAJOR_VERSION
    VER_MIN = $$APP_MINOR_VERSION
    VER_PAT = $$APP_PATCH_VERSION

    export(DEFINES)
    export(VERSION)
    export(VER_MAJ)
    export(VER_MIN)
    export(VER_PAT)
    export(APP_MAJOR_VERSION)
    export(APP_MINOR_VERSION)
    export(APP_PATCH_VERSION)
    export(APP_BUILD_VERSION)

    return (1)
}
