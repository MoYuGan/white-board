#include "zindexchanegedrecord.h"

ZIndexChanegedRecord::ZIndexChanegedRecord() : BaseRecord(ZIndexChange), mOldZIndex(0), mNewZIndex(0)
{

}

ZIndexChanegedRecord::~ZIndexChanegedRecord()
{

}

void ZIndexChanegedRecord::setZIndex(const qreal oldIndex, const qreal newIndex)
{
    mOldZIndex = oldIndex;
    mNewZIndex = newIndex;
}

qreal ZIndexChanegedRecord::getOldZIndex() const
{
    return mOldZIndex;
}

qreal ZIndexChanegedRecord::getNewZIndex() const
{
    return mNewZIndex;
}
