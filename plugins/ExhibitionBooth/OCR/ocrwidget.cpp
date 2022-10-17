#include "ocrwidget.h"
#include "ui_ocrwidget.h"
#include "ShareStyle/db_scale.h"
#include <QPainter>
#include "db_mboxtooltip.h"
#include <QClipboard>
#include <QScrollBar>

OCRWidget::OCRWidget(const QPixmap &pixmap, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OCRWidget),
    m_pPixmap(pixmap)
{
    ui->setupUi(this);
    this->initWidget();
    this->resizeWidget();

    m_pOcrThread = new OcrThread;
    connect(m_pOcrThread, &OcrThread::workFinished, this, [=](int i){
        qDebug()<<"work finished";
        //ui->pushButton_redoOCR->show();
        ui->pushButton_close->show();
        if (1 == i) {
            ui->textEdit->clear();
            QStringList wordList = m_pOcrThread->getWordList();

            foreach(QString str, wordList) {
                ui->textEdit->append(str);
            }
            ui->pushButton_copyAll->show();
            ui->pushButton_copySelect->show();
            ui->label->hide();
            ui->textEdit->show();
        }else {
            ui->label->clear();
            ui->label->setPixmap(QPixmap(":/images/wujieguo.png"));
        }
    }, Qt::DirectConnection);
}

OCRWidget::~OCRWidget()
{
    if (nullptr != m_pOcrThread)
        m_pOcrThread->deleteLater();
    delete ui;
}

void OCRWidget::show()
{
    QWidget::show();
    this->raise();
    ui->label->setText(tr("正在识别......"));
    m_pOcrThread->start(m_pPixmap);
}

void OCRWidget::resizeWidget()
{
    QSize size = DB_ApplicationScale::getScaleSize(QSize(1000, 800));
    ui->frame->setFixedSize(size);
    size = DB_ApplicationScale::getScaleSize(QSize(400, 400));
    ui->label->setFixedSize(size);
    ui->label_title->setFixedHeight(DB_ApplicationScale::getScaleSize(50));
    size = DB_ApplicationScale::getScaleSize(QSize(100, 40));
    ui->pushButton_redoOCR->setFixedSize(size);
    ui->pushButton_copySelect->setFixedSize(size);
    ui->pushButton_copyAll->setFixedSize(size);
    ui->pushButton_close->setFixedSize(size);
    ui->frame_bottom->setFixedHeight(DB_ApplicationScale::getScaleSize(80));
    ui->frame_bottom->setContentsMargins(0, DB_ApplicationScale::getScaleSize(20),
                                         DB_ApplicationScale::getScaleSize(20),
                                         DB_ApplicationScale::getScaleSize(20));
    ui->verticalLayout->setSpacing(DB_ApplicationScale::getScaleSize(10));

    ui->frame->setStyleSheet(QString("#%1{border: none;"
                                     "background: white;"
                                     "border-radius: %2px;}").arg(ui->frame->objectName())
                             .arg(DB_ApplicationScale::getScaleSize(5)));
    ui->label_title->setContentsMargins(DB_ApplicationScale::getScaleSize(10), 0, 0, 0);
    ui->label_title->setStyleSheet(QString("%1 QLabel{border-top-left-radius: %2px;"
                                           "border-top-right-radius: %2px;}").arg(ui->label_title->styleSheet())
                                   .arg(DB_ApplicationScale::getScaleSize(5)));
    QColor color = QColor(102, 102, 102);
    ui->textEdit->setStyleSheet(QString("QTextEdit{border: none;"
                                        "border-top: %1px solid rgb(225, 225, 225);"
                                        "border-bottom: %1px solid rgb(225, 225, 225);"
                                        "color: rgba(%2, %3, %4, %5);}")
                                .arg(DB_ApplicationScale::getScaleSize(1))
                                .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
    ui->textEdit->verticalScrollBar()->setStyleSheet(QString(
                                     "QScrollBar:vertical{"
                                     "width: %1px;"
                                     "border: none;"
                                     "background: transparent;"
                                     "margin: 0px 0px 0px 0px;"
                                     "}"
                                     "QScrollBar::handle{"
                                      "background: rgb(78,  155,  252);"
                                     "border-radius: %2px;"
                                     "width: %1px;"
                                     "max-height: %3px;"
                                     "}"
                                     "QScrollBar::add-line, QScrollBar::sub-line{"
                                     "height: 0px;"
                                     "background: transparent;"
                                     "}"
                                     "QScrollBar::sub-page, QScrollBar::add-page{"
                                     "background: transparent;"
                                     "}").arg(DB_ApplicationScale::getScaleSize(30))
                                    .arg(DB_ApplicationScale::getScaleSize(5))
                                    .arg(DB_ApplicationScale::getScaleSize(60)));
    ui->label->setStyleSheet(QString("QLabel{color: rgba(%1, %2, %3, %4);}")
                             .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
    ui->pushButton_close->setStyleSheet(QString("%1 QPushButton{border-radius: %2px;}")
                                        .arg(ui->pushButton_close->styleSheet())
                                        .arg(DB_ApplicationScale::getScaleSize(5)));
    ui->pushButton_copyAll->setStyleSheet(QString("%1 QPushButton{border-radius: %2px;}")
                                        .arg(ui->pushButton_copyAll->styleSheet())
                                        .arg(DB_ApplicationScale::getScaleSize(5)));
    ui->pushButton_copySelect->setStyleSheet(QString("%1 QPushButton{border-radius: %2px;}")
                                        .arg(ui->pushButton_copySelect->styleSheet())
                                        .arg(DB_ApplicationScale::getScaleSize(5)));
    ui->pushButton_redoOCR->setStyleSheet(QString("%1 QPushButton{border-radius: %2px;}")
                                        .arg(ui->pushButton_redoOCR->styleSheet())
                                        .arg(DB_ApplicationScale::getScaleSize(5)));

    QFont font = DB_ApplicationScale::getFont(20);
    ui->label_title->setFont(font);
    font = DB_ApplicationScale::getFont(40);
    ui->label->setFont(font);
    font = DB_ApplicationScale::getFont(14);
    ui->textEdit->setFont(font);
    ui->pushButton_redoOCR->setFont(font);
    ui->pushButton_copySelect->setFont(font);
    ui->pushButton_copyAll->setFont(font);
    ui->pushButton_close->setFont(font);
}

void OCRWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::transparent);
}

void OCRWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    ui->frame->move(QPoint((this->width() - ui->frame->width())/2,
                           (this->height() - ui->frame->height())/2));
}

void OCRWidget::initWidget()
{
    ui->frame->setLayout(ui->verticalLayout);
    ui->frame_bottom->setLayout(ui->horizontalLayout_2);
    ui->label->setScaledContents(true);
    ui->textEdit->hide();
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->verticalLayout_2->setAlignment(ui->label, Qt::AlignCenter);

    ui->pushButton_redoOCR->hide();
    ui->pushButton_copyAll->hide();
    ui->pushButton_copySelect->hide();
    ui->pushButton_close->hide();

    connect(ui->pushButton_redoOCR, &CustomPushButton::clicked, [=](){
        ui->pushButton_redoOCR->hide();
        ui->pushButton_copyAll->hide();
        ui->pushButton_copySelect->hide();
        ui->label->setPixmap(QPixmap());
        ui->label->setText(tr("正在识别......"));
        ui->label->show();
        ui->textEdit->hide();
        m_pOcrThread->start(m_pPixmap);
    });
    connect(ui->pushButton_close, &CustomPushButton::clicked, [=](){
        if(m_pOcrThread->isRunning()) {
            m_pOcrThread->releaseThread();
        }
        this->deleteLater();
    });
    connect(ui->pushButton_copySelect, &CustomPushButton::clicked, [=](){
        QString text = ui->textEdit->textCursor().selectedText().trimmed();
        if (text.isEmpty()) {
            DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
            m_pToolTip->showMBox(ui->frame, tr("请选中需要复制的文本"), QPoint(DB_ApplicationScale::getScaleSize(720),
                                                                     DB_ApplicationScale::getScaleSize(740)));
            return;
        }
        this->copyText(text);
        DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
        m_pToolTip->showMBox(ui->frame, tr("复制完成"), QPoint(DB_ApplicationScale::getScaleSize(720),
                                                           DB_ApplicationScale::getScaleSize(740)));
    });
    connect(ui->pushButton_copyAll, &CustomPushButton::clicked, [=](){
        QString text = ui->textEdit->toPlainText().trimmed();
        if (text.isEmpty()) {
            DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
            m_pToolTip->showMBox(ui->frame, tr("未有文本"), QPoint(DB_ApplicationScale::getScaleSize(820),
                                                               DB_ApplicationScale::getScaleSize(740)));
            return;
        }
        this->copyText(text);
        DB_MBoxToolTip *m_pToolTip = new DB_MBoxToolTip(this);
        m_pToolTip->showMBox(ui->frame, tr("复制完成"), QPoint(DB_ApplicationScale::getScaleSize(820),
                                                           DB_ApplicationScale::getScaleSize(740)));
    });
}

void OCRWidget::copyText(const QString &text)
{
    QClipboard *clipboard = QApplication::clipboard();   //获取系统剪贴板指针
    clipboard->setText(text);                     //设置剪贴板内容
    return;
}
