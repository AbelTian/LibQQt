# QQt应用程序框架软件   

中文全名 ****QQt应用程序框架软件****。  
英文全名 ****QQt Application Framework Software****。  
英文简称 ****LibQQt****。  
主库名称 ****LibQQt****。  

*QQt应用程序框架软件是应用程序框架层的一系列库集合，持续实现这一层的功能，主库是LibQQt，辅助（平级扩展）库有QQtExquisite、QQtHighGrade、QQtIndustrialControl、QQtInput、QQtInstallFramework、QQtMediaExtention、QQtStyle、QQtTool等，很多流行Qt Wrapper库都在辅助库中。
QQt应用程序框架软件全部使用Multi-link技术实施工程管理。*  

*QQt应用程序框架软件广泛支持各个操作系统，包括Windows、macOS、Linux桌面，包括Android（含Simulator）、iOS（含Simulator）、e-Linux等嵌入式桌面。
QQt应用程序框架软件广泛支持各种编译器，在Windows平台，支持MSVC、MSVC64、MINGW32、MINGW64等，在类Unix平台，支持GCC、CLANG等，还支持Android、iOS、ARM32、ARMHF32、MIPS32等多种嵌入式编译器等。*        

[QQt应用程序框架软件库列表](project.md)  


# 主库 LibQQt  

LibQQt为应用程序提供丰富的组件、处理Qt存在的问题、适配多个平台开发等功能，能够适配桌面、嵌入式桌面的开发，提供统一接口，极大提升了用户开发应用程序的能力。  
LibQQt为用户自动生成Library SDK，主动帮助用户发布App和资源文件。   
2018年1月，LibQQt代码变更数量已达30万，主要面向初、中、高级软件相关专业、有一定App开发经验的工程师。    
LibQQt现进行正式发布版本v2.1.6.0，欢迎工程师们使用。  
2018年8月，LibQQt代码变更数量已达45万，主要面向嵌入式、桌面平台进行了功能和库扩充，使用多链接技术v2加强了管理能力。    
LibQQt现进行正式发布版本v3.1，欢迎工程师们使用。    
2018年11月，LibQQt代码变更数量已达46万，作者正式申请软件著作权，使用多链接技术v2.2继续加强工程管理能力。  
LibQQt现进行正式发布版本v3.1.1.0，欢迎工程师们使用。  

gitee link: https://gitee.com/drabel/LibQQt  
github link: https://github.com/AbelTian/LibQQt  


========================================================================   
# 摘要介绍   

*LibQQt包括基础组成、精美组成、高级组成*   
- 基础组成，可以完成专业App所需要的业务功能和图形功能。  
- 精美组成，包括高级业务功能和超级图形功能。（都在src/exquisite文件夹里）  
- 高级组成，包括App工程师们不多使用，不太熟悉的、比较艰难的功能。（都在src/highgrade文件夹里）    

*如果用户希望精简LibQQt，qqt_header.pri里面有很多模块开关，开开关关能修剪。*  
*不建议使用cmake，建议使用qmake。*  
*自动发布应用程序，自动拷贝应用配置，自动发布依赖库。（请正确配置三个主目录）*  


========================================================================  
# 详细介绍  

1. 支持绘制图表
    - [QQtChart](src/charts/qqtchartview.h) (compatiable with QChart and QCustomPlot)  
2. 支持检测USB设备热插拔  
3. 自定义了一部分特殊需要的控件，用来解决Qt的嵌入式bug。
    - 包括完全使用图片的checkbox（switchbutton）
    - QQtTabWidget，解决QtTab不能竖排横显文字的问题
    - QQt进度条，解决Qt进度条在Dialog中导致系统死机的问题(e-linux)    
1. 添加精美控件
    - 包括有多种效果的Widget、Dialog
    - 二维码生成器、识别器，校验码生成器
    - 九宫格技术展示图片
    - 添加osd widgets
    - 添加svg support widgets
    - 添加gif support Widgets  
        - 可以方便的设置动态按钮等。  
        - 有[QQtGifWidget](src/exquisite/gifwidgets/qqtgifwidget.h)、QQtGifButton等。   
    - 添加color support widgets  
        - 单色Widget。  
    - 添加click and click sound widget  
        - 带按键声，支持长按、双击的widget、label和dialog等控件。  
    - 添加bodymover、bodyresizer、clickhelper、mouselocker
        - qqtwindowattribute、qqtwidgeteffect等窗口属性、特效功能提供者。
        - 帮助用户通过installEventFilter实现关于窗口和鼠标的完善的功能。
    - 添加不规则控件
        - qqtirregularwidget、qqtirregularpushbutton等，帮助用户在窗口中添加不规则图形控件。
        - 可以在图象区域/不规则区域响应鼠标消息。
        - 只需要设置一张图片即可，透明部分不响应鼠标消息。
    - 以及未列出的等20余种自定义widget。
4. 有线和无线网络自动连接管理器 (e-linux)  
6. 解决Qt4.8.7在嵌入式屏幕上QGraphics系统不正常绘画的问题 
7. QQt输入法  
    - 重写了UI，适配多种屏幕  
    - 由于版权等一些原因，这个模块在LibQQt 3.0的时候移除。  
    - 我制作了QQtInput库以提供输入法功能，请用户到我的工程主页，查看QQtInput工程。  
8. Qt对象管理器  
    - 用于管理已经生成的Qt对象实例，objectName是唯一查找索引。  
    - 含有QQtObjectFactory，用于动态注册、生成来自QObject和QWidget的类。
9. 嵌入式视频播放器，模拟端口实时预览器  
    - *已经移动到独立的QQtMediaExtention库，专门提供媒体功能，主要是视频媒体。*
0. QQt打印机，支持打印pdf
2. QQtWord，支持doc文档编写，输出pdf格式。
4. QQtTreeView，添加Qt4内部没有TreeView
    - 包括QQtXmlTreeModel、QQtJsonTreeModel、QQtFileSystemTreeModel、QQtSqlTreeModel
6. QQt通讯套件。
     - 通讯口类   
        - QQtNfcClient、QQtNfcServer 支持近场通讯。  
        - QQtSerialPort 兼容QSerialPort and QextSerialPort
        - [QQtTcpClient](src/network/qqttcpclient.h)、QQtTcpServer、QQtUdpClient、QQtUdpServer
        - QQtBluetoothSocket、QQtBluetoothServer +QQtBluetoothManager
        - QQtWebAccessManager，支持http、ftp等主流协议，高并发传输，管理cookie和session。
        - [QQtWebSocket](src/network/qqtwebsocketclient.h) 接口
        - 一个句柄代表一个和外部通信的节点。  
     - 报文虚类（接口类） [QQtMessage](src/network/qqtmessage.h)  
        - 在协议里总是用这个报文的临时句柄，用来解协议包和压协议包。
     - 协议虚类（接口类） [QQtProtocol](src/network/qqtprotocol.h) [QQtProtocolManager](src/network/qqtprotocolmanager.h)
        - 程序业务代码就是依靠这个协议句柄进行通信工作的。  
7. 添加应用中常用的form
    - *全在frame文件夹*
8. 支持多页表格 [QQtMultiPageTableWidget](src/widgets/qqtmultipagetablewidget.h)  
9. 添加 [QQtApplication](src/frame/qqtapplication.h)，支持入门级、通用级、专用级嵌入式App所必须的初始化内容
5. 支持Qt5.8、Qt5.9.2、Qt5.10   
    - 建议桌面使用这个版本，对三大桌面，和IOS Android e-linux支持都很好。  
0. 跨平台支持macOS、iOS、Android、Windows、Linux、MIPS、ARM等。  
1. 添加矢量图形widgets  
     - 比如 QQtSvgProgressbar
     - QQtSvgCheckBox
     - [QQtSvgPushButton](src/exquisite/svgwidgets/qqtsvgpushbutton.h)  
2. 添加核心类之[QQtDictionary](src/core/qqtdictionary.h)   
     - 化解C Plus Plus中没有字典类别的尴尬。    
3. 添加Multi-link工程管理pri组  
     - [Multi-link technology](multi-link/add_multi_link_technology.pri)，既多链接工程管理技术。
     - [add_base_manager.pri](multi-link/multi-link/add_base_manager.pri)，app和lib工程的基础管理者。  
     - 基于qmake，用户可以轻易的链接LibQQt和添加自定义library。  
     - 工程版本变更可以使用add_version(1,0,0,0)实现了。  
5. 升级多媒体音频  
    - 添加内存服务器（一套Input（Reader），Output（Writer）），处理内存和设备之间的数据交互。（这部分的功能完全按照为内存服务的思路设计研发。）  
    - [QQtAudioManager](src/multimedia/qqtaudiomanager.h)、  
        - 将 AudioInputDevice 和 AudioOutputDevice 当做一个设备进行读写，App处理获取到的声音。
    - 增加QQtWavAudioManager、QQtWavSoundEffect、QQtWavSound，
        - 像操作一个设备一样读、写wav文件，其实是两个wav文件。
    - 增加QQtVideoManager、QQtLogicVideoManager，
        - 支持桌面摄像头采集画面，支持模拟摄像头采集画面。
6. 添加Http功能支持工具
    - QQtWebAccessManager，支持管理Session、Cookies。    
    - 添加GumboQuery爬虫工具，爬取网页信息。  
    - 支持webservice (QtSoap)  
8. 添加Qt没有的组件QQtTitleBar  
    - 可以组完全自定义的Form。  
    - 加上QQtOSDFrame、QQtOSDForm可以组透明Form。    
8. **HighGrade** Module 增加新成员    
    - 难度高，谨慎使用。  
    - 线程间、进程间通信组件   
        - QQtSharedMemory，实现可以跨线程、进程的变量，却按照临时变量的方式使用。  
        - QQtLocalServer QQtLocalClient, QQtNamedPipe使用QLocalSocket、PIPE实现跨线程通讯。      
        - QQtLocalQueueServer QQtLocalQueueClient QQtMessageQueue使用QQtLocalQueueSocket实现跨线程通讯。  
        - 使用方法都类似于QQtSharedMemory。  
   - QQtSingletonApplication 单例App，基于QQtApplication，使用QLocalSocket的进程间通信实现。  


========================================================================  
# 多链接发布技术    

[Multiple Link Technology](multi-link.md)   
LibQQt为方便用户开发App过程方便的发布程序，所以添加了多链接和自动发布功能，基于qmake工程管理器的多链接发布技术。  
用户只需要为多链接技术做相应的目录设定，就可以自动发布应用、自动发布配置项目，自动发布依赖库。  

多链接技术还包括添加设置版本，添加语言，添加程序图标，添加工程常用函数和工程基础配置设定，方便用户不必再进行复杂设置初始化。  
多链接技术还包括为Lib工程发布SDK。    
多链接技术提供的add_base_manager.pri，只需要包含这一个pri文件，用户就可以使用多链接技术，很方便。    
经过发布的App直接点击就可以运行，*大的省去了用户手动发布App的劳烦过程。  
有了Multi-link，Qt C++软件工程师就好像在编辑一个软件的源程序一样处理多个软件。    

*Multi-link提供ProductExecTool，可以对产品集中调用运行、查看运行效果。*  
*Multi-link提供SdkListTool，方便用户查看已经准备好的SDK在各个平台准备情况的表格。*  
*Multi-link提供AddLibraryTool，方便用户通过准备好的SDK自动生成add_library_xxx.pri的链接环。*  
*Multi-link提供AddLibraryTool-Multiple，可以同时对多套SDK进行生成链接环。*  
*Multi-link提供Multi-linkConfigTool，方便用户配置Multi-link v2必需的三大路径，build/sdk/deploy root。*  

*LibQQt3.0基于Multi-link2.0发布，用户使用LibQQt 3，代表用户接受其工程管理工具Multi-link 2.*  


========================================================================  
# 版本分割    

LibQQt R2支持Qt5 Qt4，    
LibQQt R3支持Qt5，由于使用Multi-link 2，不支持Qt4。  
现在R3是master分支。  
[版本划分图谱](changelog.md)   


========================================================================  
# 使用案例  

[看入门用例截图](screenshot.md)  


========================================================================  
# 使用方法  

在Windows平台上，  
*把LibQQt/extra/touch.exe 复制到C:\Windows*   
*把LibQQt/extra/md5.exe 复制到C:\Windows*   
  
[走，去看看入门用法](usage.md)  
[入门了，去看看学习设置工程目录](project-manager.md)  
发现了一个问题: [new issue link](https://gitee.com/drabel/LibQQt/issues/new?issue%5Bassignee_id%5D=0&issue%5Bmilestone_id%5D=0)  


========================================================================  
# 依赖学习知识   

[预习Git入门](usage-git.md)  


========================================================================  
# LibQQt百科   

[跳转到LibQQt的百科知识页面](wiki/wiki.md "Wiki Page")  
[阅读我的LibQQt博客进行一系列的学习](http://blog.csdn.net/Dr_Abel)   
[LibQQt视频图说](http://v.youku.com/v_show/id_XMzUzODQ4MTczMg==.html?spm=a2hzp.8244740.0.0)  
[看看LibQQt的文档](doc/knowledge-about-libQQt.md)  


========================================================================  
# 联系我  

邮箱: tianduanrui@163.com  
QQ: 2657635903  
LibQQt技术分享和交流群: 560584206

========================================================================  
# 用户使用协议  

[LibQQt用户使用协议](licence.md)   


========================================================================  
# 收费处  

[LibQQt收费处](charge.md)   


========================================================================  
# 项目标识  

![logo](screenshot/logo.png "Logo")    


# 版权信息   

Copyright © 2017 Tianduanrui. All rights reserved.    
Assigned by Dezhou.    
