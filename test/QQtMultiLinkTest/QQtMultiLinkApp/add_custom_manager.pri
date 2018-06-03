#----------------------------------------------------------------
#app_custom_manager.pri
#这个文件用于给用户自定义管理内容，随意添加自己所需要的library、defines、config等等。
#拷贝到用户app工程目录里使用用
#----------------------------------------------------------------
################################################################
##link Other library
################################################################
#LIBS +=

#以下是Multi Link技术更新后使用的方式

#针对QQt 多link技术的App，链接针对QQt 多link技术的Lib 只需要使用这一行代码，别的什么都不用管了。
#对没有使用多link技术的Lib 拷贝到QQT_SDK_ROOT下对应目录就行了。
#不使用多link技术的App？你不要使用这个函数，无法使用。
app_link(QQtBasedLibTest)
#还有头文件 :)
app_include(QQtBasedLibTest)

#以上都是标准路径，以下是自定义路径里的。

#头文件很复杂？也可以支持。建议使用相对路径。确认：SDK ROOT肯定是在一个公共的位置，而且不易改变。
#这个函数会到$$QQT_SDK_ROOT/LibName/$$QKIT_STD_DIR/include目录里找。相当于在Lib的需要inlude的头文件目录里有子目录
#qmake函数对子目录的兼容不是非常好。所以用户链接Lib，请自行添加include目录子目录的内容
#这两个函数的意义是在$$QQT_SDK_ROOT/QQtBasedLibTest/$$QKIT_STD_DIR/include/下的子路径添加include
app_add_include(QQtBasedLibTest, QQtBasedLibTest)
#这个函数的意义是在$$QQT_SDK_ROOT/QQtBasedLibTest/$$QKIT_STD_DIR/lib里查找添加xxx_lib
app_add_library(QQtBasedLibTest, QQtBasedLibTest)

