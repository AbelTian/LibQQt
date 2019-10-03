#ifndef QQTHORIZONTALTEXTTABWIDGET_H
#define QQTHORIZONTALTEXTTABWIDGET_H

#include <qqttabwidget.h>
#include <qqthorizontaltexttabbar.h>

#include <qqtcore.h>
#include <qqt-local.h>

/**
 * @brief The QQtHorizontalTextTabWidget class
 * 使用自定义tabbar，
 * tabbar竖向的时候，文字是横向的。
 */
class QQTSHARED_EXPORT QQtHorizontalTextTabWidget : public QQtTabWidget
{
    Q_OBJECT
public:
    explicit QQtHorizontalTextTabWidget ( QWidget* parent = nullptr );

signals:

public slots:

private:
    QQtHorizontalTextTabBar* m_bar;

    // QQtTabWidget interface
public:
    virtual void setObjectName ( const QString& name ) override;
    virtual QQtTabBar* localTabBar() const override { return m_bar; }
};

#endif // QQTHORIZONTALTEXTTABWIDGET_H
