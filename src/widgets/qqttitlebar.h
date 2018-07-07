#ifndef QQTTITLEBAR
#define QQTTITLEBAR

#include <QQtWidget>

class QLabel;
class QToolButton;

#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtTitleBar : public QQtWidget
{
    Q_OBJECT

public:
    explicit QQtTitleBar ( QWidget* parent = 0 );
    ~QQtTitleBar();

    void setMinimizeVisible ( bool setting );
    void setMaximizeVisible ( bool setting );

    QQtWidget* iconLabel() { return m_pIconLabel; }
    QLabel* titleLabel() { return m_pTitleLabel; }
    QToolButton* minimizeButton() { return m_pMinimizeButton; }
    QToolButton* maximizeButton() { return m_pMaximizeButton; }
    QToolButton* closeButton() { return m_pCloseButton; }

protected:

    // 双击标题栏进行界面的最大化/还原
    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) override;

    // 进行鼠界面的拖动
    virtual void mousePressEvent ( QMouseEvent* event ) override;

    virtual void mouseReleaseEvent ( QMouseEvent* event ) override;

    virtual void mouseMoveEvent ( QMouseEvent* event ) override;

    // 设置界面标题与图标
    virtual bool eventFilter ( QObject* obj, QEvent* event );

private slots:

    // 进行最小化、最大化/还原、关闭操作
    void onClicked();

private:

    // 最大化/还原
    void updateMaximize();

private:
    //QLabel会有角上遗漏颜色。
    QQtWidget* m_pIconLabel;
    QLabel* m_pTitleLabel;
    QToolButton* m_pMinimizeButton;
    QToolButton* m_pMaximizeButton;
    QToolButton* m_pCloseButton;
    bool bMousePressed;
    QPoint pressedPoint;

};

#endif // QQTTITLEBAR
