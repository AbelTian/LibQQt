#include "qqtcustomqrdecodewidget.h"
#include "QZXing.h"

#include <QPainter>
#include <QDebug>

#include <QMouseEvent>
#include <QTimerEvent>
#include <QShowEvent>

#include <QApplication>
#include <QScreen>
#include <QUrl>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QCursor>

#include <QClipboard>
#include <QMetaMethod>
#include <QToolTip>
#include <QFontMetrics>

QQtCustomQrDecodeWidget::QQtCustomQrDecodeWidget ( QWidget* parent )
    : QWidget ( parent ), m_bScaned ( false )
{
    this->resize ( 300, 300 );
    setWindowOpacity ( 1 );
    setWindowFlags ( /*this->windowFlags() |*/ Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    // 设置透明
    setAttribute ( Qt::WA_TranslucentBackground );

    m_nY    = 20;
    m_nTimerId = -1;
    m_strScanResult = "Hello World!";
    m_startPoint = QPoint();
    m_nDirection =  DOWN;

    QMenu* resizeMenu = new QMenu ( this );
    resizeMenu->setTitle ( "重置大小" );
    resizeMenu->addAction ( tr ( "200*200" ) );
    resizeMenu->addAction ( tr ( "300*300" ) );
    resizeMenu->addAction ( tr ( "400*400" ) );

    mainMenu = new QMenu ( this );
    mainMenu->addMenu ( resizeMenu );
    mainMenu->addSeparator();
    mainMenu->addAction ( tr ( "重新扫描" ) );
    mainMenu->addAction ( tr ( "打开链接" ) );
    mainMenu->addAction ( tr ( "复制结果到粘贴板" ) );
    mainMenu->addSeparator();
    mainMenu->addAction ( tr ( "退出" ) );

    connect ( resizeMenu, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( SltActionTriggered ( QAction* ) ) );
    connect ( mainMenu, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( SltActionTriggered ( QAction* ) ) );
    this->setCursor ( Qt::PointingHandCursor );

    // 启动定时器
    m_nTimerId = startTimer ( 15 );
}

QQtCustomQrDecodeWidget::~QQtCustomQrDecodeWidget()
{
    // 启动定时器
    if ( -1 == m_nTimerId )
    {
        m_nTimerId = startTimer ( 15 );
    }

    delete mainMenu;
    mainMenu = NULL;
}

// -------------------------处理鼠标点击移动-----------------------------//
void QQtCustomQrDecodeWidget::mousePressEvent ( QMouseEvent* e )
{
    if ( e->button() == Qt::RightButton )
    {
        mainMenu->popup ( QCursor::pos() );
    }
    else
    {
        m_startPoint = e->pos();
    }
}

void QQtCustomQrDecodeWidget::mouseMoveEvent ( QMouseEvent* e )
{
    if ( m_startPoint.isNull() )
        return;

    if ( ( e->pos() - m_startPoint ).manhattanLength() > 0 )
    {
        QPoint p = pos() + e->pos() - m_startPoint;
        move ( p );
    }
}

void QQtCustomQrDecodeWidget::mouseReleaseEvent ( QMouseEvent* )
{
    m_startPoint = QPoint();
}

/**
 * @brief MainWidget::paintEvent
 * @param e
 */
void QQtCustomQrDecodeWidget::paintEvent ( QPaintEvent* )
{
    QPainter painter ( this );
    painter.setRenderHint ( QPainter::Antialiasing );

    // 扫描完成
    if ( m_bScaned )
    {
        painter.setPen ( Qt::red );
        painter.drawRoundRect ( this->rect(), 2, 2 );
        QRect rect = this->rect();
        rect.setX ( this->rect().x() + 1 );
        rect.setY ( this->rect().y() + 1 );
        rect.setWidth ( this->width() - 2 );
        rect.setHeight ( this->height() - 2 );

        painter.fillRect ( rect, Qt::white );

        painter.setPen ( QPen ( Qt::black, 2 ) );
        painter.setFont ( QFont ( "微软雅黑", 14 ) );
        painter.drawText ( 0, 0, this->width(), 50, Qt::AlignCenter, tr ( "扫描结果：" ) );
        QTextOption option;
        option.setWrapMode ( QTextOption::WordWrap );

        QFont font ( "微软雅黑", 12 );

        painter.setFont ( font );
        painter.setBrush ( Qt::yellow );
        painter.drawText ( QRect ( 5, 50, this->width() - 10, this->height() - 50 ), m_strScanResult, option );
    }
    else
    {
        painter.fillRect ( this->rect(), Qt::transparent );

        int nWidth = qMin ( this->width(), this->height() );
        nWidth -= 20;

        painter.setPen ( QPen ( Qt::white, 2 ) );
        painter.drawRect ( 10, 10, nWidth, nWidth );

        // 绘制4个角
        painter.setPen ( QPen ( Qt::red, 4 ) );
        painter.drawLine ( 10, 10,  nWidth / 10 + 10, 10 );
        painter.drawLine ( 10 + nWidth - nWidth / 10, 10,  10 + nWidth, 10 );

        painter.drawLine ( 10, 10 + nWidth,  nWidth / 10 + 10, 10 + nWidth );
        painter.drawLine ( 10 + nWidth - nWidth / 10, 10 + nWidth,  10 + nWidth, 10 + nWidth );


        // 底部横线
        painter.drawLine ( 10, 10,  10, 10 + nWidth / 10 );
        painter.drawLine ( 10, 10 + nWidth - nWidth / 10,  10, 10 + nWidth );

        painter.drawLine ( 10 + nWidth, 10, 10 + nWidth, 10 + nWidth / 10 );
        painter.drawLine ( 10 + nWidth, 10 + nWidth - nWidth / 10,  10 + nWidth, 10 + nWidth );

        // 绘制横向动态的那个线
        painter.drawLine ( 40, m_nY, nWidth - 20, m_nY );
    }
}

/**
 * @brief MainWidget::timerEvent
 * @param event
 */
void QQtCustomQrDecodeWidget::timerEvent ( QTimerEvent* event )
{
    if ( event->timerId() == m_nTimerId )
    {
        if ( m_nY >= ( this->height() - 20 ) )
        {
            m_nDirection = UP;
            ScanRecord();
        }
        else if ( m_nY <= 20 )
        {
            m_nDirection = DOWN;
            ScanRecord();
        }


        if ( DOWN == m_nDirection )
        {
            m_nY += 2;
        }
        else
        {
            m_nY -= 2;
        }

        update();
    }
}

// 菜单响应
void QQtCustomQrDecodeWidget::SltActionTriggered ( QAction* action )
{
    // 退出
    if ( !QString::compare ( "退出", action->text() ) )
    {
        if ( -1 != m_nTimerId )
        {
            killTimer ( m_nTimerId );
        }

        qApp->quit();
    }
    else if ( !QString::compare ( "重新扫描", action->text() ) )
    {
        m_nY    = 20;
        m_strScanResult = "Hello World!";
        m_startPoint = QPoint();
        m_nDirection =  DOWN;
        m_bScaned = false;

//        setAttribute(Qt::WA_TranslucentBackground, true);

        // 启动定时器
        if ( -1 == m_nTimerId )
        {
            m_nTimerId = startTimer ( 15 );
        }
    }
    else if ( !QString::compare ( "打开链接", action->text() ) )
    {
        QDesktopServices::openUrl ( QUrl ( m_strScanResult ) );
    }
    else if ( !QString::compare ( "复制结果到粘贴板", action->text() ) )
    {
        // 复制到粘贴板
        if ( !m_strScanResult.isEmpty() )
        {
            QApplication::clipboard()->setText ( m_strScanResult );
        }
        // 如果未选取要复制的内容进行提示
        else
        {
            QToolTip::showText ( QCursor::pos(), tr ( "未扫描到任何数据!" ), this );
        }
    }
    else if ( !QString::compare ( "200*200", action->text() ) )
    {
        this->resize ( QSize ( 200, 200 ) );
    }
    else if ( !QString::compare ( "300*300", action->text() ) )
    {
        this->resize ( QSize ( 300, 300 ) );
    }
    else if ( !QString::compare ( "400*400", action->text() ) )
    {
        this->resize ( QSize ( 400, 400 ) );
    }
}

/**
 * @brief MainWidget::ScanRecord
 * 扫描图片
 */
void QQtCustomQrDecodeWidget::ScanRecord()
{
    QScreen* screen ;//= QGuiApplication::primaryScreen();
    int nWidth = qMin ( this->width(), this->height() );
    nWidth -= 20;
    QPixmap pixmap ;//= screen->grabWindow ( 0, this->pos().x() + 10, this->pos().y() + 10, nWidth, nWidth );

    // 解析二维码
    QZXing decoder ( QZXing::DecoderFormat_QR_CODE );
    m_strScanResult = decoder.decodeImage ( pixmap.toImage() );

    qDebug() << m_strScanResult;

    // 解析结果为空直接返回
    if ( m_strScanResult.isEmpty() )
        return;

    // 显示扫描结果
//    setAttribute(Qt::WA_TranslucentBackground, false);

    m_bScaned = true;
    killTimer ( m_nTimerId );
    m_nTimerId = -1;
}

