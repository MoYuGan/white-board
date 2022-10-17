#include "pagepanel.h"
#include "ui_pagepanel.h"
#include "pagethread.h"
PagePanel::PagePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagePanel)
{
    ui->setupUi(this);
    this->initWidget();
}

PagePanel::~PagePanel()
{
    delete ui;
}

void PagePanel::changeTabPixmap(int var)
{
    m_PageList.value(var)->mSetPixmap(m_SceneList.at(var)->getPixmap());
}

void PagePanel::resizeWidget()
{
    QSize size = Public_Function::getScaleSize(QSize(288, 636));
    this->setFixedSize(size);
    int border = Public_Function::getScaleSize(10);
    ui->verticalLayout->setContentsMargins(border, border, border, border);
    ui->verticalLayout->setSpacing(Public_Function::getScaleSize(10));
    size = Public_Function::getScaleSize(QSize(268, 150));
    ui->listWidget->setGridSize(QSize(ui->listWidget->width(), size.height() + Public_Function::getScaleSize(10)));

    foreach (BoardScene *scene, m_SceneList) {
        scene->setSceneRect(0, 0, g_ScreenWidth, g_ScreenHeight);
    }
}

void PagePanel::show()
{
    QWidget::show();
    this->raise();
}

void PagePanel::hide()
{
    QWidget::hide();
    emit this->panelHide();
}


/*
*  添加新页
*  参数一：插入页的位置，参数二：页背景，参数三：背景编号
*/
BoardScene* PagePanel::addPage(int index, const QPixmap &bgPixmap, int bgNum)
{
    QSize size = Public_Function::getScaleSize(QSize(268, 150));

    PushButton_6* button = new PushButton_6(bgPixmap, index);
    button->setCheckable(true);
    button->setFixedSize(size);
    m_pPageGroup->addButton(button);
    connect(button, &PushButton_6::toggled, this, &PagePanel::onPageToggled);
    connect(button, &PushButton_6::deleteItem, this, &PagePanel::onPageDelete);
    m_PageList.insert(index, button);

    BoardScene *scene = new BoardScene;
    scene->setSceneRect(0, 0, g_ScreenWidth, g_ScreenHeight);
    scene->setBackgroundBrush(QBrush(bgPixmap));
    scene->setProperty("bgNum", bgNum);
    m_SceneList.insert(index, scene);

    //创建listWidgetItem
    QListWidgetItem *widgetItem = new QListWidgetItem;
    widgetItem->setSizeHint(size);
    ui->listWidget->insertItem(index, widgetItem);  //QListWidgetItem不能指定父控件，否则inserItem没有用
    ui->listWidget->setItemWidget(widgetItem, button);  //必须放在insertItem之后，否则不显示

    index++;
    for(int i = index; i < m_PageList.size(); i++)
    {
        m_PageList.at(i)->mSetIndex(i);
    }
    return scene;
}

int PagePanel::getPageSize()
{
    return m_PageList.size();
}

int PagePanel::getPageIndex()
{
    return m_PageList.indexOf((PushButton_6*)m_pPageGroup->checkedButton());
}

void PagePanel::setPageChecked(int index)
{
    if (index < 0 || index >= m_PageList.size())
        return;

    m_PageList.at(index)->setChecked(true);
}

void PagePanel::lastPage()
{
    int index = this->getPageIndex();
    if (-1 == index || 0 == index)
        return;

    this->setPageChecked(index - 1);
}

void PagePanel::nextPage()
{
    int index = this->getPageIndex();
    if (-1 == index || (m_PageList.size() - 1) == index)
        return;

    this->setPageChecked(index + 1);
}

void PagePanel::clearPage()
{
    foreach(PushButton_6 *button, m_PageList) {
        this->deletePage(button);
    }
}

void PagePanel::getAllScenePixmap(QList<QPixmap> *pixmapList)
{
    foreach(BoardScene *scene, m_SceneList) {
        pixmapList->push_back(scene->getSceneToPixmap());
    }
}

QPixmap PagePanel::getScenePixmap(int index)
{
    if (index < 0 ||  index >= m_SceneList.size())
        return QPixmap();
    return m_SceneList.at(index)->getSceneToPixmap();
}

QVector<BoardScene *> PagePanel::getBoardSceneList()
{
    return m_SceneList;
}

void PagePanel::updateSceneList(BoardScene *scene)
{
//    for (int var = 0; var < m_SceneList.count(); ++var) {
//      if(getPageIndex() ==var)m_PageList.value(var)->mSetPixmap(scene->getSceneToPixmap());
//      else m_PageList.value(var)->mSetPixmap(m_SceneList.at(var)->getSceneToPixmap());
//    }

    for (int var = 0; var < m_SceneList.count(); ++var) {
      if(getPageIndex() ==var)m_PageList.value(var)->mSetPixmap(scene->getSceneToPixmap());
      else m_PageList.value(var)->mSetPixmap(m_SceneList.at(var)->getPixmap());
    }

}

void PagePanel::paintEvent(QPaintEvent *event)
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

void PagePanel::initWidget()
{
    ui->verticalLayoutWidget_10->hide();
    this->setLayout(ui->verticalLayout);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滑动条
    ui->listWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel);  //设置垂直滑动模式
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置此属性不会影响自定义item widget选中样式
    QScroller::grabGesture(ui->listWidget, QScroller::LeftMouseButtonGesture);//设置滑动手势
    m_pPageGroup = new QButtonGroup(this);
    m_pPageGroup->setExclusive(true);   
}

void PagePanel::deletePage(PushButton_6 *button)
{
    int index = m_PageList.indexOf(button);
    if (-1 == index)
        return;

    BoardScene *scene = m_SceneList.value(index);
    for(int i = index; i < m_PageList.size(); i++) {
        m_PageList.at(i)->mSetIndex(i - 1);
    }

    m_pPageGroup->removeButton(button);
    m_PageList.removeOne(button);
    m_SceneList.removeOne(scene);
    QListWidgetItem *item = ui->listWidget->takeItem(index);
    delete item;

    button->deleteLater();
    scene->deleteLater();
    /*********change123 解决非选中页面删除页数不变的问题***********/
    emit pageIndexChanged(m_SceneList.value(this->getPageIndex()));
}

void PagePanel::onPageToggled(bool checked)
{
    PushButton_6* btn = static_cast<PushButton_6*>(sender());
    if (checked) {
        emit pageIndexChanged(m_SceneList.value(m_PageList.indexOf(btn)));
    }

}

void PagePanel::onPageDelete()
{
    if (1 == m_PageList.size())
        return;

    PushButton_6* button = static_cast<PushButton_6*>(sender());
    if (button->isChecked()) {
        int index = m_PageList.indexOf(button);
        if (index < (m_PageList.size() - 1))
            m_PageList.at(index + 1)->setChecked(true);
        else if (index == (m_PageList.size() - 1) && index > 0)
            m_PageList.at(index - 1)->setChecked(true);
    }
    this->deletePage(button);
}

