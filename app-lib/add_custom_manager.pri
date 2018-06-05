#----------------------------------------------------------------
#add_custom_manager.pri
#这个文件用于给用户自定义管理内容，随意添加自己所需要的library、defines、config等等。
#拷贝到用户app工程目录里使用用
#建议拷贝走使用。
#----------------------------------------------------------------

################################################################
##基础使用方法
################################################################
#添加app版本
#add_version (1,0,0,0)

#添加依赖library
#add_library(xx)
#add_include(xx)
#add_defines(xx)

#先发布App
#app从build到deploy
#add_deploy()

#后发布依赖
#lib从sdk到build和deploy
#add_deploy_library(xx)

################################################################
##高级使用方法
################################################################
ADD_CUSTOM_MANAGER_PRI_PWD = $${PWD}
defineTest(add_custom_dependent_manager){
    libname = $$1
    isEmpty(libname):return(0)

    !equals(TARGET_NAME, $${libname}):
        exists($${ADD_CUSTOM_MANAGER_PRI_PWD}/add_library_$${libname}.pri){
        include ($${ADD_CUSTOM_MANAGER_PRI_PWD}/add_library_$${libname}.pri)
        contains(TEMPLATE, app):add_dependent_library_$${libname}()
        else:contains(TEMPLATE, lib):add_link_library_$${libname}()
        else:add_link_library_$${libname}()
    }
    return (1)
}
