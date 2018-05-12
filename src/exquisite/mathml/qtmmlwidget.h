﻿// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/mml/qtmmlwidget.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2009/04/30 13:10:43 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
**
** This file is part of a Qt Solutions component.
**
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact:  Qt Software Information (qt-info@nokia.com)
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Solutions Commercial License Agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** Please note Third Party Software included with Qt Solutions may impose
** additional restrictions and it is the user's responsibility to ensure
** that they have met the licensing requirements of the GPL, LGPL, or Qt
** Solutions Commercial license and the relevant license of the Third
** Party Software they are using.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#ifndef QTMMLWIDGET_H
#define QTMMLWIDGET_H

#include <QFrame>
#include <QtXml>

class MmlDocument;

#include <QtCore/qglobal.h>
#if defined(Q_OS_WIN)
//dynamic and static are different
#if   defined(QT_QTMMLWIDGET_LIBRARY)
#     define QT_QTMMLWIDGET_EXPORT Q_DECL_EXPORT
#elif defined(QT_QTMMLWIDGET_STATIC_LIBRARY)
#     define QT_QTMMLWIDGET_EXPORT
#else
#     define QT_QTMMLWIDGET_EXPORT Q_DECL_IMPORT
#endif
#else
//dynamic and static are equal to each other
#     define QT_QTMMLWIDGET_EXPORT
#endif

class QT_QTMMLWIDGET_EXPORT QtMmlWidget : public QFrame
{
public:
    enum MmlFont {NormalFont, FrakturFont, SansSerifFont, ScriptFont,
                  MonospaceFont, DoublestruckFont
                 };

    QtMmlWidget ( QWidget* parent = 0 );
    ~QtMmlWidget();

    QString fontName ( MmlFont type ) const;
    void setFontName ( MmlFont type, const QString& name );
    int baseFontPointSize() const;
    void setBaseFontPointSize ( int size );

    bool setContent ( const QString& text, QString* errorMsg = 0,
                      int* errorLine = 0, int* errorColumn = 0 );
    void dump() const;
    virtual QSize sizeHint() const;

    void setDrawFrames ( bool b );
    bool drawFrames() const;

    void clear();

protected:
    virtual void paintEvent ( QPaintEvent* e );

private:
    MmlDocument* m_doc;
};

class QT_QTMMLWIDGET_EXPORT QtMmlDocument
{
public:
    QtMmlDocument();
    ~QtMmlDocument();
    void clear();

    bool setContent ( QString text, QString* errorMsg = 0,
                      int* errorLine = 0, int* errorColumn = 0 );
    void paint ( QPainter* p, const QPoint& pos ) const;
    QSize size() const;

    QString fontName ( QtMmlWidget::MmlFont type ) const;
    void setFontName ( QtMmlWidget::MmlFont type, const QString& name );

    int baseFontPointSize() const;
    void setBaseFontPointSize ( int size );
private:
    MmlDocument* m_doc;
};

#endif
