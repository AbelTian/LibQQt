#---------------------------------------------------------------------
#应用程序语言翻译qmake文件。通过qmake与编译调用。
#如果需要增加某国语言，add_language(...)即可。
#---------------------------------------------------------------------
#$$APP_SOURCE_PWD on mac TRANSLATIONS error, why?
#APP_SOURCE_PWD=$${PWD}
#用户在macOS下下使用PWD符号

##############################################################################
#内部函数
##############################################################################
defineReplace(get_lupdate_language){
    #pro file
    propath = $$1
    !isEmpty(2): error("get_lupdate_language(propath) requires one argument")
    isEmpty(1): error("get_lupdate_language(propath) requires one argument")
    command =
    command = lupdate $${propath}
    #message($${command})
    return ($${command})
}

defineReplace(get_lrelease_language){
    filepath = $$1
    filename = $$2
    !isEmpty(3): error("get_lrelease_language(filepath, filename) requires two argument")
    isEmpty(2): error("get_lrelease_language(filepath, filename) requires two argument")
    command =
    command = lrelease $${filepath}/$${filename}.ts -qm $${filepath}/$${filename}.qm
    #message($${command})
    return ($${command})
}

##############################################################################
#公开函数
##############################################################################
defineTest(lupdate_language){
    #pro file
    propath = $$1
    !isEmpty(2): error("lupdate_language(propath) requires one argument")
    isEmpty(1): error("lupdate_language(propath) requires one argument")

    command =
    command += $$get_lupdate_language($${propath})

    !isEmpty(QMAKE_PRE_LINK):QMAKE_PRE_LINK+=$$CMD_SEP
    QMAKE_PRE_LINK += $${command}
    export(QMAKE_PRE_LINK)

    return (true)
}

#输入.ts的 路径 和 文件名(不带后缀)
defineTest(lrelease_language){
    filepath = $$1
    filename = $$2
    !isEmpty(3): error("lrelease_language(filepath, filename) requires two argument")
    isEmpty(2): error("lrelease_language(filepath, filename) requires two argument")

    command =
    command += $$get_lrelease_language($${filepath}, $${filename})

    !isEmpty(QMAKE_PRE_LINK):QMAKE_PRE_LINK+=$$CMD_SEP
    QMAKE_PRE_LINK += $${command}
    export(QMAKE_PRE_LINK)

    return (true)
}

#输入pro全路径 .ts路径 .ts文件名(不带后缀，相当于需要添加的语言类型)
#注意：.ts路径必要使用$${PWD}符号
defineTest(add_language){
    propath = $$1
    filepath = $$2
    filename = $$3
    isEmpty(3)|!isEmpty(4): error("add_language(propath, filepath, filename) requires three argument")

    #翻译语言起效
    TRANSLATIONS += $${filepath}/$${filename}.ts
    export(TRANSLATIONS)

    command =
    command += $$get_lupdate_language($${propath}) $$CMD_SEP
    command += $$get_lrelease_language($${filepath}, $${filename})

    !isEmpty(QMAKE_PRE_LINK):QMAKE_PRE_LINK+=$$CMD_SEP
    QMAKE_PRE_LINK += $${command}
    export(QMAKE_PRE_LINK)

    return (1)
}

defineTest(add_zh_CN_en_US){
    propath = $$1
    filepath = $$2
    isEmpty(2)|!isEmpty(3): error("add_zh_CN_en_US(propath, filepath) requires two argument")

    #翻译语言起效
    TRANSLATIONS += $${filepath}/zh_CN.ts $${filepath}/en_US.ts
    export(TRANSLATIONS)

    command =
    command += $$get_lupdate_language($${propath}) $$CMD_SEP
    command += $$get_lrelease_language($${filepath}, zh_CN) $$CMD_SEP
    command += $$get_lrelease_language($${filepath}, en_US)

    !isEmpty(QMAKE_PRE_LINK):QMAKE_PRE_LINK+=$$CMD_SEP
    QMAKE_PRE_LINK += $${command}
    export(QMAKE_PRE_LINK)

    return (1)
}

############################################################################################################################################################
#以下翻译过程qmake的时候执行
#以下函数设计思路正常，但是qmake执行堵死，请勿使用，无奈。
############################################################################################################################################################
#输入pro的完整路径
defineTest(qmake_lupdate_language){
    #pro file
    propath = $$1
    !isEmpty(2): error("qmake_lupdate_language(propath) requires one argument")
    isEmpty(1): error("qmake_lupdate_language(propath) requires one argument")
    command = $$get_lupdate_language($${propath})
    system_errcode($${command}): return (true)
    return (false)
}

#输入.ts的 路径 和 文件名(不带后缀)
defineTest(qmake_lrelease_language){
    filepath = $$1
    filename = $$2
    !isEmpty(3): error("qmake_lrelease_language(filepath, filename) requires two argument")
    isEmpty(2): error("qmake_lrelease_language(filepath, filename) requires two argument")
    command = $$get_lrelease_language($${filepath}, $${filename})
    system_errcode($${command}): return (true)
    return (false)
}

defineTest(add_qmake_language){
    propath = $$1
    filepath = $$2
    filename = $$3
    isEmpty(3)|!isEmpty(4): error("add_qmake_language(propath, filepath, filename) requires three argument")

    #翻译语言起效
    TRANSLATIONS += $${filepath}/$${filename}.ts
    export(TRANSLATIONS)

    qmake_lupdate_language($${propath})
    qmake_lrelease_language($${filepath}, $${filename})

    return (1)
}

#专门为中英文定义的
defineTest(add_qmake_zh_CN_en_US){
    propath = $$1
    filepath = $$2
    isEmpty(2)|!isEmpty(3): error("add_qmake_zh_CN_en_US(propath, filepath) requires two argument")

    #翻译语言起效
    TRANSLATIONS += $${filepath}/zh_CN.ts $${filepath}/en_US.ts
    export(TRANSLATIONS)

    qmake_lupdate_language($${propath})
    qmake_lrelease_language($${filepath}, zh_CN)
    qmake_lrelease_language($${filepath}, en_US)

    return (1)
}
