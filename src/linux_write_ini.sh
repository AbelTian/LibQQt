#!/bin/sh

function WriteINIfile()
{
    Configfile=$1
    Section=$2
    Key=$3
    NewValue=$4

    WriteINI=`sed -i "/^$Section/,/^/ {/^\[$Section/b;/^\[/b;s/^$Key*=.*/$Key=$NewValue/g;}" $Configfile`
    echo $WriteINI
}

#WriteINIfile $1 $2 $3 $4

# 解析INI
rini()
{
    # 判断参数数量
    if [ $# -lt 2 ];then
        echo 'Usage:ini <filename> <[section]> [<key>] [<newvalue>]'
        _exit
    fi

    # 讲ini文件读取到变量
    _old=`cat $1`

    # 判断变量3是否为空 如果为空 显示该[]下的所有字段
    if [ "$3" = "" ];then
        sed -n "/\[$2\]/,/\[.*\]/{
           /^\[.*\]/d
           /^[ ]*$/d
           s/;.*$//
           p
           }" $1
    # 判断变量4是否为空 如果为空 显示该字段的值
    elif [ "$4" = "" ];then
        sed -n "/\[$2\]/,/\[.*\]/{
           /^\[.*\]/d
           /^[ ]*$/d
           s/;.*$//
           s/^[ |    ]*$3[|    ]*=[ |    ]*\(.*\)[ |    ]*/\1/p
           }" $1
    else
        # 判断变量4是否为字符'#' 如果为'#' 删除改行
        if [ "$4" = "#" ];then
            sed -i "/\[$2\]/,/\[.*\]/{
               s/^[ |    ]*$3[ |    ]*=.*/ /
               }" $1
        else
            # 如果变量4不为空和'#' 修改该变量 有备注使用改语句修改
            sed -i "/\[$2\]/,/\[.*\]/{
               s/^[ |    ]*$3[ |    ]*=.*[ |    |.*]/$3=$4            /
               #s/^[ |    ]*$3[ |    ]*=[a-zA-Z0-9]*.[0-9]*.[0-9]*.[0-9]*/$3=$4/
               }" $1
            # 重新读取新文件
            _new=`cat $1`
            # 判断是否更改
            if [ "$_new" = "$_old" ];then
            # 修改没成功 使用以下语句更改
               sed -i "/\[$2\]/,/\[.*\]/{
               s/^[ |      ]*$3[ |    ]*=.*/$3=$4/
               #s/^[ |     ]*$3[ | ]*=[a-zA-Z0-9]*.[0-9]*.[0-9]*.[0-9]*/$3=$4/
               }" $1
            fi
        fi
    fi
}

rini $1 $2 $3 $4
