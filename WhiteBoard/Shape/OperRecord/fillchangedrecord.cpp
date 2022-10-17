#include "fillchangedrecord.h"

FillChangedRecord::FillChangedRecord()
    : BaseRecord(ShapeOperRecordType::FillStyleChange)
{

}

FillChangedRecord::~FillChangedRecord()
{


}

void FillChangedRecord::setFillData(const FillStyle& newFill, const FillStyle& oldFill)
{
    mNewFillData = newFill;
    mOldFillData = oldFill;
}

FillStyle FillChangedRecord::getNewFillData() const
{
    return mNewFillData;
}

FillStyle FillChangedRecord::getOldFillData() const
{
    return mOldFillData;
}
