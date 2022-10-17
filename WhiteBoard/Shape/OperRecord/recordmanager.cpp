#include "recordmanager.h"
#include <QMutex>
#include <QMutexLocker>

namespace
{
    QMutex mMutex;

    void RemoveAllRecord(ShapeOperRecord& list)
    {
        for(ShapeRecord& record : list)
        {
            if( record.pRecord != nullptr)
                delete record.pRecord;
        }
        list.clear();
    }
    void RemoveAllRecordList(QList<ShapeOperRecord>& list)
    {
        for( ShapeOperRecord& record : list)
        {
            RemoveAllRecord(record);
        }
        list.clear();
    }
}

RecordManager* RecordManager::pInstance = nullptr;

RecordManager::RecordManager()

{

}

RecordManager* RecordManager::getInstance()
{
    QMutexLocker lock(&mMutex);
    if( nullptr == pInstance )
    {
        pInstance = new RecordManager();
    }
    return pInstance;
}

void RecordManager::releaseInstance()
{
    QMutexLocker lock(&mMutex);
    if(  pInstance != nullptr)
    {
        delete pInstance;
    }
}

RecordManager::~RecordManager()
{
    RemoveAllRecordList( mDoneList);
    RemoveAllRecordList(mUnDoList );
}

void RecordManager::AddRecord(long shapeID ,   BaseRecord* record)
{
    ShapeOperRecord recordList;
    recordList.append({shapeID, record->getType(), record});
    mDoneList.append(recordList);
}

void RecordManager::AddMultiRecord(const ShapeOperRecord& list)
{
    mDoneList.append(list);
}

void RecordManager::GetUndoOnceRecord(ShapeOperRecord* targetRecord)
{
    if( targetRecord == nullptr)
        return;
    const ShapeOperRecord& record = mDoneList.back();
    *targetRecord = record;
    mUnDoList.append(record);
    mDoneList.pop_back();
}

void RecordManager::GetRedoOnceRecord(ShapeOperRecord* targetRecord)
{
    if( targetRecord == nullptr)
        return;
    const ShapeOperRecord& record = mUnDoList.back();
    *targetRecord = record;
    mDoneList.append(record);
    mUnDoList.pop_back();

}

void RecordManager::RemoveAllUndo()
{
    RemoveAllRecordList(mUnDoList );
}

void RecordManager::RemoveAllRecord()
{
    RemoveAllRecordList( mDoneList);
    RemoveAllRecordList(mUnDoList );
}
