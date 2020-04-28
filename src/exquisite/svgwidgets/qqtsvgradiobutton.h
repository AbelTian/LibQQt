#ifndef QQTSVGRADIOBUTTON_H
#define QQTSVGRADIOBUTTON_H

#include <qqtradiobutton.h>
#include <QSvgRenderer>
#include <qqtwidgets.h>
#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtSvgRadioButton : public QQtRadioButton
{
    Q_OBJECT
public:
    explicit QQtSvgRadioButton ( QWidget* parent = nullptr );

    QString stateImage ( int index );
    void setStateImage ( int index, const QString& image );

    //normal, press; uncheck, check; [0,1];
    void setNormalImage ( const QString& normal, const QString& press );
    //hover; [2];
    void setHoverImage ( const QString& hover );
    //disable; [4];
    void setDisableImage ( const QString& disable );

    //svg控件使用iconTable，必须render。
    const TBtnIconTable& iconTable() const;
    TBtnIconTable& iconTable();
    /**
     * @brief renderToVariable
     * call this function after iconTable() set.
     */
    void renderToVariable();
protected:
    //QQt基础Widget把这个函数作为把状态图设置进入当前图，
    //svgwidgets重新实现这个函数，把状态图render进入svgRender，和父类的函数工作位置不一样。
    virtual void translateImage();
signals:

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
private:
    QSvgRenderer r[BTN_MAX];

    TBtnIconTable mIconTable;
};

#endif // QQTSVGRADIOBUTTON_H
