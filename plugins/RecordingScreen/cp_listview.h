#ifndef CP_LISTVIEW_H
#define CP_LISTVIEW_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QBoxLayout>
#include "QStringListModel"
#include "QDebug"
#include "QListWidget"
#include "QMediaPlayer"
#include "QVideoWidget"
#include "QAudioDeviceInfo"
#include "QAudio"
#include "public_function.h"
class CP_ListVIew : public QWidget
{
    Q_OBJECT
public:
    explicit CP_ListVIew(QWidget *parent = nullptr);
    ~CP_ListVIew();

public:
        QString m_Text;
public slots:
    void slot_GetText(QListWidgetItem *item);
signals:
    void signal_clickList();
private:
    QListWidget* m_data;
};

#endif // CP_LISTVIEW_H
