#include "customitemdelegate.h"
#include <QtDebug>

CustomItemDelegate::CustomItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
    m_pPaddingTB = 0;
}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data();
        QString text = var.value<QString>();

        // 鼠标悬停或者选中时改变背景色
        QColor color = QColor(102, 102, 102);
        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->fillRect(option.rect, QBrush(QColor(20,134,250)));
            color = Qt::white;
        }else if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->fillRect(option.rect, QBrush(QColor(216, 216, 216)));
        }

        painter->setPen(QPen(color));
        painter->drawText(option.rect, text, QTextOption(Qt::AlignCenter));

        painter->restore();
    }
}

QSize CustomItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    if (index.isValid()) {
        return PublicFunction::getScaleSize(94, 42);
    }
}

void CustomItemDelegate::setPaddindTopAndBottom(int value)
{
    m_pPaddingTB = value;
}
