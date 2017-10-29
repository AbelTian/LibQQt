#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
private slots:
    void currentItemChanged(QListWidgetItem*, QListWidgetItem*);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
