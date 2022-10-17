#ifndef BORDERCHANGEDRECORD_H
#define BORDERCHANGEDRECORD_H

#include "baserecord.h"
#include <QObject>
/****
 *  to record the changed of border style
 * ***/
class BorderChangedRecord : public BaseRecord
{
    Q_OBJECT
public:
     explicit   BorderChangedRecord();
     virtual ~BorderChangedRecord();

    void setBorderData(const BorderStyle& newBorderData, const BorderStyle& oldBorder);

    BorderStyle getNewBorder() const;
    BorderStyle getOldBorder() const;

private:
    BorderStyle mNewBorderData;
    BorderStyle mOldBorderData;
};

#endif // BORDERCHANGEDRECORD_H
