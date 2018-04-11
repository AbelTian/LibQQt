# 入门用法

![设置Qt Creator默认编译路径](screenshot/1.png "这是Qt Creator的设置")  
Qt Creator  
Default build directory:   
/xxx/xxx/xxx/xxx/c0-buildstation 这是个你电脑上的绝对路径，根据自己情况设置  
/%{CurrentProject:Name}/%{Qt:Version}/%{CurrentKit:FileSystemName}/%{CurrentBuild:Name} 这里是个通配  
![设置Qt Creator构建套件](screenshot/2.png "这是Qt Creator的设置，设置File System Name")  
![设置当前工程的环境变量](screenshot/3.png "这是工程的环境变量设置，注意那几点")  
![链接QQt](screenshot/4.png "这是链接QQt的方法，pri都在LibQQt目录里")  
![QQt内部pri的一点点设置](screenshot/5.png "这是LibQQt需要设置的几个路径，编译路径，Sdk路径，发布路径")  
QQT_BUILD_ROOT = /Users/abel/Develop/c0-buildstation  
QQT_SDK_ROOT = /Users/abel/Develop/d1-product  
APP_DEPLOY_ROOT = /Users/abel/Develop/d1-product  

![设置成功显示](screenshot/6.png)  
如果设置成功，qmake应当显示如上例程的样子  

# V2.1.6更新链接QQt的方法  

![链接QQt](screenshot/7.png "这是链接QQt的方法，pri都在LibQQt目录里")  
![QQt内部pri的设置](screenshot/8.png "这是LibQQt需要设置的几个路径，这是新的版本，pri位置有改动")  

# 主要使用思路  

1. 按照文章所说，更改Qt Creator的默认编译路径。只有这样，才能实现多平台目标、中间目标不冲突。  
2. 参照LibQQt/src/qqt_qkit.pri里的SYSNAME变量，在Qt Creator首选项-设置构建和运行-构建套件Kit页面的每个kit的File System Name。（请使用Qt Creator 3.5以上版本，其被佩戴于Qt5.2.）  
3. 打开LibQQt工程，根据qmake输出，在用户配置目录/[.]qmake/app_configure.pri里面设置QQT_BUILD_ROOT QQT_SDK_ROOT APP_DEPLOY_ROOT三个路径变量  
4. 仿照LibQQt的例程，在用户工程.pro里include(.../LibQQt/src/app_base_manager.pri)  
5. 在Qt Creator项目-kit-构建设置页面，配置QKIT环境变量（LibQQt也需要，用户App需要），可以build了。  

在LibQQt/app/xxx.pri，用户可以选用，拷贝到自己工程目录。  
在这个过程里面，只有QKIT环境变量跟随工程build配置，其他的仅仅初始配置一次。  

# Qt Kit、Kit File System Name和QKIT、SYSNAME的关系  

LibQQt有复杂的环境设置，那么这些设置之间的关系是什么样子的呢？  
先说说，每个value在Qt Creator中的位置  

- 首选项-构建和运行-构建套件(Kit)-Every kit (初始化)    
    - File system name
- 项目-Every kit-构建设置-构建环境 （跟随build目标）  
    - QKIT  
- LibQQt/src/qqt_qkit.pri（定义之处）  
    - QKIT、SYSNAME的定义。  
- 用户配置目录/[.]qmake/app_configure.pri（初始化）  
    - QQT_SDK_ROOT 所有SDK的发布根位置
    - QQT_BUILD_ROOT 所有LibQQt应用的编译根位置
    - APP_DEPLOY_ROOT 所有LibQQt应用的发布根目录  

再说说，他们之间的对应关系  

| Qt Kit | Kit File System Name | QKIT | SYSNAME |   
| ---- | ---- | :---- | :---- |  
| Windows 32bit | Windows | WIN32 | Windows |  
| Windows 64bit | Win64 | WIN64 | Win64 |  
| Linux 32bit | Linux | LINUX | Linux |  
| Linux 64bit | Linux64 | LINUX64 | Linux64 |  
| macOS clang 64bit | MacOS | macOS | MacOS |  
| Arm 32bit | Arm32 | ARM32 | Arm32 |  
| Mips 32bit | Mips32 | MIPS32 | Mips32 |  
| Embedded 32bit | Embedded | EMBEDDED | Embedded |  
| iOS clang | iOS | iOS | iOS |  
| iOS Simulator |﻿iOS-simulator | iOSSimulator | iOS-simulator |  
| Android armeabi |﻿Android | ANDROID |﻿Android |  
| Android x86 |﻿Android_x86 | ANDROIDX86 |﻿Android_x86 |  

最后说说，他们的决定关系和由来  

QKIT决定SYSNAME，SYSNAME等于Kit File System Name.   
Qt Kit的名字，第一列，就是Qt Creator的构建套件。  
它每一个包含一个不同的系统名叫做File System Name，它还包括不同的编译器、调试器等。  
有没有感觉他们的关系很逗？明明相同的东西，写了这么多遍。  
原因是这样的，  
源代码-经过qmake变成-MakeFile-经过make变成-目标。  
Qt Creator自己配置了Kit的很多变量，可是！没有全部传给qmake！  
qmake拿不到完整的目标信息，只好自己定义一套，就是QKIT和SYSNAME，  
而Qt Creator这时就必须配合qmake完成配置。  
Qt Creator里的两处配置都是为了配合qmake进行配置的，  
无奈之举。  
等Qt Creator更新到把目标信息全部传给qmake以后，就可以删除QKIT和SYSNAME这样的设置了。  

用户设置的那几个路径属于Multi-link技术，每更换一台电脑才会更换。  
目的在于确认用户的开发、工具、编译、产品目录的设置，用于辅助qmake执行多link。   

欢迎建筑工程师、机械工程师、电子工程师、软件工程师、美术工程师等技术人员，学习使用。  

[返回](.)   

