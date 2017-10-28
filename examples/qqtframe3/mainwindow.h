#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
};

#endif // MAINWINDOW_H
