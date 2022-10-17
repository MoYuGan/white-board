#ifndef DB_TABLEDELEGATE_H
#define DB_TABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QToolBar>
#include <QObject>
#include "db_customwidget.h"

class DB_TableDelegate : public QStyledItemDelegate
{
    /*
    *   自定义课件列表TableView代理
    */
    Q_OBJECT
public:
    DB_TableDelegate(QObject *parent = nullptr);
    ~DB_TableDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setColumnWidth(int column, int width);

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const;
    void clearSelection() { m_pSelectionRow = -1; }

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    ItemButton *m_btnShared;
    ItemButton *m_btnDownload;
    ItemButton *m_btnMore;
    QPoint m_mousePos;
    QPoint m_pMousePressedPos;
    QMap<int, int> m_pColumnWidth;
    int m_pHoverRow = -1;
    int m_pSelectionRow = -1;

public slots:
    void clearHover() { m_pHoverRow = -1; }

signals:
    void changeCursor(Qt::CursorShape);
    void mouseClicked(int, int);
};

#endif // DB_TABLEDELEGATE_H
