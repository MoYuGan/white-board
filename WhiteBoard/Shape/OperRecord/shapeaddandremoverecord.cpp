#include "shapeaddandremoverecord.h"

ShapeAddAndRemoveRecord::ShapeAddAndRemoveRecord(ShapeOperRecordType _type)
    : BaseRecord(_type)
{

}

ShapeAddAndRemoveRecord:: ~ShapeAddAndRemoveRecord()
{

}

void ShapeAddAndRemoveRecord::setShapeID(long shapeID)
{
    mShapeID = shapeID;
}

long ShapeAddAndRemoveRecord::getShapeID() const
{
    return mShapeID;
}
