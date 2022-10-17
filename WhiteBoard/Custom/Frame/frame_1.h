#ifndef FRAME_1_H
#define FRAME_1_H

#include <QFrame>
#include <QPainter>
#include <QPainterPath>

class Frame_1 : public QFrame
{
    Q_OBJECT
public:
   Frame_1(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
   void show();
   void hide();
   void mSetBorder(int border);
   inline int mGetBorder() { return m_pBorder; }
   void mSetBackgroudColor(const QColor &color);
   void mSetBordRadius(int topLeft, int topRight, int bottomLeft, int bottomRight);
   void mSetMargin(int left, int top, int right, int bottom);

protected:
   void paintEvent(QPaintEvent *event);

private:
   int m_pBorder;
   int m_pLeftMargin;
   int m_pTopMargin;
   int m_pRightMargin;
   int m_pBottomMargin;
   int m_pRadiusTopLeft;
   int m_pRadiusTopRight;
   int m_pRadiusBottomLeft;
   int m_pRadiusBottomRight;
   QColor m_pBackgroundColor;

signals:
   void frameShow();
   void frameHide();
};

#endif // FRAME_1_H
