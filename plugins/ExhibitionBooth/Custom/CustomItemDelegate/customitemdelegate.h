#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include "Public/publicfunction.h"

class CustomItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CustomItemDelegate(QObject *parent = Q_NULLPTR);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const ;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setPaddindTopAndBottom(int value);
    int getPaddingTopAndBottom() { return m_pPaddingTB; }
private:
    int m_pPaddingTB;
};

#endif // CUSTOMITEMDELEGATE_H
