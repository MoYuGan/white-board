#ifndef SHAPEADDANDREMOVERECORD_H
#define SHAPEADDANDREMOVERECORD_H

#include "baserecord.h"
/*****
 *  Record for add Item or Remove Item for the scene
 * just record the shape id
 * ***/
class ShapeAddAndRemoveRecord : public BaseRecord
{
    Q_OBJECT
public:
    ShapeAddAndRemoveRecord(ShapeOperRecordType _type); // _type is for  [Add] or [Delete]
    virtual ~ShapeAddAndRemoveRecord();

    void setShapeID(long shapeID);
    long getShapeID() const;

private:
    long mShapeID;
};

#endif // SHAPEADDANDREMOVERECORD_H
