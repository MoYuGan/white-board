#ifndef PATHCHANGEDRECORD_H
#define PATHCHANGEDRECORD_H

#include "baserecord.h"
#include <QPainterPath>
/*****
 *  Path changed by Earse oper
 *
 * ***/
class PathChangedRecord : public BaseRecord
{
    Q_OBJECT
public:
    PathChangedRecord();
    virtual ~PathChangedRecord();

    void setPath(const QPainterPath& oldPath, const QPainterPath& newPath);
    const QPainterPath* getOldPath()  ;
    const QPainterPath* getNewPath()  ;

private:
    QPainterPath mNewPath;
    QPainterPath mOldPath;

};

#endif // PATHCHANGEDRECORD_H
