#!/bin/sh
tar -cf - $(find $1 -name "$2") | (cd $3; tar -xf -)