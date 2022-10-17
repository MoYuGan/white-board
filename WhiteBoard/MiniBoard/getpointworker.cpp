#include "getpointworker.h"

#include <QtDebug>
#include <QFile>

#define HID_PID 0x3088
#define HID_VID 0x0547

GetPointWorker::GetPointWorker(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<_TPPoint>("_TPPoint");
}

bool GetPointWorker::isOpenSuccess()
{
    return m_Loop;
}

char *GetPointWorker::getPath()
{
    return mpath;
}

void GetPointWorker::startWorker(char* path)
{
    mpath =path;
    if (hid_init())
    {
        qDebug()<<"error: Board init device failed";
        return;
    }
    qDebug() << " path22" << path <<Qt::endl;
    m_Handle =hid_open_path(path);
    if (!m_Handle)
    {
        qDebug()<<"error: Board unable to open device" << path <<QThread::currentThreadId();
        return;
    }
    m_Loop = true;
    unsigned char buf[64];
    int res = 0;
    while(m_Loop)
    {
        memset(buf, 0, sizeof(buf));
        res = hid_read(m_Handle, buf, sizeof(buf));
        if (res < 0) {
            qDebug()<<"error: Board failed to read hid device.";
            m_Loop = false;
            break;
        }else if (res > 0) {  //返回数据格式是64位
            this->parseData(buf, res);
        }
    } 
    mpath =nullptr;

    /*由于两块板PID和VID相同，使用会导致另外一块板接口关闭，
     * 导致呈现出一边拔掉，另一半无法书写的问题*/
    //hid_close(m_Handle);
    //hid_exit();//

}

void GetPointWorker::closeThread()
{
    m_Loop =false;
    hid_close(m_Handle);
}


void GetPointWorker::parseData(unsigned char *buf, int length)
{
    //if (64 != length)   //每个数据包64位
    //    return;
//    QString str;
//        for(int i = 0; i < length; i++)
//            str += QString("%1 ").arg(buf[i], 2, 16, QLatin1Char('0'));
//        qDebug()<<"str "<< str <<Qt::endl;

    if(64 == length)
    {
        for(int i=0; i < QString::number(buf[3]).toInt();i++)
        {
            if(i <6)getData(buf,i);
        }
    }
    else if(4 == length)
    {
        if(buf[0] ==0x0a &&buf[1] ==0x07 &&buf[2] ==0x00 &&buf[3] ==0x07)
        {
            emit sendShortcutKey(1);
        }
        else if(buf[0] ==0x0a &&buf[1] ==0x00 &&buf[2] ==0x00 &&buf[3] ==0x4b)
        {
            emit sendShortcutKey(2);
        }
        else if(buf[0] ==0x0a &&buf[1] ==0x00 &&buf[2] ==0x00 &&buf[3] ==0x4e)
        {
            emit sendShortcutKey(3);
        }
        else if(buf[0] ==0x0a &&buf[1] ==0x05 &&buf[2] ==0x00 &&buf[3] ==0x1d)
        {
            emit sendShortcutKey(4);
        }
        else if(buf[0] ==0x0a &&buf[1] ==0x07 &&buf[2] ==0x00 &&buf[3] ==0x06)
        {
            emit sendShortcutKey(5);
        }
        else if(buf[0] ==0x0a &&buf[1] ==0x07 &&buf[2] ==0x00 &&buf[3] ==0x08)
        {
            emit sendShortcutKey(6);
        }
    }
}

void GetPointWorker::getData(unsigned char *buf, int num)
{
     _TPPoint point;
     point.id =QString::number(buf[10*num +5]).toInt();
     if(point.id >6)return;
     point.ID =QString::number(buf[2]).toInt();
     if(QString::number(buf[10*num +4]).toInt() ==4)
     {
         point.state =3;//松开
         array.removeOne(QString::number(buf[10*num +5]).toInt());
     }
     else if(QString::number(buf[10*num +4]).toInt() ==7)
     {
         if(!array.contains(QString::number(buf[10*num +5]).toInt()))
         {
             point.state =1;//按下
             array.append(QString::number(buf[10*num +5]).toInt());
         }
         else point.state =2;//移动
     }
      int number1 =QString::number(buf[10*num +7]).toInt()*256;
      int number2 =QString::number(buf[10*num +6]).toInt();
      point.X =qreal(number1 +number2)/32767;

      int number3 =QString::number(buf[10*num +9]).toInt()*256;
      int number4 =QString::number(buf[10*num +8]).toInt();
      point.Y =qreal(number3 +number4)/32767;

      int number5 =QString::number(buf[10*num +11]).toInt()*256;
      int number6 =QString::number(buf[10*num +10]).toInt();
      point.W =qreal(number5 +number6);

      int number7 =QString::number(buf[10*num +13]).toInt()*256;
      int number8 =QString::number(buf[10*num +12]).toInt();
      point.H =qreal(number7 +number8);
      point.Num =QString::number(buf[3]).toInt();
      //if((point.W >=2500)&&(point.H >=5500)&&(point.id ==1)&&(point.state ==1))
      if((point.W >=1000)&&(point.H >=1000)&&(point.id ==1)&&(point.state ==1))
      {
          iseraser =true;
      }
      else if((point.id ==1)&&(point.state ==1))
      {
          iseraser =false;
      }

      if(iseraser)
      {
          if(point.id ==1)emit sendEraserDate(point);
      }
      else
      {
          emit sendPointDate(point);
      }
}
