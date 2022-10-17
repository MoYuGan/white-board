#include "borderchangedrecord.h"

BorderChangedRecord::BorderChangedRecord()
    : BaseRecord(ShapeOperRecordType::BorderStyleChange)
{

}

BorderChangedRecord::~BorderChangedRecord()
{

}


void BorderChangedRecord::setBorderData(const BorderStyle& newBorderData, const BorderStyle& oldBorder)
{
    mNewBorderData = newBorderData;
    mOldBorderData = oldBorder;
}

BorderStyle BorderChangedRecord::getNewBorder() const
{
    return mNewBorderData;
}
 BorderStyle BorderChangedRecord::getOldBorder() const
{
    return mOldBorderData;
}
