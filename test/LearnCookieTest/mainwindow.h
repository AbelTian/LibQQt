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

    QList<QNetworkCookie> getLoginCookies() {
        QUuid uuid = QUuid::createUuid ( );
        QString uuidStr = uuid.toString();
        uuidStr.remove ( '-' ).remove ( '{' ).remove ( '}' );
        uuidStr = uuidStr.toUpper();
        //pline() << uuidStr;

        const int size = 3;
        QNetworkCookie cookies[size] =
        {
            QNetworkCookie ( "orgId", "1" ),
            QNetworkCookie ( "orgName", "%25u8D44%25u9633%25u5E02%25u536B%25u8BA1%25u59D4" ),
            QNetworkCookie ( "userName", "ss_admin" )
        };

        QList<QNetworkCookie> cookieList;

        for ( int i = 0; i < size; i++ )
            cookieList.push_back ( cookies[i] );

        return cookieList;
    }

    QList<QNetworkCookie> getSessionCookies() {
        QUuid uuid = QUuid::createUuid ( );
        QString uuidStr = uuid.toString();
        uuidStr.remove ( '-' ).remove ( '{' ).remove ( '}' );
        uuidStr = uuidStr.toUpper();
        //pline() << uuidStr;
        static QString myuuidstr = uuidStr;

        const int size = 4;
        QNetworkCookie cookies[size] =
        {
            QNetworkCookie ( "JSESSIONID", myuuidstr.toLocal8Bit().constData() ),
            QNetworkCookie ( "orgId", "1" ),
            QNetworkCookie ( "orgName", "%25u8D44%25u9633%25u5E02%25u536B%25u8BA1%25u59D4" ),
            QNetworkCookie ( "userName", "ss_admin" )
        };

        QList<QNetworkCookie> cookieList;

        for ( int i = 0; i < size; i++ )
            cookieList.push_back ( cookies[i] );

        return cookieList;

    }

    void sendInitPage();
    void sendGetLoginPage();

    //工作过程分析
    //首先，登陆，post，带上用户名、密码、单位、验证码？等
    //第二，在回复中得到cookie，而后就用这个cookie
    //第三，在每一次回复后都更新cookie，并且使用新的cookie进行请求。

    void sendLoginRequest();

    void sendYaowuRequest();

private slots:
    void replyFinished ( QQtWebAccessSession* session );
    void on_pushButton_clicked();

private:
    Ui::MainWindow* ui;
    QQtWebAccessManager* m_webmanager;
    QNetworkRequest req;
    QQtWebAccessCookieJar cookiejar;
};

#endif // MAINWINDOW_H
