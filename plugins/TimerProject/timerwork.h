#ifndef TIMERWORK_H
#define TIMERWORK_H

#include <QObject>
#include <QLabel>
#include <QTimer>

class TimerWork : public QObject
{
    Q_OBJECT
public:
    explicit TimerWork(QObject *parent = nullptr);

public slots:
    void getTimeText();
    void startTimer();
    void stopTimer();
    void drawClock();
    void clearTimer();
    void getDrawLab(QLabel *,QLabel *);

signals:
    void getShowLab(QLabel *);

private:
    int minute=0;
    int second=0;
    bool timerstop =false;
    QTimer *m_pTimer;
    QLabel *interfaceLab;
    QLabel *timerLab;
    bool m_Continue = false;
};

#endif // TIMERWORK_H
