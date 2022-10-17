#include "itemtool.h"
#include "ui_itemtool.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QFrame>
#include "Public/public_function.h"
#include <QtDebug>

ItemTool::ItemTool(ToolFlags flags, bool isAdjust, QWidget *parent) :
    m_pToolFlags(flags),
    QWidget(parent),
    ui(new Ui::ItemTool)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_AcceptTouchEvents,true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(Qt::transparent));
    this->setPalette(palette);
    this->setMouseTracking(true);
    if (isAdjust)
        ui->pAdjust->setChecked(true);
    this->initWidget();
    this->resize();
}

ItemTool::~ItemTool()
{
    delete ui;
}

void ItemTool::updateFlag(ToolFlags flags)
{
    m_pToolFlags = flags;

    m_pToolNum = 9;
    if ((m_pToolFlags & ToolFlag::RM_Border) == ToolFlag::RM_Border) {
        ui->pBorder->hide();
        m_pToolNum--;
    }else
        ui->pBorder->show();
    ui->pBorder->setChecked(false);
    if ((m_pToolFlags & ToolFlag::RM_FillColor) == ToolFlag::RM_FillColor) {
        ui->pFillColor->hide();
        m_pToolNum--;
    }
    else
         ui->pFillColor->show();
    ui->pFillColor->setChecked(false);
    if ((m_pToolFlags & ToolFlag::RM_Flip) == ToolFlag::RM_Flip) {
        ui->pFlip->hide();
        m_pToolNum--;
    }
    else
         ui->pFlip->show();
    ui->pFlip->setChecked(false);
    if ((m_pToolFlags & ToolFlag::RM_Mirror) == ToolFlag::RM_Mirror) {
        ui->pMirror->hide();
        m_pToolNum--;
    }else
        ui->pMirror->show();
    ui->pMirror->setChecked(false);
    if ((m_pToolFlags & ToolFlag::RM_Clone) == ToolFlag::RM_Clone) {
        ui->pClone->hide();
        m_pToolNum--;
    }else
        ui->pClone->show();
    ui->pClone->setChecked(false);
    if ((m_pToolFlags & ToolFlag::RM_Bottom) == ToolFlag::RM_Bottom) {
        ui->pBottom->hide();
        m_pToolNum--;
    }else
        ui->pBottom->show();
    if ((m_pToolFlags & ToolFlag::RM_Top) == ToolFlag::RM_Top) {
        ui->pTop->hide();
        m_pToolNum--;
    }else
        ui->pTop->show();
    if ((m_pToolFlags & ToolFlag::RM_Delete) == ToolFlag::RM_Delete) {
        ui->pDelete->hide();
        m_pToolNum--;
    }else
        ui->pDelete->show();
    if ((m_pToolFlags & ToolFlag::RM_Adjust) == ToolFlag::RM_Adjust) {
        ui->pAdjust->hide();
        m_pToolNum--;
    }else
        ui->pAdjust->show();
    this->resize();
}

bool ItemTool::isClone()
{
    return ui->pClone->isChecked();
}

bool ItemTool::isAdjust()
{
    return ui->pAdjust->isChecked();
}

void ItemTool::clearCheck(QAbstractButton *button)
{
    if (ui->pBorder->isChecked() && ui->pBorder != button)
        ui->pBorder->setChecked(false);
    if (ui->pFillColor->isChecked() && ui->pFillColor != button)
        ui->pFillColor->setChecked(false);
    if (ui->pFlip->isChecked() && ui->pFlip != button)
        ui->pFlip->setChecked(false);
    if (ui->pMirror->isChecked() && ui->pMirror != button)
        ui->pMirror->setChecked(false);
}

void ItemTool::updateLanguage()
{
     ui->pBorder->mSetText(tr("边框"));
     ui->pFillColor->mSetText(tr("填充"));
     ui->pFlip->mSetText(tr("翻转"));
     ui->pMirror->mSetText(tr("镜像"));
     ui->pClone->mSetText(tr("克隆"));
     ui->pTop->mSetText(tr("置顶"));
     ui->pBottom->mSetText(tr("置底"));
     ui->pDelete->mSetText(tr("删除"));
     ui->pAdjust->mSetText(tr("调节"));



}

bool ItemTool::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        {
            return true;
            break;
        }
        case QEvent::TouchUpdate:
        {
            return true;
            break;
        }
        case QEvent::TouchEnd:
        {
            QTouchEvent* ev =static_cast<QTouchEvent*>(event);
            QPoint dot =ev->touchPoints().at(0).pos().toPoint();
            if(ui->pBorder->geometry().contains(dot))
             {
               ui->pBorder->setChecked(true);
             }
             else if(ui->pFillColor->geometry().contains(dot))
             {
               ui->pFillColor->setChecked(true);
             }
             else if(ui->pClone->geometry().contains(dot))
             {
                if(!ui->pClone->isChecked())
                    ui->pClone->setChecked(true);
                else
                    ui->pClone->setChecked(false);
             }
             else if(ui->pBottom->geometry().contains(dot))
             {
                emit this->toBottom();
             }
             else if(ui->pTop->geometry().contains(dot))
             {
                emit this->toTop();
             }
             else if(ui->pDelete->geometry().contains(dot))
             {
                emit this->toDelete();
             }
             else if(ui->pMirror->geometry().contains(dot))
             {
                if(!ui->pMirror->isChecked())
                    ui->pMirror->setChecked(true);
                else
                    ui->pMirror->setChecked(false);
                bool checked =ui->pMirror->isChecked();
                if (checked)
                    this->clearCheck(ui->pMirror);
                emit this->showMirrorPanel(checked, ui->pMirror->pos());
             }
             else if(ui->pFlip->geometry().contains(dot))
             {
                if(!ui->pFlip->isChecked())
                    ui->pFlip->setChecked(true);
                else
                    ui->pFlip->setChecked(false);
                bool checked =ui->pFlip->isChecked();
                if (checked)
                    this->clearCheck(ui->pFlip);
                emit this->showFlipPanel(checked, ui->pFlip->pos());
             }
             return true;
             break;
        }
        default:
        {
            break;
        }
    }
    return QWidget::event(event);
}

void ItemTool::initWidget()
{
    this->setLayout(ui->horizontalLayout_5);
    /* 主工具条 */
    ui->horizontalLayoutWidget->hide();
    ui->frame->setLayout(ui->horizontalLayout);
    ui->horizontalLayout->setSpacing(0);
    ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    ui->frame->mSetBackgroudColor(Qt::white);
    ui->pBorder->mSetIcon(QPixmap(":/images/itemToolIcon/frame@2x.png"));
    ui->pBorder->mSetText(tr("边框"));
    ui->pBorder->mSetCheckedBGColor(QColor(238,238,238));
    ui->pBorder->mSetCheckedTextColor(QColor());
    connect(ui->pBorder, &PushButton_2::toggled,this, [=](bool checked) {
        if (checked)
            this->clearCheck(ui->pBorder);
        emit this->showBorderPanel(checked, ui->pBorder->pos());
    });
    ui->pFillColor->mSetIcon(QPixmap(":/images/itemToolIcon/filling@2x.png"));
    ui->pFillColor->mSetText(tr("填充"));
    ui->pFillColor->mSetCheckedBGColor(QColor(238,238,238));
    ui->pFillColor->mSetCheckedTextColor(QColor());
    connect(ui->pFillColor, &PushButton_2::toggled,this, [=](bool checked) {
        if (checked)
            this->clearCheck(ui->pFillColor);
        emit this->showFillColorPanel(checked, ui->pFillColor->pos());
    });
    ui->pFlip->mSetIcon(QPixmap(":/images/itemToolIcon/overturn@2x.png"));
    ui->pFlip->mSetText(tr("翻转"));
    ui->pFlip->mSetCheckedBGColor(QColor(238,238,238));
    ui->pFlip->mSetCheckedTextColor(QColor());
    connect(ui->pFlip, &PushButton_2::toggled,this, [=](bool checked) {
        if (checked)
            this->clearCheck(ui->pFlip);
        emit this->showFlipPanel(checked, ui->pFlip->pos());
    });
    ui->pMirror->mSetIcon(QPixmap(":/images/itemToolIcon/Mirror@2x.png"));
    ui->pMirror->mSetText(tr("镜像"));
    ui->pMirror->mSetCheckedBGColor(QColor(238,238,238));
    ui->pMirror->mSetCheckedTextColor(QColor());
    connect(ui->pMirror, &PushButton_2::toggled, [=](bool checked) {
        if (checked)
            this->clearCheck(ui->pMirror);
        emit this->showMirrorPanel(checked, ui->pMirror->pos());
    });
    ui->pClone->mSetIcon(QPixmap(":/images/itemToolIcon/copy@2x.png"));
    ui->pClone->mSetCheckedIcon(QPixmap(":/images/itemToolIcon/copy2@2x.png"));
    ui->pClone->mSetCheckedBGColor(QColor(20,134,250));
    ui->pClone->mSetCheckedTextColor(Qt::white);
    ui->pClone->mSetText(tr("克隆"));
    //connect(ui->pClone, &PushButton_2::toggled, [=](bool checked){ emit this->toClone(checked); });
    ui->pTop->mSetIcon(QPixmap(":/images/itemToolIcon/top@2x.png"));
    ui->pTop->mSetText(tr("置顶"));
    connect(ui->pTop, &PushButton_2::clicked,this, [=](){ emit this->toTop(); });
    ui->pBottom->mSetIcon(QPixmap(":/images/itemToolIcon/bottom@2x.png"));
    ui->pBottom->mSetText(tr("置底"));
    connect(ui->pBottom, &PushButton_2::clicked,this, [=](){ emit this->toBottom(); });
    ui->pDelete->mSetIcon(QPixmap(":/images/itemToolIcon/delete@2x.png"));
    ui->pDelete->mSetText(tr("删除"));
    connect(ui->pDelete, &PushButton_2::clicked,this, [=](){ emit this->toDelete(); });
    ui->pAdjust->mSetIcon(QPixmap(":/images/itemToolIcon/delete@2x.png"));
    ui->pAdjust->mSetText(tr("调节"));
    ui->pAdjust->mSetCheckedBGColor(QColor(20,134,250));
    ui->pAdjust->mSetCheckedTextColor(Qt::white);
    connect(ui->pAdjust, &PushButton_2::clicked,this, [=](bool checked){ emit this->toAdjust(checked); });

    this->setWindowFlags(Qt::Widget);
    m_pToolNum = 9;
    if ((m_pToolFlags & ToolFlag::RM_Border) == ToolFlag::RM_Border) {
        ui->pBorder->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_FillColor) == ToolFlag::RM_FillColor) {
        ui->pFillColor->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_Flip) == ToolFlag::RM_Flip) {
        ui->pFlip->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_Mirror) == ToolFlag::RM_Mirror) {
        ui->pMirror->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_Clone) == ToolFlag::RM_Clone) {
        ui->pClone->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_Bottom) == ToolFlag::RM_Bottom) {
        ui->pBottom->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_Top) == ToolFlag::RM_Top) {
        ui->pTop->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_Delete) == ToolFlag::RM_Delete) {
        ui->pDelete->hide();
        m_pToolNum--;
    }
    if ((m_pToolFlags & ToolFlag::RM_Adjust) == ToolFlag::RM_Adjust) {
        ui->pAdjust->hide();
        m_pToolNum--;
    }
}

void ItemTool::resize()
{
    /* 主工具条 */
    QSize size = Public_Function::getScaleSize(QSize(Public_Function::getScaleSize(60) * m_pToolNum
                                                     + Public_Function::getScaleSize(50), 82));
    ui->frame->setFixedSize(size);
    int  radius = Public_Function::getScaleSize(12);
    ui->frame->mSetBordRadius(radius, radius, radius, radius);
    ui->frame->mSetBorder(Public_Function::getScaleSize(2));
    size = Public_Function::getScaleSize(QSize(60, 70));
    if (!ui->pBorder->isHidden())
        ui->pBorder->setFixedSize(size);
    if (!ui->pFillColor->isHidden())
        ui->pFillColor->setFixedSize(size);
    if (!ui->pFlip->isHidden())
        ui->pFlip->setFixedSize(size);
    if (!ui->pMirror->isHidden())
        ui->pMirror->setFixedSize(size);
    if (!ui->pClone->isHidden())
        ui->pClone->setFixedSize(size);
    if (!ui->pBottom->isHidden())
        ui->pBottom->setFixedSize(size);
    if (!ui->pTop->isHidden())
        ui->pTop->setFixedSize(size);
    if (!ui->pDelete->isHidden())
        ui->pDelete->setFixedSize(size);
    if (!ui->pAdjust->isHidden())
        ui->pAdjust->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(40, 40));
    if (!ui->pBorder->isHidden())
        ui->pBorder->mSetIconSize(size);
    if (!ui->pFillColor->isHidden())
        ui->pFillColor->mSetIconSize(size);
    if (!ui->pFlip->isHidden())
        ui->pFlip->mSetIconSize(size);
    if (!ui->pMirror->isHidden())
        ui->pMirror->mSetIconSize(size);
    if (!ui->pClone->isHidden())
        ui->pClone->mSetIconSize(size);
    if (!ui->pBottom->isHidden())
        ui->pBottom->mSetIconSize(size);
    if (!ui->pTop->isHidden())
        ui->pTop->mSetIconSize(size);
    if (!ui->pDelete->isHidden())
        ui->pDelete->mSetIconSize(size);
    if (!ui->pAdjust->isHidden())
        ui->pAdjust->mSetIconSize(size);
    radius = Public_Function::getScaleSize(10);
    if (!ui->pBorder->isHidden())
        ui->pBorder->mSetRadius(radius);
    if (!ui->pFillColor->isHidden())
        ui->pFillColor->mSetRadius(radius);
    if (!ui->pFlip->isHidden())
        ui->pFlip->mSetRadius(radius);
    if (!ui->pMirror->isHidden())
        ui->pMirror->mSetRadius(radius);
    if (!ui->pClone->isHidden())
        ui->pClone->mSetRadius(radius);
    if (!ui->pBottom->isHidden())
        ui->pBottom->mSetRadius(radius);
    if (!ui->pTop->isHidden())
        ui->pTop->mSetRadius(radius);
    if (!ui->pDelete->isHidden())
        ui->pDelete->mSetRadius(radius);
    if (!ui->pAdjust->isHidden())
        ui->pAdjust->mSetRadius(radius);

    this->adjustSize();
}

