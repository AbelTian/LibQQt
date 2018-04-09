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

# 简而言之  

为了降低用户对使用过程的理解难度，这里做下总结。  

1. 按照文章所说，更改Qt Creator的默认编译路径。只有这样，才能实现多平台目标、中间目标不冲突。  
2. 参照LibQQt/src/qqt_qkit.pri，设置-构建-Kit页面的kit的File System Name。（请使用Qt Creator 3.5以上版本，其被佩戴于Qt5.2.）  
3. 打开LibQQt，根据qmake输出，在用户配置目录/[.]qmake/app_configure.pri里面设置QQT_BUILD_ROOT QQT_SDK_ROOT APP_DEPLOY_ROOT三个变量  
4. 仿照LibQQt的例程，在用户工程pro里include(.../LibQQt/src/app_base_manager.pri)  
5. 在用户工程编译页面，配置QKIT环境变量（LibQQt也需要，用户App需要），可以build了。  

在LibQQt/app/xxx.pri，用户可以选用，拷贝到自己工程目录。  
在这个过程里面，只有QKIT环境变量跟随工程build配置，其他的仅仅初始配置一次。  

[返回](.)  
