#ifndef QQTPICTURETABWIDGET_H
#define QQTPICTURETABWIDGET_H

#include <qqttabwidget.h>
#include <qqtpicturetabbar.h>

class QQtPictureTabWidget : public QQtTabWidget
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
