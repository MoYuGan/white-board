#include "db_tabledelegate.h"

#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QtDebug>
#include <QCheckBox>
#include "Public/public_function.h"

#define BUTTON_SPACING 10
#define BUTTON_NUM  3

DB_TableDelegate::DB_TableDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_btnShared = new ItemButton(":/images/share.png");
    m_btnDownload = new ItemButton(":/images/download.png");
    m_btnMore = new ItemButton(":/images/more.png");
    m_mousePos = QPoint(-1, -1);
}

DB_TableDelegate::~DB_TableDelegate()
{
}

void DB_TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //去除选中时的焦点，即没有虚线框
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    // 不调用该函数就不进入initStyleOption进行文本绘制，避免与下面文本绘制重叠
    //QStyledItemDelegate::paint(painter, viewOption, index);

    //设置鼠标悬停行的颜色
    if (index.row() == m_pHoverRow || index.row() == m_pSelectionRow) {
        painter->fillRect(option.rect, QBrush(QColor(238,245,255)));
    }else {
        painter->fillRect(option.rect, QBrush(Qt::white));
    }

    switch (index.column())
    {
    case ColumnType::FileNameColumn: {
        QRect pixmapRect = QRect(option.rect.x(), option.rect.y() +
                                 (option.rect.height() - Public_Function::getScaleSize(18))/2,
                                 Public_Function::getScaleSize(16), Public_Function::getScaleSize(18));
        int x = pixmapRect.x() + pixmapRect.width() + Public_Function::getScaleSize(10);
        QRect textRect = QRect(x, option.rect.y(), option.rect.width() - x, option.rect.height());
        painter->setPen(QPen(index.data(Qt::ForegroundRole).value<QColor>()));
        painter->drawPixmap(pixmapRect, QPixmap(":/images/courseware/file-1.png").scaled(pixmapRect.size()));
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, index.data(Qt::DisplayRole).toString());
        return;
    }break;
    case ColumnType::FileCreateTimeColumn: {
        //分割事件字符串，只显示年月日
        QString str = index.data(Qt::DisplayRole).toString();
        QStringList list = str.split(" ");
        if (list.size() != 0) {
            painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft, QString("%1...").arg(list.at(0)));
        }
    }break;
    case ColumnType::FileSizeColumn: {
        painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft, index.data(Qt::DisplayRole).toString());
    }break;
    case ColumnType::FileOperationColumn: {
#if 1
        int spacing = Public_Function::getScaleSize(BUTTON_SPACING);
        int buttonSize = Public_Function::getScaleSize(ITEM_BUTTON_SIZE);
        int x = option.rect.x() + (option.rect.width() - spacing * (BUTTON_NUM + 1) - buttonSize * 3)/2;
        int y = option.rect.y() + (option.rect.height() - buttonSize)/2;
        m_btnShared->paintButton(painter, QPoint(x + spacing, y), m_mousePos);
        m_btnDownload->paintButton(painter, QPoint(x + buttonSize + spacing * 2, y), m_mousePos);
        m_btnMore->paintButton(painter, QPoint(x + buttonSize * 2 + spacing * 3, y), m_mousePos);
        return;
#endif
    }   break;
    default:
        break;
    }
}

QSize DB_TableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int value = m_pColumnWidth.value(index.column(), -1);
    if (-1 != value) {
        return QSize(value, Public_Function::getScaleSize(ITEM_HEIGHT));
    }
    return QStyledItemDelegate::sizeHint(option, index);
}

void DB_TableDelegate::setColumnWidth(int column, int width)
{
    m_pColumnWidth.insert(column, width);
}

/*
*   paint 中主要是调用了一个成员函数 initStyleOption 来读取 model 中的数据，并使用 QStyle 的规则来绘制
*/
void DB_TableDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    // 文件名列不绘制文本，在paint中直接自定义实现
    if (index.column() != ColumnType::FileNameColumn) {
        QStyledItemDelegate::initStyleOption(option, index);
    }
}

bool DB_TableDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
#if 1
    if (index.column() == FileOperationColumn)
    {
        int spacing = Public_Function::getScaleSize(BUTTON_SPACING);
        int buttonSize = Public_Function::getScaleSize(ITEM_BUTTON_SIZE);
        int x = option.rect.x() + (option.rect.width() - spacing * (BUTTON_NUM + 1) - buttonSize * 3)/2;
        int y = option.rect.y() + (option.rect.height() - buttonSize)/2;
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
            m_mousePos = mEvent->pos(); 
            bool setArrowCursor = true;;
            if (ItemButton::withinButtonRegion(QPoint(x + spacing, y), m_mousePos)){     //shared button
                //m_btnShared->setStatusHover();
                emit changeCursor(Qt::PointingHandCursor);
                setArrowCursor = false;
            }else if (ItemButton::withinButtonRegion(QPoint(x + buttonSize + spacing * 2, y), m_mousePos)) {    //downlaod button
                //m_btnDownload->setStatusHover();
                emit changeCursor(Qt::PointingHandCursor);
                setArrowCursor = false;
            }else if (ItemButton::withinButtonRegion(QPoint(x + buttonSize * 2 + spacing * 3, y), m_mousePos)) {    //more button
                //m_btnMore->setStatusHover();
                emit changeCursor(Qt::PointingHandCursor);
                setArrowCursor = false;
            }
            if (setArrowCursor)
                emit changeCursor(Qt::ArrowCursor);
        }else if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
            m_mousePos = mEvent->pos();
            m_pMousePressedPos = mEvent->pos();
            if (ItemButton::withinButtonRegion(QPoint(x + spacing, y), m_mousePos)){     //shared button
                m_btnShared->setStatusPressed();
            }else if (ItemButton::withinButtonRegion(QPoint(x + buttonSize + spacing * 2, y), m_mousePos)) {    //downlaod button
                m_btnDownload->setStatusPressed();
            }else if (ItemButton::withinButtonRegion(QPoint(x + buttonSize * 2 + spacing * 3, y), m_mousePos)) {    //more button
                m_btnMore->setStatusPressed();
            }
        }else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
            m_mousePos = mEvent->pos();
            if (ItemButton::withinButtonRegion(QPoint(x + spacing, y), m_mousePos) &&
                    ItemButton::withinButtonRegion(QPoint(x + spacing, y), m_pMousePressedPos)){     //shared button
                m_btnShared->setStatusReleased();
                emit mouseClicked(0, index.row());
            }else if (ItemButton::withinButtonRegion(QPoint(x + buttonSize + spacing * 2, y), m_mousePos) &&
                      ItemButton::withinButtonRegion(QPoint(x + buttonSize + spacing * 2, y), m_pMousePressedPos)) {    //downlaod button
                m_btnDownload->setStatusReleased();
                emit mouseClicked(1, index.row());
            }else if (ItemButton::withinButtonRegion(QPoint(x + buttonSize * 2 + spacing * 3, y), m_mousePos) &&
                      ItemButton::withinButtonRegion(QPoint(x + buttonSize * 2 + spacing * 3, y), m_pMousePressedPos)) {    //more button
                m_btnMore->setStatusReleased();
                emit mouseClicked(2, index.row());
            }
        }else {
            m_btnShared->setStatusNone();
            m_btnDownload->setStatusNone();
            m_btnMore->setStatusNone();
        }
    }

    if (event->type() == QEvent::MouseMove) {
        m_pHoverRow = index.row();
    }else if (event->type() == QEvent::MouseButtonRelease) {
        //清除上一次选中行的样式
        if (-1 != m_pSelectionRow && m_pSelectionRow != index.row()) {
            model->dataChanged(model->index(m_pSelectionRow, 0),
                                       model->index(m_pSelectionRow, model->columnCount()));
        }
         m_pSelectionRow = index.row();
    }

#endif
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}


