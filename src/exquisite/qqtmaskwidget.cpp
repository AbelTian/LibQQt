#include "qqtmaskwidget.h"
#include "qapplication.h"

QQtMaskWidget* QQtMaskWidget::self = 0;
QQtMaskWidget::QQtMaskWidget ( QWidget* parent ) : QWidget ( parent )
{
    mainWidget = 0;
    setOpacity ( 0.7 );
    setBgColor ( QColor ( 0, 0, 0 ) );

    this->setWindowFlags ( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint );

    //绑定全局事件,过滤弹窗窗体进行处理
    qApp->installEventFilter ( this );
}

void QQtMaskWidget::setMainWidget ( QWidget* mainWidget )
{
    if ( this->mainWidget != mainWidget )
    {
        this->mainWidget = mainWidget;
    }
}

void QQtMaskWidget::setDialogNames ( const QStringList& dialogNames )
{
    if ( this->dialogNames != dialogNames )
    {
        this->dialogNames = dialogNames;
    }
}

void QQtMaskWidget::setOpacity ( double opacity )
{
    this->setWindowOpacity ( opacity );
}

void QQtMaskWidget::setBgColor ( const QColor& bgColor )
{
    QPalette palette = this->palette();
    palette.setBrush ( QPalette::Background, bgColor );
    this->setPalette ( palette );
}

void QQtMaskWidget::showEvent ( QShowEvent* )
{
    if ( mainWidget != 0 )
    {
        this->setGeometry ( mainWidget->geometry() );
    }
}

bool QQtMaskWidget::eventFilter ( QObject* obj, QEvent* event )
{
    if ( event->type() == QEvent::Show )
    {
        if ( dialogNames.contains ( obj->objectName() ) )
        {
            this->show();
            QWidget* w = ( QWidget* ) obj;
            w->activateWindow();
        }
    }
    else if ( event->type() == QEvent::Hide )
    {
        if ( dialogNames.contains ( obj->objectName() ) )
        {
            this->hide();
        }
    }

    return QObject::eventFilter ( obj, event );
}
