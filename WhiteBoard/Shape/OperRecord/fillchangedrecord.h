#ifndef FILLCHANGEDRECORD_H
#define FILLCHANGEDRECORD_H

#include "baserecord.h"

class FillChangedRecord : public BaseRecord
{
    Q_OBJECT
public:
    explicit FillChangedRecord();
    virtual  ~FillChangedRecord();

    void setFillData(const FillStyle& newFill, const FillStyle& oldFill);

    FillStyle getNewFillData() const;
    FillStyle getOldFillData() const;

private:
    FillStyle mNewFillData;
    FillStyle mOldFillData;
};

#endif // FILLCHANGEDRECORD_H
