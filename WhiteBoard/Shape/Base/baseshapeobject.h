#ifndef BASESHAPEOBJECT_H
#define BASESHAPEOBJECT_H

#include <QObject>
#include "Public/CommonShapeData.h"
#include "Shape/OperRecord/baserecord.h"
#include <QPainterPath>


class BaseShapeObject : public QObject
{
    Q_OBJECT
public:
    explicit BaseShapeObject(QObject *parent = nullptr);
    virtual ~BaseShapeObject();

    void setShapeID(long id){ mShapeID = id;}
    long getShapeID() const {return mShapeID;}
    virtual void updateFromRecord() =0;// border or fill changed or path changed
    //void AddRecord();
    // bordee chenaged bu user operation
    BaseRecord* BorderChanged(const BorderStyle& borderData);
    BaseRecord* FillChanged(const FillStyle& fillData);
    BaseRecord* Move(const int dx, const int dy);
    BaseRecord* Rotate(const qreal ratateAngle);
    BaseRecord* pathChanged(const QPainterPath& path);
    // all kind of changed function

    void Undo(BaseRecord*  pRecord); //recover the last oper record of   mLocalRecordList

    void Redo(BaseRecord*  pRecord);//redo the last oper record of  mLocatUndoRecordList

signals:

protected:
    long mShapeID;// the only shape id in  scene
    ShapeType mShapeType;//shape Type
    ShapePropertyType mProperty;//which property can changed or oper
    BorderStyle mBorderData;
    FillStyle mFillData;
    QPainterPath mLocalPath;
    qreal mZIndex;
    int mRotateAngle;

    bool mIsShow;

};

#endif // BASESHAPEOBJECT_H
