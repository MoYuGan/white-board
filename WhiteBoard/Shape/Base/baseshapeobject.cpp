#include "baseshapeobject.h"
#include "../OperRecord/borderchangedrecord.h"
#include "../OperRecord/zindexchanegedrecord.h"
#include "../OperRecord/poschangedrecord.h"
#include "../OperRecord/rotatechangedrecord.h"
#include "../OperRecord/fillchangedrecord.h"
#include "../OperRecord/pathchangedrecord.h"

namespace
{
    qreal GetZIndex(BaseRecord* pRecord, bool isNew)
    {
        ZIndexChanegedRecord* zIndexRecord = (ZIndexChanegedRecord*)pRecord;
        if( zIndexRecord != nullptr )
            return isNew ? zIndexRecord->getNewZIndex() :  zIndexRecord->getOldZIndex();
        return 0;
    }

    QPointF GetMoveOffset(BaseRecord* pRecord, bool isNew)
    {
        PosChangedRecord* posRecord = (PosChangedRecord*)pRecord;
        if( posRecord != nullptr)
        {
            QPointF pos = posRecord->getMovePos();
            return isNew ?  pos : QPointF( -pos.x(), -pos.y());
        }
        return QPointF(0, 0);
    }

    int GetRotateAngle(BaseRecord* pRecord, bool isNew)
    {
        RotateChangedRecord* rotateAngle = (RotateChangedRecord*)pRecord;
        if( rotateAngle != nullptr)
        {
            return isNew ? rotateAngle->getNewRotateAngle() : rotateAngle->getOldRotateAngle();
        }
        return 0;
    }

    BorderStyle GetBorder(BaseRecord* pRecord, bool isNew)
    {
        BorderChangedRecord* borderRecord = (BorderChangedRecord*)pRecord;
        if( borderRecord != nullptr)
        {
            return isNew ? borderRecord->getNewBorder() : borderRecord->getOldBorder();
        }
        return BorderStyle();
    }

    FillStyle GetFill(BaseRecord* pRecord, bool isNew)
    {
        FillChangedRecord* fillRecord = (FillChangedRecord*)pRecord;
        if( fillRecord != nullptr)
        {
            return isNew ? fillRecord->getNewFillData() : fillRecord->getOldFillData();
        }
        return FillStyle();
    }
    void GetPath(BaseRecord* pRecord, bool isNew, QPainterPath* path)
    {
        PathChangedRecord* pathRecord = (PathChangedRecord*)pRecord;
       if( pathRecord != nullptr)
       {
           const QPainterPath* tarPath = isNew ? pathRecord->getNewPath() : pathRecord->getOldPath();
           if( tarPath != nullptr && path != nullptr)
           {
               *path = *tarPath;
           }
       }

    }

}

BaseShapeObject::BaseShapeObject(QObject *parent)
    : QObject{parent},mRotateAngle(0)
{

}

BaseShapeObject::~BaseShapeObject()
{

}

BaseRecord* BaseShapeObject::BorderChanged(const BorderStyle& borderData)
{
    BorderChangedRecord* pBorderRecord = new BorderChangedRecord();
    pBorderRecord->setBorderData( borderData, mBorderData);
    mBorderData = borderData;
    updateFromRecord();
    return pBorderRecord;
}

BaseRecord* BaseShapeObject::FillChanged(const FillStyle& fillData)
{
    FillChangedRecord* pFillRecord = new FillChangedRecord();
    pFillRecord->setFillData(fillData, mFillData);
    mFillData = fillData;
    updateFromRecord();
    return pFillRecord;
}

BaseRecord* BaseShapeObject::Move(const int dx, const int dy)
{
    PosChangedRecord* posRecord = new PosChangedRecord();
    QPointF offset(dx,dy);
    posRecord->setMovePos(offset);
    updateFromRecord();
    return posRecord;
}

BaseRecord* BaseShapeObject::Rotate(const qreal rotateAngle)
{
    RotateChangedRecord* rotateRecord = new RotateChangedRecord();
    rotateRecord->setRotate(mRotateAngle, rotateAngle);
    mRotateAngle = rotateAngle;
    //updateFromRecord();
    return rotateRecord;
}

BaseRecord* BaseShapeObject::pathChanged(const QPainterPath& path)
{
    PathChangedRecord* posRecord = new PathChangedRecord();
    posRecord->setPath( mLocalPath, path);
    mLocalPath = path;
    return posRecord;
}

void BaseShapeObject::Undo(BaseRecord*  pRecord)
{
    if( pRecord == nullptr)
        return;
    if( pRecord->getType() == NoneRecord || pRecord->getType() == Add || pRecord->getType() == Delete)
        return;
    //1. get the record data
    //2. undo operation
    switch(pRecord->getType())
    {
        case BorderStyleChange:
        {
            mBorderData = GetBorder(pRecord, false);
            updateFromRecord();
            break;
        }
        case FillStyleChange:
        {
            mFillData = GetFill(pRecord, false);
             updateFromRecord();
            break;
        }
        case MoveChanged:
        {
            QPointF pos = GetMoveOffset(pRecord ,false);
            mLocalPath.translate(pos);
             updateFromRecord();
            break;
        }
        case RotateChanged:
        {
            int angle = GetRotateAngle(pRecord,  false);

            break;
        }
        case PathChanged: //earse changed
        {
            GetPath(pRecord, false, &mLocalPath);
              updateFromRecord();
            break;
        }
        case ZIndexChange: //earse changed
        {
            mZIndex = GetZIndex(pRecord, false);
            break;
        }



    }
    //3. push record data into redoList
    //4.toggle update
    updateFromRecord();
}

void BaseShapeObject::Redo(BaseRecord*  pRecord)
{

}

