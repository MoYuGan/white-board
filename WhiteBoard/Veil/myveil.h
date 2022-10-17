#ifndef MYVEIL_H
#define MYVEIL_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QFrame>
#include <QPixmap>

class Myveil : public QWidget
{
    Q_OBJECT

    enum MOUSEPOS
    {
        TOPLEFT =1,
        TOPRIGHT,
        BOTTOMLEFT,
        BOTTOMRIGHT,
        MOVE,
        NO
    };

    enum FILLANDPICTURE{ //填充和图片
        FILL =1,
        PICTURE,
    };
public:
    explicit Myveil(QWidget *parent = nullptr);
    void getMousePos(QPoint );
    void interFaceInit();
    void connectInit();
    int adapt(int );
    QSize adapt(int ,int );
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:

public slots:

private:
   FILLANDPICTURE fillandpicture = FILLANDPICTURE::FILL;
   QColor backgroundcolor = QColor(20,134,250);
   QRect topleft;
   QRect topright;
   QRect bottomleft;
   QRect bottomright;
   QRect oldrect;
   QFrame *frame;
   QPushButton *pictureBtn;
   QPushButton *fillBtn;
   QPushButton *closeBtn;
   MOUSEPOS mousepos =MOUSEPOS::NO;
   QPoint mousepress;
   QPixmap pixmap ;
   bool mousestate = false;
   int iconwidth  =24;
   int margin =6;
};

#endif // MYVEIL_H
