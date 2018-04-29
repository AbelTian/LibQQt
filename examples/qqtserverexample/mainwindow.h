#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qqtserverprotocolmanager.h"
#include "qqtserver2protocolmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();

private slots:
    //我接收一个信息，处理一下。
    //这个信息我关注它。
    void recvANotify ( const QQtProtocol* protocol,
                       const QQtMessage* message );

private:
    Ui::MainWindow* ui;
    QQtHgProtocolManager* pm0;
};

#endif // MAINWINDOW_H
