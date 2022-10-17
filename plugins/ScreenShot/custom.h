#ifndef CUSTOM_H
#define CUSTOM_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include <QPainter>
#include <QFrame>
#include <QLabel>

/*************自定义保存取消按钮**************/
class mPushButton_1 : public QPushButton
{
    Q_OBJECT
public:
    explicit mPushButton_1(QWidget *parent = nullptr);
    void setTextAndPixmap(QString ,QPixmap );
    void setLocalText(const QString& txt);
protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    QString str;
    QPixmap pixmap;
};

/*************自定义各种图标**************/
class Label_1 : public QLabel
{
    Q_OBJECT

public:
    explicit Label_1(QPixmap ,QString ,QWidget *parent = nullptr);
    virtual ~Label_1() {}
    void changePixmapAndText(QPixmap pix,QString str);

    void setLocalText(const QString& txt);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QLabel *pixmap_Lab;
    QLabel *text_Lab;

};


#endif // CUSTOM_H
