#include "qqtheaderview.h"
#include <QPainter>
#include "qqtwidgets.h"
#include <QStylePainter>
#include <QPaintEvent>
#include <QStandardItemModel>
#include <QStringListModel>

QQtHeaderView::QQtHeaderView ( Qt::Orientation orientation, QWidget* parent ) :
    QHeaderView ( orientation, parent ), ori ( orientation )
{
#if QT_VERSION <= QT_VERSION_CHECK(4,8,7)
    setFocusPolicy ( Qt::NoFocus );
    setStyleSheet ( "QHeaderView, QHeaderView::section{background:transparent;}" );
#else
#endif
}

void QQtHeaderView::paintSection ( QPainter* painter, const QRect& rect, int logicalIndex ) const
{
#if QT_VERSION <= QT_VERSION_CHECK(4,8,7)
    painter->drawText ( rect, Qt::AlignCenter, model()->headerData ( logicalIndex, ori ).toString() );
#else
    QHeaderView::paintSection ( painter, rect, logicalIndex );
#endif
}

QSize QQtHeaderView::sectionSizeFromContents ( int logicalIndex ) const
{
    /*
     * 文字宽度 不是section宽度
     */
    return QHeaderView::sectionSizeFromContents ( logicalIndex );
}

void QQtHeaderView::paintEvent ( QPaintEvent* e )
{
#if QT_VERSION <= QT_VERSION_CHECK(4,8,7)
    Q_UNUSED ( e )
    QStylePainter p ( this->viewport() );

    if ( Qt::Horizontal == ori )
    {
        for ( int i = 0; i < model()->columnCount(); i++ )
        {
            if ( isSectionHidden ( i ) )
                continue;

            QRect rect ( sectionViewportPosition ( i ), 0, sectionSize ( i ), height() );
            paintSection ( &p, rect, i );
        }
    }
    else if ( Qt::Vertical == ori )
    {
        for ( int i = 0; i < model()->rowCount(); i++ )
        {
            QRect rect ( 0, sectionViewportPosition ( i ), width(), sectionSize ( i ) );
            paintSection ( &p, rect, i );
        }
    }

    return;
#else
    QHeaderView::paintEvent ( e );
#endif
}
