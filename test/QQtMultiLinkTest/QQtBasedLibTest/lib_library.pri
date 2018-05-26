################################################
##qqt_library.pri, linking workflow
##QQt based app please include this pri to link qqt library
##dependence qqt_version.pri qqt_header.pri
##从SDK ROOT链接QQt Library
##don't modify this pri file, if you catch any issure, please make issure
##https://gitee.com/drabel/LibQt/issues/new?issue%5Bassignee_id%5D=0&issue%5Bmilestone_id%5D=0
##2017年10月29日08:54:28
################################################

################################################
##link QQt logic function
################################################
defineReplace(link_qqt_library) {
    contains(DEFINES, __DARWIN__) {
        LINK += -F$${QQT_LIB_PWD}
        LINK += -framework QQt
    } else {
        LINK += -L$${QQT_LIB_PWD}
        #win can't with the blank! error: -l QQt
        LINK += -lQQt
    }
    return ($${LINK})
}

#在Mac上，Creator运行app前必须拷贝依赖，是个deploy过程。
#Mac不用于其他操作系统，对于bundle，任何运行时刻都需要拷贝依赖，包括build完成后。
#build path里的app bundle和deploy root里的app bundle要运行都必须拷贝好QQt，这是macOS特有的。
#这个函数可以修正任何位置的app bundle
#在链接QQt的时候，也就是这里 修正app bundle有利于统一app deploy过程。app_deploy没有做这个工作，和其他平台相近似。
defineReplace(deploy_qqt_to_app_deploy_path_on_mac) {
    #need QQT_BUILD_PWD
    deploy_path = $$1
    isEmpty(1): error("deploy_qqt_to_app_deploy_path_on_mac(deploy_path) requires one argument")
    create_command = $$create_mac_sdk()
    APP_DEST_DIR=$${deploy_path}
    isEmpty(APP_DEST_DIR):APP_DEST_DIR=.
    command =
    command += chmod +x $${PWD}/linux_cur_path.sh &&
    command += . $${PWD}/linux_cur_path.sh &&
    command += rm -rf $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    #拷贝QQt.framework到app bundle里。其实，是直接在app里执行的。这个会移动走。
    command += mkdir -p $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += cd $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    #修复QQt.framework里的快捷方式
    command += $${create_command} &&
    command += chmod +x $${PWD}/linux_cd_path.sh &&
    command += . $${PWD}/linux_cd_path.sh &&

    #Qt Creator create framework but use absolute path to make link
    #QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
    #        $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks &&
    #更改app bundle链接QQt的位置。
    command += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         $${APP_DEST_DIR}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    command += macdeployqt $${APP_DEST_DIR}/$${TARGET}.app -verbose=1

    lessThan(QT_MAJOR_VERSION, 5){
        command += &&
        command += chmod +x $${PWD}/mac_deploy_qt4.sh &&
        command += $${PWD}/mac_deploy_qt4.sh $${APP_DEST_DIR}/$${TARGET}.app/Contents/MacOS/$${TARGET}
    }
    #message($$command)
    return ($${command})
}

#这个macOS POST LINK其实是因为qmake的一个bug而添加的，qmake生成的framework结构有错误，里边的快捷方式都不对，所以在此修正。
#这个只是bug1，还有bug2.
#Creator在运行app之前，如果不把这些依赖拷贝到中间目标生成目录里，就不能运行。这是macOS特有的，别的系统都不需要。所以这个修正发生在
#这个是bug2，还有bug3
#qmake在苹果下生成的app，默认链接QQt的位置是绝对路径！这里修复为相对路径。拷贝过去也失去了相对路径。
#好了，经过以上修复，app可以直接使用了。
defineReplace(fix_app_bundle_with_qqt_in_building_path_on_mac) {
    #need QQT_BUILD_PWD
    APP_DEST_DIR=$${DESTDIR}
    isEmpty(APP_DEST_DIR):APP_DEST_DIR=.
    command = $$deploy_qqt_to_app_deploy_path_on_mac($${APP_DEST_DIR})
    return ($$command)
}

#这个函数用于Lib链接QQt的时候对Lib的针对qmake生成bundle的bug的修正，
#把生成的lib的ln绝对路径更换为相对路径
#这个事情发生在build station里，Creator要运行这个里边需要依赖这个工作。
#multi link需要发布这个lib也需要依赖这个工作。
#必经之路。
defineReplace(fix_lib_in_building_path_on_mac) {
    #need QQT_BUILD_PWD
    deploy_path = $$1
    isEmpty(1): error("fix_lib_in_building_path_on_mac(deploy_path) requires one argument")
    create_command = $$create_mac_sdk()
    APP_DEST_DIR=$${deploy_path}
    isEmpty(APP_DEST_DIR):APP_DEST_DIR=.
    command =
    command += chmod +x $${PWD}/linux_cur_path.sh &&
    command += . $${PWD}/linux_cur_path.sh &&
    command += rm -rf $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += mkdir -p $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += cd $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += $${create_command} &&
    command += chmod +x $${PWD}/linux_cd_path.sh &&
    command += . $${PWD}/linux_cd_path.sh &&

    #Qt Creator create framework but use absolute path to make link
    #QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
    #        $${APP_DEST_DIR}/$${TARGET}.app/Contents/Frameworks &&
    command += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         $${APP_DEST_DIR}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    command += macdeployqt $${APP_DEST_DIR}/$${TARGET}.app -verbose=1

    lessThan(QT_MAJOR_VERSION, 5){
        command += &&
        command += chmod +x $${PWD}/mac_deploy_qt4.sh &&
        command += $${PWD}/mac_deploy_qt4.sh $${APP_DEST_DIR}/$${TARGET}.app/Contents/MacOS/$${TARGET}
    }
    #message($$command)
    return ($${command})
}

################################################
##link qqt work flow
################################################
#-------module name QQt
MODULE_NAME=QQt
module_name = $$lower($${MODULE_NAME})

#-------define the all path
#QQT std dir is not same to app std dir
QQT_STD_DIR = QQt/$${QKIT_STD_DIR}
#link from build need this, if you havent mod QQt.pro, this can only be two value, qqt's: [src]/$DESTDIR
QQT_DST_DIR = src/bin
#create platform sdk need this
QQT_SRC_PWD=$${PWD}

#need use qqt subdir proj
QQT_BUILD_PWD=$${QQT_BUILD_ROOT}/$${QQT_STD_DIR}/$${QQT_DST_DIR}
#sdk path
QQT_SDK_PWD = $${QQT_SDK_ROOT}/$${QQT_STD_DIR}
#message(QQt sdk install here:$${QQT_SDK_PWD})

contains(CONFIG, link_from_sdk) {
    QQT_LIB_PWD = $${QQT_SDK_ROOT}/$${QQT_STD_DIR}/lib
} else: contains(CONFIG, link_from_build)  {
    QQT_LIB_PWD = $${QQT_BUILD_ROOT}/$${QQT_STD_DIR}/$${QQT_DST_DIR}
}

#这里不仅仅目标为windows的时候，才会转换，
#开发Host为Windows的时候，都要转换。
#contains(QKIT_PRIVATE, WIN32||WIN64) {
equals(QMAKE_HOST.os, Windows) {
    QQT_BUILD_ROOT~=s,/,\\,g
    QQT_SDK_ROOT~=s,/,\\,g
    APP_DEPLOY_ROOT~=s,/,\\,g

    QKIT_STD_DIR~=s,/,\\,g
    QQT_STD_DIR~=s,/,\\,g
    QQT_DST_DIR~=s,/,\\,g
    QQT_BUILD_PWD~=s,/,\\,g
    QQT_SDK_PWD~=s,/,\\,g
    QQT_LIB_PWD~=s,/,\\,g
}

#我准备把install qqt sdk移动到更合适的地方。
contains(CONFIG, link_from_sdk) {
    #create sdk first
    QMAKE_PRE_LINK += $$create_qqt_sdk()
    #private struct
    equals(QKIT_PRIVATE, macOS) {
        #Fix app里、lib里的路径问题
        #
        contains(CONFIG, app_bundle) : !contains(CONFIG, lib_bundle) {
            QMAKE_POST_LINK += $$fix_app_bundle_with_qqt_in_building_path_on_mac()
        }
    }
} else : contains(CONFIG, link_from_build) {
    equals(QKIT_PRIVATE, macOS) {
        contains(CONFIG, app_bundle) : !contains(CONFIG, lib_bundle) {
            QMAKE_POST_LINK += $$fix_app_bundle_with_qqt_in_building_path_on_mac()
        }
    }
}

#这个地方的判断方式有两种，使用QKIT_PRIVATE也可以。
#是不是只有armeabi-v7a需要这个extra？
contains(ANDROID_TARGET_ARCH, armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $${QQT_LIB_PWD}/lib$${MODULE_NAME}.so
}

#从SDK里链接QQt
LIBS += $$link_qqt_library()

message (Link QQt from: $${QQT_LIB_PWD})
message(Link QQt to $${TARGET} $${QKIT_PRIVATE} on $${QMAKE_HOST.os} \
    \(Qt Kit page FileSystem Name=$${SYSNAME}. Operating System=$${QMAKE_HOST.os}.\) )
#TARGET must be equals to pro name ? no, TARGET must be placeed before qqt_library.pri
#qmake pro pri is sequential
message(Build $${TARGET} at $${OUT_PWD}/$${QKIT_STD_DIR})
