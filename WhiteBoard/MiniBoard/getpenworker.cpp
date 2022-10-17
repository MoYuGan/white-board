#include "getpenworker.h"
#include "QDebug"
GetPenWorker::GetPenWorker(QObject *parent)
    : QObject{parent}
{

}

int GetPenWorker::getPenNumber()
{
    return pencolor.count();
}

int GetPenWorker::getId()
{
    return id;
}

void GetPenWorker::getCurrentColor()
{
    emit sendGetPenMessage(id,color);
}

bool GetPenWorker::isOpenSuccess()
{
    return m_Loop;
}

//void GetPenWorker::getCurrentColorLeft()
//{
//    emit sendGetPenMessage(76,color2);
//}

//void GetPenWorker::getCurrentColorRight()
//{
//    emit sendGetPenMessage(82,color);
//}

//int GetPenWorker::getPenNumberLeft()
//{
//    return pencolor2.count();
//}

//int GetPenWorker::getPenNumberRight()
//{
//    return pencolor.count();
//}

void GetPenWorker::parseData(unsigned char *buf, int length)
{
    if(64 == length)
    {
        //8 9 10 右边
        //11 12 13左边
        id =QString::number(buf[5]).toInt();
        if(QString::number(buf[8]).toInt() ==0)
        {
            if(!pencolor.contains("black"))pencolor.append("black");
        }
        else if(QString::number(buf[8]).toInt() ==1)
        {
            if(pencolor.contains("black"))pencolor.removeOne("black");
        }

        if(QString::number(buf[9]).toInt() ==0)
        {
            if(!pencolor.contains("red"))pencolor.append("red");
        }
        else if(QString::number(buf[9]).toInt() ==1)
        {
            if(pencolor.contains("red"))pencolor.removeOne("red");
        }

        if(QString::number(buf[10]).toInt() ==0)
        {
            if(!pencolor.contains("blue"))pencolor.append("blue");
        }
        else if(QString::number(buf[10]).toInt() ==1)
        {
            if(pencolor.contains("blue"))pencolor.removeOne("blue");
        }
        if(pencolor.count() != pennumber)
        {
           pennumber = pencolor.count();
           if(pennumber >0)
           {
               color =pencolor.last();
               emit sendGetPenMessage(id,pencolor.last());
           }
           else
           {
               emit sendGetPenMessage(id,"none");
           }
        }
    }

//    QString str;
//    for(int i = 0; i < length; i++)
//        str += QString("%1 ").arg(buf[i], 2, 16, QLatin1Char('0'));
//    qDebug()<<"str " << QString::number(buf[5]).toInt() << str <<Qt::endl;
}


void GetPenWorker::startWorker(char *path)
{
    qDebug() << " path" << path<<Qt::endl;
    if (hid_init())
    {
        qDebug()<<"error: Pen init device failed";
        return;
    }
    m_Handle =hid_open_path(path);
    if (!m_Handle)
    {
        qDebug()<<"error: Pen unable to open device" << path <<QThread::currentThreadId();
        return;
    }
    else
        qDebug() << " success" <<Qt::endl;
    m_Loop = true;
    unsigned char buf[64];
    int res = 0;
    while(m_Loop)
    {
        memset(buf, 0, sizeof(buf));
        res = hid_read(m_Handle, buf, sizeof(buf));
        if (res < 0) {
            qDebug()<<"error: Pen failed to read hid device.";
            m_Loop = false;
            break;
        }else if (res > 0) {  //返回数据格式是64位
            this->parseData(buf, res);
        }
    }
}

void GetPenWorker::closeThread()
{
    m_Loop = false;
    hid_close(m_Handle);
}
