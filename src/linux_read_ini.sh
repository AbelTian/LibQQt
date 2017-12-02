#!/bin/sh

ReadINIfile()
{     
    Configfile=$1
    Section=$2
    Key=$3
    ReadINI=`awk -F '=' '/\['$Section'\]/{a=1}a==1&&$1~/'$Key'/{print $2;exit}' $Configfile`
    echo "$ReadINI"
}

ReadINIfile $1 $2 $3
