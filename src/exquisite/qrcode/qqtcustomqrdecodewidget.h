/******************************************************************
 * Copyright (C) 2017 - All Rights Reserved by
 * 文 件 名 : mainwidget.h ---
 * 作 者    : 倪又华
 * 编写日期 : 2017
 * 说 明    :
 * 历史纪录 :
 * <作者>    <日期>        <版本>        <内容>
 * Niyh     2017/7
 * T.D.R    2017/11       MOD
 ******************************************************************/
#ifndef QQTCUSTOMQRDECODEWIDGET_H
#define QQTCUSTOMQRDECODEWIDGET_H

#include <QWidget>
#include <QAction>
#include <QMenu>
#include "qqtcore.h"
#include "qqt-local.h"

typedef enum
{
    UNKNOW,
    UP,
    DOWN,
} E_DIRECTION;


class QQTSHARED_EXPORT QQtCustomQrDecodeWidget : public QWidget
{
    Q_OBJECT

public:
    QQtCustomQrDecodeWidget(QWidget* parent = 0);
    ~QQtCustomQrDecodeWidget();

protected:
    QPoint m_startPoint;
    int m_nY;
    int m_nDirection;
    int m_nTimerId;
    bool m_bScaned;
    QString m_strScanResult;

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent*);

    void paintEvent(QPaintEvent* e);
    void timerEvent(QTimerEvent* event);

private:
    QMenu* mainMenu;
private slots:
    void SltActionTriggered(QAction* action);

private:
    void ScanRecord();
};

#endif // QQTCUSTOMQRDECODEWIDGET_H
