#ifndef QQTGIFCHECKBOX_H
#define QQTGIFCHECKBOX_H

#include <qqtcheckbox.h>
#include <qqtwidgets.h>
#include <qqtcore.h>
#include <qqt-local.h>

/**
 * @brief The QQtGifCheckBox class
 * 准备ByteArray，QIODevice，ImageTable，状态QMovie，
 * 初始化Normal态，开启timer，
 * 事件驱动更改状态QMovie为当前QMovie。
 */
class QQTSHARED_EXPORT QQtGifCheckBox : public QQtCheckBox
{
    Q_OBJECT
public:
    explicit QQtGifCheckBox ( QWidget* parent = nullptr );

    QString stateImage ( int index );
    void setStateImage ( int index, const QString& image );

    //normal, press; uncheck, check; [0,1];
    void setNormalImage ( const QString& normal, const QString& press );
    //hover; [2];
    void setHoverImage ( const QString& hover );
    //disable; [4];
    void setDisableImage ( const QString& disable );

    //gif控件使用iconTable，必须render。
    const TBtnIconTable& iconTable() const;
    TBtnIconTable& iconTable();
    /**
     * @brief renderToVariable
     * call this function after iconTable() set.
     */
    void renderToVariable();
    //以上函数把图片设置到ImageTable()。

    inline QMovie* movieHandler() const { return m_movie; }
    inline QTimer* timerHandler() const { return m_frameTimer; }

protected:
    //QQt基础Widget把这个函数作为把状态图设置进入当前图，
    //gifwidgets重新实现这个函数，把状态图文件设置进QMovie，和父类的函数工作位置不一样。
    virtual void translateImage();

    //内部Timer实时把QMovie图设置到当前图。

signals:

public slots:
private:
    TBtnIconTable mIconTable;
    QMovie mMovie[BTN_MAX];

    QMovie* m_movie;
    QTimer* m_frameTimer;

protected slots:
    virtual void slotFramePlayback();

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
};

#endif // QQTGIFCHECKBOX_H
