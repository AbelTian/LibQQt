#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqtv4l2videomanager.h>

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
    void on_pushButton_2_clicked();

    void slotCaptured ( const QImage& img );
private:
    Ui::MainWindow* ui;

    QQtV4L2VideoManager* manager;
};

#endif // MAINWINDOW_H
