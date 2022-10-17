#ifndef FRAME_2_H
#define FRAME_2_H

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include "Custom/Label/label_1.h"
class Frame_2 : public QFrame
{
    Q_OBJECT
public:
    explicit Frame_2(QWidget *parent = nullptr);
    void setPixmapShow(int );
    void swithcPixmap();

protected:
   void paintEvent(QPaintEvent *event);
   bool eventFilter(QObject *watched, QEvent *event);

signals:
   void sendOpenSignal();

private:
   QPixmap pixmap;
   QLabel *laber;//调换成功
   QLabel *laber2;//记忆黑板功能已关闭
   QLabel *laber3;//未检测到可使用的记忆黑板
   Label_1 *laber4;//加载动画
   QTimer *timer;//调换成功定时器
   QTimer *timer2;//隐藏加载动画定时器
   bool exchange =false;

};

#endif // FRAME_2_H
