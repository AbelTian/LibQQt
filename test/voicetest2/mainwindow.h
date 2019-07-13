#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqtaudiomanager.h>
#include <qqtwavaudiomanager.h>

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

    //录音到wav
    void wavRecReadyRead();
    //读取rec wav播放
    void wavFileReadyRead();
    void on_pushButton_3_clicked();

    void on_inHS_valueChanged ( int value );

    void on_outHS_valueChanged ( int value );

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow* ui;
    QQtAudioManager manager;

    QQtAudioManager wavRecManager;
    QQtWavAudioManager wavFileManager;
};

#endif // MAINWINDOW_H
