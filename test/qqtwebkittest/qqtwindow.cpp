#include "qqtwindow.h"
#include "ui_qqtwindow.h"
#include "qqtobjectfactory.h"
#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "QtWebKit/QWebView"
#include <QFile>

QQTWindow::QQTWindow ( QWidget* parent ) :
    QStackedWidget ( parent ),
    ui ( new Ui::QQTWindow )
{
    ui->setupUi ( this );

    QQtObjectManager::registerObject ( this );

#ifdef __EMBEDDED_LINUX__
    /*
     * 这里只要frameless足够
     */
    setWindowFlags ( Qt::FramelessWindowHint );
    /*
     * 控件背景透明，显示设置的图片背景或者下一级背景。
     */
    setAttribute ( Qt::WA_TranslucentBackground, true );
#endif
    //setFixedSize(1024, 600);
    moveCenter ( this );

    connect ( ui->lineEdit, SIGNAL ( btnClicked() ),
              this, SLOT ( brow() ) );

    connect ( ui->textEdit, SIGNAL ( textChanged() ),
              this, SLOT ( refresh() ) );

    ui->textEdit->setMinimumWidth ( 500 );
}

QQTWindow::~QQTWindow()
{
    delete ui;
}

void QQTWindow::brow()
{
    ui->widget->load ( QUrl ( ui->lineEdit->text() ) );
}

void QQTWindow::refresh()
{
    ui->widget_2->setHtml ( ui->textEdit->toPlainText() );
}
