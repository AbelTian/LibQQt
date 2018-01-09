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


[返回](README.md)  
