#ifndef QQTOSDFRAME_H
#define QQTOSDFRAME_H

#include <qqtwidget.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * QQtOSDFrame
 * 透明背景的Frame，可以应用于作为透明窗体。
 *
 * 提供绘制窗体的边框。
 * 支持QSS修饰。
 * 可以设置背景。
 */
class QQTSHARED_EXPORT QQtOSDFrame : public QQtWidget
{
    Q_OBJECT
public:
    explicit QQtOSDFrame ( QWidget* parent = nullptr );

    virtual ~QQtOSDFrame();

signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
};

#endif // QQTOSDFRAME_H
