#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qqtdictionary.h>
#include <qqtwebaccessmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();

protected slots:
    void replyFinished ( QQtWebAccessSession* );
    void replyFinished2 ( QQtWebAccessSession* );
    void replyFinished3 ( QQtWebAccessSession* );
    void replyFinished4 ( QQtWebAccessSession* );

private:
    Ui::MainWindow* ui;

    QQtWebAccessManager* manager;
    QQtWebAccessManager* manager2;
    QQtWebAccessManager* manager3;
    QQtWebAccessManager* manager4;
};

#endif // MAINWINDOW_H
