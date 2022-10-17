#include "pathchangedrecord.h"

PathChangedRecord::PathChangedRecord() : BaseRecord(PathChanged)
{


}

PathChangedRecord::~PathChangedRecord()
{


}

void PathChangedRecord::setPath(const QPainterPath& oldPath, const QPainterPath& newPath)
{
    mNewPath.clear();
    mNewPath = newPath;
    mOldPath.clear();
    mOldPath = oldPath;


}

const QPainterPath* PathChangedRecord::getOldPath()
{
    return (const QPainterPath*)(&mOldPath);
}

const QPainterPath* PathChangedRecord::getNewPath()
{
    return (const QPainterPath*)(&mNewPath);
}
