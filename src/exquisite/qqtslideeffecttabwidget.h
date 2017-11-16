#ifndef QQTSLIDEEFFECTTABWIDGET_H
#define QQTSLIDEEFFECTTABWIDGET_H

#include <qqttabwidget.h>
#include <qqtslideeffecttabbar.h>

class QQtSlideEffectTabWidget : public QQtTabWidget
{
    Q_OBJECT
public:
    explicit QQtSlideEffectTabWidget(QWidget* parent = nullptr);

signals:

public slots:

private:
    QQtSlideEffectTabBar* m_bar;

    // QQtTabWidget interface
public:
    virtual void setObjectName(const QString& name) Q_DECL_OVERRIDE;
    virtual QQtTabBar* localTabBar() const Q_DECL_OVERRIDE { return m_bar; }
};

#endif // QQTSLIDEEFFECTTABWIDGET_H
