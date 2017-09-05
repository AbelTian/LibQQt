#include "qqtlineeditwithsearch.h"
#include <QHBoxLayout>
#include "qqtwidgets.h"

QQTLineEditWithSearch::QQTLineEditWithSearch(QWidget *parent) :
    QLineEdit(parent)
{
    m_btnBrower = new QPushButton(this);
    QSize size = QSize(sizeHint().height(), sizeHint().height());
    m_btnBrower->setFixedSize(size);
    m_btnBrower->setFocusPolicy(Qt::NoFocus);    // 得到焦点时，不显示虚线框
    m_btnBrower->setFlat(true);
    m_btnBrower->setCursor(QCursor(Qt::PointingHandCursor));
    m_btnBrower->setIcon(QIcon("./skin/default/bt_brower.png"));
    m_btnBrower->setIconSize(size);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(0, 0, 1, 0);
    hLayout->addStretch();
    hLayout->addWidget(m_btnBrower);
    setLayout(hLayout);

    /*
     * 设置输入框中文件输入区，不让输入的文字在被隐藏在按钮下
     */
    setTextMargins(0, 1, size.width(), 1);

    connect(m_btnBrower, SIGNAL(clicked()), this, SIGNAL(btnClicked()));
}

void QQTLineEditWithSearch::setButtonText(QString text)
{
    m_btnBrower->setText(text);
}

void QQTLineEditWithSearch::setObjectName(const QString &name)
{
    QLineEdit::setObjectName(name);
    m_btnBrower->setObjectName(QString("%1_button").arg(name));
}
