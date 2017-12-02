################################################
##qqt_library.pri
##QQt based app please include this pri to link qqt library
##dependence qqt_version.pri qqt_header.pri
##don't modify this pri file, if you catch any issure, please make issure
##https://gitee.com/drabel/LibQt/issues/new?issue%5Bassignee_id%5D=0&issue%5Bmilestone_id%5D=0
##2017年10月29日08:54:28
################################################
#TARGET must be equals to pro name ? no, TARGET must be placeed before qqt_library.pri
#qmake pro pri is sequential
message(Link QQt to $${TARGET} $${QKIT_PRIVATE} \
    at $${QT_VERSION} $${SYSNAME} $${BUILD} \
    on $${QMAKE_HOST.os})


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

#在Mac上，运行前必须拷贝依赖，是个deploy过程。
#Mac不用于其他操作系统，对于bundle，任何运行时刻都需要拷贝依赖，包括build完成后。
defineReplace(deploy_qqt_on_mac) {
    #need QQT_BUILD_PWD
    deploy_path = $$1
    isEmpty(1): error("deploy_qqt_on_mac(deploy_path) requires one argument")
    create_command = $$create_mac_sdk()
    DEPLOY_DESTDIR=$${deploy_path}
    isEmpty(DEPLOY_DESTDIR):DEPLOY_DESTDIR=.
    command =
    command += chmod +x $${PWD}/linux_cur_path.sh &&
    command += . $${PWD}/linux_cur_path.sh &&
    command += rm -rf $${DEPLOY_DESTDIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += mkdir -p $${DEPLOY_DESTDIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += cd $${DEPLOY_DESTDIR}/$${TARGET}.app/Contents/Frameworks/QQt.framework &&
    command += $${create_command} &&
    command += chmod +x $${PWD}/linux_cd_path.sh &&
    command += . $${PWD}/linux_cd_path.sh &&

    #Qt Creator create framework but use absolute path to make link
    #QMAKE_POST_LINK += cp -rf $${QQT_LIB_PWD}/QQt.framework \
    #        $${DEPLOY_DESTDIR}/$${TARGET}.app/Contents/Frameworks &&
    command += install_name_tool -change QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         @rpath/QQt.framework/Versions/$${QQT_MAJOR_VERSION}/QQt \
         $${DEPLOY_DESTDIR}/$${TARGET}.app/Contents/MacOS/$${TARGET} &&
    command += macdeployqt $${DEPLOY_DESTDIR}/$${TARGET}.app -verbose=1

    lessThan(QT_MAJOR_VERSION, 5){
        command += &&
        command += chmod +x $${PWD}/mac_deploy_qt4.sh &&
        command += $${PWD}/mac_deploy_qt4.sh $${DEPLOY_DESTDIR}/$${TARGET}.app/Contents/MacOS/$${TARGET}
    }
    #message($$command)
    return ($$command)
}

defineReplace(copy_qqt_on_mac) {
    #need QQT_BUILD_PWD
    command = $$deploy_qqt_on_mac($${DESTDIR})
    return ($$command)
}


################################################
##link qqt work flow
################################################
#-------module name QQt
MODULE_NAME=QQt
module_name = $$lower($${MODULE_NAME})

#-------define the all path
#create platform sdk need this
QQT_SRC_PWD=$${PWD}
#need use qqt subdir proj
QQT_BUILD_PWD=$${QQT_BUILD_ROOT}/$${QQT_STD_DIR}/$${QQT_DST_DIR}
#sdk path
QQT_SDK_PWD = $${QQT_SDK_ROOT}/$${QQT_STD_DIR}
#message(QQt sdk install here:$${QQT_SDK_PWD})

contains(CONFIG, link_from_sdk) {
    #create sdk first
    QMAKE_PRE_LINK += $$create_qqt_sdk()
    #private struct
    QQT_LIB_PWD = $${QQT_SDK_ROOT}/$${QQT_STD_DIR}/lib
    equals(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$copy_qqt_on_mac()
    }
}

contains(CONFIG, link_from_build) {
    QQT_LIB_PWD = $${QQT_BUILD_ROOT}/$${QQT_STD_DIR}/$${QQT_DST_DIR}
    equals(QKIT_PRIVATE, macOS) {
        QMAKE_POST_LINK += $$copy_qqt_on_mac()
    }
}

LIBS += $$link_qqt_library()
message (Link QQt from: $${QQT_LIB_PWD})

