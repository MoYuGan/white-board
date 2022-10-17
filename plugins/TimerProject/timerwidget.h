#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include "timerwork.h"

class TimerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimerWidget(QWidget *parent = nullptr);
    void initCustom();
    void initconnect();
    void setShowTime();
    void killThread();
protected:
    void paintEvent(QPaintEvent *event);

signals:
    void sendMessage(QString );
    void sendLabel(QLabel* ,QLabel*);
    void sendShowLabel();
    void sendTimerStart();
    void sendTimerStop();
    void sendTimerClear();

public slots:
    void maxBtnslot();
    void startBtnslot();
    void clearBtnslot();

private:

    QLabel *timerLab;
    QLabel *interfaceLab;
    QPushButton *maxBtn;
    QPushButton *startBtn;
    QPushButton *clearBtn;
    QThread *thread;
    QHBoxLayout *hlayout1;
    QHBoxLayout *hlayout2;
    QVBoxLayout *vlayout;
    TimerWork *timerwork;
    int flage =1;
};

#endif // TIMERWIDGET_H
