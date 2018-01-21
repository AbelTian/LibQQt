#include "qqtgiflabel.h"

QQtGifLabel::QQtGifLabel ( QWidget* parent ) : QQtLabel ( parent )
{
    m_movie = new QMovie ( this );
    setMovie ( m_movie );
}

void QQtGifLabel::setGifFile ( QString gifFile )
{
    m_movie->setFileName ( gifFile );
    m_movie->start();
}
