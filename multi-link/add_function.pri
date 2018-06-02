#------------------------------------------------------------------
#app_function.pri
#please dont modify this pri
#2017年12月01日14:05:43
#------------------------------------------------------------------
contains(QMAKE_HOST.os,Windows) {
    SCRIPT_SUFFIX=bat
    CMD_SEP = &
    MOVE = move /y
    COPY = copy /y
    COPY_DIR = xcopy /s /q /y /i /r /h
    MK_DIR = mkdir
    RM = del /q
    CD = cd /d
    RM_DIR = rd /s /q
    #PATH_SEP=\\
} else:contains(QMAKE_HOST.os, Darwin) {
    SCRIPT_SUFFIX=sh
    CMD_SEP = &&
    MOVE = mv
    COPY = cp -f
    COPY_DIR = cp -R -L -f -apc
    MK_DIR = mkdir -p
    RM = rm -f
    CD = cd
    LN = ln -sfn
    RM_DIR = rm -rf
    #PATH_SEP=/
} else {
    SCRIPT_SUFFIX=sh
    CMD_SEP = &&
    MOVE = mv
    COPY = cp -f
    COPY_DIR = cp -rf
    MK_DIR = mkdir -p
    RM = rm -f
    CD = cd
    LN = ln -sf
    RM_DIR = rm -rf
    #PATH_SEP=/
}

################################################
##get command string 这些函数一般内部使用
################################################
defineReplace(get_mkdir) {
    filepath = $$1
    isEmpty(1): error("get_mkdir(filepath) requires one argument")
    command = $${MK_DIR} $${filepath}
    #message($${command})
    return ($${command})
}
defineReplace(get_errcode) {
    cmd_exec = $$1
    isEmpty(1): error("get_errcode(command) requires one argument")
    contains(QMAKE_HOST.os,Windows) {
        command = $${cmd_exec} >nul & echo %errorlevel%
    } else {
        command = "$${cmd_exec}" 2>/dev/null; echo $?
    }
    #message($$command)
    return ($$command)
}
defineReplace(get_empty_file) {
    filename = $$1
    isEmpty(1): error("get_empty_file(filename) requires one argument")
    command =
    equals(QMAKE_HOST.os, Windows) {
        command = echo . 2> $${filename}
    } else {
        command = echo 2> $${filename}
    }
    return ($$command)
}
defineReplace(get_write_file) {
    filename = $$1
    variable = $$2
    !isEmpty(3): error("get_write_file(name, content) requires two arguments.")
    isEmpty(2): error("get_write_file(name, content) requires two arguments.")
    command = echo $${variable} >> $${filename}
    return ($$command)
}

LINUX_CP_FILES = $${PWD}/linux_cp_files.sh
defineReplace(get_copy_dir_and_file) {
    source = $$1
    pattern = $$2
    target = $$3
    !isEmpty(4): error("get_copy_dir_and_file(source, pattern, target) requires three arguments.")
    isEmpty(3) : error("get_copy_dir_and_file(source, pattern, target) requires three arguments.")
    command =
    equals(QMAKE_HOST.os, Windows) {
        command = $${COPY_DIR} $${source}\\$${pattern} $${target}
    } else {
        command = chmod +x $${LINUX_CP_FILES} $${CMD_SEP}
        command += $${LINUX_CP_FILES} $${source} $${pattern} $${target}
    }
    return ($$command)
}

WIN_READ_INI = $${PWD}/win_read_ini.bat
LINUX_READ_INI = $${PWD}/linux_read_ini.sh
defineReplace(get_read_ini_command) {
    file_name = $$1
    sect_name = $$2
    key_name = $$3
    !isEmpty(4): error("get_read_ini_command(file, section, key) requires three arguments.")
    isEmpty(3) : error("get_read_ini_command(file, section, key) requires three arguments.")
    command =
    equals(QMAKE_HOST.os, Windows) {
        #if use $${PWD}/...directoly this PWD is the refrence pri file path
        command = $${WIN_READ_INI} %file_name% %sect_name% %key_name%
    } else {
        command = chmod +x $${LINUX_READ_INI} $$CMD_SEP
        command += $${LINUX_READ_INI} $${file_name} $${sect_name} $${key_name}
    }
    #message ($$command)
    return ($$command)
}

WIN_WRITE_INI = $${PWD}/win_write_ini.bat
LINUX_WRITE_INI = $${PWD}/linux_write_ini.sh
defineReplace(get_write_ini_command) {
    file_name = $$1
    sect_name = $$2
    key_name = $$3
    new_value = $4
    !isEmpty(5): error("get_write_ini_command(file, section, key, value) requires four arguments.")
    isEmpty(4) : error("get_write_ini_command(file, section, key, value) requires four arguments.")
    command =
    equals(QMAKE_HOST.os, Windows) {
        #if use $${PWD}/...directoly this PWD is the refrence pri file path
        command = $${WIN_WRITE_INI} %file_name% %sect_name% %key_name% %new_value%
    } else {
        command = chmod +x $${LINUX_WRITE_INI} $$CMD_SEP
        command += $${LINUX_WRITE_INI} $${file_name} $${sect_name} $${key_name} $${new_value}
    }
    #message ($$command)
    return ($$command)
}

defineReplace(get_md5_command) {
    filename = $$1
    isEmpty(1): error("get_md5_command(filename) requires one argument")
    !isEmpty(2): error("get_md5_command(filename) requires one argument")
    command =
    equals(QMAKE_HOST.os, Windows) {
        command = md5 -n $${filename}
    } else:mac* {
        command = md5 -q $${filename}
    } else {
        command = md5sum -b $${filename} | cut -d \' \' -f1
    }
    return ($$command)
}
defineReplace(get_user_home) {
    command =
    equals(QMAKE_HOST.os, Windows) {
        command = echo %HOMEDRIVE%%HOMEPATH%
    } else {
        command = echo $HOME
    }
    #message ($$command)
    return ($$command)
}

defineReplace(get_user_config_path) {
    command =
    #windows下编译android工程，qmake CONFIG里面不包含win32而是android、linux、unix。
    #win32 只有在目标是win32的时候才会在CONFIG里面出现。开发平台用QMAKE_HOST.os
    #注意：qmake在windows平台下，无论目标，明令行一律按照windows控制台风格。不以目标区分，Attention!。
    #win32 {
    equals(QMAKE_HOST.os, Windows) {
        command = echo %APPDATA%
    } else {
        command = echo $HOME
    }
    #message ($$command)
    return ($$command)
}

#将路径里的[反]斜杠转换为开发机上的格式。
#注意：不是按照目标进行转换的，所以仅仅用于命令行操作的FLOW。
#defineReplace(get_path) {
#    command =
#    return ($$command)
#}

################################################
##custom functions 用户喜欢这些函数
################################################
# system is default a replace and test function, can be used in condition, but
# system execute succ return 1 fail return 0 it is not follow command error code.
# define test used in condition my impletement
# system_error return command errcode and it is a test function not a replace function
# 如果自定义的这个函数和系统函数重名，会调用系统函数。
defineTest(system_errcode) {
    command = $$1
    isEmpty(1): error("system_errcode(command) requires one argument")
    #special process
    command = $$get_errcode($$command)
    #the command is only return ret(0,1) wrappered by get_errcode
    ret = $$system("$${command}")
    #message($$command)
    #message($$ret)
    #if eval configed ...
    #error: if(ret) : return (false)
    #erro : eval(ret = 0): return (false)
    #succ:
    #equals(ret, 0):return (false)
    #return(true)
    #succ:but msvc creator auto qmake....
    return ($${ret})
}

#can be used in condition
#test function and replace function can be same name
defineTest(mkdir) {
    filename = $$1
    isEmpty(1): error("mkdir(name) requires one argument")
    command = $$get_mkdir($${filename})
    #message ($$command)
    system_errcode($${command}): return (true)
    return (false)
}

#can be used in values
#must $$ !
#return values. true is 'true', false is 'false', xx0, xx1 is list
defineReplace(mkdir) {
    filename = $$1
    isEmpty(1): error("mkdir(name) requires one argument")
    command = $$get_mkdir($${filename})
    result = $$system("$${command}")
    return ($${result})
}


#only use in condition! return true is 1, false is 0
#refuse $$ !
#return only true(1) or false(0)
defineTest(empty_file) {
    filename = $$1
    isEmpty(1): error("empty_file(filename) requires one argument")
    command = $$get_empty_file($$filename)
    #message($$command)
    system_errcode($${command}): return (true)
    return(false)
}

## but system write_file where ?
## bug: but qt4 write twice... when file exist, if empty_file first, write once....
## bug: this is a test function, but it wont exec, because + 2>/dev/null.
defineTest(write_line) {
    filename = $$1
    variable = $$2
    !isEmpty(3): error("write_line(name, content) requires two arguments.")
    isEmpty(2): error("write_line(name, content) requires two arguments.")
    command = $$get_write_file($${filename}, $${variable})
    #message($$command)
    system_errcode($${command}): return(true)
    return (false)
}

defineTest(copy_dir_and_file) {
    source = $$1
    pattern = $$2
    target = $$3
    !isEmpty(4): error("copy_dir_and_file(source, pattern, target) requires three arguments.")
    isEmpty(3) : error("copy_dir_and_file(source, pattern, target) requires three arguments.")

    command = $$get_copy_dir_and_file($$filename)
    system_errcode($${command}): return (true)
    return (false)
}

defineTest(is_same_file) {
    filename1 = $$1
    filename2 = $$2
    isEmpty(2): error("is_same_file(filename1, filename2) requires two argument")
    !isEmpty(3): error("is_same_file(filename1, filename2) requires two argument")

    command1 = $$get_md5_command($${filename1})
    command2 = $$get_md5_command($${filename2})
    result1 = $$system($${command1})
    result2 = $$system($${command2})

    #message($$filename1 $$result1)
    #message($$filename2 $$result2)
    equals(result1, $${result2}) : return(true)
    return (false)
}

defineReplace(read_ini) {
    file_name = $$1
    sect_name = $$2
    key_name = $$3
    !isEmpty(4): error("read_ini(file, section, key) requires three arguments.")
    isEmpty(3) : error("read_ini(file, section, key) requires three arguments.")
    command = $$get_read_ini_command($${file_name}, $${sect_name}, $${key_name})
    echo = $$system("$${command}")
    #message($$command)
    #message($$echo)
    return ($${echo})
}

defineReplace(write_ini) {
    file_name = $$1
    sect_name = $$2
    key_name = $$3
    new_value = $$4
    !isEmpty(5): error("write_ini_command(file, section, key, value) requires four arguments.")
    isEmpty(4) : error("write_ini_command(file, section, key, value) requires four arguments.")
    command = $$get_write_ini_command($${file_name}, $${sect_name}, $${key_name}, $${new_value})
    echo = $$system("$${command}")
    #message($$command)
    #message($$echo)
    return ($${echo})
}

defineReplace(user_home) {
    command = $$get_user_home()
    echo = $$system("$${command}")
    #message($$command)
    #message($$echo)
    return ($${echo})
}

defineReplace(user_config_path) {
    command = $$get_user_config_path()
    echo = $$system("$${command}")
    #message($$command)
    #message($$echo)
    return ($${echo})
}

