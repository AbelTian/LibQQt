#ifndef QQTHORIZONTALTEXTTABWIDGET_H
#define QQTHORIZONTALTEXTTABWIDGET_H

#include <qqttabwidget.h>
#include <qqthorizontaltexttabbar.h>

class QQtHorizontalTextTabWidget : public QQtTabWidget
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
