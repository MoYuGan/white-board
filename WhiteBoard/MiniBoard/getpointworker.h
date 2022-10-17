#ifndef GETPOINTWORKER_H
#define GETPOINTWORKER_H

#include <QObject>
#include "hidapi/hidapi.h"
#include <QMetaType>
#include <QFile>
#include <QThread>

typedef struct TouchPlanetPoint
{
    int id =0;
    int state =0;
    int Num =0;
    int ID =0;
    qreal X =0;
    qreal Y =0;
    qreal W =0;
    qreal H =0;
}_TPPoint;

Q_DECLARE_METATYPE(_TPPoint)


class GetPointWorker : public QObject
{
    Q_OBJECT
public:
    explicit GetPointWorker(QObject *parent = nullptr);
    bool isOpenSuccess();
    char* getPath();

public slots:
    void startWorker(char* );
    void closeThread();

private:
    bool m_Loop = false;
    void parseData(unsigned char *buf, int length);
    void getData(unsigned char *buf, int num);
    QVector<int>array;
    bool iseraser =false;
    char* mpath =nullptr;
    hid_device *m_Handle =nullptr;

signals:
    void sendPointDate(_TPPoint );
    void sendEraserDate(_TPPoint );
    void sendShortcutKey(int );//1桌面 2上一页 3下一页 4新建 5键盘 6窗口
};

#endif // GETPOINTWORKER_H
