#include "checkminiboardnumber.h"
#include "hidapi/hidapi.h"
#include <QDebug>
CheckMiniBoardNumber::CheckMiniBoardNumber(QObject *parent)
    : QThread{parent}
{

}

void CheckMiniBoardNumber::setNumber(int num)
{
    number =num;
}

void CheckMiniBoardNumber::closeThread( )
{
    isrun =false;
}

void CheckMiniBoardNumber::run()
{
    isrun =true;
    while (isrun)
    {
        int boardnumber =0;
        hid_device_info *info=hid_enumerate(0,0);
        while (info)
        {
            if((info->product_id ==12424)&&(info->vendor_id ==1351))
            {
                boardnumber++;
            }
            info = info->next;
        }
        if(boardnumber !=number)
        {
            emit sendNumberChangeSignal(boardnumber);
        }
        sleep(2);
    }
}
