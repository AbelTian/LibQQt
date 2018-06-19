#ifndef QQTSLIDETABWIDGET_H
#define QQTSLIDETABWIDGET_H

#include <qqttabwidget.h>
#include <qqtslidetabbar.h>

#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtSlideTabWidget : public QQtTabWidget
{
    Q_OBJECT
public:
    explicit QQtSlideTabWidget ( QWidget* parent = nullptr );

signals:

public slots:

private:
    QQtSlideTabBar* m_bar;

    // QQtTabWidget interface
public:
    virtual void setObjectName ( const QString& name ) override;
    virtual QQtTabBar* localTabBar() const override { return m_bar; }
};

#endif // QQTSLIDETABWIDGET_H
