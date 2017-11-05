#include "qqtdialog.h"
#include "qqtcore.h"
#include <QIcon>

QQtDialog::QQtDialog(QWidget* parent) :
    QDialog(parent)
{
    setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭 show的功能强大起来 可以使用输入法

#if 0
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground, true);
    QPalette plt = palette();
    plt.setColor(QPalette::Normal, QPalette::Shadow, QColor(255, 149, 12, 255));
    plt.setColor(QPalette::Normal, QPalette::Window, QColor(255, 255, 255, 255));
    setPalette(plt);
#endif


    setAttribute(Qt::WA_DeleteOnClose, false);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowFlags(windowFlags() | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowIcon(QIcon("./skin/default/bk_logo.ico"));
}

QQtDialog::~QQtDialog()
{
}
