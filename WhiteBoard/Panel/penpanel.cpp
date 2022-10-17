#include "penpanel.h"
#include "ui_penpanel.h"
#include <QDebug>
PenPanel::PenPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PenPanel)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    this->initWidget();

}

PenPanel::~PenPanel()
{
    delete ui;
}

void PenPanel::show()
{
    QWidget::show();
    this->raise();
}

void PenPanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

void PenPanel::resizeWidget()
{
#if 1
    /*画笔面板*/
    QSize size = Public_Function::getScaleSize(QSize(564, 369));
    this->setFixedSize(size);
    ui->verticalLayout->setAlignment(ui->label_line_2, Qt::AlignCenter);
    ui->verticalLayout->setAlignment(ui->label_line_3, Qt::AlignCenter);
    ui->horizontalLayout->setContentsMargins(Public_Function::getScaleSize(20), Public_Function::getScaleSize(10),
                                               Public_Function::getScaleSize(16), Public_Function::getScaleSize(10));
    ui->horizontalLayout_2->setContentsMargins(Public_Function::getScaleSize(26), 0, 0, 0);
    ui->horizontalLayout_2->setSpacing(Public_Function::getScaleSize(16));
    ui->horizontalLayout_3->setContentsMargins(Public_Function::getScaleSize(33), 0, 0, 0);
    ui->horizontalLayout_3->setSpacing(Public_Function::getScaleSize(22));

    ui->horizontalLayout_14->setContentsMargins(Public_Function::getScaleSize(26), 0, 0, 0);
    ui->horizontalLayout_14->setSpacing(Public_Function::getScaleSize(16));
    ui->horizontalLayout_13->setContentsMargins(Public_Function::getScaleSize(33), 0, 0, 0);
    ui->horizontalLayout_13->setSpacing(Public_Function::getScaleSize(22));

    ui->horizontalLayout_16->setContentsMargins(Public_Function::getScaleSize(26), 0, 0, 0);
    ui->horizontalLayout_16->setSpacing(Public_Function::getScaleSize(16));
    ui->horizontalLayout_15->setContentsMargins(Public_Function::getScaleSize(33), 0, 0, 0);
    ui->horizontalLayout_15->setSpacing(Public_Function::getScaleSize(22));

    ui->horizontalLayout_18->setContentsMargins(Public_Function::getScaleSize(26), 0, 0, 0);
    ui->horizontalLayout_18->setSpacing(Public_Function::getScaleSize(16));
    ui->horizontalLayout_17->setContentsMargins(Public_Function::getScaleSize(33), 0, 0, 0);
    ui->horizontalLayout_17->setSpacing(Public_Function::getScaleSize(22));
    size = Public_Function::getScaleSize(QSize(28, 28));
    ui->pPenPanelLock->setFixedSize(size);

    size = Public_Function::getScaleSize(QSize(100, 82));
    ui->fountainPen->mSetRoundSize(size);
    ui->fountainPen->msetTextAndPixmap(tr("钢笔"),QPixmap(":/images/pen/bichu3@2x.png"));
    ui->softPen->mSetRoundSize(size);
    ui->softPen->msetTextAndPixmap(tr("软笔"),QPixmap(":/images/pen/bichu4@2x.png"));
    ui->nitePen->mSetRoundSize(size);
    ui->nitePen->msetTextAndPixmap(tr("荧光笔"),QPixmap(":/images/pen/bichu5@2x.png"));
    ui->patternPen->mSetRoundSize(size);
    ui->patternPen->msetTextAndPixmap(tr("图案笔"),QPixmap(":/images/pen/bichu7@2x.png"));

    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pPenColor1->setFixedSize(size);
    ui->pPenColor2->setFixedSize(size);
    ui->pPenColor3->setFixedSize(size);
    ui->pPenColor4->setFixedSize(size);
    ui->pPenColor5->setFixedSize(size);
    ui->pPenColor6->setFixedSize(size);
    ui->pPenColor7->setFixedSize(size);
    ui->pPenCustomColor->setFixedSize(size);

    ui->softPenColor1->setFixedSize(size);
    ui->softPenColor2->setFixedSize(size);
    ui->softPenColor3->setFixedSize(size);
    ui->softPenColor4->setFixedSize(size);
    ui->softPenColor5->setFixedSize(size);
    ui->softPenColor6->setFixedSize(size);
    ui->softPenColor7->setFixedSize(size);
    ui->softPenCustomColor->setFixedSize(size);

    ui->nitePenColor1->setFixedSize(size);
    ui->nitePenColor2->setFixedSize(size);
    ui->nitePenColor3->setFixedSize(size);
    ui->nitePenColor4->setFixedSize(size);
    ui->nitePenColor5->setFixedSize(size);
    ui->nitePenColor6->setFixedSize(size);
    ui->nitePenColor7->setFixedSize(size);
    ui->nitePenCustomColor->setFixedSize(size);

    ui->patternPenColor1->setFixedSize(size);
    ui->patternPenColor2->setFixedSize(size);
    ui->patternPenColor3->setFixedSize(size);
    ui->patternPenColor4->setFixedSize(size);
    ui->patternPenColor5->setFixedSize(size);
    ui->patternPenColor6->setFixedSize(size);
    ui->patternPenColor7->setFixedSize(size);
    ui->patternPenCustomColor->setFixedSize(size);


    size = Public_Function::getScaleSize(QSize(36, 36));
    ui->pPenColor1->mSetIconSize(size);
    ui->pPenColor2->mSetIconSize(size);
    ui->pPenColor3->mSetIconSize(size);
    ui->pPenColor4->mSetIconSize(size);
    ui->pPenColor5->mSetIconSize(size);
    ui->pPenColor6->mSetIconSize(size);
    ui->pPenColor7->mSetIconSize(size);
    ui->pPenCustomColor->mSetIconSize(size);

    ui->softPenColor1->mSetIconSize(size);
    ui->softPenColor2->mSetIconSize(size);
    ui->softPenColor3->mSetIconSize(size);
    ui->softPenColor4->mSetIconSize(size);
    ui->softPenColor5->mSetIconSize(size);
    ui->softPenColor6->mSetIconSize(size);
    ui->softPenColor7->mSetIconSize(size);
    ui->softPenCustomColor->mSetIconSize(size);

    ui->nitePenColor1->mSetIconSize(size);
    ui->nitePenColor2->mSetIconSize(size);
    ui->nitePenColor3->mSetIconSize(size);
    ui->nitePenColor4->mSetIconSize(size);
    ui->nitePenColor5->mSetIconSize(size);
    ui->nitePenColor6->mSetIconSize(size);
    ui->nitePenColor7->mSetIconSize(size);
    ui->nitePenCustomColor->mSetIconSize(size);

    ui->patternPenColor1->mSetIconSize(size);
    ui->patternPenColor2->mSetIconSize(size);
    ui->patternPenColor3->mSetIconSize(size);
    ui->patternPenColor4->mSetIconSize(size);
    ui->patternPenColor5->mSetIconSize(size);
    ui->patternPenColor6->mSetIconSize(size);
    ui->patternPenColor7->mSetIconSize(size);
    ui->patternPenCustomColor->mSetIconSize(size);

    size = Public_Function::getScaleSize(QSize(6, 6));
    ui->pPenSize1->mSetRoundSize(size);
    ui->softPenSize1->mSetRoundSize(size);
    ui->nitePenSize1->mSetRoundSize(size);
    ui->patternPenSize1->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(26, 26));
    ui->pPenSize1->setFixedSize(size);
    ui->softPenSize1->setFixedSize(size);
    ui->nitePenSize1->setFixedSize(size);
    ui->patternPenSize1->setFixedSize(size);

    size = Public_Function::getScaleSize(QSize(14, 14));
    ui->pPenSize2->mSetRoundSize(size);
    ui->softPenSize2->mSetRoundSize(size);
    ui->nitePenSize2->mSetRoundSize(size);
    ui->patternPenSize2->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(34, 34));
    ui->pPenSize2->setFixedSize(size);
    ui->softPenSize2->setFixedSize(size);
    ui->nitePenSize2->setFixedSize(size);
    ui->patternPenSize2->setFixedSize(size);

    size = Public_Function::getScaleSize(QSize(22, 22));
    ui->pPenSize3->mSetRoundSize(size);
    ui->softPenSize3->mSetRoundSize(size);
    ui->nitePenSize3->mSetRoundSize(size);
    ui->patternPenSize3->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(42, 42));
    ui->pPenSize3->setFixedSize(size);
    ui->softPenSize3->setFixedSize(size);
    ui->nitePenSize3->setFixedSize(size);
    ui->patternPenSize3->setFixedSize(size);

    size = Public_Function::getScaleSize(QSize(30, 30));
    ui->pPenSize4->mSetRoundSize(size);
    ui->softPenSize4->mSetRoundSize(size);
    ui->nitePenSize4->mSetRoundSize(size);
    ui->patternPenSize4->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(50, 50));
    ui->pPenSize4->setFixedSize(size);
    ui->softPenSize4->setFixedSize(size);
    ui->nitePenSize4->setFixedSize(size);
    ui->patternPenSize4->setFixedSize(size);

    size = Public_Function::getScaleSize(QSize(38, 38));
    ui->pPenSize5->mSetRoundSize(size);
    ui->softPenSize5->mSetRoundSize(size);
    ui->nitePenSize5->mSetRoundSize(size);
    ui->patternPenSize5->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(58, 58));
    ui->pPenSize5->setFixedSize(size);
    ui->softPenSize5->setFixedSize(size);
    ui->nitePenSize5->setFixedSize(size);
    ui->patternPenSize5->setFixedSize(size);

    size = Public_Function::getScaleSize(QSize(46, 46));
    ui->pPenSize6->mSetRoundSize(size);
    ui->softPenSize6->mSetRoundSize(size);
    ui->nitePenSize6->mSetRoundSize(size);
    ui->patternPenSize6->mSetRoundSize(size);
    size = Public_Function::getScaleSize(QSize(66, 66));
    ui->pPenSize6->setFixedSize(size);
    ui->softPenSize6->setFixedSize(size);
    ui->nitePenSize6->setFixedSize(size);
    ui->patternPenSize6->setFixedSize(size);

    size = Public_Function::getScaleSize(QSize(526, 1));
    ui->label_line_2->setFixedSize(size);
    ui->label_line_3->setFixedSize(size);
    ui->label_line_4->setFixedSize(size);
    ui->label_line_6->setFixedSize(size);
    ui->label_line_7->setFixedSize(size);
    ui->label_line_8->setFixedSize(size);
#endif
}

bool PenPanel::isLocked()
{
    return ui->pPenPanelLock->isChecked();
}

void PenPanel::setCheckedColor(int id)
{
    ui->fountainPen->setChecked(true);
    QAbstractButton *button = m_PenColorGroup->button(id);
    if (nullptr != button)
    {
        button->setChecked(true);
        this->onColorBtnGroupToggled(button);
    }
}

void PenPanel::setCheckedSize(int id)
{
    QAbstractButton *button = m_PenSizeGroup->button(id);
    if (nullptr != button)
    {
        button->setChecked(true);
        this->onSizeBtnGroupToggled(button);
    }
}

void PenPanel::setLockBtnVisable(bool visable)
{
    ui->pPenPanelLock->setVisible(visable);
}

bool PenPanel::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton && ui->pPenPanelLock->isVisible()) {
            m_MousePressed = true;
            m_LastPoint = mouseEvent->pos();
        }
    }else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (m_MousePressed) {
            if (!ui->pPenPanelLock->isChecked())
                ui->pPenPanelLock->setChecked(true);
            QPoint pt = mouseEvent->globalPos();
            int x = pt.x() - m_LastPoint.x();
            int y = pt.y() - m_LastPoint.y();
            QWidget *parent = (QWidget *)this->parent();
            x = x < 0 ? 0 : ((x + this->width()) > parent->width() ? (parent->width() - this->width()) : x);
            y = y < 0 ? 0 : ((y + this->height()) > parent->height() ? (parent->height() - this->height()) : y);
            this->move(x, y);
        }
    }else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton)
            m_MousePressed = false;
    }
    return QWidget::eventFilter(watched, event);
}

void PenPanel::hideOtherPen()
{
    ui->softPen->hide();
    ui->nitePen->hide();
    ui->patternPen->hide();
}

void PenPanel::isMiniBoard(bool bo)
{
    miniboard =bo;
}

void PenPanel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    QColor color(135, 135, 135);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    int border = 6;
    int alpha;
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(border - i, border - i),
                           QPoint(this->width() - (border - i),
                            this->height() - (border - i)));
        QPainterPath path;
        int radius = Public_Function::getScaleSize(12);
        path = Public_Function::getRoundRectPath(rect, radius);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }
        switch(i)
        {
        case 0: alpha = 80; break;
        case 1: alpha = 50; break;
        case 2: alpha = 30; break;
        case 3: alpha = 15; break;
        case 4: alpha = 10; break;
        case 5: alpha = 7; break;
        }
        color.setAlpha(alpha);
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void PenPanel::initWidget()
{
    ui->verticalLayoutWidget_3->hide();
    this->setLayout(ui->verticalLayout);

    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setDocumentMode(true);
    ui->tabWidget->setCurrentWidget(ui->fountainPentab);

    /*笔的类型*/
    m_PenStyleGroup = new QButtonGroup(this);
    m_PenStyleGroup->setExclusive(true);
    m_PenStyleGroup->addButton(ui->fountainPen, 1);
    m_PenStyleGroup->addButton(ui->softPen, 2);
    m_PenStyleGroup->addButton(ui->nitePen, 3);
    m_PenStyleGroup->addButton(ui->patternPen, 4);
    connect(m_PenStyleGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onStyleBtnGroupToggled);
    this->onStyleBtnGroupToggled(m_PenStyleGroup->button(1));

    /**************钢笔***************/
    ui->pPenColor1->mSetIconColor(Qt::white);
    ui->pPenColor2->mSetIconColor(Qt::black);
    ui->pPenColor3->mSetIconColor(QColor(247,56,89));
    ui->pPenColor4->mSetIconColor(QColor(255,168,0));
    ui->pPenColor5->mSetIconColor(QColor(255,222,41));
    ui->pPenColor6->mSetIconColor(QColor(172,115,255));
    ui->pPenColor7->mSetIconColor(QColor(0,184,169));
    ui->pPenCustomColor->mSetIconColor(QColor(47,150,255));
    ui->pPenCustomColor->hide();
    connect(ui->pPenPanelLock, &PushButton_Basic::toggled,this, [=](bool checked){ if (!checked) this->hide(); });

    m_PenColorGroup = new QButtonGroup(this);
    m_PenColorGroup->setExclusive(true);
    m_PenColorGroup->addButton(ui->pPenColor1, 1);
    m_PenColorGroup->addButton(ui->pPenColor2, 2);
    m_PenColorGroup->addButton(ui->pPenColor3, 3);
    m_PenColorGroup->addButton(ui->pPenColor4, 4);
    m_PenColorGroup->addButton(ui->pPenColor5, 5);
    m_PenColorGroup->addButton(ui->pPenColor6, 6);
    m_PenColorGroup->addButton(ui->pPenColor7, 7);
    m_PenColorGroup->addButton(ui->pPenCustomColor);
    connect(m_PenColorGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onColorBtnGroupToggled);
    ui->pPenColor1->setChecked(true);

    m_PenSizeGroup = new QButtonGroup(this);
    m_PenSizeGroup->setExclusive(true);
    m_PenSizeGroup->addButton(ui->pPenSize1, 1);
    m_PenSizeGroup->addButton(ui->pPenSize2, 2);
    m_PenSizeGroup->addButton(ui->pPenSize3, 3);
    m_PenSizeGroup->addButton(ui->pPenSize4, 4);
    m_PenSizeGroup->addButton(ui->pPenSize5, 5);
    m_PenSizeGroup->addButton(ui->pPenSize6, 6);
    connect(m_PenSizeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onSizeBtnGroupToggled);
    ui->pPenSize2->setChecked(true);

   /**************软笔***************/
   ui->softPenColor1->mSetIconColor(Qt::white);
   ui->softPenColor2->mSetIconColor(Qt::black);
   ui->softPenColor3->mSetIconColor(QColor(247,56,89));
   ui->softPenColor4->mSetIconColor(QColor(255,168,0));
   ui->softPenColor5->mSetIconColor(QColor(255,222,41));
   ui->softPenColor6->mSetIconColor(QColor(172,115,255));
   ui->softPenColor7->mSetIconColor(QColor(0,184,169));
   ui->softPenCustomColor->mSetIconColor(QColor(47,150,255));
   ui->softPenCustomColor->hide();
   ui->softPenColor1->setChecked(true);

   softPenColorGroup = new QButtonGroup(this);
   softPenColorGroup->setExclusive(true);
   softPenColorGroup->addButton(ui->softPenColor1, 1);
   softPenColorGroup->addButton(ui->softPenColor2, 2);
   softPenColorGroup->addButton(ui->softPenColor3, 3);
   softPenColorGroup->addButton(ui->softPenColor4, 4);
   softPenColorGroup->addButton(ui->softPenColor5, 5);
   softPenColorGroup->addButton(ui->softPenColor6, 6);
   softPenColorGroup->addButton(ui->softPenColor7, 7);
   softPenColorGroup->addButton(ui->softPenCustomColor);
   connect(softPenColorGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onColorBtnGroupToggled);

   softPenSizeGroup = new QButtonGroup(this);
   softPenSizeGroup->setExclusive(true);
   softPenSizeGroup->addButton(ui->softPenSize1, 1);
   softPenSizeGroup->addButton(ui->softPenSize2, 2);
   softPenSizeGroup->addButton(ui->softPenSize3, 3);
   softPenSizeGroup->addButton(ui->softPenSize4, 4);
   softPenSizeGroup->addButton(ui->softPenSize5, 5);
   softPenSizeGroup->addButton(ui->softPenSize6, 6);
   ui->softPenSize2->setChecked(true);
   connect(softPenSizeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onSizeBtnGroupToggled);

   /**************荧光笔***************/
   ui->nitePenColor1->mSetIconColor(Qt::white);
   ui->nitePenColor2->mSetIconColor(Qt::black);
   ui->nitePenColor3->mSetIconColor(QColor(247,56,89));
   ui->nitePenColor4->mSetIconColor(QColor(255,168,0));
   ui->nitePenColor5->mSetIconColor(QColor(255,222,41));
   ui->nitePenColor6->mSetIconColor(QColor(172,115,255));
   ui->nitePenColor7->mSetIconColor(QColor(0,184,169));
   ui->nitePenCustomColor->mSetIconColor(QColor(47,150,255));
   ui->nitePenCustomColor->hide();
   ui->nitePenColor4->setChecked(true);

   nitePenColorGroup = new QButtonGroup(this);
   nitePenColorGroup->setExclusive(true);
   nitePenColorGroup->addButton(ui->nitePenColor1, 1);
   nitePenColorGroup->addButton(ui->nitePenColor2, 2);
   nitePenColorGroup->addButton(ui->nitePenColor3, 3);
   nitePenColorGroup->addButton(ui->nitePenColor4, 4);
   nitePenColorGroup->addButton(ui->nitePenColor5, 5);
   nitePenColorGroup->addButton(ui->nitePenColor6, 6);
   nitePenColorGroup->addButton(ui->nitePenColor7, 7);
   nitePenColorGroup->addButton(ui->nitePenCustomColor);
   connect(nitePenColorGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onColorBtnGroupToggled);

   nitePenSizeGroup = new QButtonGroup(this);
   nitePenSizeGroup->setExclusive(true);
   nitePenSizeGroup->addButton(ui->nitePenSize1, 1);
   nitePenSizeGroup->addButton(ui->nitePenSize2, 2);
   nitePenSizeGroup->addButton(ui->nitePenSize3, 3);
   nitePenSizeGroup->addButton(ui->nitePenSize4, 4);
   nitePenSizeGroup->addButton(ui->nitePenSize5, 5);
   nitePenSizeGroup->addButton(ui->nitePenSize6, 6);
   ui->nitePenSize4->setChecked(true);
   connect(nitePenSizeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onSizeBtnGroupToggled);


   /**************图案笔***************/
   ui->patternPenColor1->setPixmap(QPixmap(":/images/pen/smail@2x.png"));
   ui->patternPenColor2->setPixmap(QPixmap(":/images/pen/star@2x.png"));
   ui->patternPenColor3->setPixmap(QPixmap(":/images/pen/plaint@2x.png"));
   ui->patternPenColor4->setPixmap(QPixmap(":/images/pen/dui@2x.png"));
   ui->patternPenColor5->setPixmap(QPixmap(":/images/pen/cuo@2x.png"));
   ui->patternPenColor6->setPixmap(QPixmap(":/images/pen/doubt@2x.png"));
   ui->patternPenColor7->setPixmap(QPixmap(":/images/pen/red@2x.png"));
   ui->patternPenCustomColor->setPixmap(QPixmap(":/images/pen/flower@2x.png"));
   ui->patternPenColor3->setChecked(true);

   patternPenColorGroup = new QButtonGroup(this);
   patternPenColorGroup->setExclusive(true);
   patternPenColorGroup->addButton(ui->patternPenColor1, 1);
   patternPenColorGroup->addButton(ui->patternPenColor2, 2);
   patternPenColorGroup->addButton(ui->patternPenColor3, 3);
   patternPenColorGroup->addButton(ui->patternPenColor4, 4);
   patternPenColorGroup->addButton(ui->patternPenColor5, 5);
   patternPenColorGroup->addButton(ui->patternPenColor6, 6);
   patternPenColorGroup->addButton(ui->patternPenColor7, 7);
   patternPenColorGroup->addButton(ui->patternPenCustomColor);
   connect(patternPenColorGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onPixmapBtnGroupToggled);
   ui->patternPenColor3->setChecked(true);

   patternPenSizeGroup = new QButtonGroup(this);
   patternPenSizeGroup->setExclusive(true);
   patternPenSizeGroup->addButton(ui->patternPenSize1, 1);
   patternPenSizeGroup->addButton(ui->patternPenSize2, 2);
   patternPenSizeGroup->addButton(ui->patternPenSize3, 3);
   patternPenSizeGroup->addButton(ui->patternPenSize4, 4);
   patternPenSizeGroup->addButton(ui->patternPenSize5, 5);
   patternPenSizeGroup->addButton(ui->patternPenSize6, 6);
   connect(patternPenSizeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&PenPanel::onPixmapSizeBtnGroupToggled);
   ui->patternPenSize4->setChecked(true);
}

void PenPanel::onPixmapBtnGroupToggled(QAbstractButton *button)
{
    QString str =QString();
    if (ui->patternPenColor1 == button) {
        str = QString(":/images/pen/smail@2x.png");
    }else if (ui->patternPenColor2 == button) {
        str = QString(":/images/pen/star@2x.png");
    }else if (ui->patternPenColor3 == button) {
        str = QString(":/images/pen/plaint@2x.png");
    }else if (ui->patternPenColor4 == button) {
        str = QString(":/images/pen/dui@2x.png");
    }else if (ui->patternPenColor5 == button) {
        str = QString(":/images/pen/cuo@2x.png");
    }else if (ui->patternPenColor6 == button) {
        str = QString(":/images/pen/doubt@2x.png");
    }else if (ui->patternPenColor7 == button) {
        str = QString(":/images/pen/red@2x.png");
    }else if (ui->patternPenCustomColor == button) {
        str = QString(":/images/pen/flower@2x.png");
    }
    if(g_PenType == PenType::TuAnBi)g_TuAnBi.str =str;
}

void PenPanel::onPixmapSizeBtnGroupToggled(QAbstractButton *button)
{
    if (ui->patternPenSize1 == button) {
        g_TuAnBi.PenSize = Public_Function::getScaleSize(50);
    }else if (ui->patternPenSize2 == button) {
        g_TuAnBi.PenSize = Public_Function::getScaleSize(60);;
    }else if (ui->patternPenSize3 == button) {
        g_TuAnBi.PenSize = Public_Function::getScaleSize(70);;
    }else if (ui->patternPenSize4 == button) {
        g_TuAnBi.PenSize = Public_Function::getScaleSize(80);;
    }else if (ui->patternPenSize5 == button) {
        g_TuAnBi.PenSize = Public_Function::getScaleSize(90);;
    }else if (ui->patternPenSize6 == button) {
        g_TuAnBi.PenSize = Public_Function::getScaleSize(100);;
    };
}

void PenPanel::onColorBtnGroupToggled(QAbstractButton *button)
{
    QColor color;
    if (ui->pPenColor1 == button) {
        color = ui->pPenColor1->mGetColor();
    }else if (ui->pPenColor2 == button) {
        color = ui->pPenColor2->mGetColor();
    }else if (ui->pPenColor3 == button) {
        color = ui->pPenColor3->mGetColor();
    }else if (ui->pPenColor4 == button) {
        color = ui->pPenColor4->mGetColor();
    }else if (ui->pPenColor5 == button) {
        color = ui->pPenColor5->mGetColor();
    }else if (ui->pPenColor6 == button) {
        color = ui->pPenColor6->mGetColor();
    }else if (ui->pPenColor7 == button) {
        color = ui->pPenColor7->mGetColor();
    }else if (ui->pPenCustomColor == button) {
        color = ui->pPenCustomColor->mGetColor();
    }

    else if (ui->softPenColor1 == button) {
        color = ui->softPenColor1->mGetColor();
    }else if (ui->softPenColor2 == button) {
        color = ui->softPenColor2->mGetColor();
    }else if (ui->softPenColor3 == button) {
        color = ui->softPenColor3->mGetColor();
    }else if (ui->softPenColor4 == button) {
        color = ui->softPenColor4->mGetColor();
    }else if (ui->softPenColor5 == button) {
        color = ui->softPenColor5->mGetColor();
    }else if (ui->softPenColor6 == button) {
        color = ui->softPenColor6->mGetColor();
    }else if (ui->softPenColor7 == button) {
        color = ui->softPenColor7->mGetColor();
    }else if (ui->softPenCustomColor == button) {
        color = ui->softPenCustomColor->mGetColor();
    }

    else if (ui->nitePenColor1 == button) {
        color = ui->nitePenColor1->mGetColor();
    }else if (ui->nitePenColor2 == button) {
        color = ui->nitePenColor2->mGetColor();
    }else if (ui->nitePenColor3 == button) {
        color = ui->nitePenColor3->mGetColor();
    }else if (ui->nitePenColor4 == button) {
        color = ui->nitePenColor4->mGetColor();
    }else if (ui->nitePenColor5 == button) {
        color = ui->nitePenColor5->mGetColor();
    }else if (ui->nitePenColor6 == button) {
        color = ui->nitePenColor6->mGetColor();
    }else if (ui->nitePenColor7 == button) {
        color = ui->nitePenColor7->mGetColor();
    }else if (ui->nitePenCustomColor == button) {
        color = ui->nitePenCustomColor->mGetColor();
    };

    if(!miniboard)
    {
        if(g_PenType == PenType::GangBi)g_GangBi.penColor =color;
        else if(g_PenType == PenType::RuanBi)g_RuanBi.penColor =color;
        else if (g_PenType == PenType::YingGuangBi)g_YingGuangBi.penColor =QColor(color.red(),color.green(),color.blue(),125);
    }
    else
    {
        emit penColorChanged(color);
    }
}

void PenPanel::onSizeBtnGroupToggled(QAbstractButton *button)
{
    int size =2;
    if (ui->pPenSize1 == button) {
        size = Public_Function::getScaleSize(2);
    }else if (ui->pPenSize2 == button) {
        size = Public_Function::getScaleSize(5);
    }else if (ui->pPenSize3 == button) {
        size = Public_Function::getScaleSize(8);
    }else if (ui->pPenSize4 == button) {
        size = Public_Function::getScaleSize(11);
    }else if (ui->pPenSize5 == button) {
        size = Public_Function::getScaleSize(14);
    }else if (ui->pPenSize6 == button) {
        size = Public_Function::getScaleSize(17);
    }

    else if (ui->softPenSize1 == button) {
        size = Public_Function::getScaleSize(2);
    }else if (ui->softPenSize2 == button) {
        size = Public_Function::getScaleSize(5);;
    }else if (ui->softPenSize3 == button) {
        size = Public_Function::getScaleSize(8);;
    }else if (ui->softPenSize4 == button) {
        size = Public_Function::getScaleSize(11);;
    }else if (ui->softPenSize5 == button) {
        size = Public_Function::getScaleSize(14);;
    }else if (ui->softPenSize6 == button) {
        size = Public_Function::getScaleSize(17);;
    }

    else if (ui->nitePenSize1 == button) {
        size = Public_Function::getScaleSize(4);
    }else if (ui->nitePenSize2 == button) {
        size = Public_Function::getScaleSize(7);;
    }else if (ui->nitePenSize3 == button) {
        size = Public_Function::getScaleSize(10);;
    }else if (ui->nitePenSize4 == button) {
        size = Public_Function::getScaleSize(13);;
    }else if (ui->nitePenSize5 == button) {
        size = Public_Function::getScaleSize(16);;
    }else if (ui->nitePenSize6 == button) {
        size = Public_Function::getScaleSize(19);;
    };

    if(!miniboard)
    {
        if(g_PenType == PenType::GangBi)g_GangBi.PenSize =size;
        else if(g_PenType == PenType::RuanBi)g_RuanBi.PenSize =size;
        else if (g_PenType == PenType::YingGuangBi)g_YingGuangBi.PenSize =size;
    }
    else
    {
        emit penSizeChanged(size);
    }
}

void PenPanel::onStyleBtnGroupToggled(QAbstractButton *button)
{
    if (ui->fountainPen == button)
    {
        ui->tabWidget->setCurrentWidget(ui->fountainPentab);
        g_PenType =PenType::GangBi;
    }
    else if (ui->softPen == button)
    {
        ui->tabWidget->setCurrentWidget(ui->softPentab);
        g_PenType =PenType::RuanBi;
    }
    else if (ui->nitePen == button)
    {
        ui->tabWidget->setCurrentWidget(ui->nitePentab);
        g_PenType =PenType::YingGuangBi;
    }
    else if (ui->patternPen == button)
    {
        ui->tabWidget->setCurrentWidget(ui->patternPentab);
        g_PenType=PenType::TuAnBi;
    }
}

void PenPanel::updateLanguage()
{
    ui->label_penPanelTitle->setText(tr("笔触属性"));
    ui->fountainPen->msetTextAndPixmap(tr("钢笔"),QPixmap(":/images/pen/bichu3@2x.png"));
    ui->softPen->msetTextAndPixmap(tr("软笔"),QPixmap(":/images/pen/bichu4@2x.png"));
    ui->nitePen->msetTextAndPixmap(tr("荧光笔"),QPixmap(":/images/pen/bichu5@2x.png"));
    ui->patternPen->msetTextAndPixmap(tr("图案笔"),QPixmap(":/images/pen/bichu7@2x.png"));

}
