#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void setSum();
    void set2Sum();
    void set3Sum();

    void set4Sum();
    void set5Sum();

    void set6Sum();

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
