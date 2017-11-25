#ifndef QQTWINDOW_H
#define QQTWINDOW_H

#include <QStackedWidget>

namespace Ui {
class QQTWindow;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
/**
 * @brief The QQTWindow class
 * 窗口切换有绿屏 ，启动时的绿屏，解决。
 * 窗口跳转不再经过信号和槽，而是通过这个注册的主窗的函数
 */
class QQTWindow : public QStackedWidget
{
    Q_OBJECT

public:
    explicit QQTWindow(QWidget *parent = 0);
    ~QQTWindow();

public slots:
    void doubleClicked(const QModelIndex& index);
private:
    VlcInstance *_instance;
    VlcMediaPlayer *_player;
    VlcMedia *_media;
private:
    Ui::QQTWindow *ui;

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *) override;
    void dropEvent(QDropEvent *) override;
};

#endif // QQTWINDOW_H
