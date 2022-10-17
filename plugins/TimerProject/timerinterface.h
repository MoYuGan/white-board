#ifndef TIMERINTERFACE_H
#define TIMERINTERFACE_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include "timerwidget.h"
#include "downwidget.h"
#include "TimerPlugin.h"
class TimerInterface : public TimerPlugin
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "TimerPlugin/01" FILE "TimerPlugin.json")
    Q_INTERFACES(TimerPlugin)//填写接口类名称
#endif
public:
    explicit TimerInterface(QWidget *parent = nullptr);
    void initCustom();
    void initConnect();
    void timerSizeChange(QString );
    void downSizeChange(QString );

    void updateLanguage(bool isChinese);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    QPainterPath drawRectRounded();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:

private:
    QPushButton *timerBtn;
    QPushButton *downBtn;
    QFrame *buttonFra;
    QLabel *titelLab;
    QLabel *closeLab;
    QLabel *centreLab;
    QHBoxLayout *hlayout1;
    QHBoxLayout *hlayout2;
    QHBoxLayout *hlayout3;
    QHBoxLayout *hlayout4;
    QVBoxLayout *vlayout;
    TimerWidget *timerWidget;
    DownWidget *downWidget;
    QPointF mousepresspoint;
    bool mousepressstate =false;
    QString sizestring ="min";

};

#endif // TIMERINTERFACE_H
