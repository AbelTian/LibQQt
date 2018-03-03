#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <GumboQueryDocument.h>
#include <GumboQuerySelection.h>
#include <GumboQueryNode.h>
#include <QStringList>
#include <QTextCodec>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    m_webmanager = new QQtWebAccessManager ( this );
    connect ( m_webmanager, SIGNAL ( replyFinished ( QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished ( QQtWebAccessSession* ) ) );

    m_webmanager->setCookieJar ( &cookiejar );

    sendInitPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendInitPage()
{
    QString url =
        "http://124.161.179.36:8080/index/";
    req.setUrl ( QUrl ( url ) );    //
    m_webmanager->sendGetRequest ( req );
}

void MainWindow::sendGetLoginPage()
{
    QString url =
        "http://124.161.179.36:8080/index/ssologin.action";
    req.setUrl ( QUrl ( url ) );    //
    m_webmanager->sendGetRequest ( req );
}

void MainWindow::sendLoginRequest()
{
    req.setRawHeader ( "User-Agent",
                       "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_5) AppleWebKit/603.2.4 (KHTML, like Gecko) Version/10.1.1 Safari/603.2.4" );
    req.setRawHeader ( "Accept-Encoding", "gzip, deflate" );
    req.setRawHeader ( "Accept-Language", "zh-cn" );
    req.setRawHeader ( "Connection", "keep-alive" );
    req.setRawHeader ( "Content-Type", "application/x-www-form-urlencoded; charset=UTF-8" );
    req.setRawHeader ( "DNT", "1" );
    req.setRawHeader ( "Origin", "http://124.161.179.36:8080" );
    req.setRawHeader ( "Host", "124.161.179.36:8080" );

    req.setRawHeader ( "X-Requested-With", "XMLHttpRequest" );
    req.setRawHeader ( "Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8" );
    req.setRawHeader ( "Upgrade-Incecure-Requests", "1" );

//    req.setRawHeader ( "Referer",
//                       "http://124.161.179.36:8080/sso/login?service=http%3A%2F%2F124.161.179.36%3A8080%2Findex%2Fssologin.action" );

    QList<QNetworkCookie> cookieList = getLoginCookies();
    QListIterator<QNetworkCookie> itor ( cookieList );

    while ( itor.hasNext() )
    {
        QNetworkCookie cookie = itor.next();
        cookiejar.insertCookie ( cookie );
    }

//    QVariant cookieVar;
//    cookieVar.setValue ( cookiejar.cookiesForUrl() );
//    req.setHeader ( QNetworkRequest::CookieHeader, cookieVar );


    QString url =
        "http://124.161.179.36:8080/sso/login?service=http%3A%2F%2F124.161.179.36%3A8080%2Findex%2Fssologin.action";
    req.setUrl ( QUrl ( url ) );    //
    req.setRawHeader ( "Content-Length", "124" );

    QByteArray data;
    data = "isJgChecked=on&orgid=1&username=ss_admin&isZhChecked=on&lt=e2s2&_eventId=submit&rememberMe=1&password=MTExMTEx&imageCode=954";
    m_webmanager->sendPostRequest ( req, data );
}

void MainWindow::sendYaowuRequest()
{
    req.setRawHeader ( "Accept", "application/json, text/javascript, */*; q=0.01" );
    req.setRawHeader ( "Referer", "http://124.161.179.36:8080/index/ssologin.action" );
    QString url =
        "http://124.161.179.36:8080/index/dictionaryItem/queryItemTreeListByCode.action?dictionaryCode=DIC_GBT2260_2007&itemCode=null";
    QByteArray cookieBytes =
        "JSESSIONID=40E28196F1766BDEC15F6B11B465E8EE; orgId=1; orgName=%25u8D44%25u9633%25u5E02%25u536B%25u8BA1%25u59D4; userName=ss_admin";

    req.setRawHeader ( "Referer", "http://124.161.179.36:8080/dictionary-manage/yptym/totymzdmx.action" );
    url = QString ( "http://124.161.179.36:8080/dictionary-manage/yptym/queryZDMXList.action" );
    cookieBytes =
        "JSESSIONID=03D49123CB34BDBEA60E2F36C23118C9; orgId=1; orgName=%25u8D44%25u9633%25u5E02%25u536B%25u8BA1%25u59D4; userName=ss_admin";

    //登陆
    cookieBytes =
        "JSESSIONID=74F47D80C4681A4E3E1509018AE68747; orgId=1; orgName=%25u8D44%25u9633%25u5E02%25u536B%25u8BA1%25u59D4; userName=ss_admin";


    //mReq.setRawHeader ( "Referer", "http://124.161.179.36:8080/dictionary-manage/yptym/totymzdmx.action" );
    url = QString ( "http://124.161.179.36:8080/sso/login?service=http%3A%2F%2F124.161.179.36%3A8080%2Fdictionary-manage%2Findex.action" );
    cookieBytes =
        "";


    QList<QNetworkCookie> cookieList = getSessionCookies();
    //pline() << cookieList;
    QVariant cookieVar;
    cookieVar.setValue ( cookieList );

    req.setUrl ( QUrl ( url ) );    //

    //mReq.setHeader ( QNetworkRequest::CookieHeader, cookieVar );//
    //cookiejar.setCookiesFromUrl ( cookieList, url );
}

void MainWindow::replyFinished ( QQtWebAccessSession* session )
{
    QNetworkReply* reply = session->getWebAccessReply();
    //pline() << reply->readAll();
    pline() << "请求的网址" << reply->url().toString();

    QList<QNetworkCookie>  cookies = m_webmanager->cookieJar()->cookiesForUrl ( reply->url() );
    //pline() << "内部cookie" << cookies;
    cookies = cookiejar.cookiesForUrl ( reply->url() );
    static QList<QNetworkCookie> staticCookieList = cookies;

    if ( staticCookieList != cookies )
    {
        pline() << "cookies 在这次请求返回后被更换了";
        staticCookieList = cookies;
    }

    pline() << "我本地存储的cookie" << cookies;

    int nHttpCode = reply->attribute ( QNetworkRequest::HttpStatusCodeAttribute ).toInt(); //http返回码

    if ( nHttpCode == 200 ) //成功
    {
        pline() << "success";
    }
    else if ( nHttpCode == 302
              || nHttpCode == 301 )
    {
        QString redirect = reply->attribute ( QNetworkRequest::RedirectionTargetAttribute ).toString();
        pline() << "redirect" << "重定向url是" << redirect;

        req.setRawHeader ( "Content-Length", "0" );
//        QVariant var;
//        var.setValue ( cookieList );
//        req.setHeader ( QNetworkRequest::CookieHeader, var );

        if ( redirect.contains ( "http" ) )
            req.setUrl ( QUrl ( redirect ) );
        else
        {
            req.setUrl ( QUrl ( "http://124.161.179.36:8080" + redirect ) );
        }

        m_webmanager->sendGetRequest ( req );

        return;
    }
    else
    {
        pline() << nHttpCode <<  "fail";
        return;
    }

    QByteArray resultContent = reply->readAll();
    //pline() << QString ( resultContent );
    QString result1 = resultContent;
    //pline() << result1.toLatin1().constData();
    pline() << QTextCodec::codecForHtml ( resultContent )->name();
    QString codecName = QTextCodec::codecForHtml ( resultContent )->name();

    /*用页面源文件的编码来进行解码 GB2312 or UTF-8*/
    QTextCodec* pCodec = QTextCodec::codecForName ( "UTF-8" );
    QString strResult = pCodec->toUnicode ( resultContent );
    //pline() << strResult;

    QTextCodec* pCodec2 = QTextCodec::codecForName ( "UTF-8" );
    QByteArray resultContent2 = pCodec2->fromUnicode ( strResult );
    QString result2 = resultContent2;
    //pline() << result2;

    pline() << QTextCodec::codecForLocale()->name();

    pline() << result2;

    //获取初始页面成功，开始获取登录页面
    if ( result2.contains ( "0;url=ssologin.action" ) )
    {
        sendGetLoginPage();
        return;
    }
    //获取登录页面成功，需要获取验证码，使用用户名密码开始登录请求。
    else if ( result2.contains ( "!--登录框start--" ) )
    {
        //这里是登陆的最后一步，也是关键一步，但是没有实现。这个函数里面，验证码是错误的，所以登录失败，再一次进入相同页面。
        //关于地址：服务器IP 端口
        //关于用户名密码，加密的密码。（抓包软件抓到的那种。）
        //关于验证码，没有实现读取，所以实现到这里就停下了。但是使用cookie进行通信的过程顺序理清楚了。
        //这个程序的重点在于学习http带cookie的工作过程。
        sendLoginRequest();
        return;
    }

    QTextCodec* pCodec3 = QTextCodec::codecForName ( "GBK" );
    QByteArray resultContent3 = pCodec3->fromUnicode ( resultContent2 );
    QString result3 = resultContent3;
    QFile file ( "/Users/abel/Desktop/cc.html" );
    file.open ( QFile::WriteOnly );
    file.write ( result1.toLocal8Bit().constData() );
    file.close();

    return;

    GumboQueryDocument doc;
    doc.parse ( result2.toLocal8Bit().constData() );
    GumboQuerySelection s = doc.find ( "table" );

    GumboQueryNode pNode = s.nodeAt ( 0 );
    QString txt = QString::fromStdString ( pNode.text() );

    //pline() << txt;
    QStringList tList = txt.split ( "\n", QString::SkipEmptyParts );
}

void MainWindow::on_pushButton_clicked()
{

}
