#include "tabtools_1.h"
#include <QtDebug>

TabTools_1::TabTools_1(QWidget *parent) : QWidget(parent)
{
    this->initWidget();
    this->resize();

}

void TabTools_1::resize()
{
    QSize size = PublicFunction::getScaleSize(288, 48);
    this->setFixedSize(size.width(), size.height() + m_TransparentBorder);
    m_BtnAdd->setFixedSize(PublicFunction::getScaleSize(30, 30));
    int height = PublicFunction::getScaleSize(9) + m_TransparentBorder/2;
    m_BtnAdd->move(PublicFunction::getScaleSize(16),height);
    m_BtnLastPage->setFixedSize(PublicFunction::getScaleSize(30, 30));
    m_BtnLastPage->move(PublicFunction::getScaleSize(70), height);
    m_Frame->setFixedSize(PublicFunction::getScaleSize(116, 36));
    m_Frame->setStyleSheet(QString("#m_Frame{border: 1px solid rgba(204,204,204);"
                                   "background: rgba(240,240,240);"
                                   "border-radius: %1px;}").arg(PublicFunction::getScaleSize(4)));
    m_Frame->move(PublicFunction::getScaleSize(113), PublicFunction::getScaleSize(6) + m_TransparentBorder/2);
    m_BtnShowPageList->setFixedSize(PublicFunction::getScaleSize(20, 20));
    m_Layout->setContentsMargins(0, 0, PublicFunction::getScaleSize(11), 0);
    m_BtnNextPage->setFixedSize(PublicFunction::getScaleSize(30, 30));
    m_BtnNextPage->move(PublicFunction::getScaleSize(242), height);

    m_PageListFrame->setFixedSize(PublicFunction::getScaleSize(288), PublicFunction::getScaleSize(639));
    m_vLayout->setContentsMargins(PublicFunction::getScaleSize(10), PublicFunction::getScaleSize(16),
                                  PublicFunction::getScaleSize(10), PublicFunction::getScaleSize(10));
    m_vLayout->setSpacing(PublicFunction::getScaleSize(10));
    m_PageListFrame->setStyleSheet(QString("#m_PageListFrame{background: white;"
                                           "border-radius: %1px;"
                                           "border: 1px solid rgb(185, 185, 185);}").arg(PublicFunction::getScaleSize(4)));
    m_PageListFrame->move(QPoint(this->x() + this->width() - m_PageListFrame->width(), this->y() - PublicFunction::getScaleSize(12)));
    //通过设置gridsize调整Item之间的间距，间距为gridSize的高度减去item的高度
    m_PageListWidget->setGridSize(QSize(m_PageListWidget->width(), PublicFunction::getScaleSize(160)));

    size = PublicFunction::getScaleSize(30, 30);
    m_BtnLastPage->mSetIconSize(size);
    m_BtnNextPage->mSetIconSize(size);
    m_BtnAdd->mSetIconSize(size);
    m_BtnShowPageList->mSetIconSize(PublicFunction::getScaleSize(20, 20));

    m_LabelPageText->setFont(PublicFunction::getFont(16));
    m_PageListLabelText->setFont(PublicFunction::getFont(16));
}

void TabTools_1::insertItem(int index, const QPixmap &pixmap)
{
    CustomPushButton_2* button = new CustomPushButton_2(pixmap, index, m_PageListFrame);
    button->setCheckable(true);
    m_ItemGroup->addButton(button);
    connect(button, &CustomPushButton_2::toggled, this, &TabTools_1::onItemToggled);
    connect(button, &CustomPushButton_2::deleteItem, this, &TabTools_1::onItemDelete);
    m_ItemList.insert(index, button);

    //创建listWidgetItem
    QSize size = PublicFunction::getScaleSize(QSize(268, 150));
    QListWidgetItem *widgetItem = new QListWidgetItem(m_PageListWidget);
    widgetItem->setSizeHint(size);
    m_PageListWidget->setItemWidget(widgetItem, button);
    m_PageListWidget->addItem(widgetItem);
}

void TabTools_1::setItemChecked(int index)
{
    if (index < 0 || index >= m_ItemList.size())
        return;

    m_ItemList.at(index)->setChecked(true);
}

void TabTools_1::changeItemPixmap(int index, const QPixmap &pixmap)
{
    if (index < 0 || index >= m_ItemList.size())
        return;

    CustomPushButton_2 *button = m_ItemList.at(index);
    button->mSetPixmap(pixmap);
}

void TabTools_1::addPage()
{
    m_BtnAdd->click();
}

void TabTools_1::hidePageListWidget()
{
    m_PageListFrame->hide();
    m_BtnShowPageList->setChecked(false);
}

void TabTools_1::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::transparent);
    QColor color(135, 135, 135);
    int border = 4;
    for(int i = 0; i < border; i++)
    {
        QRect rect = QRect(QPoint(border - i, border - i),
                           QPoint(this->width() - (border - i),
                            this->height() - (border - i)));
        QPainterPath path;
        path = PublicFunction::getRoundRectPath(rect, border, border, border, border);
        path.setFillRule(Qt::WindingFill);

        if (0 == i) {
            painter.fillPath(path, Qt::white);
        }

        switch(i)
        {
        case 0:
            color.setAlpha(80);
            break;
        case 1:
            color.setAlpha(50);
            break;
        case 2:
            color.setAlpha(20);
            break;
        case 3:
            color.setAlpha(15);
            break;
        case 4:
            color.setAlpha(10);
            break;
        case 5:
            color.setAlpha(7);
            break;
        case 6:
            color.setAlpha(3);
            break;
        default:
            break;
        }
        QPen pen;
        pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(pen);
        painter.drawPath(path);
    }
}

void TabTools_1::initWidget()
{
    m_BtnAdd = new CustomPushButton_1(this);
    m_BtnAdd->mSetIcon(QPixmap(":/images/tianjia_1@2x.png"), QPixmap(), QPixmap(":/images/tianjia2_1@2x.png"));
    m_BtnLastPage = new CustomPushButton_1(this);
    m_BtnLastPage->mSetIcon(QPixmap(":/images/shangyiye_1@2x.png"));
    m_BtnNextPage = new CustomPushButton_1(this);
    m_BtnNextPage->mSetIcon(QPixmap(":/images/xiayiye_1@2x.png"));

    m_Frame = new QFrame(this);
    m_Frame->setObjectName("m_Frame");
    m_Layout= new QHBoxLayout(m_Frame);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setSpacing(0);
    m_LabelPageText = new QLabel(this);
    m_BtnShowPageList = new CustomPushButton_1(this);
    m_BtnShowPageList->mSetIcon(QPixmap(":/images/zhankai_1@2x.png"), QPixmap(":/images/zhankai2_1@2x.png"), QPixmap());
    m_BtnShowPageList->setCheckable(true);
    m_Layout->addWidget(m_LabelPageText, 1, Qt::AlignCenter);
    m_Layout->addWidget(m_BtnShowPageList, 0, Qt::AlignCenter);

    m_PageListFrame = new QFrame(this);
    m_PageListFrame->setObjectName("m_PageListFrame");;
    m_PageListFrame->hide();
    m_vLayout = new QVBoxLayout(m_PageListFrame);
    m_vLayout->setContentsMargins(0, 0, 0, 0);
    m_vLayout->setSpacing(0);
    m_PageListLabelText = new QLabel(m_PageListFrame);
    m_PageListLabelText->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_PageListLabelText->setText(tr("画板页签"));
    m_PageListWidget = new QListWidget(m_PageListFrame);
    m_PageListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滑动条
    m_PageListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_PageListWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel);  //设置垂直滑动模式
    m_PageListWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置此属性不会影响自定义item widget选中样式
    m_PageListWidget->setStyleSheet(QString("QListWidget{"
                                            "border: none;"
                                            "background: transparent;"
                                            "}"));

    QScroller::grabGesture(m_PageListWidget, QScroller::LeftMouseButtonGesture);//设置滑动手势
    m_vLayout->addWidget(m_PageListLabelText, 0, Qt::AlignLeft);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_PageListWidget);
    m_vLayout->addLayout(hlayout);


    m_ItemGroup = new QButtonGroup(this);
    m_ItemGroup->setExclusive(true);

    connect(m_BtnShowPageList, &CustomPushButton_1::toggled, this, &TabTools_1::onShowPageListBtnToggled);
    connect(m_BtnAdd, &CustomPushButton_1::clicked, this, &TabTools_1::onAddBtnClicked);
    connect(m_BtnLastPage, &CustomPushButton_1::clicked, [=](){ emit this->lastPageClicked(); });
    connect(m_BtnNextPage, &CustomPushButton_1::clicked, [=](){ emit this->nextPageClicked(); });
    connect(m_BtnLastPage, &CustomPushButton_1::clicked, this, &TabTools_1::onLastPageBtnClicked);
    connect(m_BtnNextPage, &CustomPushButton_1::clicked, this, &TabTools_1::onNextPageBtnClicked);
}

void TabTools_1::onShowPageListBtnToggled(bool checked)
{
    if (checked) {
        m_PageListFrame->setParent((QWidget *)this->parent());
        m_PageListFrame->move(QPoint(this->x() + this->width() - m_PageListFrame->width(),
                                     this->y() - PublicFunction::getScaleSize(12) - m_PageListFrame->height()));
        m_PageListFrame->show();
    }else {
        m_PageListFrame->hide();
    }
}

void TabTools_1::onAddBtnClicked()
{
    emit addPageClicked();
}

void TabTools_1::onLastPageBtnClicked()
{
    int index = m_ItemList.indexOf((CustomPushButton_2*)m_ItemGroup->checkedButton());
    if (index > 0)
        m_ItemList.at(--index)->setChecked(true);
}

void TabTools_1::onNextPageBtnClicked()
{
    int index = m_ItemList.indexOf((CustomPushButton_2*)m_ItemGroup->checkedButton());
    if (index >= 0 && index < (m_ItemList.size() - 1))
        m_ItemList.at(++index)->setChecked(true);
}

void TabTools_1::onItemDelete()
{
    if (1 == m_ItemList.size())
        return;

    CustomPushButton_2* btn = static_cast<CustomPushButton_2*>(sender());
    int index = m_ItemList.indexOf(btn);
    qDebug() << " index " << index << m_ItemList.count() << endl;

    emit hasDelete(index);
    for(int i = index; i < m_ItemList.size(); i++) {
        m_ItemList.at(i)->mSetIndex(i -1);
    }

    m_ItemGroup->removeButton(btn);
    m_ItemList.removeOne(btn);
    QListWidgetItem *item = m_PageListWidget->takeItem(index);
    delete item;

    if (btn->isChecked()) {
        if (m_ItemList.size() > index)
            m_ItemList.at(index)->setChecked(true);
        else
            m_ItemList.last()->setChecked(true);
    }
    btn->deleteLater();

}

void TabTools_1::onItemToggled(bool checked)
{
    CustomPushButton_2* btn = static_cast<CustomPushButton_2*>(sender());
    if (checked) {
        m_LabelPageText->setText(QString("%1/%2").arg(m_ItemList.indexOf((CustomPushButton_2*)m_ItemGroup->checkedButton()) + 1).arg(m_ItemList.size()));
        int index = m_ItemList.indexOf((CustomPushButton_2*)m_ItemGroup->checkedButton());
        if (0 == index)
            m_BtnLastPage->mSetIcon(QPixmap(":/images/shangyiye_1@2x.png"));
        else
            m_BtnLastPage->mSetIcon(QPixmap(":/images/shangyiye2_1@2x.png"));

        if ((m_ItemList.size() - 1) == index)
            m_BtnNextPage->mSetIcon(QPixmap(":/images/xiayiye_1@2x.png"));
        else
            m_BtnNextPage->mSetIcon(QPixmap(":/images/xiayiye2_1@2x.png"));

        emit currentItemChanged(m_ItemList.indexOf(btn));
    }
}

