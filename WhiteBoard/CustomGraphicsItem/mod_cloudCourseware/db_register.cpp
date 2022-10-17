#include "db_register.h"
#include "ui_db_register.h"

#include <QEvent>
#include <QMouseEvent>
#include <QRegExp>
#include <QRegExpValidator>

DB_Register::DB_Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DB_Register)
{
    ui->setupUi(this);
    initWidget();
    this->resize();

    m_pMBoxToolTip = new DB_CustomWidget1(this);
    m_pMBoxToolTip->hide();

    m_pHttpThread = new DB_HttpThread;
    connect(m_pHttpThread, &DB_HttpThread::httpThreadFinished, this, &DB_Register::onHttpThreadFinished);

    connect(ui->pGetVerificationCode, &QPushButton::clicked, this, &DB_Register::getVerificationCode);
    connect(ui->label_loginNow, &DB_CustomLabel_1::mouseClicked, [=](){ emit showLoginPage(); });
    connect(ui->label_loginNow2, &DB_CustomLabel_1::mouseClicked, [=](){ emit showLoginPage(); });
    connect(ui->label_and, &DB_CustomLabel_1::mouseClicked, [=](){
        if (ui->checkBox->isChecked())
            ui->checkBox->setChecked(false);
        else
            ui->checkBox->setChecked(true);
    });
    connect(ui->label_privacyPolicy, &DB_CustomLabel_1::mouseClicked, [=]{
        emit showDocument(1);
    });
    connect(ui->label_serviceAgreement, &DB_CustomLabel_1::mouseClicked, [=]{
        emit showDocument(2);
    });

}

DB_Register::~DB_Register()
{
    if (m_pHttpThread)
        delete m_pHttpThread;
    delete ui;
}

void DB_Register::show()
{
    QWidget::show();
    this->initDisplay();
}

void DB_Register::resize()
{
    QSize size = DB_ApplicationScale::getScaleSize(QSize(40, 30));
    ui->verticalLayout->setContentsMargins(size.width(), size.height(), size.width(), 0);
    ui->verticalLayout_2->setSpacing(size.height());
    ui->verticalLayout_2->setContentsMargins(0, size.height(), 0, DB_ApplicationScale::getScaleWidth(10));
    ui->verticalLayout_3->setSpacing(size.height());
    ui->verticalLayout_3->setContentsMargins(0, size.height(), 0, DB_ApplicationScale::getScaleWidth(10));
    ui->horizontalLayout_12->setContentsMargins(DB_ApplicationScale::getScaleWidth(10), 0, 0, 0);
    ui->horizontalLayout_13->setContentsMargins(DB_ApplicationScale::getScaleWidth(10), 0, 0, 0);
    ui->horizontalLayout_14->setContentsMargins(DB_ApplicationScale::getScaleWidth(10), 0, 0, 0);
    ui->horizontalLayout_15->setContentsMargins(DB_ApplicationScale::getScaleWidth(10), 0, 0, 0);
    size = DB_ApplicationScale::getScaleSize(QSize(0, 50));
    ui->frame_2->setFixedHeight(size.height());
    ui->frame_3->setFixedHeight(size.height());
    ui->frame_4->setFixedHeight(size.height());
    ui->frame_5->setFixedHeight(size.height());
    ui->pushButton_next->setFixedHeight(size.height());
    ui->pushButton_finished->setFixedHeight(size.height());
    size = DB_ApplicationScale::getScaleSize(QSize(18, 18));
    ui->label_userIcon->setFixedSize(size);
    ui->label_passwdIcon->setFixedSize(size);
    ui->label_passwdIcon_1->setFixedSize(size);
    ui->label_codeIcon->setFixedSize(size);
    size = DB_ApplicationScale::getScaleSize(QSize(16, 16));
    ui->label_setup1->setFixedSize(size);
    ui->label_setup2->setFixedSize(size);
    ui->label_serviceAgreement->setContentsMargins(DB_ApplicationScale::getScaleWidth(5), 0,
                                                   DB_ApplicationScale::getScaleWidth(5), 0);
    ui->label_privacyPolicy->setContentsMargins(DB_ApplicationScale::getScaleWidth(5), 0,
                                                DB_ApplicationScale::getScaleWidth(5), 0);
    ui->checkBox->setStyleSheet(QString("QCheckBox::indicator{"
                                                  "width:%1px;"
                                                  "height:%1px;}")
                                          .arg(QString::number(DB_ApplicationScale::getScaleWidth(16))));
    ui->pGetVerificationCode->setFixedWidth(DB_ApplicationScale::getScaleWidth(80));

    QFont font = DB_ApplicationScale::getFont(16);
    ui->label_3->setFont(font);
    ui->pushButton_next->setFont(font);
    ui->pushButton_finished->setFont(font);
    font = DB_ApplicationScale::getFont(14);
    ui->label_inputPhone->setFont(font);
    ui->label_setPassword->setFont(font);
    ui->lineEdit_telephone->setFont(font);
    ui->lineEdit_verificationCode->setFont(font);
    ui->lineEdit_inputPassword->setFont(font);
    ui->lineEdit_reputPassword->setFont(font);
    ui->pGetVerificationCode->setFont(font);
    ui->checkBox->setFont(font);
    ui->label_and->setFont(font);
    ui->label_serviceAgreement->setFont(font);
    ui->label_privacyPolicy->setFont(font);
    ui->label_loginNow->setFont(font);
    ui->label_loginNow2->setFont(font);

    ui->frame_2->setStyleSheet(QString("#%1{border: 1px solid rgb(105, 105, 105); "
                                     "border-radius: %2px}").arg(ui->frame_2->objectName())
                                    .arg(DB_ApplicationScale::getScaleWidth(5)));
    ui->frame_3->setStyleSheet(QString("#%1{border: 1px solid rgb(105, 105, 105); "
                                     "border-radius: %2px;"
                                       "border-top-right-radius: 0px;"
                                       "border-bottom-right-radius: 0px;"
                                       "border-right: none;}").arg(ui->frame_3->objectName())
                                    .arg(DB_ApplicationScale::getScaleWidth(5)));
    ui->frame_4->setStyleSheet(QString("#%1{border: 1px solid rgb(105, 105, 105); "
                                     "border-radius: %2px}").arg(ui->frame_4->objectName())
                                    .arg(DB_ApplicationScale::getScaleWidth(5)));
    ui->frame_5->setStyleSheet(QString("#%1{border: 1px solid rgb(105, 105, 105); "
                                     "border-radius: %2px}").arg(ui->frame_5->objectName())
                                    .arg(DB_ApplicationScale::getScaleWidth(5)));
}

void DB_Register::initDisplay()
{
    ui->label_setup1->isHighlight(true);
    ui->label_inputPhone->setStyleSheet("color: rgb(78, 155, 252);");
    ui->label_setup2->isHighlight(false);
    ui->label_setPassword->setStyleSheet("color: rgb(185,  185, 185);");
    ui->lineEdit_verificationCode->clear();
    ui->lineEdit_telephone->clear();
    ui->lineEdit_inputPassword->clear();
    ui->lineEdit_reputPassword->clear();
    ui->checkBox->setChecked(false);
    ui->stackedWidget->setCurrentWidget(ui->widget);
}

void DB_Register::stopHttpThread()
{
    m_pHttpThread->stop();
}

void DB_Register::initWidget()
{
    this->setLayout(ui->verticalLayout);
    ui->frame_2->setLayout(ui->horizontalLayout_12);
    ui->frame_3->setLayout(ui->horizontalLayout_13);
    ui->frame_4->setLayout(ui->horizontalLayout_14);
    ui->frame_5->setLayout(ui->horizontalLayout_15);
    ui->widget->setLayout(ui->verticalLayout_2);
    ui->widget_2->setLayout(ui->verticalLayout_3);
    ui->stackedWidget->addWidget(ui->widget);
    ui->stackedWidget->addWidget(ui->widget_2);

    //设置手机号码格式,只允许按格式输入
    QRegExp regexp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QRegExpValidator *validator = new QRegExpValidator(regexp);
    ui->lineEdit_telephone->setValidator(validator);

    //设置校验码格式,只允许按格式输入
    QRegExp regexp1("[0-9]{6}");
    QRegExpValidator *validator1 = new QRegExpValidator(regexp1);
    ui->lineEdit_verificationCode->setValidator(validator1);
}

bool DB_Register::checkTelephone(const QString &str, QString *tip)
{
    if (str.isEmpty()) {
        *tip = QString(tr("请输入手机号码"));
        return false;
    }

    if (11 != str.length()) {
        *tip = QString(tr("请输入正确的手机号码"));
        return false;
    }
    return true;
}

bool DB_Register::checkPassword(const QString &str, QString *tip)
{
    if (str.isEmpty()) {
        *tip = QString(tr("请输入密码"));
        return false;
    }
    return true;
}

bool DB_Register::checkVerificationCode(const QString &str, QString *tip)
{
    if (str.isEmpty()) {
        *tip = QString(tr("请输入验证码"));
        return false;
    }

    if (6 != str.length()) {
        *tip = QString(tr("请输入正确的验证码"));
        return false;
    }

    return true;
}

void DB_Register::getVerificationCode()
{
    m_pMBoxToolTip->setParent((QWidget*)ui->pushButton_next->parent());
    QString tip;
    if (!checkTelephone(ui->lineEdit_telephone->text().trimmed(), &tip)) {
        m_pMBoxToolTip->setText(tip);
        ui->lineEdit_telephone->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    m_pHttpThread->start(HttpFunction::CheckRegistered, QList<QString>() << ui->lineEdit_telephone->text());
    //显示加载框
    ui->frame_loading->show();
}

void DB_Register::on_pushButton_next_clicked()
{
    m_pMBoxToolTip->setParent((QWidget*)ui->pushButton_next->parent());
    QString tip;
    if (!checkTelephone(ui->lineEdit_telephone->text().trimmed(), &tip)) {
        m_pMBoxToolTip->setText(tip);
        ui->lineEdit_telephone->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    if (!checkPassword(ui->lineEdit_verificationCode->text().trimmed(), &tip)) {
        m_pMBoxToolTip->setText(tip);
        ui->lineEdit_verificationCode->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    //是否勾选协议
    if (!ui->checkBox->isChecked()) {
        m_pMBoxToolTip->setText(tr("请阅读并同意服务协议和隐私政策"));
        //ui->checkBox->setStyleSheet("QCheckBox{color: red;} QCheckBox::indicator{border:1px solid red; color: black;}");
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    //校验验证码
    m_pHttpThread->start(HttpFunction::CheckVerificationCode, QList<QString>() << ui->lineEdit_telephone->text()
                         << ui->lineEdit_verificationCode->text());
    ui->frame_loading->show();
}

void DB_Register::on_pushButton_finished_clicked()
{
    /* 密码字符类型四种 */
    QString passwdRequireLLetter = QString("abcdefghijklmnopqrstuvwxyz");
    QString passwdRequireCLetter = QString("ABCDEFGHIJKLMNOPQRSTUVWSYZ");
    QString passwdRequireNum = QString("0123456789");
    QString passwdRequireSpecialChar = QString("!@#$%^&*()_+");

    QString inPassword = ui->lineEdit_inputPassword->text();
    QString rePassword = ui->lineEdit_reputPassword->text();
    bool isLLetter;
    bool isCLetter;
    bool isNum;
    bool isSpecialChar;

    //密码不能为空
    if (inPassword.isEmpty()) {
        m_pMBoxToolTip->setText(tr("请输入密码"));
        ui->lineEdit_inputPassword->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    //第二次密码不能为空
    if (rePassword.isEmpty()) {
        m_pMBoxToolTip->setText(tr("请再次输入密码"));
        ui->lineEdit_reputPassword->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    //两次密码必须一致
    if (inPassword.compare(rePassword) != 0) {
        m_pMBoxToolTip->setText(tr("密码不一致"));
        ui->lineEdit_reputPassword->clear();
        ui->lineEdit_reputPassword->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    //密码长度大于6位小于16位(输入框已限制最大输入个数)
    if (inPassword.length() < 6) {
        m_pMBoxToolTip->setText(tr("密码长度不符合要求"));
        ui->lineEdit_inputPassword->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    QRegExp regexp("[a-z]|[A-Z]|[0-9]|[!@#$%^&*()_+]");
    QString cutText = inPassword.remove(regexp);
    if (!cutText.isEmpty()) {
        m_pMBoxToolTip->setText(tr("密码至少包含大写或小写字母、数字、特殊字符（!@#$%^&*()_+） 中的三种，长度为6-16位。"));
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_finished->x() + ui->pushButton_finished->width()/2, ui->pushButton_finished->y()));
        return;
    }

    /* 判断密码字符类型必须大于三种 */
    for (int i = 0; i < inPassword.length(); i++) {
        QChar ch = inPassword.at(i);
        if (passwdRequireLLetter.contains(ch))
            isLLetter = true;
        else if (passwdRequireCLetter.contains(ch))
            isCLetter = true;
        else if (passwdRequireNum.contains(ch))
            isNum = true;
        else if (passwdRequireSpecialChar.contains(ch))
            isSpecialChar = true;
    }
    int typeNum = 0;
    if (isLLetter)
        typeNum++;
    if (isCLetter)
        typeNum++;
    if (isNum)
        typeNum++;
    if (isSpecialChar)
        typeNum++;
    if (typeNum < 3) {
        m_pMBoxToolTip->setText(tr("密码格式不符合要求"));
        ui->lineEdit_inputPassword->setFocus();
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        return;
    }

    //开始注册
    m_pHttpThread->start(HttpFunction::RegisterAccount, QList<QString>() << ui->lineEdit_telephone->text()
                         << ui->lineEdit_verificationCode->text()
                         << ui->lineEdit_inputPassword->text());
    ui->frame_loading->show();
}

void DB_Register::onHttpThreadFinished(HttpFunction fun, QVariant variant)
{
    _HttpRetData data = variant.value<_HttpRetData>();
    switch (fun) {
    case HttpFunction::CheckRegistered: {
        if (1 == data.state) {
            m_pMBoxToolTip->setText(tr("该手机号码已经注册"));
            m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
            ui->frame_loading->hide();
        }else {
            m_pHttpThread->start(HttpFunction::GetVerificationCode, QList<QString>() << ui->lineEdit_telephone->text());
        }
    }break;
    case HttpFunction::GetVerificationCode: {
        if (1 == data.state) {
            m_pMBoxToolTip->setText(tr("发送成功"));
        }else {
            m_pMBoxToolTip->setText(tr("发送失败"));
        }
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        ui->frame_loading->hide();
    }break;
    case HttpFunction::CheckVerificationCode: {
        if (1 == data.state) {
            m_pMBoxToolTip->setParent((QWidget *)ui->pushButton_finished->parent());
            ui->stackedWidget->setCurrentWidget(ui->widget_2);
            ui->label_setup1->isHighlight(false);
            ui->label_setup2->isHighlight(true);
            ui->label_setPassword->setStyleSheet("color: rgb(78, 155, 252);");
            ui->label_inputPhone->setStyleSheet("color: rgb(185,  185, 185);;");
        }else {
            m_pMBoxToolTip->setText(tr("验证码错误"));
            ui->lineEdit_verificationCode->clear();
            ui->lineEdit_verificationCode->setFocus();
            m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_next->x() + ui->pushButton_next->width()/2, ui->pushButton_next->y()));
        }
        ui->frame_loading->hide();
    }break;
    case HttpFunction::RegisterAccount: {
        if (1 == data.state) {
            m_pMBoxToolTip->setText(tr("注册成功"));
        }else {
            m_pMBoxToolTip->setText(tr("注册失败"));
        }
        m_pMBoxToolTip->showMBox(QPoint(ui->pushButton_finished->x() + ui->pushButton_finished->width()/2, ui->pushButton_finished->y()));
        ui->frame_loading->hide();
    }break;
    default:
        break;
    }
}
