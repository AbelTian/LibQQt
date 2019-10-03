#ifndef QQTPICTURETABWIDGET_H
#define QQTPICTURETABWIDGET_H

#include <qqttabwidget.h>
#include <qqtpicturetabbar.h>
#include "qqtcore.h"
#include "qqt-local.h"

/**
 * @brief The QQtPictureTabWidget class
 * 使用自定义tabbar的tabwidget。
 * 以图片为主的tabbar。
 *
 * 必须在这里写一个tabwidget，
 * Qt的tabwidget有个现象，用户设置的自定义tabbar必须写在构造函数里才会有效，
 * 所以，这里写一个tabwidget。
 * 用户所有自定义的tabbar都必须伴随写一个tabwidget。
 */
class QQTSHARED_EXPORT QQtPictureTabWidget : public QQtTabWidget
{
    Q_OBJECT
public:
    explicit QQtPictureTabWidget ( QWidget* parent = nullptr );
    virtual ~QQtPictureTabWidget() {}

signals:

public slots:
private:
    QQtPictureTabBar* m_bar;

    // QQtTabWidget interface
public:
    virtual void setObjectName ( const QString& name ) override;
    virtual QQtTabBar* localTabBar() const override { return m_bar; }
};

#endif // QQTPICTURETABWIDGET_H
