#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqttcpclient.h>
#include <touchmonitorprotocol.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();
    //业务层初始化一下这个实例，总是从这里获取协议句柄进行对外读写。
    QQtTcpClient* TouchMonitorInstance ( TouchMonitorProtocol*& protocol, QObject* parent = 0 );

private:
    Ui::MainWindow* ui;
    QQtTcpClient* s0;
    TouchMonitorProtocol* p0;
};

#endif // MAINWINDOW_H
