//#include "stdafx.h"

#include "qqtframelesshelper.h"
#include "qqtframelesshelperprivate.h"

#include <QWidget>
#include <QPushButton>
#include <QDebug>

QQtFramelessHelper::QQtFramelessHelper(QWidget* parent) : QObject(parent)
{
    d = new QQtFramelessHelperPrivate(parent);
}

void QQtFramelessHelper::setResizeMargins(int margin)
{
    setResizeMargins(QMargins(margin, margin, margin, margin));
}

void QQtFramelessHelper::setResizeMargins(const QMargins& margins)
{
    d->margins = margins;
}

void QQtFramelessHelper::setCloseButton(QPushButton* button, bool edgeResize)
{
    d->buttonClose = button;
    connect(d->buttonClose, SIGNAL(clicked(bool)),
            d->parent, SLOT(close()));

    if (edgeResize)
    {
        d->addEdgeWidget(button);
    }
}

void QQtFramelessHelper::setMaximizedButton(QPushButton* button, bool edgeResize)
{
    d->buttonMaximized = button;
    connect(d->buttonMaximized, SIGNAL(clicked(bool)),
            d->parent, SLOT(showMaximized()));

    if (edgeResize)
    {
        d->addEdgeWidget(button);
    }

    d->refreshMaximizedButton();
}

void QQtFramelessHelper::setMinimizedButton(QPushButton* button, bool edgeResize)
{
    d->buttonMinimized = button;
    connect(d->buttonMinimized, SIGNAL(clicked(bool)),
            d->parent, SLOT(showMinimized()));

    if (edgeResize)
    {
        d->addEdgeWidget(button);
    }
}

void QQtFramelessHelper::setRestoreButton(QPushButton* button, bool edgeResize)
{
    d->buttonRestore = button;
    connect(d->buttonRestore, SIGNAL(clicked(bool)),
            d->parent, SLOT(showNormal()));

    if (edgeResize)
    {
        d->addEdgeWidget(button);
    }

    d->refreshMaximizedButton();
}

void QQtFramelessHelper::addEdgeWidget(QWidget* widget)
{
    d->addEdgeWidget(widget);
}

void QQtFramelessHelper::addDragWidget(QWidget* widget)
{
    d->addDragWidget(widget);
}










