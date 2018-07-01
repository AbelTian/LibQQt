#ifndef QQTFRAMELESSHELPER_H
#define QQTFRAMELESSHELPER_H

/**
 * T.D.R (QQ:2657635903) mod 2017年10月21日21:24:43
**/

#include <QObject>
#include <QMargins>

#include <qqtcore.h>
#include <qqt-local.h>

class QPushButton;
class QWidget;
class QQtFramelessHelperPrivate;

class QQTSHARED_EXPORT QQtFramelessHelper : public QObject
{
    Q_OBJECT
public:
    explicit QQtFramelessHelper ( QWidget* parent = 0 );

    void setResizeMargins ( int margin );
    void setResizeMargins ( const QMargins& margins );

    void setCloseButton ( QPushButton* button, bool edgeResize = true );
    void setMaximizedButton ( QPushButton* button, bool edgeResize = true );
    void setMinimizedButton ( QPushButton* button, bool edgeResize = true );
    void setRestoreButton ( QPushButton* button, bool edgeResize = true );

    void addEdgeWidget ( QWidget* widget );
    void addDragWidget ( QWidget* widget );

private:
    QQtFramelessHelperPrivate* d;
};

#endif // QQTFRAMELESSHELPER_H
