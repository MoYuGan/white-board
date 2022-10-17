#ifndef CUSTOMFRAME_1_H
#define CUSTOMFRAME_1_H

#include <QFrame>
#include <QPainter>
#include "Public/publicfunction.h"

class CustomFrame_1 : public QFrame
{
    Q_OBJECT
public:
    CustomFrame_1(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

   void mSetBordRadius(int topLeft, int topRight, int bottomLeft, int bottomRight) {
       m_pRadiusTopLeft = topLeft;
       m_pRadiusTopRight = topRight;
       m_pRadiusBottomLeft = bottomLeft;
       m_pRadiusBottomRight = bottomRight;
   }

protected:
   void paintEvent(QPaintEvent *event);

private:
   int m_pRadiusTopLeft;
   int m_pRadiusTopRight;
   int m_pRadiusBottomLeft;
   int m_pRadiusBottomRight;
};

#endif // CUSTOMFRAME_1_H
