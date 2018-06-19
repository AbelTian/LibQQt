# Qt Creator安装须知  

有一些同学认为安装Qt Creator就是安装Qt，不是的。 

Qt Creator是一款使用qmake对用户Qt工程进行管理的IDE。 

qmake是我们常说的generate make工具，理论上它独立于Qt，即独立于Qt Library。  
qmake理论上独立于Qt，但是Qt设计者将其依附于Qt之中，用于帮助Qt Creator区分Qt的版本（目标跨平台）。  
qmake跟随Qt发布，即跟随Qt Library发布，通常我们所说的Qt是Qt Library。  
Qt版本来源于Qt Library版本，qmake的版本独立于Qt版本， Qt Creator版本独立于Qt版本。 我们一般只关注Qt版本和qmake所指向的Qt版本，它俩其实是一个概念。

Qt Creator包括对Qt Versions的支持，通过查找qmake实现，它支持多版本、多目标的Qt。  
它包含对qmake、cmake的使用能力，也就是能管理工程源代码树。
它包含对make的使用能力，也就是能编译。  
它包含对gdb、windbg等调试器的支持，也就是能调试。  
另外，  
它包含对astyle、clang-format的支持，也就是能保存时格式化代码。  
它包含对源码外编译（shadow build）的支持，也就是对Qt Creator设置的默认编译目录，指定了qmake和编译器工作的根位置。这里注意：Qt Creator可以根据自身的变量通配目录名，这些变量不是qmake的，它没有把这些变量完全传给qmake的pr[o,i,f]们。（Qt5）  

# 安装目录  

Qt Creator通常跟随于Qt各个版本发布一个版本，用户选择新版本使用就好了，在安装目录Tools\bin目录里。按个最新的Qt，找Tools目录就用它。  
Qt 其他的版本，把安装目录里的Qt版本号目录，剪切到这个新版本的Qt安装根目录里，并排各版本号目录，Qt Versions那里随便选好了，你使用了哪个版本的Qt、针对了哪个目标，你自己知道。  
Qt Doc目录，你在里边放哪个版本的Qt Doc在Qt Creator的help里就会出现哪个让你选，操作操作就知道了，除非版本间区别太大，一般放一个。  
Qt Creator的配置目录，类Unix系统，在用户根目录/.config/QtProject里，Windows下，在用户根目录/AppData/Roaming/QtProject里。  

以上是对Qt Creator这款IDE的介绍。  

[返回](.)  
