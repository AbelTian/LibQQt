#---------------------------------------------------------------------
#应用程序语言翻译qmake文件。通过qmake与编译调用。
#如果需要增加某国语言，修改这个文件即可。
#---------------------------------------------------------------------
#$$APP_SOURCE_PWD on mac TRANSLATIONS error, why?
APP_SOURCE_PWD=$${PWD}

TRANSLATIONS = $${PWD}/../AppRoot/lang/zh_CN.ts $${PWD}/../AppRoot/lang/en_US.ts

defineReplace(lupdate_language){
    command =
    command += $$CMD_SEP
    #only pro path
    command += $$get_lupdate_language($${PWD}/$${TARGET}.pro)
    return ($$command)
}

defineReplace(lrelease_language){
    command =
    command += $$CMD_SEP
    #only pro path
    command += $$get_lrelease_language($${PWD}/../AppRoot/lang, zh_CN) $$CMD_SEP
    command += $$get_lrelease_language($${PWD}/../AppRoot/lang, en_US)
    return ($$command)
}

QMAKE_PRE_LINK += $$lupdate_language()
QMAKE_PRE_LINK += $$lrelease_language()
