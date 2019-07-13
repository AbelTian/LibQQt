#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qqtwavaudiomanager.h"
#include "qqtaudiomanager.h"

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
    void on_play_frame();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow* ui;

    QQtWavAudioManager wavManager;
    QQtAudioManager audManager;
};

#endif // MAINWINDOW_H
