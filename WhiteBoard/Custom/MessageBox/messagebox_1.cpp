#include "messagebox_1.h"
#include "ui_messagebox_1.h"
#include "Public/public_function.h"
#include <QtDebug>

MessageBox_1::MessageBox_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageBox_1)
{
    ui->setupUi(this);
    this->initWidget();
}

MessageBox_1::MessageBox_1(const QString &title, const QString &text, const QString &leftText,
                       const QString &midText, const QString &rightText, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageBox_1)
{
    ui->setupUi(this);
    this->initWidget();
    ui->label_title->setText(title);
    ui->label_text->setText(text);
    if (leftText.isEmpty())
        ui->pLeft->hide();
    else
        ui->pLeft->setText(leftText);

    if (rightText.isEmpty())
        ui->pRight->hide();
    else
        ui->pRight->setText(rightText);

    if (midText.isEmpty())
        ui->pMid->hide();
    else
        ui->pMid->setText(midText);
}

MessageBox_1::~MessageBox_1()
{
    delete ui;
}

void MessageBox_1::show()
{
    QWidget::show();
    this->raise();
}

void MessageBox_1::mSetTitle(const QString &title)
{
    ui->label_title->setText(title);
}

void MessageBox_1::mSetText(const QString &text)
{
    ui->label_text->setText(text);
}

void MessageBox_1::mSetLeftBtnText(const QString &str)
{
    ui->pLeft->setText(str);
}

void MessageBox_1::mSetMidBtnText(const QString &str)
{
    ui->pMid->setText(str);
}

void MessageBox_1::mSetRightBtnText(const QString &str)
{
    ui->pRight->setText(str);
}

void MessageBox_1::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->resize();
}

void MessageBox_1::initWidget()
{
    ui->verticalLayoutWidget->hide();
    ui->frame->setLayout(ui->verticalLayout);
    ui->frame->installEventFilter(this);
    ui->frame->mSetBackgroudColor(Qt::white);

    connect(ui->pClose, &PushButton_Basic::clicked,this, [=](){ emit mboxClosed(-1);});
    connect(ui->pLeft, &PushButton_Basic::clicked,this, [=](){ emit mboxClosed(-1);});
    connect(ui->pMid, &PushButton_Basic::clicked,this, [=](){ emit mboxClosed(0);});
    connect(ui->pRight, &PushButton_Basic::clicked,this, [=](){ emit mboxClosed(1);});
}

void MessageBox_1::resize()
{
    QSize size;
    QFont font;
    int radius;

    ui->verticalLayout->setContentsMargins(Public_Function::getScaleSize(20), Public_Function::getScaleSize(16),
                                           Public_Function::getScaleSize(20), Public_Function::getScaleSize(28));
    ui->horizontalLayout_2->setSpacing(Public_Function::getScaleSize(20));
    size = Public_Function::getScaleSize(QSize(396, 236));
    ui->frame->setFixedSize(size);
    radius = Public_Function::getScaleSize(12);
    ui->frame->mSetBordRadius(radius, radius, radius, radius);
    size = Public_Function::getScaleSize(QSize(22, 22));
    ui->pClose->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(100, 42));
    ui->pLeft->setFixedSize(size);
    ui->pRight->setFixedSize(size);
    ui->pMid->setFixedSize(size);

    font = Public_Function::getFont(18);
    font.setBold(true);
    font.setWeight(70);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 1);
    ui->label_title->setFont(font);
    font = Public_Function::getFont(15);
    ui->label_text->setFont(font);
    font = Public_Function::getFont(13);
    ui->pLeft->setFont(font);
    ui->pMid->setFont(font);
    ui->pRight->setFont(font);

    ui->pMid->setStyleSheet(QString("QPushButton{"
                                    "color: rgb(20,134,250);"
                                    "border: %1px solid rgb(20,134,250);"
                                    "border-radius: %2px;"
                                    "background-color: white;"
                                    "}"
                                    "QPushButton::hover{"
                                    "background-color: rgb(229,242,255);"
                                    "border: none;"
                                    "}").arg(Public_Function::getScaleSize(1))
                            .arg(Public_Function::getScaleSize(5)));
    ui->pLeft->setStyleSheet(QString("QPushButton{"
                                     "color: rgb(102, 102, 102);"
                                     "border: %1px solid rgb(224, 224, 224);"
                                     "border-radius: %2px;"
                                     "background-color: white;"
                                     "}"
                                     "QPushButton::hover{"
                                     "background-color: rgb(238,238,238);"
                                     "border: none;"
                                     "}").arg(Public_Function::getScaleSize(1))
                             .arg(Public_Function::getScaleSize(5)));
    ui->pRight->setStyleSheet(QString("QPushButton{"
                                     "background-color: rgb(20,134,250);"
                                     "color: white;"
                                     "border-radius: %1px;"
                                     "border: none;"
                                     "}"
                                     "QPushButton::hover{"
                                     "background-color: rgb(19,119,221);"
                                     "}").arg(Public_Function::getScaleSize(5)));

    ui->frame->move(QPoint((this->width() - ui->frame->width())/2,
                           (this->height() - ui->frame->height())/2));
}
