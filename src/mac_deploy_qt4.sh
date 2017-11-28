#!/usr/bin/env bash
appname=$1
qtmodule=Qt3Support\ QtCore\ QtDBus\ QtDeclarative\ QtDesigner\ QtDesignerComponents\ QtGui\ QtHelp\ QtMultimedia\ QtNetwork\ QtOpenGL\ QtScript\ QtScriptTools\ QtSql\ QtSvg\ QtTest\ QtWebKit\ QtXml\ QtXmlPatterns\ phonon
for recur in $qtmodule
do
    install_name_tool -change ${recur}.framework/Versions/4/${recur} @rpath/${recur}.framework/Versions/4/${recur} ${appname}
    install_name_tool -change @executable_path/../Frameworks/${recur}.framework/Versions/4/${recur} @rpath/${recur}.framework/Versions/4/${recur} ${appname}
done
install_name_tool -add_rpath @executable_path/../Frameworks ${appname}
