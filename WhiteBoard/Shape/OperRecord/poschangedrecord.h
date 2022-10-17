#ifndef POSCHANGEDRECORD_H
#define POSCHANGEDRECORD_H

#include "baserecord.h"
#include <QPointF>

class PosChangedRecord : public BaseRecord
{
    Q_OBJECT
public:
    explicit PosChangedRecord();
    virtual  ~PosChangedRecord();

    void setMovePos(const QPointF& pos);
    QPointF getMovePos() const;

private:
    QPointF mMovePos;//the pos of move
};

#endif // POSCHANGEDRECORD_H
