#ifndef QQTHORIZONTALTEXTEFFECTTABWIDGET_H
#define QQTHORIZONTALTEXTEFFECTTABWIDGET_H

#include <qqttabwidget.h>
#include <qqthorizontaltexteffecttabbar.h>

class QQtHorizontalTextEffectTabWidget : public QQtTabWidget
{
    Q_OBJECT
public:
    explicit QQtHorizontalTextEffectTabWidget(QWidget* parent = nullptr);

signals:

public slots:

private:
    QQtHorizontalTextEffectTabBar* m_bar;

    // QQtTabWidget interface
public:
    virtual void setObjectName(const QString& name) override;
    virtual QQtTabBar* localTabBar() const override { return m_bar; }
};

#endif // QQTHORIZONTALTEXTEFFECTTABWIDGET_H
