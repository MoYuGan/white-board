#include "calculator.h"
#include "ui_calculator.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>
#include <QtMath>
#include <Public/public_function.h>
Calculator::Calculator(QWidget *parent) :
    CalculatorInterFace(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint,true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setFixedSize(Public_Function::getScaleSize(350,422));
    initLayout();
    initConnect();
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::initLayout()
{
    ui->titel->setText(tr("计算器"));
    ui->titel->setFont(Public_Function::getFont(18));
    ui->titel->setAutoFillBackground(false);

    stylesheet1 = QString("QPushButton{border-radius:%1px;background-color:rgba(229,242,255,1);}QPushButton:hover{background-color:rgba(190,222,255,1);}"
                          "QPushButton:pressed{background-color:rgba(229,242,255,1);}").arg(Public_Function::getScaleSize(8));

    stylesheet2 = QString("QPushButton{border-radius:%1px;background-color:rgba(238,238,238,1);color:rgba(68,68,68,1);font-size:%2px;}"
                          "QPushButton:hover{background-color:rgba(220,220,220,1);}QPushButton:pressed{background-color:rgba(238,238,238,1);}"
                          ).arg(Public_Function::getScaleSize(8)).arg(Public_Function::getScaleSize(26));

    ui->upshow->hide();
    ui->downshow->setFont(Public_Function::getFont(28));
    ui->downshow->setText("0");
    ui->downshow->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->upshow->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    ui->show_Wid->setFixedSize(Public_Function::getScaleSize(310,50));
    ui->show_Wid->setStyleSheet(QString("background-color:rgba(238,238,238,1);border-radius:%1px;").arg(Public_Function::getScaleSize(8)));

    ui->close->setPixmap(QPixmap(":/Pixmap/guanbi@2x.png"));
    ui->close->installEventFilter(this);

    ui->Btn_cut->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_cut->setStyleSheet(stylesheet1);
    ui->Btn_cut->setIcon(QIcon(":/Pixmap/jisuanqi1@2x.png"));
    ui->Btn_cut->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_clear1->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_clear1->setStyleSheet(stylesheet1);
    ui->Btn_clear1->setIcon(QIcon(":/Pixmap/jisuanqi2@2x.png"));
    ui->Btn_clear1->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_clear2->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_clear2->setStyleSheet(stylesheet1);
    ui->Btn_clear2->setIcon(QIcon(":/Pixmap/jisuanqi3@2x.png"));
    ui->Btn_clear2->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_sign->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_sign->setStyleSheet(stylesheet1);
    ui->Btn_sign->setIcon(QIcon(":/Pixmap/jisuanqi4@2x.png"));
    ui->Btn_sign->setIconSize(Public_Function::getScaleSize(30,30));


    ui->Btn_genhao->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_genhao->setStyleSheet(stylesheet1);
    ui->Btn_genhao->setIcon(QIcon(":/Pixmap/jisuanqi5@2x.png"));
    ui->Btn_genhao->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_percentage->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_percentage->setStyleSheet(stylesheet1);
    ui->Btn_percentage->setIcon(QIcon(":/Pixmap/jisuanqi6@2x.png"));
    ui->Btn_percentage->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_fenmu->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_fenmu->setStyleSheet(stylesheet1);
    ui->Btn_fenmu->setIcon(QIcon(":/Pixmap/jisuanqi7@2x.png"));
    ui->Btn_fenmu->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_devide->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_devide->setStyleSheet(stylesheet1);
    ui->Btn_devide->setIcon(QIcon(":/Pixmap/jisuanqi9@2x.png"));
    ui->Btn_devide->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_multiply->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_multiply->setStyleSheet(stylesheet1);
    ui->Btn_multiply->setIcon(QIcon(":/Pixmap/jisuanqi10@2x.png"));
    ui->Btn_multiply->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_minus->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_minus->setStyleSheet(stylesheet1);
    ui->Btn_minus->setIcon(QIcon(":/Pixmap/jisuanqi11@2x.png"));
    ui->Btn_minus->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_add->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_add->setStyleSheet(stylesheet1);
    ui->Btn_add->setIcon(QIcon(":/Pixmap/jisuanqi12@2x.png"));
    ui->Btn_add->setIconSize(Public_Function::getScaleSize(30,30));

    ui->Btn_result->setFixedSize(Public_Function::getScaleSize(54,110));
    ui->Btn_result->setStyleSheet("QPushButton{border-radius:8px;background-color:rgba(20,134,250,1);image:url(:/Pixmap/jisuanqi8.png);}"
                               "QPushButton:hover{background-color:rgba(20,134,250,1);}");

    ui->Btn_0->setFixedSize(Public_Function::getScaleSize(118,50));
    ui->Btn_0->setText("0");
    ui->Btn_0->setStyleSheet(stylesheet2);

    ui->Btn_dot->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_dot->setText(".");
    ui->Btn_dot->setStyleSheet(stylesheet2);

    ui->Btn_1->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_1->setText("1");
    ui->Btn_1->setStyleSheet(stylesheet2);

    ui->Btn_2->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_2->setText("2");
    ui->Btn_2->setStyleSheet(stylesheet2);

    ui->Btn_3->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_3->setText("3");
    ui->Btn_3->setStyleSheet(stylesheet2);

    ui->Btn_4->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_4->setText("4");
    ui->Btn_4->setStyleSheet(stylesheet2);

    ui->Btn_5->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_5->setText("5");
    ui->Btn_5->setStyleSheet(stylesheet2);

    ui->Btn_6->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_6->setText("6");
    ui->Btn_6->setStyleSheet(stylesheet2);

    ui->Btn_7->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_7->setText("7");
    ui->Btn_7->setStyleSheet(stylesheet2);

    ui->Btn_8->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_8->setText("8");
    ui->Btn_8->setStyleSheet(stylesheet2);

    ui->Btn_9->setFixedSize(Public_Function::getScaleSize(54,50));
    ui->Btn_9->setText("9");
    ui->Btn_9->setStyleSheet(stylesheet2);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(ui->Btn_cut,0,0,1,1);
    grid->addWidget(ui->Btn_clear1,0,1,1,1);
    grid->addWidget(ui->Btn_clear2,0,2,1,1);
    grid->addWidget(ui->Btn_sign,0,3,1,1);
    grid->addWidget(ui->Btn_genhao,0,4,1,1);

    grid->addWidget(ui->Btn_7,1,0,1,1);
    grid->addWidget(ui->Btn_8,1,1,1,1);
    grid->addWidget(ui->Btn_9,1,2,1,1);
    grid->addWidget(ui->Btn_devide,1,3,1,1);
    grid->addWidget(ui->Btn_percentage,1,4,1,1);

    grid->addWidget(ui->Btn_4,2,0,1,1);
    grid->addWidget(ui->Btn_5,2,1,1,1);
    grid->addWidget(ui->Btn_6,2,2,1,1);
    grid->addWidget(ui->Btn_multiply,2,3,1,1);
    grid->addWidget(ui->Btn_fenmu,2,4,1,1);

    grid->addWidget(ui->Btn_1,3,0,1,1);
    grid->addWidget(ui->Btn_2,3,1,1,1);
    grid->addWidget(ui->Btn_3,3,2,1,1);
    grid->addWidget(ui->Btn_minus,3,3,1,1);
    grid->addWidget(ui->Btn_result,3,4,2,1);

    grid->addWidget(ui->Btn_0,4,0,1,2);
    grid->addWidget(ui->Btn_dot,4,2,1,1);
    grid->addWidget(ui->Btn_add,4,3,1,1);
    grid->setHorizontalSpacing(Public_Function::getScaleSize(10));
    grid->setVerticalSpacing(Public_Function::getScaleSize(10));
    grid->setMargin(Public_Function::getScaleSize(10));

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addStretch(0);
    hlayout2->addLayout(grid);
    hlayout2->addStretch(0);

    QHBoxLayout *hlayout3 = new QHBoxLayout();
    hlayout3->addStretch(0);
    hlayout3->addWidget(ui->show_Wid);
    hlayout3->addStretch(0);

    hlayout1->addWidget(ui->titel);
    hlayout1->addStretch(0);
    hlayout1->addWidget(ui->close);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout2);
    vlayout->addStretch(0);

}

void Calculator::initConnect()
{
    connect(ui->Btn_0,&QPushButton::clicked,this,[=](){digitClicked(0);});
    connect(ui->Btn_1,&QPushButton::clicked,this,[=](){digitClicked(1);});
    connect(ui->Btn_2,&QPushButton::clicked,this,[=](){digitClicked(2);});
    connect(ui->Btn_3,&QPushButton::clicked,this,[=](){digitClicked(3);});
    connect(ui->Btn_4,&QPushButton::clicked,this,[=](){digitClicked(4);});
    connect(ui->Btn_5,&QPushButton::clicked,this,[=](){digitClicked(5);});
    connect(ui->Btn_6,&QPushButton::clicked,this,[=](){digitClicked(6);});
    connect(ui->Btn_7,&QPushButton::clicked,this,[=](){digitClicked(7);});
    connect(ui->Btn_8,&QPushButton::clicked,this,[=](){digitClicked(8);});
    connect(ui->Btn_9,&QPushButton::clicked,this,[=](){digitClicked(9);});
    connect(ui->Btn_add,&QPushButton::clicked,this,[=](){additiveOperatorClicked("+");});
    connect(ui->Btn_minus,&QPushButton::clicked,this,[=](){additiveOperatorClicked("-");});
    connect(ui->Btn_multiply,&QPushButton::clicked,this,[=](){multiplicativeOperatorClicked("\303\227");});
    connect(ui->Btn_devide,&QPushButton::clicked,this,[=](){multiplicativeOperatorClicked("\303\267");});
    connect(ui->Btn_percentage,&QPushButton::clicked,this,[=](){percentageClicked();});
    connect(ui->Btn_dot,&QPushButton::clicked,this,[=](){pointClicked();});
    connect(ui->Btn_clear1,&QPushButton::clicked,this,[=](){clear();});
    connect(ui->Btn_clear2,&QPushButton::clicked,this,[=](){clearAll();});
    connect(ui->Btn_sign,&QPushButton::clicked,this,[=](){changeSignClicked();});
    connect(ui->Btn_genhao,&QPushButton::clicked,this,[=](){unaryOperatorClicked(1);});
    connect(ui->Btn_fenmu,&QPushButton::clicked,this,[=](){unaryOperatorClicked(3);});
    connect(ui->Btn_result,&QPushButton::clicked,this,[=](){equalClicked();});
    connect(ui->Btn_cut,&QPushButton::clicked,this,[=](){backspaceClicked();});
}

CalculatorInterFace *Calculator::getWidget()
{
    Calculator *calc = new Calculator;
    return calc;
}

void Calculator::updateLanguage(bool isChinese)
{
    if( !isChinese)
        ui->titel->setText("Calculator");
}

bool Calculator::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == ui->close)
        {
            emit sendCloseMessage();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void Calculator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(this->rect(),15,15);
}

void Calculator::mousePressEvent(QMouseEvent *event)
{
    if(event->button() ==Qt::LeftButton)
    {
        mousepressdot =event->pos();
        mousepress =true;
    }
}

void Calculator::mouseMoveEvent(QMouseEvent *event)
{
    if(mousepress)
    this->move(event->globalPos() -mousepressdot);
}

void Calculator::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mousepress =false;
}

void Calculator::digitClicked(int num)
{
    int digitValue = num;
    if (ui->downshow->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        ui->downshow->clear();
        waitingForOperand = false;
    }
    ui->downshow->setText(ui->downshow->text() + QString::number(digitValue));
}

void Calculator::unaryOperatorClicked(int num)
{
    double operand = ui->downshow->text().toDouble();
    double result = 0.0;

    if (1 == num) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (2 == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (3 == num) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    ui->downshow->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked(QString st)
{
    QString clickedOperator = st;
    double operand = ui->downshow->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {

        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        ui->downshow->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {

        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        ui->downshow->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;

    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked(QString st)
{
    QString clickedOperator = st;
    double operand = ui->downshow->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        ui->downshow->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = ui->downshow->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }
    ui->downshow->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        ui->downshow->setText("0");
    if (!ui->downshow->text().contains('.'))
        ui->downshow->setText(ui->downshow->text() + tr("."));
    waitingForOperand = false;
}

void Calculator::percentageClicked()
{
    QString text = ui->downshow->text();
    double value = text.toDouble();
    value /=100;
    ui->downshow->setText(QString::number(value));
}

void Calculator::changeSignClicked()
{
    QString text = ui->downshow->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    ui->downshow->setText(text);
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = ui->downshow->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    ui->downshow->setText(text);
}

void Calculator::clear()
{
    if (waitingForOperand)
        return;

    ui->downshow->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    ui->downshow->setText("0");
    waitingForOperand = true;
}

void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    ui->downshow->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = ui->downshow->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += ui->downshow->text().toDouble();
}

void Calculator::abortOperation()
{
    clearAll();
    ui->downshow->setText(tr("无效输入"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(CalculatorInterFace, Calculator)
#endif // QT_VERSION < 0x050000
