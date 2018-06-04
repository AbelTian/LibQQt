#------------------------------------------------------------------------------------------------
##add_sdk.pri, making sdk function

##install to SDK path
##把Library按照SDK格式安装到LIB_SDK_ROOT
##发布到sdk是为Multi link准备的。
##依赖add_version.pri

##please don't modify this pri
#------------------------------------------------------------------------------------------------

##SDK格式
##LibGroupName/Windows/include/libName/***.h
##                    /bin/libName<ver>[d].dll
##                    /lib/libName<ver>[d].a .lib

##LibGroupName/Linux/include/libName/***.h
##                  /bin/
##                  /lib/libName.so.*

##LibGroupName/macOS/include/libName/***.h
##                  /bin/
##                  /lib/libName<ver>.dylib
##                      /libName[_debug].dylib

##LibGroupName/macOS/include/libName/***.h
##                  /bin/
##                  /lib/libName.framework/Headers/***.h
##                                        /libName[_debug]

#固定SDK结构，操作系统中直接使用这个目录结构。
#没有SDK SubDir结构！

################################################
#add_sdk
#add_sdk_from_subdirs
#add_sdk_to_Qt
#add_sdk_header
#del_sdk

ADD_SDK_PRI_PWD = $${PWD}

#在build path修复app (macOS专有)
#copy lib
#fix bundle路径链接
#不修复，直接拷贝，所有的快捷方式会丢失，变成实体
#拷贝temp进行修复。
defineReplace(get_add_mac_sdk_fix_building_framework) {

    APP_DEST_DIR=$${DESTDIR}
    isEmpty(APP_DEST_DIR):APP_DEST_DIR=.

    libname = $$TARGET
    librealname = $$TARGET
    libtempname = $${libname}_temp

    command =
    command += chmod +x $${ADD_SDK_PRI_PWD}/linux_cur_path.sh &&
    command += . $${ADD_SDK_PRI_PWD}/linux_cur_path.sh &&

    #create temp
    command += $$MK_DIR $${APP_DEST_DIR}/$${libtempname}.framework &&
    #进去
    command += cd $${APP_DEST_DIR}/$${libtempname}.framework &&

    #修复framework里的快捷方式
    #need APP_BUILD_PWD
    create_command = $$get_add_mac_sdk($${libname}, $${librealname})
    command += $${create_command} &&

    command += chmod +x $${ADD_SDK_PRI_PWD}/linux_cd_path.sh &&
    command += . $${ADD_SDK_PRI_PWD}/linux_cd_path.sh &&

    #拷贝prl到新的里
    command += $$COPY $${APP_DEST_DIR}/$${libname}.framework/$${librealname}.prl $${APP_DEST_DIR}/$${libtempname}.framework/$${librealname}.prl $$CMD_SEP

    #del 原先的
    command += $$RM_DIR $${APP_DEST_DIR}/$${libname}.framework &&
    #rename 临时的 framework 到原先的
    command += $$MOVE $${APP_DEST_DIR}/$${libtempname}.framework $${APP_DEST_DIR}/$${libname}.framework

    #message($$command)
    return ($${command})
}


################################################
##lib install functions
##variable can be private and default inherit
##内部实现
################################################
defineReplace(get_add_sdk_dir_struct) {
    #if it's qt library, don't create
    command =
    !equals(LIB_SDK_PWD , $$[QT_INSTALL_DATA]){
        contains(QSYS_PRIVATE, macOS):contains(TEMPLATE, lib_bundle) {
            #bundle模式没有include目录
        } else {
            command += $$MK_DIR $$LIB_INC_DIR $$CMD_SEP
        }
        command += $$MK_DIR $$LIB_BIN_DIR $$CMD_SEP
        command += $$MK_DIR $$LIB_LIB_DIR $$CMD_SEP
        command += $$MK_DIR $$LIB_CMAKE_DIR $$CMD_SEP
        command += $$MK_DIR $$LIB_PRI_PATH
    }
    return ($$command)
}

defineReplace(get_add_windows_sdk) {
    #need cd sdk root

    command =
    #copy header
    command += $${COPY_DIR} $${LIB_SRC_PWD}\\*.h* $${LIB_INC_DIR} $$CMD_SEP
    #should be *.dll *.lib
    command += $${COPY_DIR} $${LIB_BUILD_PWD}\\* $${LIB_LIB_DIR} $$CMD_SEP
    #move *.dll
    command += $${MOVE} $${LIB_LIB_DIR}\\*.dll $${LIB_BIN_DIR}

    return ($$command)
}

defineReplace(get_add_linux_sdk) {
    #need cd sdk root
    copy_command = $$get_copy_dir_and_file($${LIB_SRC_PWD}, "*.h*", $${LIB_INC_DIR})
    command =
    command += $${copy_command} $$CMD_SEP
    #should be *.so.* *.a
    command += $$COPY_DIR $${LIB_BUILD_PWD}/* $${LIB_LIB_DIR}

    return ($$command)
}

#理论上，只要用户设置了Version，就能读到Version Major
#add_version里面有初始化版本号，所以，用户什么都不设置，将会是0版本号。
#从libname.framework拷贝到当前新建的framework 内部为librealname
defineReplace(get_add_mac_sdk){
    #need cd framework root
    #LIB_BUILD_PWD libname libmajorver

    libname = $$1
    librealname = $$2
    libmajorver = $$3
    #isEmpty(1): error("get_add_mac_sdk(libname, librealname, libmajorver) requires at last one argument")
    !isEmpty(4): error("get_add_mac_sdk(libname, librealname, libmajorver) requires at most three argument")

    isEmpty(1):libname = $$TARGET_NAME
    isEmpty(2):librealname = $${libname}
    isEmpty(3):libmajorver = $$VER_MAJ
    isEmpty(libmajorver){
        error(Have you modifyed add_version.pri, please dont modify it.)
    }

    #这里的isEmpty没有用。
    #isEmpty(libmajorver):libmajorver = $$system(readlink $${LIB_BUILD_PWD}/$${libname}.framework/Versions/Current)
    #message($${LIB_BUILD_PWD}/$${libname}.framework/Versions/Current $$TARGET major version $$libmajorver)

    LIB_BUNDLE_VER_DIR   = Versions/$${libmajorver}
    LIB_BUNDLE_CUR_DIR   = Versions/Current
    LIB_BUNDLE_INC_DIR   = $${LIB_BUNDLE_VER_DIR}/Headers
    LIB_BUNDLE_RES_DIR   = $${LIB_BUNDLE_VER_DIR}/Resources
    LIB_BUNDLE_EXE_FILE  = $${LIB_BUNDLE_VER_DIR}/$${librealname}

    LIB_BUNDLE_CUR_INC_DIR   = $${LIB_BUNDLE_CUR_DIR}/Headers
    LIB_BUNDLE_CUR_RES_DIR   = $${LIB_BUNDLE_CUR_DIR}/Resources
    LIB_BUNDLE_CUR_EXE_FILE  = $${LIB_BUNDLE_CUR_DIR}/$${librealname}

    LIB_BUNDLE_CUR_LINK  = Current
    LIB_BUNDLE_INC_LINK  = Headers
    LIB_BUNDLE_RES_LINK  = Resources
    LIB_BUNDLE_EXE_LINK  = $${librealname}

    command =
    command += $$MK_DIR $$LIB_BUNDLE_VER_DIR $$CMD_SEP
    command += $$MK_DIR $$LIB_BUNDLE_INC_DIR $$CMD_SEP
    #copy lib
    #should be *
    command += $$COPY_DIR $${LIB_BUILD_PWD}/$${libname}.framework/$${LIB_BUNDLE_VER_DIR}/* $$LIB_BUNDLE_VER_DIR $$CMD_SEP
    #copy header
    copy_command = $$get_copy_dir_and_file($${LIB_SRC_PWD}, "*.h*", $${LIB_BUNDLE_INC_DIR})
    command += $${copy_command} $$CMD_SEP
    #link header current resources
    command += $$CD Versions $$CMD_SEP
    command += $$LN $${libmajorver} $${LIB_BUNDLE_CUR_LINK} $$CMD_SEP
    command += $$CD .. $$CMD_SEP
    command += $$LN $$LIB_BUNDLE_CUR_INC_DIR  $${LIB_BUNDLE_INC_LINK} $$CMD_SEP
    command += $$LN $$LIB_BUNDLE_CUR_RES_DIR  $${LIB_BUNDLE_RES_LINK} $$CMD_SEP
    command += $$LN $$LIB_BUNDLE_CUR_EXE_FILE $${LIB_BUNDLE_EXE_LINK}
    lessThan(QT_MAJOR_VERSION, 5){
        command += $$CMD_SEP
        command += chmod +x $${ADD_SDK_PRI_PWD}/mac_deploy_qt4.sh $$CMD_SEP
        command += $${ADD_SDK_PRI_PWD}/mac_deploy_qt4.sh $${LIB_BUNDLE_VER_DIR}/$${libname}
    }
    return ($$command)
}

#这个函数是支持发布Qt Library用的，add_sdk用到了。
defineReplace(get_add_Qt_lib_pri){
    #need cd sdk root
    #LIB_BASE_DIR libname LIB_VERSION MODULE_CNAME
    ##write qt_lib_qqtcore.pri

    command =
    command += $$get_empty_file($${LIB_PRI_FILEPATH}) $$CMD_SEP
    command += echo "QT.$${liblowername}.VERSION = $${APP_VERSION}" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${liblowername}.name = $${libname}"  >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${liblowername}.module = $${libname}"  >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    contains(QSYS_PRIVATE, Win32|Windows|Win64) {
        command += echo "QT.$${liblowername}.libs = \$$QT_MODULE_LIB_BASE"  >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.bins = \$$QT_MODULE_BIN_BASE"  >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${liblowername}.libs = '\$$QT_MODULE_LIB_BASE'"  >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.bins = '\$$QT_MODULE_BIN_BASE'"  >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    }
    contains(QSYS_PRIVATE, Win32|Windows|Win64) {
        command += echo "QT.$${liblowername}.includes = \$$QT_MODULE_INCLUDE_BASE \$$QT_MODULE_INCLUDE_BASE/$${libname}" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.frameworks = " >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.module_config = v2 " >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    }else:equals(QSYS_PRIVATE, macOS) {
        command += echo "QT.$${liblowername}.includes = '\$$QT_MODULE_LIB_BASE/$${libname}.framework/Headers'"  >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.frameworks = '\$$QT_MODULE_LIB_BASE'" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.module_config = v2 lib_bundle" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${liblowername}.includes = '\$$QT_MODULE_INCLUDE_BASE \$$QT_MODULE_INCLUDE_BASE/$${libname}'" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.frameworks = " >> $${LIB_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${liblowername}.module_config = v2 " >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    }
    greaterThan(QT_MAJOR_VERSION, 4):{
        command += echo "QT.$${liblowername}.depends = core sql network gui xml widgets" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${liblowername}.depends = core sql network gui xml" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    }
    command += echo "QT.$${liblowername}.uses =" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${liblowername}.DEFINES = LIB_LIBRARY" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${liblowername}.enabled_features =" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${liblowername}.disabled_features =" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT_CONFIG +=" >> $${LIB_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT_MODULES += $${liblowername}" >> $${LIB_PRI_FILEPATH}
    return ($$command)
}

################################################
##Lib deploy sdk workflow
##SDK发布过程
################################################

defineReplace(get_add_sdk_work_flow){
    #need cd sdk root

    libname = $$1
    librealname = $$2
    #isEmpty(1): error("get_add_mac_sdk(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_mac_sdk(libname, librealname) requires at most two argument")
    isEmpty(1):libname = $$TARGET_NAME
    isEmpty(2): librealname = $${libname}
    liblowername = $$lower($${librealname})

    command =
    contains(QSYS_PRIVATE, macOS) {
        #在编译路径里，创作一次sdk，完成framework链接等的修复工作
        command += $$get_add_mac_sdk_fix_building_framework() $$CMD_SEP
        #command += echo $$libname fix framework success. $$CMD_SEP
    }
    #command += $$RM_DIR $${LIB_SDK_PWD} $$CMD_SEP
    command += $$MK_DIR $${LIB_SDK_PWD} $$CMD_SEP
    command += $$CD $${LIB_SDK_PWD} $$CMD_SEP
    command += $$get_add_sdk_dir_struct() $$CMD_SEP

    #这里不是目标为Windows才拷贝，而是开发机是Windows就得这么拷贝。
    #Windows下，Win目标、Android目标都走这里。
    #contains(QSYS_PRIVATE, Win32|Windows|Win64) {
    equals(QMAKE_HOST.os, Windows) {
        #message(create lib windows struct library)
        command += $$get_add_windows_sdk() $$CMD_SEP
        command += $$COPY $${LIB_BUILD_PWD}\\*.prl lib $$CMD_SEP
    } else {
        #macOS lib_bundle make sdk
        contains(QSYS_PRIVATE, macOS):contains(CONFIG, lib_bundle) {
            #message(create lib mac bundle framework)
            command += $$MK_DIR lib/$${libname}.framework $$CMD_SEP
            command += $$CD lib/$${libname}.framework $$CMD_SEP
            command += $$get_add_mac_sdk($${librealname}, $${librealname}) $$CMD_SEP
            command += $$CD ../../ $$CMD_SEP
            #create prl
            command += $$COPY $${LIB_BUILD_PWD}/$${librealname}.framework/$${librealname}.prl lib/$${libname}.framework/$${librealname}.prl $$CMD_SEP
        } else {
            #Android在linux开发机下也会走这里，Android目标，Lib可以发布Win和Linux两种格式的SDK。
            #message(create lib linux struct library)
            #macOS no bundle 也会走这里，已经支持非bundle
            command += $$get_add_linux_sdk() $$CMD_SEP
            command += $$COPY $${LIB_BUILD_PWD}/*.prl lib $$CMD_SEP
        }
    }

    command += $$get_add_Qt_lib_pri()
    #$$CMD_SEP
    #command += echo $$libname create sdk success.

    return ($$command)
}

################################################
##Lib deploy sdk work flow
##初始化SDK发布过程需要的变量
################################################
defineReplace(get_add_sdk_private){

    libname = $$1
    librealname = $$2
    #isEmpty(1): error("get_add_mac_sdk(libname, librealname) requires at last one argument")
    !isEmpty(3): error("get_add_mac_sdk(libname, librealname) requires at most two argument")
    isEmpty(1):libname = $$TARGET_NAME
    isEmpty(2): librealname = $${libname}
    liblowername = $$lower($${librealname})

    #qqt defined these dir struct, used from qt library
    LIB_INC_DIR = include/$${TARGET_NAME}
    LIB_BIN_DIR = bin
    LIB_LIB_DIR = lib
    LIB_CMAKE_DIR=lib/cmake/$${libname}
    LIB_PRI_PATH=mkspecs/modules
    LIB_PRI_FILEPATH=$${LIB_PRI_PATH}/qt_lib_$${liblowername}.pri

    #不仅仅发布目标为Windows的时候需要改变，
    #开发Host是Windows的时候都要改变。路径问题是两种操作系统固有的痛。
    #contains(QSYS_PRIVATE, Win32|Windows|Win64) {
    equals(QMAKE_HOST.os, Windows) {
        #on windows every path must use \ sep.
        LIB_SRC_PWD~=s,/,\\,g
        LIB_BUILD_PWD~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g

        LIB_INC_DIR~=s,/,\\,g
        LIB_BIN_DIR = bin
        LIB_LIB_DIR = lib
        LIB_CMAKE_DIR~=s,/,\\,g
        LIB_PRI_PATH~=s,/,\\,g
        LIB_PRI_FILEPATH~=s,/,\\,g

        #ignored
        HEADERS_WIN=$${HEADERS}
        HEADERS_WIN~=s,/,\\,g
        #on windows, copy all *.h*, include closed feature header.
        #qmake regexp use perl grammer
        #HEADERS_WIN~=s/[d ]+/h+/g how to mod space to +
    }
    #create library struct
    #create platform sdk
    #create mkspec module pri
    command = $$get_add_sdk_work_flow($${libname}, $${librealname})

    #message ($$command)
    return ($${command})
}


################################################
##用户调用的函数
################################################
#依赖
LIB_SDK_SOURCE_PWD = $$PWD
LIB_SDK_BUILD_DESTDIR = $$DESTDIR
defineTest(add_sdk_src_dir){
    LIB_SDK_SOURCE_PWD = $$1
    export(LIB_SDK_SOURCE_PWD)
    return (1)
}

#libgroupname<主目录名>
#libname 这里 libname是内定的 就是用户设置的TARGET 没有修饰的那个 如果想发布成随意的样子....
#librealname 用户自定义名称，一般省略 = 修饰名是没有问题的。
#libsrcdir PWD
#libdstdir DESTDIR
defineTest(add_sdk){
    #isEmpty(1):error(add_sdk(libgroupname, libsrcdir, libdstdir, librealname) need at least one argument)
    #!isEmpty(5): error("add_sdk(libgroupname, libsrcdir, libdstdir, librealname) requires at most four argument")

    contains(QSYS_PRIVATE, macOS) {
        #equals(APP_MAJOR_VERSION, 0):message(add_sdk(libname, libsrcdir, libdstdir) macos app major version is "0," have you setted it?)
    }

    #LIB_SDK_ROOT下

    #主目录名
    libgroupname = $$TARGET_NAME
    !isEmpty(1):libgroupname=$$1

    #create platform sdk need this
    #源代码目录
    LIB_SRC_PWD=$${PWD}
    !isEmpty(2):LIB_SRC_PWD=$$2

    #编译目标位置
    LIB_DST_DIR=$$DESTDIR
    !isEmpty(3):LIB_DST_DIR = $$3

    #lib名 用户不能改变
    libname = $$TARGET_NAME

    #经过修饰的lib名
    librealname = $$TARGET
    #用户可以指定，但是必须自定义TARGET名字。非标准。这样会影响链接时候的名字，用户需要自定义链接。
    !isEmpty(4) {
        librealname = $$4
        TARGET = $$librealname
        export(TARGET)
    }

    #liblowername依赖librealname
    liblowername = $$lower($${librealname})

    #need use qqt subdir proj
    LIB_BUILD_PWD=$${APP_BUILD_ROOT}/$${libname}/$${QSYS_STD_DIR}
    !isEmpty(LIB_DST_DIR):LIB_BUILD_PWD=$${LIB_BUILD_PWD}/$${LIB_DST_DIR}

    #LIB std dir is not same to app std dir
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}

    #sdk path
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    #message($${TARGET_NAME} sdk install here:$${LIB_SDK_PWD})

    #这里不仅仅目标为windows的时候，才会转换，
    #开发Host为Windows的时候，都要转换。
    #contains(QSYS_PRIVATE, Win32|Windows||Win64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_BUILD_ROOT~=s,/,\\,g
        LIB_SDK_ROOT~=s,/,\\,g
        APP_DEPLOY_ROOT~=s,/,\\,g

        QSYS_STD_DIR~=s,/,\\,g
        LIB_STD_DIR~=s,/,\\,g
        LIB_DST_DIR~=s,/,\\,g
        LIB_BUILD_PWD~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
    }

    command += $$get_add_sdk_private($${libname}, $${librealname})
    #message($$command)

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    QMAKE_POST_LINK += $$command

    export(QMAKE_POST_LINK)

    return (1)
}

#依赖 libname libsrcdir libdstdir
#添加一个参数 subdirs列表 包含subdirs层 子文件夹层 说的是build路径比较深的情况
#libgroupname 一般为不修饰的target 可以为空
#PWD
#DESTDIR
#sub层列表 从头到尾 如果为空，则等于add_sdk()
#librealname 建议用户不要设置
#支持Qt5，不支持Qt4. Qt4 qmake比较落后。
defineTest(add_sdk_from_subdirs){
    #isEmpty(1):error(add_subdir_sdk(libname, libsrcdir, libdstdir) need at last one argument)
    contains(QSYS_PRIVATE, macOS) {
        #equals(APP_MAJOR_VERSION, 0):message(add_sdk(libname, libsrcdir, libdstdir) macos app major version is "0," have you setted it?)
    }

    #LIB_SDK_ROOT下

    #主目录名
    libgroupname = $$TARGET_NAME
    !isEmpty(1):libgroupname=$$1

    #create platform sdk need this
    #源代码目录
    LIB_SRC_PWD=$${PWD}
    !isEmpty(2):LIB_SRC_PWD=$$2

    #编译目标位置
    LIB_DST_DIR=$$DESTDIR
    !isEmpty(3):LIB_DST_DIR = $$3

    #lib名 用户不能改变
    libname = $$TARGET_NAME

    #经过修饰的lib名
    librealname = $$TARGET
    #用户可以指定，但是必须自定义TARGET名字。非标准。这样会影响链接时候的名字，用户需要自定义链接。
    !isEmpty(5) {
        librealname = $$5
        TARGET = $$librealname
        export(TARGET)
    }

    #liblowername依赖librealname
    liblowername = $$lower($${librealname})

    #LIB std dir is not same to app std dir
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}

    #编译目录的完全位置
    LIB_BUILD_PWD=
    isEmpty(4){
        #add sdk level
    LIB_BUILD_PWD=$${APP_BUILD_ROOT}/$${libname}/$${QSYS_STD_DIR}
    !isEmpty(LIB_DST_DIR):LIB_BUILD_PWD=$${LIB_BUILD_PWD}/$${LIB_DST_DIR}
    } else {
        #sub dir level
        LIB_SUBDIR_LIST=$$4
        first_value = $$first(LIB_SUBDIR_LIST)
        LIB_BUILD_PWD=$${APP_BUILD_ROOT}/$${first_value}/$${QSYS_STD_DIR}
        LIB_SUBDIR_LIST -= $$first_value
        for(dir, LIB_SUBDIR_LIST) {
            LIB_BUILD_PWD=$${LIB_BUILD_PWD}/$${dir}
        }
        LIB_BUILD_PWD=$${LIB_BUILD_PWD}/$${TARGET}
        !isEmpty(LIB_DST_DIR):LIB_BUILD_PWD=$${LIB_BUILD_PWD}/$${LIB_DST_DIR}
    }

    #sdk path
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    #message($${TARGET} sdk install here:$${LIB_SDK_PWD})

    #这里不仅仅目标为windows的时候，才会转换，
    #开发Host为Windows的时候，都要转换。
    #contains(QSYS_PRIVATE, Win32|Windows||Win64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_BUILD_ROOT~=s,/,\\,g
        LIB_SDK_ROOT~=s,/,\\,g
        APP_DEPLOY_ROOT~=s,/,\\,g

        QSYS_STD_DIR~=s,/,\\,g
        LIB_STD_DIR~=s,/,\\,g
        LIB_DST_DIR~=s,/,\\,g
        LIB_BUILD_PWD~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
    }

    command += $$get_add_sdk_private($${libname}, $${librealname})
    #message($$command)

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    QMAKE_POST_LINK += $$command

    export(QMAKE_POST_LINK)

    return (1)
}

#if you want to use QQt with QT += QQt please open this feature
defineTest(add_sdk_to_Qt){
    #isEmpty(1):error(add_sdk_to_Qt(libname, libsrcdir, libdstdir) need at last one argument)

    contains(QSYS_PRIVATE, macOS) {
        #equals(APP_MAJOR_VERSION, 0):message(add_sdk(libname, libsrcdir, libdstdir) macos app major version is "0," have you setted it?)
    }

    #LIB_SDK_ROOT下

    #主目录名
    libgroupname = $$TARGET_NAME
    !isEmpty(1):libgroupname=$$1

    #create platform sdk need this
    #源代码目录
    LIB_SRC_PWD=$${PWD}
    !isEmpty(2):LIB_SRC_PWD=$$2

    #编译目标位置
    LIB_DST_DIR=$$DESTDIR
    !isEmpty(3):LIB_DST_DIR = $$3

    #lib名 用户不能改变
    libname = $$TARGET_NAME

    #经过修饰的lib名
    librealname = $$TARGET
    #用户可以指定，但是必须自定义TARGET名字。非标准。这样会影响链接时候的名字，用户需要自定义链接。
    !isEmpty(4) {
        librealname = $$4
        TARGET = $$librealname
        export(TARGET)
    }

    #liblowername依赖librealname
    liblowername = $$lower($${librealname})

    #need use qqt subdir proj
    LIB_BUILD_PWD=$${APP_BUILD_ROOT}/$${libname}/$${QSYS_STD_DIR}
    !isEmpty(LIB_DST_DIR):LIB_BUILD_PWD=$${LIB_BUILD_PWD}/$${LIB_DST_DIR}

    #LIB std dir is not same to app std dir
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}

    #sdk path
    LIB_SDK_PWD = $$[QT_INSTALL_DATA]
    #message(QQt sdk install here:$${LIB_SDK_PWD})

    #这里不仅仅目标为windows的时候，才会转换，
    #开发Host为Windows的时候，都要转换。
    #contains(QSYS_PRIVATE, Win32|Windows||Win64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_BUILD_ROOT~=s,/,\\,g
        LIB_SDK_ROOT~=s,/,\\,g
        APP_DEPLOY_ROOT~=s,/,\\,g

        QSYS_STD_DIR~=s,/,\\,g
        LIB_STD_DIR~=s,/,\\,g
        LIB_DST_DIR~=s,/,\\,g
        LIB_BUILD_PWD~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
    }

    command += $$get_add_sdk_private($${libname}, $${librealname})
    #message($$command)

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    QMAKE_POST_LINK += $$command

    export(QMAKE_POST_LINK)

    return (1)
}

defineTest(del_sdk){
    #isEmpty(1):error(del_sdk(libname, libsrcdir, libdstdir) need at last one argument)

    contains(QSYS_PRIVATE, macOS) {
        #equals(APP_MAJOR_VERSION, 0):message(add_sdk(libname, libsrcdir, libdstdir) macos app major version is "0," have you setted it?)
    }

    #LIB_SDK_ROOT下

    #主目录名
    libgroupname = $$TARGET_NAME
    !isEmpty(1):libgroupname=$$1

    #create platform sdk need this
    #源代码目录
    LIB_SRC_PWD=$${PWD}
    !isEmpty(2):LIB_SRC_PWD=$$2

    #编译目标位置
    LIB_DST_DIR=$$DESTDIR
    !isEmpty(3):LIB_DST_DIR = $$3

    #lib名 用户不能改变
    #约束：用户设置的TARGET，必须和pro的名字一样。
    libname = $$TARGET_NAME

    #经过修饰的lib名
    librealname = $$TARGET
    #用户可以指定，但是必须自定义TARGET名字。非标准。这样会影响链接时候的名字，用户需要自定义链接。
    !isEmpty(4) {
        librealname = $$4
        TARGET = $$librealname
        export(TARGET)
    }

    #liblowername依赖librealname
    liblowername = $$lower($${librealname})

    #need use qqt subdir proj
    LIB_BUILD_PWD=$${APP_BUILD_ROOT}/$${libname}/$${QSYS_STD_DIR}
    !isEmpty(LIB_DST_DIR):LIB_BUILD_PWD=$${LIB_BUILD_PWD}/$${LIB_DST_DIR}

    #LIB std dir is not same to app std dir
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}

    #sdk path
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    #message(QQt sdk install here:$${LIB_SDK_PWD})
    LIB_SDK_ALL = $${LIB_SDK_PWD}/*

    #这里不仅仅目标为windows的时候，才会转换，
    #开发Host为Windows的时候，都要转换。
    #contains(QSYS_PRIVATE, Win32|Windows||Win64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_BUILD_ROOT~=s,/,\\,g
        LIB_SDK_ROOT~=s,/,\\,g
        APP_DEPLOY_ROOT~=s,/,\\,g

        QSYS_STD_DIR~=s,/,\\,g
        LIB_STD_DIR~=s,/,\\,g
        LIB_DST_DIR~=s,/,\\,g
        LIB_BUILD_PWD~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g
        LIB_SDK_ALL~=s,/,\\,g
    }

    command += $$RM_DIR $${LIB_SDK_ALL}
    #message($$command)

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK += $$CMD_SEP
    QMAKE_POST_LINK += $$command

    export(QMAKE_POST_LINK)

    return (1)
}

#发布没有后缀名的头文件
#sdkroot下，主目录名
#库名字 没有修饰的库名字
#类名
#保存位置 相对路径 不写则为根目录。
#头文件 不设置 为空 则为类名小写。
defineTest(add_sdk_header){
    isEmpty(3):error(add_sdk_header(libgroupname, libname, classname, headerdir, headername) need at least one argument)

    libgroupname = $$1
    libname = $$2
    classname = $$3
    headerdir = $$4
    headername = $$5

    isEmpty(libname):libname = $$libgroupname
    isEmpty(headername):headername = $$lower($${classname}).h

    #LIB std dir is not same to app std dir
    LIB_STD_DIR = $${libgroupname}/$${QSYS_STD_DIR}

    #sdk path
    LIB_SDK_PWD = $${LIB_SDK_ROOT}/$${LIB_STD_DIR}
    #message(QQt sdk install here:$${LIB_SDK_PWD})

    LIB_INC_DIR = include/$${libname}
    contains(QMAKE_HOST.os, Darwin){
        contains(CONFIG, lib_bundle) {
            LIB_INC_DIR = lib/$${libname}.framework/Headers
        }
    }

    !isEmpty(headerdir):headerdir=$${headerdir}/
    HEADER_FILE = $${headerdir}$${classname}

    #这里不仅仅目标为windows的时候，才会转换，
    #开发Host为Windows的时候，都要转换。
    #contains(QSYS_PRIVATE, Win32|Windows||Win64) {
    equals(QMAKE_HOST.os, Windows) {
        APP_BUILD_ROOT~=s,/,\\,g
        LIB_SDK_ROOT~=s,/,\\,g
        APP_DEPLOY_ROOT~=s,/,\\,g

        QSYS_STD_DIR~=s,/,\\,g
        LIB_STD_DIR~=s,/,\\,g
        LIB_DST_DIR~=s,/,\\,g
        LIB_BUILD_PWD~=s,/,\\,g
        LIB_SDK_PWD~=s,/,\\,g

        LIB_INC_DIR~=s,/,\\,g
        HEADER_FILE~=s,/,\\,g
    }

    command =
    command += $$CD $${LIB_SDK_PWD} $$CMD_SEP
    command += $$CD $${LIB_INC_DIR} $$CMD_SEP

    contains(QMAKE_HOST.os, Windows){
        command += $${ADD_SDK_PRI_PWD}/win_write_header.bat $${headername} $${HEADER_FILE}
    } else {
        command += chmod +x $${ADD_SDK_PRI_PWD}/linux_write_header.sh $$CMD_SEP
        command += $${ADD_SDK_PRI_PWD}/linux_write_header.sh $${headername} $${HEADER_FILE}
    }

    !isEmpty(QMAKE_POST_LINK):QMAKE_POST_LINK+=$$CMD_SEP
    QMAKE_POST_LINK += $$command
    export(QMAKE_POST_LINK)

    return(1)
}
