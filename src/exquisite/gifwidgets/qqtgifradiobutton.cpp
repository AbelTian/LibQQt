#include "qqtgifradiobutton.h"

QQtGifRadioButton::QQtGifRadioButton ( QWidget* parent ) : QQtRadioButton ( parent )
{
    m_movie = & ( mMovie[BTN_NORMAL] );
    m_frameTimer = new QTimer ( this );
    m_frameTimer->setSingleShot ( false );
    connect ( m_frameTimer, SIGNAL ( timeout() ),
              this, SLOT ( slotFramePlayback() ) );
}

/**
 * 设置到局部变量
 */

QString QQtGifRadioButton::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mIconTable[BTN_NORMAL];
    return mIconTable[index];
}

void QQtGifRadioButton::setStateImage ( int index, const QString& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mIconTable[index] = image;
    renderToVariable();
    //update();
}

void QQtGifRadioButton::setNormalImage ( const QString& normal, const QString& press )
{
    mIconTable[BTN_NORMAL] = normal;
    mIconTable[BTN_PRESS] = press;
    renderToVariable();
    //update();
}

void QQtGifRadioButton::setHoverImage ( const QString& hover )
{
    mIconTable[BTN_HOVER] = hover;
    renderToVariable();
    //update();
}

void QQtGifRadioButton::setDisableImage ( const QString& disable )
{
    mIconTable[BTN_DISABLE] = disable;
    renderToVariable();
    //update();
}

const TBtnIconTable& QQtGifRadioButton::iconTable() const
{
    return mIconTable;
}

TBtnIconTable& QQtGifRadioButton::iconTable()
{
    return mIconTable;
}

void QQtGifRadioButton::renderToVariable()
{
    TBtnIconTable& icons = iconTable();
    for ( int i = BTN_NORMAL; i < BTN_MAX; i++ )
        mMovie[i].setFileName ( icons[i] );
    translateImage();
}

/**
 * 事件驱动
 * 内存中准备好ImageTable、ImageDevice；准备好QMovie；
 * 事件开始，QMovie设置为当前的Movie启动，其他的停止；
 * 只有一个Timer。
 */

void QQtGifRadioButton::mousePressEvent ( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        setWorkState ( BTN_PRESS );
    }
    QRadioButton::mousePressEvent ( event );
    translateImage();
    //update();
}

void QQtGifRadioButton::mouseReleaseEvent ( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
#ifdef __EMBEDDED_LINUX__
        setWorkState ( BTN_NORMAL );
#else
        if ( rect().contains ( event->pos() ) )
            setWorkState ( BTN_HOVER );
        else
            setWorkState ( BTN_NORMAL );
#endif
    }
    QRadioButton::mouseReleaseEvent ( event );
    translateImage();
    //update();
}

void QQtGifRadioButton::enterEvent ( QEvent* event )
{
    setWorkState ( BTN_HOVER );
    QRadioButton::enterEvent ( event );
    translateImage();
    //update();
}

void QQtGifRadioButton::leaveEvent ( QEvent* event )
{
    setWorkState ( BTN_NORMAL );
    QRadioButton::leaveEvent ( event );
    translateImage();
    //update();
}

void QQtGifRadioButton::translateImage()
{
    //设置当前Movie。
    m_movie->stop();

    //
    int state = workState();

    if ( isCheckable() )
#ifdef __EMBEDDED_LINUX__
#else
        if ( !isHover() )
#endif
        if ( isChecked() )
            state = BTN_CHECK;
        else
            state = BTN_UNCHECK;

    //qDebug() << isEnabled();
    if ( !isEnabled() )
        state = BTN_DISABLE;
    m_movie = & ( mMovie[state] );

    m_movie->start();
    m_frameTimer->setInterval ( m_movie->speed() );
    m_frameTimer->start();
}

void QQtGifRadioButton::slotFramePlayback()
{
    //把movie的图片设置到mImage。
    setImage ( m_movie->currentImage() );
    update();
}

void QQtGifRadioButton::paintEvent ( QPaintEvent* event )
{
#if 1
    //如果把translateImage放在外边，就需要这个代码，作为对初始化的补充。
    if ( image().isNull() )
        setImage ( m_movie->currentImage() );
#endif

    if ( image().isNull() )
        return QRadioButton::paintEvent ( event );

    //qDebug() << isEnabled() << mWorkState;

    QStylePainter p ( this );
#if 0
    p.drawItemPixmap ( rect(), Qt::AlignCenter, QIcon ( QPixmap::fromImage ( image() ) ).pixmap ( rect().size(),
                       QIcon::Normal, QIcon::On ) );
#else
    p.drawItemPixmap ( rect(), Qt::AlignLeft | Qt::AlignTop,
                       /*不.copy() 切出图片的中间部分使用*/
                       QPixmap::fromImage ( image()
                                            .scaled ( rect().width(), rect().height(), Qt::IgnoreAspectRatio )
                                          ) );
#endif

    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, isEnabled(), text() );
}
