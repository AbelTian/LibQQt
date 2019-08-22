#include "qqtgraphicsview.h"
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include "qqtcore.h"
#include "qqtgraphicsscene.h"
#include "qqt-qt.h"

QQtGraphicsView::QQtGraphicsView ( QWidget* parent ) :
    QGraphicsView ( parent )
{
}


void QQtGraphicsView::paintEvent ( QPaintEvent* e )
{
#if 1
    //已经确认，Qt4，在PC和板子上，这同一套计算代码，都存在问题
    QGraphicsView::paintEvent ( e );
    return;
#endif

#if 1

    if ( e->type() == QPaintEvent::Paint )
    {
        QPainter p ( this->viewport() );
        const QRectF rf = rect();
        const QRect rt = sceneRect().toRect();
        //pline() << rt << rf << rect();
        //         pline() << logicalDpiX() << logicalDpiY();
        //pc 96 0.81,0.46 743,593 778，628
        //p.scale(1.5/1, 1.5/1);
        QQtGraphicsScene* sn = ( QQtGraphicsScene* ) scene();
        sn->render ( &p, rf, rt );
    }

    return;
#endif

#if 0

    if ( !scene() )
    {
        QGraphicsView::paintEvent ( e );
        return;
    }

    // Set up painter state protection.
    bool painterStateProtection = paintingActive();

    // Determine the exposed region
    QRegion exposedRegion = e->region();
    QRectF exposedSceneRect = mapToScene ( exposedRegion.boundingRect() ).boundingRect();

    // Set up the painter
    QPainter painter ( viewport() );


#ifndef QT_NO_RUBBERBAND

    if ( RubberBandDrag )
        painter.save();

#endif

    // Set up render hints

    // Set up viewport transform
    const bool viewTransformed = isTransformed();

    if ( viewTransformed )
        painter.setWorldTransform ( viewportTransform() );

    const QTransform viewTransform = painter.worldTransform();

    // Draw background
    if ( ( cacheMode() & CacheBackground )
#ifdef Q_WS_X11
         && X11->use_xrender
#endif
       )
    {
        // Recreate the background pixmap, and flag the whole background as
        // exposed.
        bool mustResizeBackgroundPixmap = true;

        if ( mustResizeBackgroundPixmap )
        {
            QPixmap backgroundPixmap = QPixmap ( viewport()->size() );
            QBrush bgBrush = viewport()->palette().brush ( viewport()->backgroundRole() );

            if ( !bgBrush.isOpaque() )
                d->backgroundPixmap.fill ( Qt::transparent );

            QPainter p ( &backgroundPixmap );
            p.fillRect ( 0, 0, d->backgroundPixmap.width(), d->backgroundPixmap.height(), bgBrush );
            d->backgroundPixmapExposed = QRegion ( viewport()->rect() );
            d->mustResizeBackgroundPixmap = false;
        }

        // Redraw exposed areas
        if ( !d->backgroundPixmapExposed.isEmpty() )
        {
            QPainter backgroundPainter ( &d->backgroundPixmap );
            backgroundPainter.setClipRegion ( d->backgroundPixmapExposed, Qt::ReplaceClip );

            if ( viewTransformed )
                backgroundPainter.setTransform ( viewTransform );

            QRectF backgroundExposedSceneRect = mapToScene ( d->backgroundPixmapExposed.boundingRect() ).boundingRect();
            drawBackground ( &backgroundPainter, backgroundExposedSceneRect );
            d->backgroundPixmapExposed = QRegion();
        }

        // Blit the background from the background pixmap
        if ( viewTransformed )
        {
            painter.setWorldTransform ( QTransform() );
            painter.drawPixmap ( QPoint(), d->backgroundPixmap );
            painter.setWorldTransform ( viewTransform );
        }
        else
        {
            painter.drawPixmap ( QPoint(), d->backgroundPixmap );
        }
    }
    else
    {
        if ( ! ( d->optimizationFlags & DontSavePainterState ) )
            painter.save();

        drawBackground ( &painter, exposedSceneRect );

        if ( ! ( d->optimizationFlags & DontSavePainterState ) )
            painter.restore();
    }

    // Items
    if ( ! ( d->optimizationFlags & IndirectPainting ) )
    {
        const quint32 oldRectAdjust = d->scene->d_func()->rectAdjust;

        if ( d->optimizationFlags & QGraphicsView::DontAdjustForAntialiasing )
            d->scene->d_func()->rectAdjust = 1;
        else
            d->scene->d_func()->rectAdjust = 2;

        d->scene->d_func()->drawItems ( &painter, viewTransformed ? &viewTransform : 0,
                                        &d->exposedRegion, viewport() );
        d->scene->d_func()->rectAdjust = oldRectAdjust;

        // Make sure the painter's world transform is restored correctly when
        // drawing without painter state protection (DontSavePainterState).
        // We only change the worldTransform() so there's no need to do a full-blown
        // save() and restore(). Also note that we don't have to do this in case of
        // IndirectPainting (the else branch), because in that case we always save()
        // and restore() in QGraphicsScene::drawItems().
        if ( !d->scene->d_func()->painterStateProtection )
            painter.setOpacity ( 1.0 );

        painter.setWorldTransform ( viewTransform );
    }
    else
    {
        // Make sure we don't have unpolished items before we draw
        if ( !d->scene->d_func()->unpolishedItems.isEmpty() )
            d->scene->d_func()->_q_polishItems();

        // We reset updateAll here (after we've issued polish events)
        // so that we can discard update requests coming from polishEvent().
        d->scene->d_func()->updateAll = false;

        // Find all exposed items
        bool allItems = false;
        QList<QGraphicsItem*> itemList = d->findItems ( d->exposedRegion, &allItems, viewTransform );

        if ( !itemList.isEmpty() )
        {
            // Generate the style options.
            const int numItems = itemList.size();
            QGraphicsItem** itemArray = &itemList[0]; // Relies on QList internals, but is perfectly valid.
            QStyleOptionGraphicsItem* styleOptionArray = d->allocStyleOptionsArray ( numItems );
            QTransform transform ( Qt::Uninitialized );

            for ( int i = 0; i < numItems; ++i )
            {
                QGraphicsItem* item = itemArray[i];
                QGraphicsItemPrivate* itemd = item->d_ptr.data();
                itemd->initStyleOption ( &styleOptionArray[i], viewTransform, d->exposedRegion, allItems );
                // Cache the item's area in view coordinates.
                // Note that we have to do this here in case the base class implementation
                // (QGraphicsScene::drawItems) is not called. If it is, we'll do this
                // operation twice, but that's the price one has to pay for using indirect
                // painting :-/.
                const QRectF brect = adjustedItemEffectiveBoundingRect ( item );

                if ( !itemd->itemIsUntransformable() )
                {
                    transform = item->sceneTransform();

                    if ( viewTransformed )
                        transform *= viewTransform;
                }
                else
                {
                    transform = item->deviceTransform ( viewTransform );
                }

                itemd->paintedViewBoundingRects.insert ( d->viewport, transform.mapRect ( brect ).toRect() );
            }

            // Draw the items.
            drawItems ( &painter, numItems, itemArray, styleOptionArray );
            d->freeStyleOptionsArray ( styleOptionArray );
        }
    }

    // Foreground
    drawForeground ( &painter, exposedSceneRect );

#ifndef QT_NO_RUBBERBAND

    // Rubberband
    if ( d->rubberBanding && !d->rubberBandRect.isEmpty() )
    {
        painter.restore();
        QStyleOptionRubberBand option;
        option.initFrom ( viewport() );
        option.rect = d->rubberBandRect;
        option.shape = QRubberBand::Rectangle;

        QStyleHintReturnMask mask;

        if ( viewport()->style()->styleHint ( QStyle::SH_RubberBand_Mask, &option, viewport(), &mask ) )
        {
            // painter clipping for masked rubberbands
            painter.setClipRegion ( mask.region, Qt::IntersectClip );
        }

        viewport()->style()->drawControl ( QStyle::CE_RubberBand, &option, &painter, viewport() );
    }

#endif

    painter.end();

    // Restore painter state protection.
    d->scene->d_func()->painterStateProtection = true;
#endif

}


void QQtGraphicsView::drawItems ( QPainter* painter, int numItems, QGraphicsItem* items[],
                                  const QStyleOptionGraphicsItem options[] )
{
    for ( int i = 0; i < numItems; ++i )
    {
        // Save painter
        QQtGraphicsItem* item = ( QQtGraphicsItem* ) items[i];

        if ( item->flags() & QGraphicsItem::ItemClipsToShape )
        {
            painter->setClipPath ( item->shape(), Qt::IntersectClip );
        }

        item->paint ( painter, &options[i] );
    }
}
