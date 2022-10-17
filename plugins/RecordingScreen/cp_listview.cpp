#include "cp_listview.h"

CP_ListVIew::CP_ListVIew(QWidget *parent) : QWidget(parent)
{

    setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_data = new QListWidget(this);
    QFont font;
    font.setFamily("Microsoft YaHei Regular, Microsoft YaHei Regular-Regular;");
    font.setPixelSize(14);
    font.setWeight(400);

    //Audio Input
    QVector<QString> aDeviceListI;
    QList<QAudioDeviceInfo> audioDeviceListI = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    int count = 0;
    foreach (QAudioDeviceInfo devInfo, audioDeviceListI)
    {
        QString strName = devInfo.deviceName();
        if (devInfo.isNull()) continue;
        if (strName[0] == 65533) continue;
        bool bFound = false;
        foreach (QString dev, aDeviceListI) {
            if (strName == dev){
                bFound = true;
            }
        }
        if (bFound == true) continue;
        QListWidgetItem * pItem = new QListWidgetItem;
        pItem->setText(strName);
        pItem->setSizeHint(Public_Function::getScaleSize(345,35));
        pItem->setFont(font);

        m_data->insertItem(count,pItem);
        count ++;
    }



    m_data->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_data->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_data->setStyleSheet("QListWidget{background:#eeeeee;border:none}"
                          "QListWidget::item{background:#eeeeee;}"
                          "QListWidget::item::hover{background:#e0e0e0}"
                          "QListWidget::item::selected{color:#1486FA}");

    m_data->adjustSize();
    m_data->setFixedWidth(Public_Function::getScaleSize(356));
    qDebug() << m_data->width() << m_data->height();

    connect(m_data,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(slot_GetText(QListWidgetItem*)));

}

void CP_ListVIew::slot_GetText(QListWidgetItem *item)
{
    m_Text = item->text();
    emit signal_clickList();
}


CP_ListVIew::~CP_ListVIew()
{

}
