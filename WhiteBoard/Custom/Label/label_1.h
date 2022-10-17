#ifndef LABEL_1_H
#define LABEL_1_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPainter>

class Label_1 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_1(QWidget *parent = nullptr);
    void show();
    void hide();

protected:
    void paintEvent(QPaintEvent *);

signals:

private:
    QTimer *timer;
    QPixmap pixmap;
    int number =1;

};

#endif // LABEL_1_H
