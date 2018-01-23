#include "qqtwidget.h"
#include <QStylePainter>
#include "qqtcore.h"

QQtWidget::QQtWidget ( QWidget* parent ) :
    QWidget ( parent )
{
    m_style = QQTCENTER;

    m_lcTimer = new QTimer ( this );
    m_lcTimer->setSingleShot ( true );
    m_lcTimer->setInterval ( 2200 );
    connect ( m_lcTimer, SIGNAL ( timeout() ),
              this, SLOT ( slot_timeout() ) );
}

QQtWidget::~QQtWidget()
{
}

void QQtWidget::setPixmap ( const QString& pic )
{
    bool ret = mImg.load ( pic );
    /*请确认文件是否拷贝成功。*/
    //pline() << ret << mImg.isNull();
    update();
}

void QQtWidget::setPixmap ( const QPixmap& pixmap )
{
    mImg = pixmap.toImage();
    update();
}

void QQtWidget::setPixmap ( const QImage& image )
{
    mImg = image;
    update();
}

void QQtWidget::paintEvent ( QPaintEvent* event )
{
    if ( mImg.isNull() )
        return QWidget::paintEvent ( event );

    QStylePainter p ( this );

    switch ( m_style )
    {
        case QQTCENTER:
        {
            /*
             * 要达到居中的目标，QImage需要做的size判断很繁复，这里使用QIcon做一些中间转换的后续转换，可以很容易的达到绘制合理大小的pixmap的目的。
             * source: pixmap file image
             * QImage 输入、输出两侧是pixmap
             * 借助(+QIcon) QIcon 输入、输出两侧也是pixmap
             * dest: 所需要的、合理大小的pixmap
             */
            QIcon icon;
            icon.addPixmap ( QPixmap::fromImage ( mImg ), QIcon::Normal, QIcon::On );
            p.drawItemPixmap ( rect(), Qt::AlignCenter, icon.pixmap ( rect().size(), QIcon::Normal, QIcon::On ) );
            //QSize mSize = mImg.rect() > rect() ? rect().size() : mImg.size();
            //p.drawItemPixmap ( rect(), Qt::AlignCenter, QPixmap::fromImage ( mImg.scaled ( mSize, Qt::KeepAspectRatio ) ) );
        }
        break;

        case QQTTILEDWIDTH:
        {
            p.drawItemPixmap ( rect(), Qt::AlignLeft | Qt::AlignTop,
                               /*.copy() 切出图片的左上部分使用*/
                               QPixmap::fromImage ( mImg.copy ( rect() )
                                                    .scaledToWidth ( rect().width() )
                                                  ) );
        }
        break;

        case QQTZOOMWIDTH:
        {
            p.drawItemPixmap ( rect(), Qt::AlignLeft | Qt::AlignTop,
                               /*不.copy() 切出图片的中间部分使用*/
                               QPixmap::fromImage ( mImg
                                                    .scaled ( rect().width(), mImg.height(), Qt::IgnoreAspectRatio )
                                                  ) );
        }
        break;

        default:
        {

        }
        break;
    }

    return QWidget::paintEvent ( event );
}


void QQtWidget::mousePressEvent ( QMouseEvent* event )
{
    m_lcTimer->start();
    return QWidget::mousePressEvent ( event );
}

void QQtWidget::mouseReleaseEvent ( QMouseEvent* event )
{
    if ( m_lcTimer->isActive() )
    {
        m_lcTimer->stop();
        emit click();
    }

    return QWidget::mouseReleaseEvent ( event );
}

void QQtWidget::mouseDoubleClickEvent ( QMouseEvent* event )
{
    emit doubleClick();
    return QWidget::mouseDoubleClickEvent ( event );
}

void QQtWidget::slot_timeout()
{
    emit longClick();
}

