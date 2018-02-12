#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqtaudiomanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();

    QAudioDeviceInfo findInputAudioDeviceInfoByName ( QString devName );

    QAudioDeviceInfo findOutputAudioDeviceInfoByName ( QString devName );

private slots:
    void on_pushButton_2_clicked();
    void currentInputRowChanged ( QModelIndex, QModelIndex );
    void currentOutputRowChanged ( QModelIndex, QModelIndex );
    void on_pushButton_clicked();
    void readyRead();
    void on_pushButton_3_clicked();

    void on_inHS_valueChanged ( int value );

    void on_outHS_valueChanged ( int value );

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow* ui;
    QQtAudioManager manager;
};

#endif // MAINWINDOW_H
