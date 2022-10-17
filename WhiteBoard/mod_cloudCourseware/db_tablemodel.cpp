#include "db_tablemodel.h"

#include <QColor>
#include <QFont>

DB_TableModel::DB_TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

// 更新表格数据
void DB_TableModel::updateData(QVector<_CoIoData> recordList)
{
    m_recordList = recordList;
    beginResetModel();
    endResetModel();
}

int DB_TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_recordList.count();
}

int DB_TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return TABLE_COLUMN_COUNT;
}

QVariant DB_TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||  index.row() > m_recordList.size())
        return QVariant();

    int nRow = index.row();
    int nColumn = index.column();
    _CoIoData data = m_recordList.at(nRow);

    switch (role)
    {
    case Qt::BackgroundColorRole:
        return QColor(Qt::white);
    case Qt::ForegroundRole:
        return QColor(165, 165, 165);
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::DisplayRole:
    {
        if (ColumnType::FileNameColumn == nColumn)
            return data.fileName;
        else if (ColumnType::FileCreateTimeColumn == nColumn)
            return data.createTime;
        else if (ColumnType::FileSizeColumn == nColumn) {
            float sizeKB = ((float)data.fileSize)/1024.00;
            if (sizeKB > 1024) {
                return QString("%1M").arg(QString::number(sizeKB/1024.00, 'f', 2));
            }else {
                if (sizeKB < 0.01)
                    return QString("0KB");
                else
                    return QString("%1KB").arg(QString::number(sizeKB, 'f', 2));
            }
        }else
            return "";
    }
    default:
        break;
    }
    return QVariant();
}

// 表格可选中、可复选
Qt::ItemFlags DB_TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
    return flags;
}

//反序
void DB_TableModel::reverseOrder()
{
    if (0 == m_recordList.size())
        return;

    QVector<_CoIoData> newList;
    for(int i = m_recordList.size(); i > 0; ) {
        i--;
        newList.push_back(m_recordList.at(i));
    }
    m_recordList = newList;
    // 更新数据
    beginResetModel();
    endResetModel();
}
