# LibQQt功能详细介绍   

1. 支持绘制图表
    - QQtChart (compatiable with QChart and QCustomPlot)  
2. 支持检测USB设备热插拔  
3. 自定义了一部分特殊需要的控件，用来解决Qt的嵌入式bug。
    - 包括完全使用图片的checkbox（switchbutton）
    - QQtTabWidget，解决QtTab不能竖排横显文字的问题
    - QQt进度条，解决Qt进度条在Dialog中导致系统死机的问题
1. 添加精美控件
    - 包括复杂的圆盘进度条, SpeedMeter    
    - 包括有多种效果的Widget、Dialog
    - 二维码生成器、识别器，校验码生成器
    - 九宫格技术展示图片
    - Html解析器
    - 以及未列出的等20余种自定义widget。
4. 有线和无线网络自动连接管理类  
6. 解决Qt4.8.7在嵌入式屏幕上QGraphics系统不正常绘画的问题 
7. QQt输入法
    - 重写了UI，适配多种屏幕
8. Qt对象工厂，允许注册、生成、查找和删除所有来自QObject以及QWidget的类。
9. 嵌入式视频播放器，模拟端口实时预览器
0. QQt打印机，支持打印pdf
2. QQtWord，支持doc文档编写，输出pdf格式。
4. QQtTreeView，添加Qt4内部没有TreeView
    - 包括QQtXmlTreeModel、QQtJsonTreeModel、QQtFileSystemTreeModel、QQtSqlTreeModel
5. 支持工程的版本变更
    - 在qqt_version.pri里面是QQt的版本和源文件内版本宏定义  
    - 在app_version.pri里面是App的版本和源文件内版本宏定义  
6. QQt通讯套件。
     - 通讯口类   
        - QQtSerialPort 兼容QSerialPort and QextSerialPort
        - [QQtSocketTcpClient](src/network/qqtsockettcpclient.h)、QQtSocketTcpServer、QQtSocketUdpClient
        - QQtBluetoothSocket +QQtBluetoothManager
        - QQtWebAccessManager，支持http、ftp等主流协议，高并发传输。
        - QQtWebSocket接口
     - 协议虚类（接口类） [QQtProtocol](src/network/qqtprotocol.h) QQtWebSocketProtocol
     - 报文虚类（接口类） [QQtMessage](src/network/qqtmessage.h)
5. 支持webservice
7. 添加应用中常用的form
8. 支持多页TableWidget
9. 添加 [QQtApplication](src/frame/qqtapplication.h)，支持入门级、通用级、专用级嵌入式App所必须的初始化内容
5. 支持Qt5.9.2   
0. 跨平台支持macOS、iOS、Android、Windows、Linux、MIPS、ARM等。  
1. 添加矢量图形widgets  
     - 比如 QQtSvgProgressbar
     - QQtSvgCheckBox
2. 添加核心类之[QQtDictionary](src/core/qqtdictionary.h)   
     - 化解C Plus Plus中没有字典类别的尴尬。    
3. 添加Multi Link工程管理pri组  
     - Multi Link technology，既多链接工程管理技术。
     - 基于qmake，用户可以轻易的链接LibQQt和添加自定义library。  
4. 添加gif support Widgets  
    - 可以方便的设置动态按钮等。  
    - 有QQtGifWidget、QQtGifButton等。   
5. 升级多媒体音频  
    - 添加内存处理器，处理内存和设备之间的数据交互。  
    - QQtAudioManager、QQtWavAudioManager、  
    - QQtWavSoundEffect  
    - 将AudioDevice、wav输入输出文件，当做一个设备进行读写，App处理获取到的声音。  
    


[返回](.)  




