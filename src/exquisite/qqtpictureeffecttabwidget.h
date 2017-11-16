#ifndef QQTPICTUREEFFECTTABWIDGET_H
#define QQTPICTUREEFFECTTABWIDGET_H

#include <qqttabwidget.h>
#include <qqtpictureeffecttabbar.h>

class QQtPictureEffectTabWidget : public QQtTabWidget
{
    Q_OBJECT
public:
    explicit QQtPictureEffectTabWidget(QWidget* parent = nullptr);
    virtual ~QQtPictureEffectTabWidget() {}

signals:

public slots:
private:
    QQtPictureEffectTabBar* m_bar;

    // QQtTabWidget interface
public:
    virtual void setObjectName(const QString& name) override;
    virtual QQtTabBar* localTabBar() const override { return m_bar; }
};

#endif // QQTPICTUREEFFECTTABWIDGET_H
