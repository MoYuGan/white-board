#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QObject>
#include "Public/CommonShapeData.h"
#include "baserecord.h"

struct ShapeRecord
{
    long shapeID;
    ShapeOperRecordType recordType;
    BaseRecord* pRecord;
};
typedef   QList<ShapeRecord> ShapeOperRecord;
/*****
 * Record  Manage for all operation
 *
 * ***/
class RecordManager
{

public:
    static RecordManager* getInstance();
    static void releaseInstance();
    ~RecordManager();

    void AddRecord(long shapeID ,  BaseRecord* record);
    void AddMultiRecord(const ShapeOperRecord& list);

    void GetUndoOnceRecord(ShapeOperRecord* targetRecord); // undo last oper
    void GetRedoOnceRecord(ShapeOperRecord* targetRecord);

    void RemoveAllUndo();
    void RemoveAllRecord();

signals:


private:
    static RecordManager* pInstance;
    explicit RecordManager();
    QList<ShapeOperRecord> mDoneList; //list for the oper has done
    QList<ShapeOperRecord> mUnDoList;// list for oper  is set undo
};

#endif // RECORDMANAGER_H
