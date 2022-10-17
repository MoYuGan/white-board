#ifndef BASERECORD_H
#define BASERECORD_H

#include <QObject>
#include "Public/CommonShapeData.h"
/****
* Base Data of All Record
* private interface:
*  setOperation Type
*  get OperationType
**/
class BaseRecord : public QObject
{
    Q_OBJECT
public:
    BaseRecord(ShapeOperRecordType _type) : QObject() , mType(_type){ }
    BaseRecord() { mType = NoneRecord;}
    //virtual ~BaseOperationRecord(){}

    void setType(ShapeOperRecordType _type ) { mType = _type; }
    ShapeOperRecordType getType() const  { return mType; }

private:
    ShapeOperRecordType mType;
};

#endif // BASERECORD_H
