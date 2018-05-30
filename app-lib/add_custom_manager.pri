#----------------------------------------------------------------
#add_custom_manager.pri
#这个文件用于给用户自定义管理内容，随意添加自己所需要的library、defines、config等等。
#拷贝到用户app工程目录里使用用
#----------------------------------------------------------------
################################################################
##使用方法
################################################################
#添加app版本
#add_version (1,0,0,0)

#添加依赖library
#add_library(xx)
#add_header(xx)
#add_defines(xx)

#先发布App
#app从build到deploy
#add_deploy()

#后发布依赖
#lib从sdk到build和deploy
#add_deploy_library(xx)

#这里，就不需要用户调用。
################################################################
#对产品线的控制结构Multi-link下命令 开启产品线
################################################################
#add version 调用时机 在lib里有个约束，必须在add_sdk之前调用，其他时候没有约束。
add_version(1,0,0,0)
add_deploy()
contains(TEMPLATE, app):add_dependent_library_QQt()
else:contains(TEMPLATE, lib):add_link_library_QQt()
else:add_link_library_QQt()
