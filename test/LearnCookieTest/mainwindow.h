#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qqtcore.h"
#include "qqtwebaccessmanager.h"

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

    //工作过程分析
    //首先，登陆，post，带上用户名、密码、单位、验证码？等
    //第二，在回复中得到cookie，而后就用这个cookie
    //第三，在每一次回复后都更新cookie，并且使用新的cookie进行请求。

    //初始页面
    void sendInitPage();
    //获取登录页面
    void sendGetLoginPage();
    //开始登录 （未实现填写验证码）
    void sendLoginRequest();
    //获取数据 （未实现）
    void sendYaowuRequest();

private slots:
    void replyFinished ( QQtWebAccessSession* session );
    void on_pushButton_clicked();

protected:
    QList<QNetworkCookie> getLoginCookies();
    QList<QNetworkCookie> getSessionCookies();

private:
    Ui::MainWindow* ui;
    QQtWebAccessManager* m_webmanager;
    QNetworkRequest req;
    QQtWebAccessCookieJar cookiejar;
};

#endif // MAINWINDOW_H
