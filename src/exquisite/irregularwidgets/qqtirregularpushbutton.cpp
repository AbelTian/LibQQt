#include <qqtirregularpushbutton.h>

QQtIrregularPushbutton::QQtIrregularPushbutton ( QWidget* parent ) : QQtPushButton ( parent )
{
    setAttribute ( Qt::WA_TranslucentBackground, true );
}

QQtIrregularPushbutton::~QQtIrregularPushbutton() {}

void QQtIrregularPushbutton::resizeEvent ( QResizeEvent* event )
{
    QImage normalImage = imageTable() [BTN_NORMAL];
    if ( normalImage.isNull() )
        return QQtPushButton::resizeEvent ( event );

    //zoom
    setMask ( QPixmap::fromImage ( normalImage
                                   .scaled ( rect().width(), rect().height(), Qt::IgnoreAspectRatio )
                                 ).mask() );

    return QQtPushButton::resizeEvent ( event );
}
