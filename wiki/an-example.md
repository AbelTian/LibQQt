# 约束 
LibQQt要求使用分别的独立的多个工程，管理QQt的编译和App的编译。
- 创建app工程，在IntIns目录。不表。
- 与IntIns同目录，创建LibQQt工程
  - git clone https://gitee.com/drabel/LibQt LibQQt (当初新建工程的时候，手抖了一下，在mac下少写了一个Q..)

# 配置工程
修改app的pro文件 如下：

```c++
system(touch main.cpp)
include ($${PWD}/../LibQQt/src/app_configure.pri)
include ($${PWD}/../LibQQt/src/app_deploy.pri) (optional, 发布App用)
```

- 添加QKIT 环境变量，一般桌面上 会选择 QKIT=WIN32 或者 QKIT=LINUX 或者QKIT=macOS等几种，桌面上一般就这三种，相应的还有64位的选择。
- 运行qmake，根据错误提示和在link_qqt_library.pri下面生成的app_configure.pri配置QQT_BUILD_ROOT QQT_SDK_ROOT，如果包含了app_deploy.pri还要配置APP_DEPLOY_ROOT。设他们=XXX目录。遵循qmake语法，这个应该不难。
- 然后就开始编译，坐等编译完成。现在的master还算稳定，也就是v2.1.3，还算稳定，我在几个平台上都测试通过了，windows测试的比较少，但是一般也会通过，等详细测试了更新工程。

qqtframe2 demo，这个里面个空白的MainWindow工程，用来向用户展示应该如何使用LibQQt。
选择活动工程IntIns 运行，就可以看到窗口了。

2018年01月10日19:09:14  
exquisite是最近调试的最多的工程，通过这个工程看到的工程管理现在是最合适使用的。配合v2.1.6.0  



