#ifndef MYLOCK_H
#define MYLOCK_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
class MyLock : public QWidget
{
    Q_OBJECT
public:
    explicit MyLock(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void resize();

signals:

private:
    QPushButton *unlock;
    QLabel *label_text;
    QLabel *label_icon;
    QPixmap *pixmap_background;

public slots:
};

#endif // MYLOCK_H
