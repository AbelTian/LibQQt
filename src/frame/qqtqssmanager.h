#ifndef QQTQSSMANAGER_H
#define QQTQSSMANAGER_H

#include <QStyle>
#include <qqtcore.h>
#include <qqt-local.h>
#include <qqtapplication.h>
#include <qqtframe.h>

/**
 * @brief QQtQSSManager
 * 在配置目录里，默认在app运行当前目录。
 * skin目录
 *
 * default主题
 * default.qss是必然加载的，QQtApp的皮肤，公共qss配置，写在这里。
 * 对应的资源在default文件夹里，或者qrc里。
 *
 * blue主题 其他主题
 * blue.qss代表blue主题，对应资源在blue文件夹里。blue.qss这个文件决定主题列表里的主题的名字，qssManager会提供列表。
 * 一个主题包括[主题名].qss，和[主题名]文件夹组成。
 *
 * 原理
 * 会根据用户设置生成当前主题qss配置文件，current.qss，所以不要去碰这个临时文件。
 * current.qss里包含default.qss和用户选定的当前主题的qss，是个拼接文件。
 * 会直接对QQtApplication生效，所以必须使用QQtApplication。
 *
 * 注意：qss文件里的url路径是相对于app工作目录的相对路径。
 * 注意：资源目录不必要，可以放到qrc里。qss文件必要。
 * 注意：主题列表不包括default，其他的主题qss才是主题，default是主题公共资源。
 * 可能性设计：把资源保存在qrc里或者打包成二进制格式的文件，使用时解压到临时目录，然后再使用QSSManager加载。
 */
class QQTSHARED_EXPORT QQtQSSManager : public QObject
{
    Q_OBJECT

public:
    explicit QQtQSSManager ( QObject* parent = 0 );
    virtual ~QQtQSSManager();

    //主题列表
    QList<QString> styleList();
    //主题名 "blue"
    void setCurrentStyle ( QString styleName );
private:
    QList<QString> mStyleList;
};

#endif // QQTQSSMANAGER_H
