#ifndef QQTBODYDROPIMAGEEFFECT_H
#define QQTBODYDROPIMAGEEFFECT_H

#include <QObject>

class QQtBodyDropImageEffect : public QObject
{
    Q_OBJECT
public:
    QQtBodyDropImageEffect ( QObject* parent = 0 );
    virtual ~QQtBodyDropImageEffect();

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;
};

#endif // QQTBODYDROPIMAGEEFFECT_H
