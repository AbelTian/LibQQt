#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qqtframe.h"
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

private slots:
    void on_pushButton_clicked();
    void on_play_frame();

private:
    Ui::MainWindow* ui;

    QQtWavAudioManager wavManager;
    QQtAudioManager audManager;
};

#endif // MAINWINDOW_H
