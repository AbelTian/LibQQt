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
    virtual void setObjectName(const QString& name) Q_DECL_OVERRIDE;
    virtual QQtTabBar* localTabBar() const Q_DECL_OVERRIDE { return m_bar; }
};

#endif // QQTHORIZONTALTEXTEFFECTTABWIDGET_H
