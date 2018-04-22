#include "qqtwindow.h"
#include "ui_qqtwindow.h"
#include "qqtobjectfactory.h"
#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqtwebclient.h"
#include "qqthttpprotocol.h"
#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QNetworkReply"
#include <QtWebKitWidgets/QWebView>

QQTWindow::QQTWindow(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::QQTWindow)
{
    ui->setupUi(this);

    QQtObjectManager::registerObject(this);

#ifdef __EMBEDDED_LINUX__
    /*
     * 这里只要frameless足够
     */
    setWindowFlags(Qt::FramelessWindowHint);
    /*
     * 控件背景透明，显示设置的图片背景或者下一级背景。
     */
    setAttribute(Qt::WA_TranslucentBackground, true);
#endif
    setFixedSize(1024, 600);
    moveCenter(this);

    QQtWebClient* manager = new QQtWebClient(this);

    pline() << manager->supportedSchemes();

    QString baseUrl = "http://www.csdn.net/";
    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl));

    QString baseUrl2 = "http://download.qt.io/";
    QNetworkRequest request2;
    request2.setUrl(QUrl(baseUrl2));

    QNetworkReply *pReplay = manager->get(request);
    QNetworkReply *pReplay2 = manager->get(request2);

    pline()<<pReplay <<pReplay2;

    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray bytes = pReplay->readAll();
    //pline() << bytes;
    QFile file("csdn.net");
    file.open(QFile::WriteOnly|QFile::Truncate);
    if(file.isOpen())
    {
        file.write(bytes);
        file.close();
    }

    pline() << pReplay2->isFinished();

    bytes = pReplay2->readAll();
    file.setFileName("download.qt.io");
    file.open(QFile::WriteOnly|QFile::Truncate);
    if(file.isOpen())
    {
        file.write(bytes);
        file.close();
    }

    QWebView* view = new QWebView(this);
    view->load(QUrl::fromUserInput("download.qt.io"));
    view->show();
    view->setFixedSize(1024, 600);

    int a = 0;
    int b = 2;
    pline() << a << b;
    int c = [&a](int x) -> int {
        a = 4;
        return a + x + 5;
    }(7);

    pline() << a <<  c << b;
}

QQTWindow::~QQTWindow()
{
    delete ui;
}
