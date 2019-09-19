#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include "qqttitlebar.h"
#ifdef Q_OS_WIN
//#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif
#include <QSpacerItem>

QQtTitleBar::QQtTitleBar ( QWidget* parent )
    : QQtWidget ( parent )
{
    QWidget* win = this->window();

    win->setWindowFlags ( Qt::FramelessWindowHint | win->windowFlags() );
    win->installEventFilter ( this );

    //setStyleSheet ( "background-color:rgb(128, 126, 128);" );

    //int extent = style()->pixelMetric ( QStyle::PM_TitleBarHeight );
    //setFixedHeight ( extent );

    m_pLayout = new QHBoxLayout ( this );
    m_pIconLabel = new QQtWidget ( this );
    m_pTitleLabel = new QLabel ( this );
    QSpacerItem* item = new QSpacerItem ( 20, 20, QSizePolicy::Expanding );
    m_pMinimizeButton = new QToolButton ( this );
    m_pMaximizeButton = new QToolButton ( this );
    m_pCloseButton = new QToolButton ( this );

    //extent = style()->pixelMetric ( QStyle::PM_TitleBarButtonIconSize );
    //m_pIconLabel->setFixedSize ( QSize ( extent, extent ) );
    //m_pIconLabel->setScaledContents ( true );
    m_pIconLabel->setPixmap ( win->windowIcon().pixmap ( m_pIconLabel->size() ) );
    m_pIconLabel->setSizePolicy ( QSizePolicy::Minimum, QSizePolicy::Expanding );

    m_pTitleLabel->setText ( win->windowTitle() );
    m_pTitleLabel->setSizePolicy ( QSizePolicy::Minimum, QSizePolicy::Expanding );

    //extent = style()->pixelMetric ( QStyle::PM_TitleBarButtonSize );
    //m_pMinimizeButton->setFixedSize ( QSize ( extent, extent ) );
    //m_pMaximizeButton->setFixedSize ( QSize ( extent, extent ) );
    //m_pCloseButton->setFixedSize ( QSize ( extent, extent ) );

    m_pMinimizeButton->setIcon ( style()-> standardIcon ( QStyle::SP_TitleBarMinButton ) );
    m_pMaximizeButton->setIcon ( style()-> standardIcon ( QStyle::SP_TitleBarMaxButton ) );
    m_pCloseButton->setIcon ( style()-> standardIcon ( QStyle::SP_TitleBarCloseButton ) );

    m_pMinimizeButton->setSizePolicy ( QSizePolicy::Minimum, QSizePolicy::Expanding );
    m_pMaximizeButton->setSizePolicy ( QSizePolicy::Minimum, QSizePolicy::Expanding );
    m_pCloseButton->setSizePolicy ( QSizePolicy::Minimum, QSizePolicy::Expanding );

    m_pIconLabel->setObjectName ( "iconLabel" );
    m_pTitleLabel->setObjectName ( "titleLabel" );
    m_pMinimizeButton->setObjectName ( "minimizeButton" );
    m_pMaximizeButton->setObjectName ( "maximizeButton" );
    m_pCloseButton->setObjectName ( "closeButton" );

    m_pMinimizeButton->setToolTip ( "Minimize" );
    m_pMaximizeButton->setToolTip ( "Maximize" );
    m_pCloseButton->setToolTip ( "Close" );

    m_pLayout->addWidget ( m_pIconLabel );
    m_pLayout->addSpacing ( 5 );
    m_pLayout->addWidget ( m_pTitleLabel );
    m_pLayout->addSpacerItem ( item );
    m_pLayout->addWidget ( m_pMinimizeButton );
    m_pLayout->addWidget ( m_pMaximizeButton );
    m_pLayout->addWidget ( m_pCloseButton );
    m_pLayout->setSpacing ( 0 );
    m_pLayout->setContentsMargins ( 0, 0, 0, 0 );

    setLayout ( m_pLayout );

    connect ( m_pMinimizeButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onClicked() ) );
    connect ( m_pMaximizeButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onClicked() ) );
    connect ( m_pCloseButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( onClicked() ) );
}

QQtTitleBar::~QQtTitleBar()
{

}

void QQtTitleBar::setMinimizeVisible ( bool setting )
{
    m_pMinimizeButton->setVisible ( setting );
}

void QQtTitleBar::setMaximizeVisible ( bool setting )
{
    m_pMaximizeButton->setVisible ( setting );
}

int QQtTitleBar::layoutSpacing() { return m_pLayout->spacing(); }

void QQtTitleBar::setLayoutSpacing ( int spacing )
{
    m_pLayout->setSpacing ( spacing );
}

QMargins QQtTitleBar::layoutContentsMargins()
{
    return m_pLayout->contentsMargins();
}

void QQtTitleBar::setLayoutContentsMargins ( int left, int top, int right, int bottom )
{
    setLayoutContentsMargins ( QMargins ( left, top, right, bottom ) );
}

void QQtTitleBar::setLayoutContentsMargins ( const QMargins& margin )
{
    m_pLayout->setContentsMargins ( margin );
}

void QQtTitleBar::mouseDoubleClickEvent ( QMouseEvent* event )
{
    Q_UNUSED ( event );

    emit m_pMaximizeButton->clicked();
}

void QQtTitleBar::mousePressEvent ( QMouseEvent* event )
{
#ifdef __DESKTOP_WIN__
    if ( ReleaseCapture() )
    {
        QWidget* pWindow = this->window();
        if ( pWindow->isTopLevel() )
        {
            SendMessage ( HWND ( pWindow->winId() ), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0 );
        }
    }
    event->ignore();
#else
    if ( event->button() == Qt::LeftButton )
    {
        bMousePressed = true;
        pressedPoint = event->globalPos();
    }
    event->ignore();
#endif
    QQtWidget::mousePressEvent ( event );
}

void QQtTitleBar::mouseReleaseEvent ( QMouseEvent* event )
{
#ifdef __DESKTOP_WIN__
#else
    bMousePressed = false;
    event->ignore();
#endif
    QQtWidget::mouseReleaseEvent ( event );
}

void QQtTitleBar::mouseMoveEvent ( QMouseEvent* event )
{
#ifdef __DESKTOP_WIN__
#else
    QWidget* win = window();
    if ( bMousePressed && !win->isMaximized() )
    {
        QPoint movePoint = event->globalPos() - pressedPoint;
        QPoint widgetPos = win->pos();
        pressedPoint = event->globalPos();
        win->move ( widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y() );
    }
    event->ignore();
#endif
    QQtWidget::mouseMoveEvent ( event );
}

bool QQtTitleBar::eventFilter ( QObject* obj, QEvent* event )
{
    switch ( event->type() )
    {
        case QEvent::WindowTitleChange:
        {
            QWidget* pWidget = qobject_cast<QWidget*> ( obj );
            if ( pWidget )
            {
                m_pTitleLabel->setText ( pWidget->windowTitle() );
                return true;
            }
        }
        case QEvent::WindowIconChange:
        {
            QWidget* pWidget = qobject_cast<QWidget*> ( obj );
            if ( pWidget )
            {
                //必须对外部Widget设置WindowIcon，而不是这个Widget的WindowIcon.
                QIcon icon = pWidget->windowIcon();
                m_pIconLabel->setPixmap ( icon.pixmap ( m_pIconLabel->size() ) );
                return true;
            }
        }
        case QEvent::WindowStateChange:
        case QEvent::Resize:
        {
            int extent = m_pTitleLabel->size().height();
            m_pIconLabel->setMinimumSize ( extent, extent );
            m_pMinimizeButton->setMinimumSize ( extent, extent );
            m_pMaximizeButton->setMinimumSize ( extent, extent );
            m_pCloseButton->setMinimumSize ( extent, extent );
            updateMaximize();
            return true;
        }
        default:
            break;
    }
    return QWidget::eventFilter ( obj, event );
}

void QQtTitleBar::onClicked()
{
    QToolButton* pButton = qobject_cast<QToolButton*> ( sender() );
    QWidget* pWindow = this->window();
    if ( pWindow->isTopLevel() )
    {
        if ( pButton == m_pMinimizeButton )
        {
            pWindow->showMinimized();
        }
        else if ( pButton == m_pMaximizeButton )
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if ( pButton == m_pCloseButton )
        {
            pWindow->close();
        }
    }
}

void QQtTitleBar::updateMaximize()
{
    QWidget* pWindow = this->window();
    if ( pWindow->isTopLevel() )
    {
        bool bMaximize = pWindow->isMaximized();
        if ( bMaximize )
        {
            m_pMaximizeButton->setToolTip ( tr ( "Restore" ) );
            m_pMaximizeButton->setProperty ( "maximizeProperty", "restore" );
            m_pMaximizeButton->setIcon ( style()-> standardIcon ( QStyle::SP_TitleBarNormalButton ) );
        }
        else
        {
            m_pMaximizeButton->setProperty ( "maximizeProperty", "maximize" );
            m_pMaximizeButton->setToolTip ( tr ( "Maximize" ) );
            m_pMaximizeButton->setIcon ( style()-> standardIcon ( QStyle::SP_TitleBarMaxButton ) );
        }

        m_pMaximizeButton->setStyle ( QApplication::style() );
    }
}
