#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
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
    void clicked1 ( QPoint point );
    void clicked2();

    void currentItemChanged ( QListWidgetItem* current, QListWidgetItem* previous );

private:
    Ui::MainWindow* ui;

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;
};

#endif // MAINWINDOW_H
