#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qqtframe.h"
#include "qqtwavaudiomanager.h"
#include "qqtaudiomanager.h"

#include "fmod.hpp"

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

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow* ui;

    QQtWavAudioManager wavManager;
    QQtAudioManager audManager;

//Windows下无法编译通过，Android下提示libart.so错误。
#if 0
    FMOD::System*     system;
    FMOD::Sound*      sound, *sound_to_play;
    FMOD::Channel*    channel = 0;
    FMOD_RESULT       result;
    unsigned int      version;

    int               numsubsounds;
#endif

};

#endif // MAINWINDOW_H
