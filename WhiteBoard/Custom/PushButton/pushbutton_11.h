#ifndef PUSHBUTTON_11_H
#define PUSHBUTTON_11_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include "Public/public_function.h"

class PushButton_11 : public QPushButton
{
    Q_OBJECT
public:
    PushButton_11(QWidget *parent = Q_NULLPTR);
    void m_setText(QString ,QColor color=QColor(),QPixmap pix =QPixmap());
    void setLocalTest(const QString& str);
protected:
    void paintEvent(QPaintEvent *);

private:
    QString text_Str;
    QPixmap pixmap_Pix;
    QColor color_Col;
};

#endif // PUSHBUTTON_11_H
