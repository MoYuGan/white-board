#ifndef CUSTOMPUSHBUTTON_2_H
#define CUSTOMPUSHBUTTON_2_H

#include <QPushButton>
#include <QPixmap>
#include <QEvent>
#include <QFrame>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "Public/publicfunction.h"

class CustomPushButton_2 : public QPushButton
{
    Q_OBJECT
public:
    CustomPushButton_2(const QPixmap &pixmap, int pageIndex, QWidget *parent = Q_NULLPTR);
    void mSetPixmap(const QPixmap &pixmap);
    void mSetIndex(int index);
    void setContrastModel(bool bo);
    bool eventFilter(QObject *watched, QEvent *event);
    void mGetPixmap(QPixmap *pixmap);
    void setRotateAngle(int angle);
    int getRotateAngle();
    QPixmap mGetPixmap();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pPixmap;
    int m_pPageIndex;
    QRect m_pDelectRect;
    QRect m_pCheckedRect;
    bool m_pContrastModel = false;       //对比模式(使用选择框，去掉删除框)
    int m_RotateAngle = 0;

signals:
    void deleteSignal();
};

#endif // CUSTOMPUSHBUTTON_2_H
