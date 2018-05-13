/*
 * T.D.R (QQ:2657635903) mod 2017年10月21日20:48:43
 */

/*
 * Copyright 2010 - Andre Maaßdorf
 *
 * Use, change and distribution of the code below is hereby
 * granted in any way without warranty by the original author.
 *
 */
#ifndef __QQTCUSTOMPIANOKEYBOARD_H__
#define __QQTCUSTOMPIANOKEYBOARD_H__

#include <QWidget>

class QScrollBar;

class QQtCustomPianoKeyBoard : public QWidget
{
    Q_OBJECT
public:
    QQtCustomPianoKeyBoard(QWidget*);
    ~QQtCustomPianoKeyBoard();

    void scrollToCenter();
    void emitOutOfRangeNotes(bool);
    void setRange(int s, int c, int e, bool beQuiet = false);

    virtual QSize sizeHint() const;

signals:
    void noteOn(int);
    void noteOff(int);
    void rangeChanged(int, int, int);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

private slots:
    void sliderPos(int);

private:

    void calculateSize();
    int  getNoteRangePosition(int note);
    int  getNotePosition(int note);
    bool isBlack(int note);
    int  getNoteRangeWidth(int note);
    void noteToRangeRect(int note, QRect& rect);
    int  getNoteFromMousePos(const QPoint& p, bool ignoreY = false);
    bool getRangeThumbFromMousePos(const QPoint& p, int** thumb);
    bool updateRangeThumbPosFromMousePos(const QPoint& p);
    bool fixRangeMarkers();
    bool isNoteInRange(int);

    QSize size;

    int octaves;
    int octaveWidth;
    int centerNote;
    int scrollOffset;
    int rangeSelectorSize;
    int rangeStart;
    int rangeCenter;
    int rangeEnd;
    int viewportWidth;
    bool doCenter;
    bool pianoKeyDown;
    int  currentNote;
    int*  selectedRangeThumb;
    int  rangeBoundaryMarkerWidth;
    bool m_EmitOutOfRangeNotes;
    QScrollBar*   scrollbar;
    QWidget*      parent;
};

#endif // __QQTCUSTOMPIANOKEYBOARD_H__
