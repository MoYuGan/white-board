#include "poschangedrecord.h"

PosChangedRecord::PosChangedRecord()
    : BaseRecord(MoveChanged)
{

}

PosChangedRecord::~PosChangedRecord()
{

}

void PosChangedRecord::setMovePos(const QPointF& pos)
{
    mMovePos = pos;
}

QPointF PosChangedRecord::getMovePos() const
{
    return mMovePos;
}
