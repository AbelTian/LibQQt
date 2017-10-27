#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    // 构建控件
    m_pQQLabel = new QLabel(this);
    m_pStateLabel = new QLabel(this);
    m_pQQLineEdit = new QLineEdit(this);
    m_pStateLineEdit = new QLineEdit(this);
    m_pSubmitButton = new QPushButton(this);

    m_pStateLineEdit->setReadOnly(true);
    m_pQQLabel->setText(QString::fromLocal8Bit("QQ号码："));
    m_pStateLabel->setText(QString::fromLocal8Bit("QQ状态："));
    m_pSubmitButton->setText(QString::fromLocal8Bit("提交"));

    QGridLayout* pLayout = new QGridLayout();
    pLayout->addWidget(m_pQQLabel, 0, 0);
    pLayout->addWidget(m_pQQLineEdit, 0, 1);
    pLayout->addWidget(m_pStateLabel, 1, 0);
    pLayout->addWidget(m_pStateLineEdit, 1, 1);
    pLayout->addWidget(m_pSubmitButton, 2, 1, 1, 1, Qt::AlignRight);
    pLayout->setSpacing(10);
    pLayout->setContentsMargins(10, 10, 10, 10);
    setLayout(pLayout);

    // 连接信号槽
    m_pHttp = new QtSoapHttpTransport(this);
    connect(m_pSubmitButton, SIGNAL(clicked()), this, SLOT(onSubmit()));
    connect(m_pHttp, SIGNAL(responseReady(const QtSoapMessage&)), this, SLOT(onResponse(const QtSoapMessage&)));
}

MainWindow::~MainWindow()
{

}

// 提交请求
void MainWindow::onSubmit()
{
    QtSoapMessage message;

    // 设置方法
    message.setMethod("qqCheckOnline", "http://WebXml.com.cn/");

    // 设置动作
    m_pHttp->setAction("http://WebXml.com.cn/qqCheckOnline");

    // 设置主机
    m_pHttp->setHost("www.webxml.com.cn");

    // 添加方法参数
    QString strQQ = m_pQQLineEdit->text();
    message.addMethodArgument("qqCode", "", strQQ);
    QString strXML = message.toXmlString();

    // 提交请求
    m_pHttp->submitRequest(message, "/webservices/qqOnlineWebService.asmx");
}

void MainWindow::onResponse(const QtSoapMessage& response)
{
    QString strXML = response.toXmlString();
    QDomDocument doc;
    doc.setContent(strXML);

    // 接在在线状态
    QDomNodeList nodeList = doc.elementsByTagName("qqCheckOnlineResult");
    if (!nodeList.isEmpty())
    {
        QDomNode node = nodeList.at(0);
        QString strResult = node.toElement().text();
        QString strState("N/A");
        if (QString::compare(strResult, "Y") == 0)
        {
            strState = QString::fromLocal8Bit("在线");
        }
        else if (QString::compare(strResult, "N") == 0)
        {
            strState = QString::fromLocal8Bit("离线");
        }
        else if (QString::compare(strResult, "E") == 0)
        {
            strState = QString::fromLocal8Bit("QQ号码错误");
        }
        else if (QString::compare(strResult, "A") == 0)
        {
            strState = QString::fromLocal8Bit("商业用户验证失败");
        }
        else if (QString::compare(strResult, "V") == 0)
        {
            strState = QString::fromLocal8Bit("免费用户超过数量");
        }
        m_pStateLineEdit->setText(strState);
    }
}
