#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqtvideomanager.h>

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
    void slotImageComing ( QImage );
    void slotImageComing2 ( QImage );
    void slotCapture ( QImage );

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow* ui;

    QQtVideoInput* input;
    QQtVideoInput* input2;
};

#endif // MAINWINDOW_H
