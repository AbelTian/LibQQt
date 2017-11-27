#!/bin/sh
initpath=$(pwd)
(cd $1; tar -cf - $(find . -name "$2") ) | (cd $3; tar -xf -)
cd $initpath
