#ifndef PUSHBUTTON_7_H
#define PUSHBUTTON_7_H

#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QMouseEvent>
#include "pushbutton_basic.h"
#include "Public/public_function.h"

class PushButton_7 : public PushButton_Basic
{
    Q_OBJECT
public:
    PushButton_7(const QPixmap &icon, const QPixmap &checkedIcon = QPixmap(), const QPixmap &hoverIcon = QPixmap(), QWidget *parent = Q_NULLPTR);
    void setHoverStyle(bool enabled);
    void mSetIconSize(QSize iconSize);
    bool eventFilter(QObject *watched, QEvent *event) override;

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QPixmap m_Icon = QPixmap();
    QPixmap m_CheckedIcon = QPixmap();
    QPixmap m_HoverIcon = QPixmap();
    QSize m_IconSize;
    QColor m_HoverColor = QColor();
    QColor m_BorderColor = QColor();
    bool m_MouseEnter = false;
    bool m_HasHoverStyle = false;      //是否拥有悬停效果

signals:
    void checkedClicked();

};

#endif // PUSHBUTTON_7_H
