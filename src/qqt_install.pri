################################################
##qqt_install.pri
##install to Qt library
##install to SDK path
##link from build
##please don't modify this pri
##need qqt_version.pri qqt_header.pri qqt_source.pri
################################################


################################################
##QQt install functions
##variable can be private and default inherit
################################################
defineReplace(create_dir_struct) {
    #if it's qt library, don't create
    command =
    !equals(QQT_SDK_PWD , $$[QT_INSTALL_DATA]){
        !contains(QKIT_PRIVATE, macOS) {
            command += $$MK_DIR $$QQT_INC_DIR $$CMD_SEP
        }
        command += $$MK_DIR $$QQT_LIB_DIR $$CMD_SEP
        command += $$MK_DIR $$QQT_CMAKE_DIR $$CMD_SEP
        command += $$MK_DIR $$QQT_PRI_PATH $$CMD_SEP
    }
    return ($$command)
}

defineReplace(create_windows_sdk) {
    #need cd sdk root

    command =
    #copy header
    command += $${COPY_DIR} $${QQT_SRC_PWD}\\*.h* $${QQT_INC_DIR} $$CMD_SEP
    #should be *.dll *.lib
    command += $${COPY_DIR} $${QQT_BUILD_PWD}\\* $${QQT_LIB_DIR}

    return ($$command)
}

defineReplace(create_linux_sdk) {
    #need cd sdk root
    copy_command = $$get_copy_dir_and_file($${QQT_SRC_PWD}, "*.h*", $${QQT_INC_DIR})
    command =
    command += $${copy_command} $$CMD_SEP
    #should be *.so.* *.a
    command += $$COPY_DIR $${QQT_BUILD_PWD}/* $${QQT_LIB_DIR}

    return ($$command)
}

defineReplace(create_mac_sdk){
    #need cd framework root
    #QQT_BUILD_PWD MODULE_NAME QQT_MAJOR_VERSION
    QQT_BUNDLE_VER_DIR   = Versions/$${QQT_MAJOR_VERSION}
    QQT_BUNDLE_CUR_DIR   = Versions/Current
    QQT_BUNDLE_INC_DIR   = $${QQT_BUNDLE_VER_DIR}/Headers
    QQT_BUNDLE_RES_DIR   = $${QQT_BUNDLE_VER_DIR}/Resources
    QQT_BUNDLE_EXE_FILE  = $${QQT_BUNDLE_VER_DIR}/$${MODULE_NAME}

    QQT_BUNDLE_CUR_INC_DIR   = $${QQT_BUNDLE_CUR_DIR}/Headers
    QQT_BUNDLE_CUR_RES_DIR   = $${QQT_BUNDLE_CUR_DIR}/Resources
    QQT_BUNDLE_CUR_EXE_FILE  = $${QQT_BUNDLE_CUR_DIR}/$${MODULE_NAME}

    QQT_BUNDLE_CUR_LINK  = Current
    QQT_BUNDLE_INC_LINK  = Headers
    QQT_BUNDLE_RES_LINK  = Resources
    QQT_BUNDLE_EXE_LINK  = $${MODULE_NAME}

    command =
    command += $$MK_DIR $$QQT_BUNDLE_VER_DIR $$CMD_SEP
    command += $$MK_DIR $$QQT_BUNDLE_INC_DIR $$CMD_SEP
    #copy lib
    #should be *
    command += $$COPY_DIR $${QQT_BUILD_PWD}/$${MODULE_NAME}.framework/$${QQT_BUNDLE_VER_DIR}/* $$QQT_BUNDLE_VER_DIR $$CMD_SEP
    #copy header
    copy_command = $$get_copy_dir_and_file($${QQT_SRC_PWD}, "*.h*", $${QQT_BUNDLE_INC_DIR})
    command += $${copy_command} $$CMD_SEP
    #link header current resources
    command += $$CD Versions $$CMD_SEP
    command += $$LN $${QQT_MAJOR_VERSION} $${QQT_BUNDLE_CUR_LINK} $$CMD_SEP
    command += $$CD .. $$CMD_SEP
    command += $$LN $$QQT_BUNDLE_CUR_INC_DIR  $${QQT_BUNDLE_INC_LINK} $$CMD_SEP
    command += $$LN $$QQT_BUNDLE_CUR_RES_DIR  $${QQT_BUNDLE_RES_LINK} $$CMD_SEP
    command += $$LN $$QQT_BUNDLE_CUR_EXE_FILE $${QQT_BUNDLE_EXE_LINK}
    lessThan(QT_MAJOR_VERSION, 5){
        command += &&
        command += chmod +x $${PWD}/mac_deploy_qt4.sh &&
        command += $${PWD}/mac_deploy_qt4.sh $${QQT_BUNDLE_VER_DIR}/$${MODULE_NAME}
    }
    return ($$command)
}

defineReplace(create_qt_lib_pri){
    #need cd sdk root
    #QQT_BASE_DIR MODULE_NAME QQT_VERSION MODULE_CNAME
    ##write qt_lib_qqtcore.pri

    command =
    command += $$get_empty_file($${QQT_PRI_FILEPATH}) $$CMD_SEP
    command += echo "QT.$${module_name}.VERSION = $${QQT_VERSION}" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.name = $${MODULE_NAME}"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.module = $${MODULE_NAME}"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    contains(QKIT_PRIVATE, WIN32|WIN64) {
        command += echo "QT.$${module_name}.libs = \$$QT_MODULE_LIB_BASE"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.bins = \$$QT_MODULE_BIN_BASE"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${module_name}.libs = '\$$QT_MODULE_LIB_BASE'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.bins = '\$$QT_MODULE_BIN_BASE'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    }
    contains(QKIT_PRIVATE, WIN32|WIN64) {
        command += echo "QT.$${module_name}.includes = \$$QT_MODULE_INCLUDE_BASE \$$QT_MODULE_INCLUDE_BASE/$${MODULE_NAME}" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.frameworks = " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.module_config = v2 " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    }else:equals(QKIT_PRIVATE, macOS) {
        command += echo "QT.$${module_name}.includes = '\$$QT_MODULE_LIB_BASE/$${MODULE_NAME}.framework/Headers'"  >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.frameworks = '\$$QT_MODULE_LIB_BASE'" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.module_config = v2 lib_bundle" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${module_name}.includes = '\$$QT_MODULE_INCLUDE_BASE \$$QT_MODULE_INCLUDE_BASE/$${MODULE_NAME}'" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.frameworks = " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
        command += echo "QT.$${module_name}.module_config = v2 " >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    }
    greaterThan(QT_MAJOR_VERSION, 4):{
        command += echo "QT.$${module_name}.depends = core sql network gui xml widgets" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    } else {
        command += echo "QT.$${module_name}.depends = core sql network gui xml" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    }
    command += echo "QT.$${module_name}.uses =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.DEFINES = QQT_LIBRARY" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.enabled_features =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT.$${module_name}.disabled_features =" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT_CONFIG +=" >> $${QQT_PRI_FILEPATH} $$CMD_SEP
    command += echo "QT_MODULES += $${module_name}" >> $${QQT_PRI_FILEPATH}
    return ($$command)
}

defineReplace(create_library_sdk){
    #need cd sdk root
    #QQT_BASE_DIR MODULE_NAME QQT_VERSION MODULE_CNAME
    #$1 $2 $3...
    command =
    command += $$RM_DIR $${QQT_SDK_PWD} $$CMD_SEP
    command += $$MK_DIR $${QQT_SDK_PWD} $$CMD_SEP
    command += $$CD $${QQT_SDK_PWD} $$CMD_SEP
    command += $$create_dir_struct()

    contains(QKIT_PRIVATE, WIN32|WIN64) {
        #message(create QQt windows struct library)
        command += $$create_windows_sdk() $$CMD_SEP
        command += $$COPY $${QQT_BUILD_PWD}\*.prl lib $$CMD_SEP
    } else {
        contains(QKIT_PRIVATE, macOS) {
            #message(create QQt mac bundle framework)
            command += $$MK_DIR lib/$${MODULE_NAME}.framework $$CMD_SEP
            command += $$CD lib/$${MODULE_NAME}.framework $$CMD_SEP
            command += $$create_mac_sdk() $$CMD_SEP
            command += $$CD ../../ $$CMD_SEP
            #create prl
            command += $$COPY $${QQT_BUILD_PWD}/$${MODULE_NAME}.framework/$${MODULE_NAME}.prl lib/$${MODULE_NAME}.framework/$${MODULE_NAME}.prl $$CMD_SEP
        } else {
            #message(create QQt linux struct library)
            command += $$create_linux_sdk() $$CMD_SEP
            command += $$COPY $${QQT_BUILD_PWD}/*.prl lib $$CMD_SEP
        }
    }
    command += $$create_qt_lib_pri()
    return ($$command)
}

################################################
##QQt install workflow
##used to output sdk, can't support windows and ios
##this don't need any other path set.
################################################
defineReplace(create_qqt_sdk){
    #-------module name QQt
    MODULE_NAME=QQt
    module_name = $$lower($${MODULE_NAME})

    #qqt defined these dir struct, used from qt library
    QQT_INC_DIR = include/$${MODULE_NAME}
    QQT_LIB_DIR = lib
    QQT_CMAKE_DIR=lib/cmake/$${MODULE_NAME}
    QQT_PRI_PATH=mkspecs/modules
    QQT_PRI_FILEPATH=$${QQT_PRI_PATH}/qt_lib_$${module_name}.pri

    contains(QKIT_PRIVATE, WIN32|WIN64) {
        #on windows every path must use \ sep.
        QQT_SRC_PWD~=s,/,\\,g
        QQT_BUILD_PWD~=s,/,\\,g
        QQT_SDK_PWD~=s,/,\\,g

        QQT_INC_DIR~=s,/,\\,g
        QQT_LIB_DIR = lib
        QQT_CMAKE_DIR~=s,/,\\,g
        QQT_PRI_PATH~=s,/,\\,g
        QQT_PRI_FILEPATH~=s,/,\\,g

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
    command = $$create_library_sdk()

    #message ($$command)
    return ($$command)
}

#if you want to use QQt with QT += QQt please open this feature
#unimplete: CONFIG += install_to_qt_library
defineReplace(install_to_qt_library){
    MODULE_NAME=QQt
    #QQT_BUILD_PWD
    QQT_SDK_PWD=$$[QT_INSTALL_DATA]
    message(QQt sdk install here:$${QQT_SDK_PWD})
}
