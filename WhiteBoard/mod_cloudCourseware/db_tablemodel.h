#ifndef DB_TABLEMODEL_H
#define DB_TABLEMODEL_H

#include <QAbstractTableModel>
#include "mod_http/db_httpinterface.h"
#include "db_define.h"

class DB_TableModel : public QAbstractTableModel
{
    /*
    *   自定义课件列表TableView模型
    */
public:
    DB_TableModel(QObject *parent = nullptr);
    void updateData(QVector<_CoIoData> recordList);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void reverseOrder();
    _CoIoData getCoIoData(int row) { return m_recordList.at(row); }


private:
    QVector<_CoIoData> m_recordList;
};

#endif // DB_TABLEMODEL_H
