#include <qqtbodyselectedstyle.h>

#include <QEvent>
#include <QPainter>
#include <QWidget>

#include <qqtcore.h>

QQtBodySelectedStyle::QQtBodySelectedStyle ( QObject* parent ) : QObject ( parent )
{
    hasSelected = false;
    hasStyle = SelectedStyle_QtDesigner;
}

QQtBodySelectedStyle::~QQtBodySelectedStyle()
{

}

void QQtBodySelectedStyle::setSelectedStyle ( QQtBodySelectedStyle::SelectedStyle style )
{
    hasStyle = style;
}

QQtBodySelectedStyle::SelectedStyle QQtBodySelectedStyle::selectedStyle()
{
    return hasStyle;
}

void QQtBodySelectedStyle::setSelected ( bool bSelected )
{
    hasSelected = bSelected;
}

bool QQtBodySelectedStyle::selectedStatus()
{
    return hasSelected;
}


bool QQtBodySelectedStyle::eventFilter ( QObject* watched, QEvent* event )
{
    if ( !watched->inherits ( "QWidget" ) )
        return QObject::eventFilter ( watched, event );

    //修复鼠标穿透。
    bool atti = ( qobject_cast<QWidget*> ( watched ) )->testAttribute ( Qt::WA_TransparentForMouseEvents );
    if ( atti )
        return QObject::eventFilter ( watched, event );

    if ( event->type() == QEvent::Paint )
    {
        if ( hasSelected )
        {
            QWidget* target = qobject_cast<QWidget*> ( watched );
            QPainter painter ( target );

            int w = 10;
            //如果显示有问题，可以注释掉此处的缩放。
            //只在macOS里发现了右侧和下侧裁切掉了的现象。
            //painter.scale ( ( target->rect().width() - painter.pen().width() ) / target->rect().width(),
            //              ( target->rect().height() - painter.pen().width() ) / target->rect().height() );
            //painter.scale ( 0.999, 0.999 );

            painter.save();

            switch ( hasStyle )
            {
                case SelectedStyle_QtDesigner:
                {
                    painter.setPen ( Qt::black );
                    QRect srcRect = target->rect();
                    QRect tarRect = QRect ( srcRect.left() + w / 2, srcRect.top() + w / 2, srcRect.width() - w, srcRect.height() - w );
                    painter.drawRect ( tarRect );
                    //left top
                    painter.drawRect ( 0, 0, w, w );
                    //right top
                    painter.drawRect ( target->size().width() - w, 0, w, w );
                    //left bottom
                    painter.drawRect ( 0, target->size().height() - w, w, w );
                    //right bottom
                    painter.drawRect ( target->size().width() - w, target->size().height() - w, w, w );
                    //left
                    painter.drawRect ( 0, target->size().height() / 2 - w / 2, w, w );
                    //right
                    painter.drawRect ( target->size().width() - w, target->size().height() / 2 - w / 2, w, w );
                    //top
                    painter.drawRect ( target->size().width() / 2 - w / 2, 0, w, w );
                    //bottom
                    painter.drawRect ( target->size().width() / 2 - w / 2, target->size().height() - w, w, w );
                }
                break;
                case SelectedStyle_QRCodeScaner:
                {
                    painter.setPen ( Qt::black );
                    painter.drawLine ( 0, 0, w, 0 );
                    painter.drawLine ( 0, 0, 0, w );

                    painter.drawLine ( target->size().width() - w, 0, target->size().width(), 0 );
                    painter.drawLine ( target->size().width(), 0, target->size().width(), w );

                    painter.drawLine ( 0, target->size().height() - w, 0, target->size().height() );
                    painter.drawLine ( 0, target->size().height(), w, target->size().height() );

                    painter.drawLine ( target->size().width(), target->size().height() - w,
                                       target->size().width(), target->size().height() );
                    painter.drawLine ( target->size().width() - w, target->size().height(),
                                       target->size().width(), target->size().height() );
                }
                break;
                case SelectedStyle_DottedLine:
                {
                    painter.setPen ( Qt::black );
                    painter.setPen ( Qt::DotLine );
                    painter.drawRect ( target->rect() );
                }
                break;
                case SelectedStyle_FourCheck:
                {
                    painter.setPen ( Qt::black );
                    painter.drawRect ( target->rect() );
                    painter.drawRect ( 0, 0, w, w );
                    painter.drawRect ( target->size().width() - w, 0, w, w );
                    painter.drawRect ( 0, target->size().height() - w, w, w );
                    painter.drawRect ( target->size().width() - w, target->size().height() - w, w, w );
                }
                break;
                default:
                    break;
            }

            painter.restore();
        }
        return false;
    }

    //static int i = 0;
    //p2line() << i++ << watched->objectName() << event->type() ;

    switch ( event->type() )
    {
        //用户有需要自行添加
        //case QEvent::Enter:
        //case QEvent::Leave:

        case QEvent::FocusIn:
        {
            hasSelected = true;
            //QWidget* target = qobject_cast<QWidget*> ( watched );
            //target->update();
            return false;
        }
        break;
        case QEvent::FocusOut:
        {
            hasSelected = false;
            //QWidget* target = qobject_cast<QWidget*> ( watched );
            //target->update();
            return false;
        }
        break;
        default:
            break;
    }

    return QObject::eventFilter ( watched, event );
}
