#ifndef ROTATECHANGEDRECORD_H
#define ROTATECHANGEDRECORD_H

#include "baserecord.h"

class RotateChangedRecord : public BaseRecord
{
    Q_OBJECT
public:
    explicit RotateChangedRecord();
    virtual ~RotateChangedRecord();

    void setRotate(int oldAngle, int newAngle);
    int getNewRotateAngle() const;
    int getOldRotateAngle() const;

private:
    int mNewRotateAngle;
    int mOldRotateAngle;
};

#endif // ROTATECHANGEDRECORD_H
