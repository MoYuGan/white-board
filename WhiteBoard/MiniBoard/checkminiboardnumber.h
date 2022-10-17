#ifndef CHECKMINIBOARDNUMBER_H
#define CHECKMINIBOARDNUMBER_H

#include <QObject>
#include <QThread>
class CheckMiniBoardNumber : public QThread
{
    Q_OBJECT

public:
    explicit CheckMiniBoardNumber(QObject *parent = nullptr);
    void setNumber(int );
    void closeThread( );

protected:
    void run();

signals:
    void sendNumberChangeSignal(int );

private:
    int number =0;
    bool isrun =false;

};

#endif // CHECKMINIBOARDNUMBER_H
