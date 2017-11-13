#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void setValue(int);
    void setValue();
    void setValueDown();
private:
    QTimer* m_timer ;
    QTimer* m_timer_down ;
    int value;
    int curmaxValue;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

    // QObject interface
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
