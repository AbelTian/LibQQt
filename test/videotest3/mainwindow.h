#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qqtvideomanager.h>
#include <cameracontrollerform.h>

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
    void slotISOModelChanged ( bool );

private:
    Ui::MainWindow* ui;

    QQtVideoManager* manager;
    CameraControllerForm* form;

    // QWidget interface
protected:
    virtual void moveEvent ( QMoveEvent* event ) override;
    virtual void resizeEvent ( QResizeEvent* event ) override;

    // QWidget interface
protected:
    virtual void closeEvent ( QCloseEvent* event ) override;
    virtual void showEvent ( QShowEvent* event ) override;
    virtual void hideEvent ( QHideEvent* event ) override;
};

#endif // MAINWINDOW_H
