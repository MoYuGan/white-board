#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>
#include <QPainter>
#include <QButtonGroup>
#include "customwidget.h"

namespace Ui {
class MainInterface;
}

class MainInterface : public QWidget
{
    Q_OBJECT

public:
    explicit MainInterface(QWidget *parent = 0);
    ~MainInterface();
    void initresize();
    void initconnect();
    void getUrl(QString );

protected:
    void paintEvent(QPaintEvent *event);
    QPainterPath drawRoundRect(int r);
    bool eventFilter(QObject *watched, QEvent *event);

public:
    void changePicture(QPixmap p); //更改头像
    void changeName(QString str);

signals:
    void cancellation();
    void widgetClosed();

private:
    Ui::MainInterface *ui;
    QButtonGroup *group;
    CustomWidget_9 *m_lessonsWid;
    CustomWidget_10 *m_networkWid;
    QString m_url;

};

#endif // MAININTERFACE_H
