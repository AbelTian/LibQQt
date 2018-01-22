#include "qqtgifwidget.h"

QQtGifWidget::QQtGifWidget ( QWidget* parent ) : QQtWidget ( parent )
{
    m_movie = new QMovie ( this );
    m_frameTimer = new QTimer ( this );
    m_frameTimer->setSingleShot ( false );
    connect ( m_frameTimer, SIGNAL ( timeout() ),
              this, SLOT ( slotFramePlayback() ) );
}

void QQtGifWidget::setGifFile ( QString gifFile )
{
    m_movie->setFileName ( gifFile );
    m_movie->start();
    m_frameTimer->setInterval ( m_movie->speed() );
    m_frameTimer->start();
    /*100ms*/
    //pline() << m_movie->speed();
}

void QQtGifWidget::slotFramePlayback()
{
    setPixmap ( m_movie->currentImage() );
}
