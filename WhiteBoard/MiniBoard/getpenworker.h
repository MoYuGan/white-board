#ifndef GETPENWORKER_H
#define GETPENWORKER_H

#include <QObject>
#include "hidapi/hidapi.h"
#include <QMetaType>
#include <QFile>
#include <QThread>

class GetPenWorker : public QObject
{
    Q_OBJECT
public:
    explicit GetPenWorker(QObject *parent = nullptr);
    int getPenNumber();
    int getId();
    void getCurrentColor();
    bool isOpenSuccess();

//    void getCurrentColorLeft();
//    void getCurrentColorRight();
//    int getPenNumberLeft();
//    int getPenNumberRight();

protected:
    void parseData(unsigned char *buf, int length);

public slots:
    void startWorker(char* );
    void closeThread();

signals:
    void sendGetPenMessage(int  ,QString );

private:
    bool m_Loop = false;
    QVector<QString> pencolor;
    int pennumber =0;
    QString color;
    int id;
    hid_device *m_Handle;

//    QVector<QString> pencolor2;
//    int pennumber2 =0;
//    QString color2;
};

#endif // GETPENWORKER_H
