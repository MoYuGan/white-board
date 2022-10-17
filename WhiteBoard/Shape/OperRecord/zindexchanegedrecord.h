#ifndef ZINDEXCHANEGEDRECORD_H
#define ZINDEXCHANEGEDRECORD_H

#include "baserecord.h"

class ZIndexChanegedRecord : public BaseRecord
{
    Q_OBJECT
public:
    ZIndexChanegedRecord();
    virtual ~ZIndexChanegedRecord();

    void setZIndex(const qreal oldIndex, const qreal newIndex);
    qreal getOldZIndex() const;
    qreal getNewZIndex() const;

private:
    qreal mOldZIndex;
    qreal mNewZIndex;
};

#endif // ZINDEXCHANEGEDRECORD_H
