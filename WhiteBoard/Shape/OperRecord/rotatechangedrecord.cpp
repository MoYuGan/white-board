#include "rotatechangedrecord.h"

RotateChangedRecord::RotateChangedRecord()
    : BaseRecord(RotateChanged),  mNewRotateAngle(0), mOldRotateAngle(0)
{

}

RotateChangedRecord::~RotateChangedRecord()
{

}


void RotateChangedRecord::setRotate(int oldAngle, int newAngle)
{
    mNewRotateAngle = newAngle;
    mOldRotateAngle = oldAngle;
}

int RotateChangedRecord::getNewRotateAngle() const
{
    return mNewRotateAngle;
}

int RotateChangedRecord::getOldRotateAngle() const
{
    return mOldRotateAngle;
}
