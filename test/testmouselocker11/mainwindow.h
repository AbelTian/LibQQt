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

private:
    Ui::MainWindow* ui;


    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;
};

#endif // MAINWINDOW_H
