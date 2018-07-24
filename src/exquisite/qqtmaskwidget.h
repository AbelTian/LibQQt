#ifndef QQTMASKWIDGET_H
#define QQTMASKWIDGET_H

/**
 * 弹窗遮罩层控件 作者:feiyangqingyun(QQ:517216493) 2016-12-26
 * 1:可设置需要遮罩的主窗体,自动跟随主窗体位置显示遮罩面积
 * 2:只需要将弹窗窗体的名称一开始传入队列即可,足够简单
 * 3:可设置透明度
 * 4:可设置遮罩层颜色
 * 5:不阻塞消息循坏
 */

#include <QWidget>
#include <QMutex>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtMaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QQtMaskWidget ( QWidget* parent = 0 );
    static QQtMaskWidget* Instance() {
        static QMutex mutex;

        if ( !self ) {
            QMutexLocker locker ( &mutex );

            if ( !self ) {
                self = new QQtMaskWidget;
            }
        }

        return self;
    }

protected:
    void showEvent ( QShowEvent* );
    bool eventFilter ( QObject* obj, QEvent* event );

private:
    static QQtMaskWidget* self;
    QWidget* mainWidget;        //需要遮罩的主窗体
    QStringList dialogNames;    //可能弹窗的窗体对象名称集合链表

public slots:
    void setMainWidget ( QWidget* mainWidget );
    void setDialogNames ( const QStringList& dialogNames );
    void setBgColor ( const QColor& bgColor );
    void setOpacity ( double opacity );
};

#endif // QQTMASKWIDGET_H
