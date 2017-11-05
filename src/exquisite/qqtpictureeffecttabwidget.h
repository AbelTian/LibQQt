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
    QQtTabBar* m_bar;

    // QQtTabWidget interface
public:
    virtual void setObjectName(const QString& name) override;
    virtual QTabBar* localTabBar() const override;
};

#endif // QQTPICTUREEFFECTTABWIDGET_H
