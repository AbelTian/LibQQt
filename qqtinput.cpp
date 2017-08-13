#include "qqtinput.h"
#include "ui_qqtinput.h"
#include "qdesktopwidget.h"
#include "qqtdefine.h"

QQTInput *QQTInput::_instance = 0;
QQTInput::QQTInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmInput)
{
    ui->setupUi(this);
}

QQTInput::~QQTInput()
{
    delete ui;
}

void QQTInput::Init(QString type, QString position, QString style, int btnFontSize, int labFontSize)
{
    this->currentPosition = position;
    this->currentStyle = style;
    this->btnFontSize = btnFontSize;
    this->labFontSize = labFontSize;
    this->currentType = type;

    this->InitProperty();
    this->InitForm();
    this->changeType();
    this->ChangeStyle();
    this->ChangeFont();
    this->changePosition();
}

void QQTInput::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void QQTInput::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void QQTInput::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void QQTInput::InitForm()
{
    this->mousePressed = false;
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    QDesktopWidget w;
    deskWidth = qApp->desktop()->width();//w.availableGeometry().width();
    deskHeight = qApp->desktop()->height();//w.availableGeometry().height();
    frmTopHeight = 44;

    if(QSize(deskWidth, deskHeight) == QSize(1024, 768))
    {
        frmWidth = 624;
        frmHeight = 279;
        btnWidth = 50;
        btnHeight = 50;
    }
    else if(QSize(deskWidth, deskHeight) == QSize(800, 480))
    {
        frmWidth = 516;
        frmHeight = 229;
        btnWidth = 40;
        btnHeight = 40;
    }

    m_db = newDatabaseConn();
    setDatabaseName(m_db, DB_PINYIN);

    isFirst = true;
    isPress = false;
    timerPress = new QTimer(this);
    connect(timerPress, SIGNAL(timeout()), this, SLOT(reClicked()));

    currentFocusWidget = 0;
    currentWidget = 0;
    currentLineEdit = 0;
    currentTextEdit = 0;
    currentPlain = 0;
    currentBrowser = 0;
    currentEditType = "";

    ui->btnDel->iconTable()[BTN_NORMAL] = "./skin/default/key_del.png";
    ui->btnDel->iconTable()[BTN_PRESS] = "./skin/default/key_del_press.png";
    ui->btnDel->iconTable()[BTN_UNCHECK] = "./skin/default/key_del.png";
    ui->btnDel->iconTable()[BTN_CHECK] = "./skin/default/key_del_press.png";
    ui->btnDel->iconTable()[BTN_HOVER] = "./skin/default/key_del.png";
    ui->btnDel->iconTable()[BTN_DISABLE] = "./skin/default/key_del.png";

    ui->btnDelete->iconTable()[BTN_NORMAL] = "./skin/default/key_del.png";
    ui->btnDelete->iconTable()[BTN_PRESS] = "./skin/default/key_del_press.png";
    ui->btnDelete->iconTable()[BTN_UNCHECK] = "./skin/default/key_del.png";
    ui->btnDelete->iconTable()[BTN_CHECK] = "./skin/default/key_del_press.png";
    ui->btnDelete->iconTable()[BTN_HOVER] = "./skin/default/key_del.png";
    ui->btnDelete->iconTable()[BTN_DISABLE] = "./skin/default/key_del.png";

    ui->btnClose->iconTable()[BTN_NORMAL] = "./skin/default/key_close.png";
    ui->btnClose->iconTable()[BTN_PRESS] = "./skin/default/key_close_press.png";
    ui->btnClose->iconTable()[BTN_UNCHECK] = "./skin/default/key_close.png";
    ui->btnClose->iconTable()[BTN_CHECK] = "./skin/default/key_close_press.png";
    ui->btnClose->iconTable()[BTN_HOVER] = "./skin/default/key_close.png";
    ui->btnClose->iconTable()[BTN_DISABLE] = "./skin/default/key_close.png";

    ui->btnSpace->iconTable()[BTN_NORMAL] = "./skin/default/key_blank.png";
    ui->btnSpace->iconTable()[BTN_PRESS] = "./skin/default/key_blank_press.png";
    ui->btnSpace->iconTable()[BTN_UNCHECK] = "./skin/default/key_blank.png";
    ui->btnSpace->iconTable()[BTN_CHECK] = "./skin/default/key_blank_press.png";
    ui->btnSpace->iconTable()[BTN_HOVER] = "./skin/default/key_blank.png";
    ui->btnSpace->iconTable()[BTN_DISABLE] = "./skin/default/key_blank.png";

    ui->btnReturn->iconTable()[BTN_NORMAL] = "./skin/default/key_return.png";
    ui->btnReturn->iconTable()[BTN_PRESS] = "./skin/default/key_return_press.png";
    ui->btnReturn->iconTable()[BTN_UNCHECK] = "./skin/default/key_return.png";
    ui->btnReturn->iconTable()[BTN_CHECK] = "./skin/default/key_return_press.png";
    ui->btnReturn->iconTable()[BTN_HOVER] = "./skin/default/key_return.png";
    ui->btnReturn->iconTable()[BTN_DISABLE] = "./skin/default/key_return.png";

    ui->radioCN->setPixmap("./skin/default/key.png", "./skin/default/key_press.png");
    ui->radioCN->setFixedSize(btnWidth, btnHeight);
    ui->radioCN->setPixmap("./skin/default/key.png", "./skin/default/key_press.png");
    ui->radioEN->setFixedSize(btnWidth, btnHeight);
    ui->radioEN->setPixmap("./skin/default/key.png", "./skin/default/key_press.png");
    ui->radioEN->setFixedSize(btnWidth, btnHeight);
    ui->radioNum->setPixmap("./skin/default/key.png", "./skin/default/key_press.png");
    ui->radioNum->setFixedSize(btnWidth, btnHeight);
    ui->checkShift->setPixmap("./skin/default/key_shift.png", "./skin/default/key_shift_press.png");
    ui->checkShift->setFixedSize(btnWidth, btnHeight);

    connect(ui->radioNum, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    connect(ui->checkShift, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    connect(ui->radioCN, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    connect(ui->radioEN, SIGNAL(clicked()), this, SLOT(btn_clicked()));

    ui->radioEN->setChecked(true);

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        connect(b, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    }

    /*
     * 绑定全局改变焦点信号槽
     */
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    /*
     * 绑定按键事件过滤器
     */
    qApp->installEventFilter(this);
}

void QQTInput::InitProperty()
{
    ui->btnOther1->setProperty("btnOther", true);
    ui->btnOther2->setProperty("btnOther", true);
    ui->btnOther3->setProperty("btnOther", true);
    ui->btnOther4->setProperty("btnOther", true);
    ui->btnOther5->setProperty("btnOther", true);
    ui->btnOther6->setProperty("btnOther", true);
    ui->btnOther7->setProperty("btnOther", true);
    ui->btnOther8->setProperty("btnOther", true);
    ui->btnOther9->setProperty("btnOther", true);
    ui->btnOther10->setProperty("btnOther", true);
    ui->btnOther11->setProperty("btnOther", true);
    ui->btnOther12->setProperty("btnOther", true);
    ui->btnOther13->setProperty("btnOther", true);
    ui->btnOther14->setProperty("btnOther", true);
    ui->btnOther15->setProperty("btnOther", true);
    ui->btnOther16->setProperty("btnOther", true);
    ui->btnOther17->setProperty("btnOther", true);
    ui->btnOther18->setProperty("btnOther", true);
    ui->btnOther19->setProperty("btnOther", true);
    ui->btnOther20->setProperty("btnOther", true);
    ui->btnOther21->setProperty("btnOther", true);
    ui->btnOther22->setProperty("btnOther", true);
    ui->btnOther23->setProperty("btnOther", true);
    ui->btnOther24->setProperty("btnOther", true);

    ui->btnDot->setProperty("btnOther", true);
    ui->btnSpace->setProperty("btnOther", true);
    ui->btnDelete->setProperty("btnOther", true);
    ui->radioCN->setProperty("btnOther", true);
    ui->radioNum->setProperty("btnOther", true);
    ui->btnReturn->setProperty("btnOther", true);
    ui->radioEN->setProperty("btnOther", true);
    ui->btnDel->setProperty("btnOther", true);

    ui->btn0->setProperty("btnNum", true);
    ui->btn1->setProperty("btnNum", true);
    ui->btn2->setProperty("btnNum", true);
    ui->btn3->setProperty("btnNum", true);
    ui->btn4->setProperty("btnNum", true);
    ui->btn5->setProperty("btnNum", true);
    ui->btn6->setProperty("btnNum", true);
    ui->btn7->setProperty("btnNum", true);
    ui->btn8->setProperty("btnNum", true);
    ui->btn9->setProperty("btnNum", true);

    ui->btna->setProperty("btnLetter", true);
    ui->btnb->setProperty("btnLetter", true);
    ui->btnc->setProperty("btnLetter", true);
    ui->btnd->setProperty("btnLetter", true);
    ui->btne->setProperty("btnLetter", true);
    ui->btnf->setProperty("btnLetter", true);
    ui->btng->setProperty("btnLetter", true);
    ui->btnh->setProperty("btnLetter", true);
    ui->btni->setProperty("btnLetter", true);
    ui->btnj->setProperty("btnLetter", true);
    ui->btnk->setProperty("btnLetter", true);
    ui->btnl->setProperty("btnLetter", true);
    ui->btnm->setProperty("btnLetter", true);
    ui->btnn->setProperty("btnLetter", true);
    ui->btno->setProperty("btnLetter", true);
    ui->btnp->setProperty("btnLetter", true);
    ui->btnq->setProperty("btnLetter", true);
    ui->btnr->setProperty("btnLetter", true);
    ui->btns->setProperty("btnLetter", true);
    ui->btnt->setProperty("btnLetter", true);
    ui->btnu->setProperty("btnLetter", true);
    ui->btnv->setProperty("btnLetter", true);
    ui->btnw->setProperty("btnLetter", true);
    ui->btnx->setProperty("btnLetter", true);
    ui->btny->setProperty("btnLetter", true);
    ui->btnz->setProperty("btnLetter", true);

    labCh.append(ui->labCh0);
    labCh.append(ui->labCh1);
    labCh.append(ui->labCh2);
    labCh.append(ui->labCh3);
    labCh.append(ui->labCh4);
    labCh.append(ui->labCh5);
    labCh.append(ui->labCh6);
    labCh.append(ui->labCh7);
    labCh.append(ui->labCh8);
    labCh.append(ui->labCh9);
    for (int i = 0; i < 10; i++) {
        labCh[i]->installEventFilter(this);
    }
}

void QQTInput::ShowPanel()
{
    this->setVisible(true);
}

bool QQTInput::checkPress()
{
    /*
     * 只有属于输入法键盘的合法按钮才继续处理
     */
    bool num_ok = btnPress->property("btnNum").toBool();
    bool other_ok = btnPress->property("btnOther").toBool();
    bool letter_ok = btnPress->property("btnLetter").toBool();
    if (num_ok || other_ok || letter_ok) {
        return true;
    }
    return false;
}

void QQTInput::reClicked()
{
    if (isPress) {
        timerPress->setInterval(30);
        btnPress->click();
    }
}

void QQTInput::btn_clicked()
{
    /*
     * 如果当前焦点控件类型为空,则返回不需要继续处理
     */
    if (currentEditType == "") {
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();
    //pline() << objectName;
    /*
     * 大小写
     */
    if (objectName == "checkShift") {
        if (currentType == "min") {
            currentType = "max";
            if(!ui->checkShift->isChecked())
                ui->checkShift->setChecked(true);
            changeType();
        } else if (currentType == "max") {
            currentType = "min";
            if(ui->checkShift->isChecked())
                ui->checkShift->setChecked(false);
            changeType();
        } else if (currentType == "chinese"){
        }
    } else if (objectName == "radioNum") {
        if(0 == ui->stackedWidget->currentIndex()) {
            ui->stackedWidget->setCurrentIndex(1);
        } else if(1 == ui->stackedWidget->currentIndex()) {
        //    ui->stackedWidget->setCurrentIndex(0);
        }
    } else if (objectName == "radioCN") {
        if (currentType == "min" || currentType == "max") {
            currentType = "chinese";
            ui->checkShift->setPixmap("./skin/default/key_hidden.png", "./skin/default/key_hidden.png");
            if(ui->checkShift->isChecked())
                ui->checkShift->setChecked(false);
            ui->checkShift->update();
            changeType();
        } else if (currentType == "chinese") {
        }
        //if(ui->radioNum->isChecked())
        //    ui->radioNum->setChecked(false);
        if(1 == ui->stackedWidget->currentIndex())
            ui->stackedWidget->setCurrentIndex(0);
    } else if (objectName == "radioEN") {
        if (currentType == "min" || currentType == "max") {
        } else if (currentType == "chinese") {
            currentType = "min";
            ui->checkShift->setPixmap("./skin/default/key_shift.png", "./skin/default/key_shift_press.png");
            if(ui->checkShift->isChecked())
                ui->checkShift->setChecked(false);
            ui->checkShift->update();
            changeType();
        }
        //if(ui->radioNum->isChecked())
        //    ui->radioNum->setChecked(false);
        if(1 == ui->stackedWidget->currentIndex())
            ui->stackedWidget->setCurrentIndex(0);
    } else if (objectName == "btnDelete" || objectName == "btnDel") {
        /*
         * 如果当前是中文模式,则删除对应拼音,删除完拼音之后再删除对应文本输入框的内容
         */
        if (currentType == "chinese") {
            QString txt = ui->labPY->text();
            int len = txt.length();
            if (len > 0) {
                ui->labPY->setText(txt.left(len - 1));
                selectChinese();
            } else {
                deleteValue();
            }
        } else {
            deleteValue();
        }
    } else if (objectName == "btnPre") {
        if (currentPY_index >= 20) {
            /*
             * 每次最多显示10个汉字,所以每次向前的时候索引要减20
             */
            if (currentPY_index % 10 == 0) {
                currentPY_index -= 20;
            } else {
                currentPY_index = currentPY_count - (currentPY_count % 10) - 10;
            }
        } else {
            currentPY_index = 0;
        }
        showChinese();
    } else if (objectName == "btnNext") {
        if (currentPY_index < currentPY_count - 1) {
            showChinese();
        }
    } else if (objectName == "btnClose") {
        this->setVisible(false);
    } else if (objectName == "btnSpace") {
        insertValue(" ");
    } else if (objectName == "btnReturn") {
        insertValue("\n");
    }else {
        QString value = btn->text();
        /*
         * 如果是&按钮，因为对应&被过滤,所以真实的text为去除前面一个&字符
         */
        if (objectName == "btnOther7") {
            value = value.right(1);
        }
        /*
         * 当前不是中文模式,则单击按钮对应text为传递参数
         */
        if (currentType != "chinese") {
            insertValue(value);
        } else {
            /*
             * 中文模式下,不允许输入特殊字符,单击对应数字按键取得当前索引的汉字
             */
            if (btn->property("btnOther").toBool()) {
                if (ui->labPY->text().length() == 0) {
                    insertValue(value);
                }
            } else if (btn->property("btnNum").toBool()) {
                if (ui->labPY->text().length() == 0) {
                    insertValue(value);
                } else if (objectName == "btn0") {
                    setChinese(0);
                } else if (objectName == "btn1") {
                    setChinese(1);
                } else if (objectName == "btn2") {
                    setChinese(2);
                } else if (objectName == "btn3") {
                    setChinese(3);
                } else if (objectName == "btn4") {
                    setChinese(4);
                } else if (objectName == "btn5") {
                    setChinese(5);
                } else if (objectName == "btn6") {
                    setChinese(6);
                } else if (objectName == "btn7") {
                    setChinese(7);
                } else if (objectName == "btn8") {
                    setChinese(8);
                } else if (objectName == "btn9") {
                    setChinese(9);
                }
            } else if (btn->property("btnLetter").toBool()) {
                ui->labPY->setText(ui->labPY->text() + value);
                selectChinese();
            }
        }
    }
}

/*
 * 事件过滤器,用于识别鼠标单击汉字标签处获取对应汉字
 */
bool QQTInput::eventFilter(QObject *obj, QEvent *event)
{
    //pline() << obj->objectName() << currentEditType << event->type();
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->labCh0) {
            setChinese(0);
        } else if (obj == ui->labCh1) {
            setChinese(1);
        } else if (obj == ui->labCh2) {
            setChinese(2);
        } else if (obj == ui->labCh3) {
            setChinese(3);
        } else if (obj == ui->labCh4) {
            setChinese(4);
        } else if (obj == ui->labCh5) {
            setChinese(5);
        } else if (obj == ui->labCh6) {
            setChinese(6);
        } else if (obj == ui->labCh7) {
            setChinese(7);
        } else if (obj == ui->labCh8) {
            setChinese(8);
        } else if (obj == ui->labCh9) {
            setChinese(9);
        } else if (currentEditType != "" && obj != ui->btnClose) {
            ShowPanel();
        }
        btnPress = (QPushButton *)obj;
        if (checkPress()) {
            isPress = true;
            timerPress->start(500);
        }
        //pline() << currentEditType;
        return false;
    } else if (event->type() == QEvent::MouseMove) {
        if(isVisible())
            return true;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        btnPress = (QPushButton *)obj;
        if (checkPress()) {
            isPress = false;
            timerPress->stop();
            btnPress->update();
        }
        return false;
    } else if (event->type() == QEvent::KeyPress) {
        /*
         * 如果输入法窗体不可见,则不需要处理
         */
        if (!isVisible()) {
            return QWidget::eventFilter(obj, event);
        }

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        /*
         * Shift切换输入法模式,esc键关闭输入法面板,空格取第一个汉字,退格键删除
         * 中文模式下回车键取拼音,中文模式下当没有拼音时可以输入空格
         */
        if (keyEvent->key() == Qt::Key_Space) {
            if (ui->labPY->text() != "") {
                setChinese(0);
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            insertValue(ui->labPY->text());
            ui->labPY->setText("");
            selectChinese();
            return true;
        } else if (keyEvent->key() == Qt::Key_Shift) {
            bool bChecked = ui->checkShift->isChecked()?false:true;
            ui->checkShift->setChecked(bChecked);
            return true;
        } else if (keyEvent->key() == Qt::Key_Escape) {
            ui->btnClose->click();
            return true;
        } else if (keyEvent->key() == Qt::Key_Backspace) {
            ui->btnDelete->click();
            return true;
        } else if (keyEvent->text() == "+" || keyEvent->text() == "=") {
            if (ui->labPY->text() != "") {
                ui->btnNext->click();
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->text() == "-" || keyEvent->text() == "_") {
            if (ui->labPY->text() != "") {
                ui->btnPre->click();
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->key() == Qt::Key_CapsLock) {
            if (currentType != "max") {
                currentType = "max";
            } else {
                currentType = "min";
            }
            changeType();
            return true;
        } else {
            if (currentEditType == "QWidget") {
                return false;
            }
            QString key;
            if (currentType == "chinese") {
                key = keyEvent->text();
            } else if (currentType == "min") {
                key = keyEvent->text().toLower();
            } else if (currentType == "max") {
                key = keyEvent->text().toUpper();
            }
            QList<QPushButton *> btn = this->findChildren<QPushButton *>();
            foreach (QPushButton * b, btn) {
                if (b->text() == key) {
                    b->click();
                    return true;
                }
            }
        }
        return false;
    }
    return QWidget::eventFilter(obj, event);
}

void QQTInput::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
    currentFocusWidget = nowWidget;
    //pline() << currentEditType << "oldWidget:" << oldWidget << " nowWidget:" << nowWidget;
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget)) {
        /*
         * 在Qt5和linux系统中(嵌入式linux除外),当输入法面板关闭时,焦点会变成无,然后焦点会再次移到焦点控件处
         * 这样导致输入法面板的关闭按钮不起作用,关闭后马上有控件获取焦点又显示.
         * 为此,增加判断,当焦点是从有对象转为无对象再转为有对象时不要显示.
         * 这里又要多一个判断,万一首个窗体的第一个焦点就是落在可输入的对象中,则要过滤掉
         */

#ifndef __MIPS_LINUX__
        if (oldWidget == 0x0 && !isFirst) {
            return;
        }
#endif

        isFirst = false;
        if (nowWidget->inherits("QLineEdit")) {
            QLineEdit *lineedit = (QLineEdit *)nowWidget;
            if(!lineedit->isReadOnly())
            {
                currentLineEdit = (QLineEdit *)nowWidget;
                currentEditType = "QLineEdit";
                ShowPanel();
            }
        } else if (nowWidget->inherits("QTextEdit")) {
            currentTextEdit = (QTextEdit *)nowWidget;
            currentEditType = "QTextEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QPlainTextEdit")) {
            currentPlain = (QPlainTextEdit *)nowWidget;
            currentEditType = "QPlainTextEdit";
            ShowPanel();
#if 0
        } else if (nowWidget->inherits("QComboBox")) {
            QComboBox *cbox = (QComboBox *)nowWidget;
            /*
             * 只有当下拉选择框处于编辑模式才可以输入
             */
            if (cbox->isEditable()) {
                currentLineEdit = cbox->lineEdit() ;
                currentEditType = "QLineEdit";
                ShowPanel();
            }
        } else if (nowWidget->inherits("QSpinBox") ||
                   nowWidget->inherits("QDoubleSpinBox") ||
                   nowWidget->inherits("QDateEdit") ||
                   nowWidget->inherits("QTimeEdit") ||
                   nowWidget->inherits("QDateTimeEdit")) {
            currentWidget = nowWidget;
            currentEditType = "QWidget";
            ShowPanel();
#endif
        } else {
            /*
             * 需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
             */
            currentWidget = 0;
            currentLineEdit = 0;
            currentTextEdit = 0;
            currentPlain = 0;
            currentBrowser = 0;
            currentEditType = "";
            currentType = "min";
            changeType();
            this->setVisible(false);
            //pline();
            return;
        }
        //pline() << currentEditType;
        /*
         * 如果要实现android键盘的效果，再考虑此处，否则不考虑
         */
        changePosition();
    }
    /*
     * 这部分代码不可更改 除非添加控件
     */
    //pline() << currentEditType;
}

void QQTInput::changeType()
{
    /*
     * 如果需要更改输入法初始模式,改变currentType这个变量即可
     * min--小写模式  max--大写模式  chinese--中文模式
     */
    //currentType = "min";
    if (currentType == "max") {
        changeLetter(true);
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    } else if (currentType == "min") {
        changeLetter(false);
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    } else {
        changeLetter(false);
        ui->btnOther12->setText("。");
        ui->btnOther14->setText("：");
        ui->btnOther17->setText("，");
        ui->btnOther18->setText("；");
        ui->btnOther21->setText("“");
    }
    /*
     * 每次切换到模式,都要执行清空之前中文模式下的信息
     */
    clearChinese();
    ui->labPY->setText("");
}

void QQTInput::changeLetter(bool isUpper)
{
    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        if (b->property("btnLetter").toBool()) {
            if (isUpper) {
                b->setText(b->text().toUpper());
            } else {
                b->setText(b->text().toLower());
            }
        }
    }
}

void QQTInput::selectChinese()
{
    clearChinese();
    QSqlQuery query(m_db);
    QString currentPY = ui->labPY->text();
    QString sql = "select [word] from [pinyin] where [pinyin]='" + currentPY + "';";
    query.exec(sql);
    /*
     * 逐个将查询到的字词加入汉字队列
     */
    while(query.next()) {
        QString result = query.value(0).toString();
        QStringList text = result.split(" ");
        foreach (QString txt, text) {
            if (txt.length() > 0) {
                allPY.append(txt);
                currentPY_count++;
            }
        }
    }
    showChinese();
}

void QQTInput::showChinese()
{
    /*
     * 每个版面最多显示10个汉字
     */
    int count = 0;
    currentPY.clear();
    for (int i = 0; i < 10; i++) {
        labCh[i]->setText("");
    }

    for (int i = currentPY_index; i < currentPY_count; i++) {
        if (count == 10) {
            break;
        }
        QString txt = QString("%1  ").arg(allPY[currentPY_index]);
        currentPY.append(allPY[currentPY_index]);
        labCh[count]->setText(txt);
        count++;
        currentPY_index++;
    }
    qDebug() << "currentPY_index:" << currentPY_index << "currentPY_count:" << currentPY_count;
}

void QQTInput::insertValue(QString value)
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->insert(value);
    } else if (currentEditType == "QTextEdit") {
        currentTextEdit->insertPlainText(value);
    } else if (currentEditType == "QPlainTextEdit") {
        currentPlain->insertPlainText(value);
    } else if (currentEditType == "QTextBrowser") {
        currentBrowser->insertPlainText(value);
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(value));
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void QQTInput::deleteValue()
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->backspace();
    } else if (currentEditType == "QTextEdit") {
        /*
         * 获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
         */
        QTextCursor cursor = currentTextEdit->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QPlainTextEdit") {
        /*
         * 获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
         */
        QTextCursor cursor = currentPlain->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QTextBrowser") {
        /*
         * 获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
         */
        QTextCursor cursor = currentBrowser->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier, QString());
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void QQTInput::setChinese(int index)
{
    int count = currentPY.count();
    if (count > index) {
        insertValue(currentPY[index]);
        /*
         * 添加完一个汉字后,清空当前汉字信息,等待重新输入
         */
        clearChinese();
        ui->labPY->setText("");
    }
}

void QQTInput::clearChinese()
{
    /*
     * 清空汉字,重置索引
     */
    for (int i = 0; i < 10; i++) {
        labCh[i]->setText("");
    }
    allPY.clear();
    currentPY.clear();
    currentPY_index = 0;
    currentPY_count = 0;
}

void QQTInput::changeRect()
{
    QRect geo = geometry();
    if (currentType == "min" || currentType == "max") {
        geo.adjust(0, +frmTopHeight, 0, 0);
    } else if (currentType == "chinese") {
        geo.adjust(0, -frmTopHeight, 0, 0);
    }
    setFixedHeight(geo.height());
    setGeometry(geo);
}

void QQTInput::changePosition()
{
    /*
     * 如果需要更改输入法面板的显示位置,改变currentPosition这个变量即可
     * control--显示在对应输入框的正下方 bottom--填充显示在底部  center--窗体居中显示
     */
    //currentPosition = "";

    /*
     * 根据用户选择的输入法位置设置-居中显示-底部填充-显示在输入框正下方
     */

    int frmRealHeight = frmHeight;
    //if(currentType != "chinese")
    //    frmRealHeight = frmHeight - frmTopHeight;
    setFixedSize(frmWidth, frmRealHeight);

    if(QSize(deskWidth, deskHeight) == QSize(1024, 768))
    {
        ui->btnSpace->setFixedWidth(278);
        ui->btnReturn->setFixedWidth(107);
        ui->widgetTop->setFixedHeight(54);
        ui->widgetMain->setFixedHeight(171);
        ui->widgetBottom->setFixedHeight(54);
    }
    else if(QSize(deskWidth, deskHeight) == QSize(800, 480))
    {
        ui->btnSpace->setFixedWidth(228);
        ui->btnReturn->setFixedWidth(87);
        ui->widgetTop->setFixedHeight(44);
        ui->widgetMain->setFixedHeight(141);
        ui->widgetBottom->setFixedHeight(44);
    }

    if (currentPosition == "center") {
        QPoint pos = QPoint(deskWidth / 2 - frmWidth / 2, deskHeight / 2 - frmRealHeight / 2);
        this->setGeometry(pos.x(), pos.y(), frmWidth, frmRealHeight);
    } else if (currentPosition == "bottom_cover") {
        this->setGeometry(0, deskHeight - frmRealHeight, deskWidth, frmRealHeight);
    } else if (currentPosition == "control") {
        if(currentFocusWidget == NULL)
            return;
        QRect rect = currentFocusWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.top() + 27 + 2);
        QPoint pos2 = QPoint(rect.left(), rect.bottom() + 2);
        pos = currentFocusWidget->mapToGlobal(pos);
        pos2 = currentFocusWidget->mapToGlobal(pos2);
        int ih2 = pos2.y() + frmHeight;
        int ih = pos.y() + frmHeight;

        if(ih > deskHeight && ih2 > deskHeight)
            //up
            this->setGeometry(( deskWidth - frmWidth) / 2, 0, frmWidth, frmRealHeight);
        else
            //down
            this->setGeometry(( deskWidth - frmWidth) / 2,
                              ( deskHeight - frmRealHeight),
                              frmWidth, frmRealHeight);
    } else if (currentPosition == "bottom_middle") {
        QPoint pos = QPoint(deskWidth / 2 - frmWidth / 2, deskHeight - frmRealHeight);
        qDebug() << deskHeight << frmHeight;
        this->setGeometry(pos.x(), pos.y(), frmWidth, frmRealHeight);
    }
}

void QQTInput::ChangeStyle()
{
    /*
     * 如果需要更改输入法面板的样式,改变currentStyle这个变量即可
     * blue--淡蓝色  dev--dev风格  black--黑色  brown--灰黑色  lightgray--浅灰色  darkgray--深灰色  gray--灰色  silvery--银色
     */
    //currentStyle = "";

    if (currentStyle == "blue") {
        changeStyle("#DEF0FE", "#C0DEF6", "#C0DCF2", "#386487");
    } else if (currentStyle == "dev") {
        changeStyle("#C0D3EB", "#BCCFE7", "#B4C2D7", "#324C6C");
    } else if (currentStyle == "gray") {
        changeStyle("#E4E4E4", "#A2A2A2", "#A9A9A9", "#000000");
    } else if (currentStyle == "lightgray") {
        changeStyle("#EEEEEE", "#E5E5E5", "#D4D0C8", "#6F6F6F");
    } else if (currentStyle == "darkgray") {
        changeStyle("#D8D9DE", "#C8C8D0", "#A9ACB5", "#5D5C6C");
    } else if (currentStyle == "black") {
        changeStyle("#4D4D4D", "#292929", "#D9D9D9", "#CACAD0");
    } else if (currentStyle == "brown") {
        changeStyle("#667481", "#566373", "#C2CCD8", "#E7ECF0");
    } else if (currentStyle == "silvery") {
        changeStyle("#E1E4E6", "#CCD3D9", "#B2B6B9", "#000000");
    } else if (currentStyle == "QQT") {
        changeStyle("#909090", "#909090", "#909090", "#000000");
    }
}

void QQTInput::ChangeFont()
{
    /*
     * 输入法面板字体大小,如果需要更改面板字体大小,该这里即可
     */
    //btnFontSize = 10;
    //labFontSize = 10;

    QFont btnFont(this->font().family(), btnFontSize);
    QFont labFont(this->font().family(), labFontSize);

    QList<QPushButton *> btns = ui->widgetMain->findChildren<QPushButton *>();
    foreach (QPushButton * btn, btns) {
        btn->setFont(btnFont);
    }

    QList<QLabel *> labs = ui->widgetTop->findChildren<QLabel *>();
    foreach (QLabel * lab, labs) {
        lab->setFont(labFont);
    }
    ui->btnPre->setFont(labFont);
    ui->btnNext->setFont(labFont);
    ui->btnClose->setFont(labFont);
}

void QQTInput::changeStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor)
{
    QStringList qss;

    qss.append(QString("QWidget#frmInput{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append(QString("QWidget#widgetTopPinyin{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(QString("#FFFFFF")).arg(QString("#FFFFFF")));
    qss.append(QString("QWidget#widgetTopHanzi{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(QString("#F4F4F4")).arg(QString("#F4F4F4")));
    //normal
    qss.append(QString("QPushButton{padding:1px;color:%1;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 %2, stop: 1 %2);border: 0px solid %3;border-radius:6px;}")
               .arg(textColor).arg("#FFFFFF").arg(borderColor));
    qss.append(QString("QPushButton::pressed {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 %1, stop: 0.5 %1, stop: 1.0 %1); border-color: %2; }")
               .arg("#FF8400").arg(borderColor));
    //return
    qss.append(QString("QPushButton#btnReturn{padding:5px;color:%1;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 %2, stop: 1 %2);border: 1px solid %3;border-radius:6px;}")
               .arg("#FFFFFF").arg("#FF8400").arg(borderColor));
    qss.append(QString("QPushButton#btnReturn::pressed {color:%1; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 %2, stop: 0.5 %2, stop: 1.0 %2); border-color: %3; }")
               .arg("#000000").arg("#FFFFFF").arg(borderColor));

    //pre next
    qss.append(QString("QPushButton#btnPre,QPushButton#btnNext{padding:5px;color:%1;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 %2, stop: 1 %2);border: 1px solid %3;border-radius:6px;}")
               .arg("#000000").arg("#F4F4F4").arg("#F4F4F4"));
    qss.append(QString("QPushButton#btnPre::pressed,QPushButton#btnNext::pressed {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 %1, stop: 0.5 %1, stop: 1.0 %1); border-color: %2; }")
               .arg("#F4F4F4").arg("#F4F4F4"));

    //qss.append(QString("QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
    //           .arg(topColor).arg(bottomColor));
    qss.append(QString("QLabel{color:%1;}").arg(textColor));
    qss.append(QString("QLineEdit{border:1px solid %1;border-radius:5px;padding:2px;background:none;selection-background-color:%2;selection-color:%3;}")
               .arg(borderColor).arg(bottomColor).arg(topColor));
    this->setStyleSheet(qss.join(""));
}
