#ifndef QQTOSDFORM_H
#define QQTOSDFORM_H

#include <qqtwidget.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * QQtOSDForm
 * 透明背景的Form，可以应用于作为透明窗口。
 * 这个窗口只是提供实现思路，由于内部窗体的Widget无法直接交给用户继承并且实现，所以给用户方法，在源程序里按照方法实现。
 */
class QQTSHARED_EXPORT QQtOSDForm : public QQtWidget
{
    Q_OBJECT
public:
    explicit QQtOSDForm ( QWidget* parent = nullptr ) : QQtWidget ( parent ) {
        //必要，最底层，提供透明背景。
        setAttribute ( Qt::WA_TranslucentBackground, true );

        //optional，qqtformbodymousehelper，提供支持鼠标点击窗体进行移动。
        //QQtFormBodyMouseHelper* helper = new QQtFormBodyMouseHelper(this);

        //在ui文件里，设置竖向Layout。
        //上边为QQtTitleBar，用户设置高度。
        //下边为QQtOSDFrame，提供透明和边框。
        //在QQtOSDFrame里面实现用户的需求。
    }

    ~QQtOSDForm() {}

signals:

public slots:
};

#endif // QQTOSDFORM_H
