#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qcamera.h>
#include <qqtvideomanager.h>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * 经过测试，无论如何QVideoProbe都不能从Android拿到录像，原因不明。
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void slotSetPicture ( QImage );

    void present ( const QVideoFrame& frame );

private:
    Ui::MainWindow* ui;

    QCamera* camera;
    QVideoProbe* probe;
};

#endif // MAINWINDOW_H
