#ifndef QQTLABEL_H
#define QQTLABEL_H

#include <QLabel>
#include <QTimer>
#include <qqtcore.h>

/**
 * 用于解决QLabel可能存在的问题.
 */
class QQtLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QQtLabel ( QWidget* parent = nullptr );
    virtual ~QQtLabel() {}
};

#endif // QQTLABEL_H
