#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T22:23:34
#
#-------------------------------------------------

QT       += widgets

TARGET = QtCSVLib
TEMPLATE = lib

CONFIG += debug_and_release
CONFIG += build_all

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#-------------------------------------------------
#Multi-link v2.4 提供的技术
#-------------------------------------------------
include($${PWD}/../../multi-link/add_base_manager.pri)

#本工程默认编译为动态库。
#此处更改工程编译状态，为用户提供自有状态CONFIG、宏，用户自主选择。
add_dynamic_library_project()
#add_static_library_project()

#-------------------------------------------------
#用户工程配置
#-------------------------------------------------
add_version(1,5,0,0)

#本库依赖QQt
#add_dependent_manager(QQt)

#本库导出SDK到LIB_SDK_ROOT
add_source_dir($$PWD/qtcsv/include/qtcsv)
add_sdk(QtCSVLib, $$add_target_name())
#add_sdk_header_no_postfix(QtCSVLib, $$add_target_name(), QtCSVLib)

#-------------------------------------------------
#用户工程配置
#-------------------------------------------------
!msvc {
    # flags for gcc-like compiler
    CONFIG += warn_on
    QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self \
            -Wswitch-enum -Wundef -Wpointer-arith \
            -Wdisabled-optimization -Wcast-align -Wcast-qual
}

include($${PWD}/qtcsvlib_header.pri)
include($${PWD}/qtcsvlib_source.pri)

CONFIG += continue_build
contains(CONFIG, continue_build){
    system("touch $${PWD}/qtcsvlib.cpp")
}

message($${TARGET} build obj dir $$add_host_path($${OUT_PWD}) $$OBJECTS_DIR)
message($${TARGET} build moc dir $$add_host_path($${OUT_PWD}) $$MOC_DIR)
message($${TARGET} build uih dir $$add_host_path($${OUT_PWD}) $$UI_DIR)
message($${TARGET} build rcc dir $$add_host_path($${OUT_PWD}) $$RCC_DIR)
message($${TARGET} build dst dir $$add_host_path($${OUT_PWD}) $$DESTDIR)
message ($${TARGET} QT $${QT})
message ($${TARGET} config $${CONFIG})
message ($${TARGET} DEFINE $${DEFINES})
