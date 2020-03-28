#ifndef QLOGICPREVIEWUI_H
#define QLOGICPREVIEWUI_H

#include <QWidget>
#include <QImage>

#include <qqtlogicvideomanager.h>

#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqt-local.h"

namespace Ui {
class QQtLogicPreviewWidget;
}

/**
 * @brief The QQtLogicPreviewWidget class
 * QQt模拟摄像头预览控件
 * 省略dmmu的Qt Wrapper类
 */
class QQTSHARED_EXPORT QQtLogicPreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQtLogicPreviewWidget ( QWidget* parent = 0 );
    virtual ~QQtLogicPreviewWidget();

    int play();
    int close();

private slots:
    void slotReadyRead ( const QImage& image );

private:
    Ui::QQtLogicPreviewWidget* ui;

    bool bFullScreen;
    QWidget* m_parent;
    QRect geome;
    Qt::WindowFlags flags;

    QQtLogicVideoManager* manager;
    QImage mImage;
    // QWidget interface
protected:
    void paintEvent ( QPaintEvent* );
    void mousePressEvent ( QMouseEvent* e );
};

#endif // QLOGICPREVIEWUI_H
