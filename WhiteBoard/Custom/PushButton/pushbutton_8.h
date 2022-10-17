#ifndef PUSHBUTTON_8_H
#define PUSHBUTTON_8_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
class PushButton_8 : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton_8(QWidget *parent = nullptr);
    void msetTextAndPixmap(QString ,QPixmap );
    void mSetRoundSize(const QSize size);

protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:

private:
    QString m_text;
    QPixmap m_icon;
    bool m_isout =true;

};

#endif // PUSHBUTTON_8_H
