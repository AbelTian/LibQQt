#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qqtdicthelper.h>
#include <usercustomtreemodel.h>
#include <qqtprogressbardelegate.h>
#include <qqtbuttonitemdelegate.h>
#include <qqtcheckboxdelegate.h>
#include <qqtslideritemdelegate.h>
#include <qqtframe.h>

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

    QQtDictionary mDict;
    UserCustomTreeModel* mModel;
};

#endif // MAINWINDOW_H
