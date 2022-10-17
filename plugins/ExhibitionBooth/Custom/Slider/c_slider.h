#ifndef C_SLIDER_H
#define C_SLIDER_H

#include <QLabel>
#include <QPainter>
#include "Public/publicfunction.h"

class C_Slider : public QLabel
{
public:
    C_Slider(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void mSizeChanged(qint64 currentSize, qint64 totalSize);

protected:
    void paintEvent(QPaintEvent *) override;


private:
    qreal m_SubWidth;

};

#endif // C_SLIDER_H
