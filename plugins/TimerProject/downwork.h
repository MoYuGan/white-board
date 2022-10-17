#ifndef DOWNWORK_H
#define DOWNWORK_H

#include <QObject>
#include <QTimer>
#include <QLabel>

class DownWork : public QObject
{
    Q_OBJECT
public:
    explicit DownWork(QObject *parent = nullptr);
    void updateText();
    void addBlank(QString &,int );

signals:

public slots:
    void getTimeNum(int ,int ,int );
    void startTimer();
    void stopTimer();
    void getDrawLab(QLabel *);
    void showTimeText();

private:
    QTimer *mtimer;
    QLabel *showtime;
    int hour =1;
    int minute =1;
    int second =1;
    bool m_Continue = false;
};


#endif // DOWNWORK_H
