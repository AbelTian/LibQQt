#---------------------------------------------------------------------
#应用程序语言翻译qmake文件。通过qmake与编译调用。
#如果需要增加某国语言，修改这个文件即可。
#拷贝到用户app工程目录里使用用
#---------------------------------------------------------------------
#$$APP_SOURCE_PWD on mac TRANSLATIONS error, why?
APP_SOURCE_PWD=$${PWD}

TRANSLATIONS = $${PWD}/AppRoot/lang/zh_CN.ts $${PWD}/AppRoot/lang/en_US.ts

defineReplace(lupdate_language){
    command =
    #only pro path
    command += $$get_lupdate_language($${PWD}/$${TARGET}.pro)
    return ($$command)
}

defineReplace(lrelease_language){
    command =
    #only pro path
    command += $$get_lrelease_language($${PWD}/../AppRoot/lang, zh_CN) $$CMD_SEP
    command += $$get_lrelease_language($${PWD}/../AppRoot/lang, en_US)
    return ($$command)
}

##########################################################################################
##Work flow
##########################################################################################
QMAKE_PRE_LINK += $$CMD_SEP $$lupdate_language()
QMAKE_PRE_LINK += $$CMD_SEP $$lrelease_language()
