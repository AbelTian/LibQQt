#ifndef QQTWINDOW_H
#define QQTWINDOW_H

#include <QStackedWidget>

namespace Ui {
class QQTWindow;
}

/**
 * @brief The QQTWindow class
 * 窗口切换有绿屏 ，启动时的绿屏，解决。
 * 窗口跳转不再经过信号和槽，而是通过这个注册的主窗的函数
 */
class QQTWindow : public QStackedWidget
{
    Q_OBJECT

public:
    explicit QQTWindow(QWidget *parent = 0);
    ~QQTWindow();

private:
    Ui::QQTWindow *ui;
};

#endif // QQTWINDOW_H
