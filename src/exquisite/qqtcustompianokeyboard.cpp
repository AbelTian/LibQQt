/*
 * Copyright 2010 - Andre Maa脽dorf
 *
 * Use, change and distribution of the code below is hereby
 * granted in any way without warranty by the original author.
 *
 */
#include "qqtcustompianokeyboard.h"
#include <QPainter>
#include <QScrollBar>
#include <QRect>
#include <QMouseEvent>
#include <QPainterPath>
#include <QCommonStyle>
#include <QStyleOption>

#define WWIDTH  23  // full width of white keys
#define BWIDTH  15  // width of black keys
#define WHEIGHT 80  // length of white keys
#define BHEIGHT 50  // length of black keys

struct key
{
    int  pos;
    int  width;
    int  height;
    bool isBlack;
} octave[12] =
{
    {                  0, WWIDTH, WHEIGHT, false},  // c
    {  WWIDTH - BWIDTH / 2, BWIDTH, BHEIGHT,  true}, // cis
    {             WWIDTH, WWIDTH, WHEIGHT, false},  // d
    {2 * WWIDTH - BWIDTH / 2, BWIDTH, BHEIGHT,  true}, // dis
    {           2 * WWIDTH, WWIDTH, WHEIGHT, false}, // e
    {           3 * WWIDTH, WWIDTH, WHEIGHT, false}, // f
    {4 * WWIDTH - BWIDTH / 2, BWIDTH, BHEIGHT,  true}, // fis
    {           4 * WWIDTH, WWIDTH, WHEIGHT, false}, // g
    {5 * WWIDTH - BWIDTH / 2, BWIDTH, BHEIGHT,  true}, // gis
    {           5 * WWIDTH, WWIDTH, WHEIGHT, false}, // a
    {6 * WWIDTH - BWIDTH / 2, BWIDTH, BHEIGHT,  true}, // ais
    {           6 * WWIDTH, WWIDTH, WHEIGHT, false} // h
};


QQtCustomPianoKeyBoard::QQtCustomPianoKeyBoard(QWidget* p) : \
    QWidget(p),
    octaves(10),
    octaveWidth(0),
    centerNote(60),
    scrollOffset(0),
    rangeSelectorSize(20),
    rangeStart(57),
    rangeCenter(60),
    rangeEnd(65),
    viewportWidth(0),
    doCenter(false),
    pianoKeyDown(false),
    currentNote(-1),
    selectedRangeThumb(NULL),
    rangeBoundaryMarkerWidth(15),
    m_EmitOutOfRangeNotes(true),
    parent(p)
{
    scrollbar = new QScrollBar(Qt::Horizontal, this);
    scrollbar->move(0, rangeSelectorSize + octave[0].height + 1);
    scrollbar->setMinimum(0);
    scrollbar->setSingleStep(5);
    scrollbar->setMinimumHeight(20);
    calculateSize();
    connect(scrollbar, SIGNAL(valueChanged(int)), this, SLOT(sliderPos(int)));
}

QQtCustomPianoKeyBoard::~QQtCustomPianoKeyBoard()
{
}

void QQtCustomPianoKeyBoard::calculateSize()
{
    for (unsigned int i = 0; i < 12; i++)
        if (!octave[i].isBlack)
            octaveWidth += octave[i].width;

    size.setWidth(octaveWidth * octaves + 1);
    size.setHeight(rangeSelectorSize + octave[0].height + scrollbar->height() + 1);
}

void QQtCustomPianoKeyBoard::scrollToCenter()
{
    doCenter = true;
    update();
}

void QQtCustomPianoKeyBoard::emitOutOfRangeNotes(bool e)
{
    m_EmitOutOfRangeNotes = e;
}

void QQtCustomPianoKeyBoard::setRange(int s, int c, int e, bool beQuiet)
{
    rangeStart = s - 1;
    rangeCenter = c;
    rangeEnd = e + 1;
    fixRangeMarkers();

    if (!beQuiet)
        emit rangeChanged(rangeStart + 1, rangeCenter, rangeEnd - 1);

    update();
}

QSize QQtCustomPianoKeyBoard::sizeHint() const
{
    return size;
}

inline int QQtCustomPianoKeyBoard::getNoteRangePosition(int note)
{
    int _note = note % 12;
    int notePos = octave[_note].pos;

    if (octave[(_note + 23) % 12].isBlack)
        notePos += BWIDTH / 2;

    return notePos + (note / 12) * octaveWidth - scrollOffset;
}

inline int QQtCustomPianoKeyBoard::getNotePosition(int note)
{
    int _note = note % 12;
    int notePos = octave[_note].pos;

    return notePos + (note / 12) * octaveWidth - scrollOffset;
}

inline bool QQtCustomPianoKeyBoard::isBlack(int note)
{
    return octave[note % 12].isBlack;
}

inline int QQtCustomPianoKeyBoard::getNoteRangeWidth(int note)
{
    int _note = note % 12;
    int width = octave[_note].width;

    if (octave[(_note + 1) % 12].isBlack)
        width -= BWIDTH / 2;

    if (octave[(_note + 23) % 12].isBlack)
        width -= BWIDTH / 2;

    return width;
}

inline void QQtCustomPianoKeyBoard::noteToRangeRect(int note, QRect& rect)
{
    int noteStart = getNoteRangePosition(note);
    int noteWidth = getNoteRangeWidth(note);
    rect.setRect(noteStart, 0, noteWidth, rangeSelectorSize);
}

void QQtCustomPianoKeyBoard::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    /*
      QCommonStyle style;
      QStyleOption opt;
      opt.initFrom(this);
      style.drawPrimitive(QStyle::PE_FrameWindow, &opt, &painter, this);
    */
    painter.fillRect(0, rangeSelectorSize, octaves * octaveWidth, octave[0].height, Qt::white);
    painter.setPen(Qt::black);

    if (parent)
        viewportWidth = parent->width();
    else
        viewportWidth = size.width();

    if (parent && parent->width() >= size.width())
    {
        scrollbar->setVisible(false);
        scrollOffset = 0;
    }
    else
    {
        scrollbar->setVisible(true);
        scrollbar->setMinimumWidth(viewportWidth);
        scrollbar->setMaximumWidth(viewportWidth);
        scrollbar->setMaximum(size.width() - viewportWidth);
        scrollbar->setPageStep(viewportWidth);
    }


    if (scrollbar->isVisible() && doCenter)
    {
        scrollbar->setValue(getNoteRangePosition(centerNote) - viewportWidth / 2 + WWIDTH / 2);
        doCenter = false;
    }

    // draw piano keys...
    for (int i = 0; i < octaves; i++)
    {
        for (unsigned int j = 0; j < 12; j++)
        {
            int pos = octaveWidth * i + octave[j].pos - scrollOffset;

            if ((pos >= 0 && pos <= viewportWidth) || (pos < 0 && pos + octave[i].width >= 0))
            {
                if (octave[j].isBlack)
                {
                    painter.fillRect(pos, rangeSelectorSize, octave[j].width, octave[j].height, Qt::SolidPattern);
                }
                else
                {
                    painter.drawRect(pos, rangeSelectorSize, octave[j].width, octave[j].height);

                    if (j == 0)
                        painter.drawText(pos + 8, rangeSelectorSize + octave[j].height - 5, QString("%1").arg(i));
                }
            }
        }
    }

    // highlight currently active key
    if (currentNote != -1)
    {
        int _octave = currentNote / 12;
        int _key = currentNote % 12;
        int _pos = octaveWidth * _octave + octave[_key].pos - scrollOffset;

        if (isBlack(_key))
        {
            painter.fillRect(_pos, rangeSelectorSize, octave[_key].width, octave[_key].height, Qt::blue);
        }
        else
        {
            int _width = getNoteRangeWidth(currentNote);
            int _pos2 = getNoteRangePosition(currentNote);
            painter.fillRect(_pos2, rangeSelectorSize, _width, BHEIGHT, Qt::blue);
            painter.fillRect(_pos, rangeSelectorSize + BHEIGHT, octave[_key].width, octave[_key].height - BHEIGHT, Qt::blue);
        }
    }

    // draw range selector...
    QRect rStart, rCenter, rEnd;
    noteToRangeRect(rangeStart, rStart);
    noteToRangeRect(rangeCenter, rCenter);
    noteToRangeRect(rangeEnd, rEnd);

    painter.fillRect(rStart.right(), rStart.top(), rEnd.left() - rStart.right(), rEnd.bottom() - rStart.top(),
                     Qt::lightGray);

    painter.setPen(Qt::blue);
    QPainterPath rangeStartPath(rStart.topRight());
    rangeStartPath.lineTo(rStart.bottomRight());
    rangeStartPath.lineTo(rStart.topRight() - QPoint(rangeBoundaryMarkerWidth, 0));
    painter.drawPath(rangeStartPath);
    painter.fillPath(rangeStartPath, Qt::blue);

    QPainterPath rangeEndPath(rEnd.topLeft());
    rangeEndPath.lineTo(rEnd.topLeft() + QPoint(rangeBoundaryMarkerWidth, 0));
    rangeEndPath.lineTo(rEnd.bottomLeft());
    painter.drawPath(rangeEndPath);
    painter.fillPath(rangeEndPath, Qt::blue);

    painter.fillRect(rCenter, Qt::red);
}

void QQtCustomPianoKeyBoard::sliderPos(int p)
{
    scrollOffset = p;
    update();
}

int QQtCustomPianoKeyBoard::getNoteFromMousePos(const QPoint& p, bool ignoreY)
{
    int _note = -1;

    if (!ignoreY && (p.y() < rangeSelectorSize || p.y() > rangeSelectorSize + WHEIGHT))
        return -1;

    bool isWhite = false;

    if (!ignoreY && (p.y() > rangeSelectorSize + BHEIGHT))
        isWhite = true;

    int _octave = (p.x() + scrollOffset) / octaveWidth;
    int _pos = (p.x() + scrollOffset) % octaveWidth;

    for (int i = 0; i < 12; i++)
    {
        if (isWhite)
        {
            if (!octave[i].isBlack && _pos >= octave[i].pos && _pos < octave[i].pos + octave[i].width)
            {
                _note = i;
                break;
            }
        }
        else
        {
            if (_pos >= octave[i].pos && _pos < octave[i].pos + octave[i].width)
            {
                _note = i;
                break;
            }
        }
    }

    if (!isWhite && !isBlack(_note) && _pos >= octave[(_note + 1) % 12 ].pos
        && _pos < octave[(_note + 1) % 12 ].pos + octave[(_note + 1) % 12 ].width)
        _note++;

    _note += _octave * 12;
    return _note;
}

bool QQtCustomPianoKeyBoard::getRangeThumbFromMousePos(const QPoint& p, int** thumb)
{
    if (p.y() >= rangeSelectorSize)
        return false;

    int _pos = getNoteRangePosition(rangeStart) + getNoteRangeWidth(rangeStart) - rangeBoundaryMarkerWidth;
    int _width = rangeBoundaryMarkerWidth;//getNoteRangeWidth(rangeStart);

    if (p.x() >= _pos && p.x() < _pos + _width)
    {
        *thumb = &rangeStart;
        return true;
    }

    _pos = getNoteRangePosition(rangeCenter);
    _width = getNoteRangeWidth(rangeCenter);

    if (p.x() >= _pos && p.x() < _pos + _width)
    {
        *thumb = &rangeCenter;
        return true;
    }

    _pos = getNoteRangePosition(rangeEnd);
    _width = rangeBoundaryMarkerWidth;//getNoteRangeWidth(rangeEnd);

    if (p.x() >= _pos && p.x() < _pos + _width)
    {
        *thumb = &rangeEnd;
        return true;
    }

    return false;
}

bool QQtCustomPianoKeyBoard::updateRangeThumbPosFromMousePos(const QPoint& p)
{
    int _note = getNoteFromMousePos(p, true);

    if (p.y() > rangeSelectorSize)
        return false;

    if (_note == -1)
        return false;

    if (_note < rangeStart)
    {
        rangeStart = _note;
        return true;
    }
    else if (_note > rangeEnd)
    {
        rangeEnd = _note;
        return true;
    }

    rangeCenter = _note;
    return true;
}

bool QQtCustomPianoKeyBoard::fixRangeMarkers()
{
    int fixed = 0;

    if (rangeStart >= rangeCenter)
    {
        rangeStart = rangeCenter - 1;
        fixed++;
    }

    if (rangeEnd <= rangeCenter)
    {
        rangeEnd = rangeCenter + 1;
        fixed++;
    }

    return fixed > 0 ? true : false;
}

bool QQtCustomPianoKeyBoard::isNoteInRange(int note)
{
    return (note > rangeStart && note < rangeEnd) ? true : false;
}

void QQtCustomPianoKeyBoard::mousePressEvent(QMouseEvent* event)
{
    currentNote = getNoteFromMousePos(event->pos());

    if (currentNote != -1)
    {
        pianoKeyDown = true;

        if (m_EmitOutOfRangeNotes || isNoteInRange(currentNote))
            emit noteOn(currentNote);

        update();
    }
    else
    {
        currentNote = -1;
        int* thumb = NULL;

        if (getRangeThumbFromMousePos(event->pos(), &thumb))
        {
            selectedRangeThumb = thumb;
        }
        else if (updateRangeThumbPosFromMousePos(event->pos()))
        {
            update();
            emit rangeChanged(rangeStart + 1, rangeCenter, rangeEnd - 1);
        }
    }
}

void QQtCustomPianoKeyBoard::mouseReleaseEvent(QMouseEvent* event)
{
    if (pianoKeyDown)
    {
        pianoKeyDown = false;

        if (m_EmitOutOfRangeNotes || isNoteInRange(currentNote))
            emit noteOff(currentNote);

        currentNote = -1;
        update();
    }
    else if (selectedRangeThumb != NULL)
    {
        emit rangeChanged(rangeStart + 1, rangeCenter, rangeEnd - 1);
        selectedRangeThumb = NULL;
    }
}

void QQtCustomPianoKeyBoard::mouseMoveEvent(QMouseEvent* event)
{
    if (pianoKeyDown)
    {
        int _note = getNoteFromMousePos(event->pos());

        if (_note != currentNote)
        {
            if (m_EmitOutOfRangeNotes || isNoteInRange(currentNote))
                emit noteOff(currentNote);

            currentNote = _note;

            if (m_EmitOutOfRangeNotes || isNoteInRange(currentNote))
                emit noteOn(currentNote);

            update();
        }
    }
    else if (selectedRangeThumb != NULL)
    {
        int _note = getNoteFromMousePos(event->pos(), true);
        *selectedRangeThumb = _note;

        if (!fixRangeMarkers())
        {
            //emit rangeChanged(rangeStart, rangeCenter, rangeEnd);
            update();
        }
    }
}
