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
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#else
    setFocusPolicy ( Qt::NoFocus );
    setStyleSheet ( "QHeaderView, QHeaderView::section{background:transparent;}" );
#endif
}

void QQtHeaderView::paintSection ( QPainter* painter, const QRect& rect, int logicalIndex ) const
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    QHeaderView::paintSection ( painter, rect, logicalIndex );
#else
    painter->drawText ( rect, Qt::AlignCenter, model()->headerData ( logicalIndex, ori ).toString() );
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
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    QHeaderView::paintEvent ( e );
#else
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
#endif
}
