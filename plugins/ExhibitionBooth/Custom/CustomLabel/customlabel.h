#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QPixmap>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "Extern/extern.h"

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = nullptr);
    void mSetPixmap(const QPixmap &pixmap, int angle = 0);
    void mSetTipPixmap(const QPixmap &pixmap);
    QPixmap getPixmap();
    void moveRect(const QPoint &subPt);
    void setRotateAngle(int angle);
    int getRotateAngle();
    void zoomIn();
    void zoomOut();
    bool eventFilter(QObject *watched, QEvent *event);
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    QPixmap m_pPixmap = QPixmap();
    QPixmap m_pTipPixmap = QPixmap();
    QRect m_pDisplayRect = QRect();
    bool m_MousePressed = false;
    QPoint m_LastMousePoint;
    int m_RotateAngle = 0;
    int m_ZoomNum = 0;
};

#endif // CUSTOMLABEL_H
