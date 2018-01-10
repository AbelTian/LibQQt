这块要说的特别多。为什么呢？因为这块的工作很多，必须设计合理才会容易编译。
这里必须提一下Multi Link技术，是这个技术帮助使用者，利用qmake这款工程管理工具来进行多个增删link-library。全称Multi-link technology，“多链接”技术，专门解决这些个app链接library出现的手工解决太多困难的问题。
先说说：

# 我遇到的问题  
1. 我的工程在自己电脑上编译很顺利，到了别的电脑上却需要经过非常大量的配置才能完成编译。
2. 我的工程我自己开发修改很容易，编译也很容易，可是和别人一起合作开发之后，修改却变得很困难，需要处理过多的冲突。
3. 工程配置工作竟然那么巨大数量，几天的功夫连一个工程都配置不完。
4. 工程管理概念太复杂，我不爱看。

这些我想读者都遇到过，我也遇到过，总是被这种路径那种路径困扰，总是被这个编译选项那个编译设置困扰。
说说我是怎么解决的：
# 解决方法  
这里不做每一条的解说，这里做一个可行性的设计方案。
Qt是跨平台的library解决方案，虽然存在某些bug和不足，但不能掩盖它的确在跨平台解决方案中独占头席，无出其右。

- 开始一个工程之前，设置Qt Creator的默认编译目录，在设置-构建-概要 里面，基于Qt4的版本没有这个设置，那个建议不要使用。
  -  %{JS: Util.asciify("/your/local/path/to/build/root/%{CurrentProject:Name}/%{Qt:Version}/%{CurrentKit:FileSystemName}/%{CurrentBuild:Name}")}
  -  %{CurrentProject:Name} 代表当前工程的名字
  -  %{Qt:Version} Qt的版本号
  -  %{CurrentKit:FileSystemName} 目标系统名称，这个在设置Qt Kit的时候，会要求设置，这里也要求设置，设置为和qqt_qkit.pri里面定义的不同的SYSNAME变量的值相同，生成的时候要用，链接的时候要用，发布拷贝库的时候也要用，还是设置成一样的吧。
  -  %{CurrentBuild:Name} Debug还是Release

这样出来的结果是 /..buildstation/QQt/5.9.2/macOS/Debug
我的编译目标就在这里，拷贝SDK的时候也在这里拷贝，而且拷贝的目的地址也是这个样子。
这样管理起来是不是很费劲，手动拷贝得走进多少目录？
的确是这样的多层多个目录，MLMA技术就是解决这个问题。

- 设置QKIT环境变量，Qt的build配置当中提供设置环境变量的位置  

有的读者疑惑，这里的设置也好多啊。的确，的确好多，但是这个多，根本不多，如果把那些拷贝不同目标系统的librayr的工作全部手动操作，那样加起来才算多，基本上开发一个平台的工作，要复制N个平台份。
我一般只设置Debug里的，Release里的一般就不设置了。
%{CurrentKit:FileSystemName} 我表示Qt Creator的这个变量，在qmake pro文件中还无法获取。等着吧，等着Qt开发组有空了把这个变量加入qmake，连QKIT这个环境变量也不用设置了。

- 运行qmake，编译终端输出所需的变量信息，根据提示，还是再Qt Creator中打开相应的app_configure.pri进行修改，添加这几个变量。这个变量有三个。
    - QQT_BUILD_ROOT 这个代表工程编译的根路径，基本上所有的Qt工程编译都在这个根路径当中，QQt也不例外。
    - QQT_SDK_ROOT 这个代表QQt library将要导出SDK的根目录位置，基本上所有的library SDK都会导出到那里，这样做是有好处的，你想想，所有的library都在一个地方被链接，是不是管理起来更容易。在我的电脑上所有不论是哪家开发的library都放在了b0-product/lib里面。QQt依赖MLMA技术自动拷贝过去。
    - APP_DEPLOY_ROOT 这个变量可选

MLMA技术会制作一套pri，能够自动生成一些lib_*.pri和app_*.pri，用户对其进行完成，以制作出library和app。MLMA会自动的进行多个library编译、多个app编译链接，library发布SDK到指定位置，发布app到指定位置等工作。提供很多易用函数，方便用户使用qmake工作。

现在版本的MLMA技术和QQt捆绑在一起，还未实现分离。经过以上设置，编译出App应该没有多大问题。QQt工程我已经制作加调试了两年有余，运行质量还是有保证的。配套完善的MLMA技术，在跨平台开发的场合，更加容易使用。

在User新开发的App当中使用QQt，不需要拷贝pri，只要include app_configure.pri就可以了，如果有需要，还可以include app_deploy.pri完成app发布工作。

另外我再单独写一篇文章介绍Multi Link技术，说说这个技术的特点和包含有哪些功能丰富的pri。 
