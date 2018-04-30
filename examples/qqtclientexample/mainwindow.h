#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qqtclientprotocol.h"
#include "qqtclient2protocol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();

public slots:
    void on_recv_say_hello ( QString );
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow* ui;
    QQtClientProtocol* p;
};

#endif // MAINWINDOW_H
