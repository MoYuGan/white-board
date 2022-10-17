#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//extern "C"
//{
//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
//#include <libavdevice/avdevice.h>
//#include <libavutil/fifo.h>
//#include <libavutil/imgutils.h>
//#include <libswresample/swresample.h>
//};
#include "QProcess"
#include "QDateTime"
#include "QDesktopWidget"
#include "QPainter"
#include <QPainterPath>
#include <QRectF>
#include <QPointF>
#include "QBoxLayout"
#include "QDateTime"
#include "QTimer"
#include "public_function.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Start();
    void Moveto(double x, double y);
    void StartTime();
public:
    int m_MarginTop = 0;
    int m_MarginLeft = 0;
    int m_MarginRight = 0;
    int m_MarginBottom = 0;
    int m_TopLeftRadius = 0;
    int m_TopRightRadius = 0;
    int m_BottomLeftRadius = 0;
    int m_BottomRightRadius = 0;
    int m_MarginBorder = 0;
    int time = 0;
    bool m_StartOrEnd = true;

public slots:
    void SLOT_End();
    void SLOT_CurrentTime();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    QProcess* po;
    QTimer* timer;

};
#endif // WIDGET_H
