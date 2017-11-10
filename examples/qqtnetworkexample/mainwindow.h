#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqtbluetoothmanager.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void addDevice(QBluetoothDeviceInfo);
    void addService(QBluetoothServiceInfo);


private slots:
    void on_btnRefresh_clicked();

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
