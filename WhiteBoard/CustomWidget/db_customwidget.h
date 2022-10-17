#ifndef DB_MBOXTOOLTIP_H
#define DB_MBOXTOOLTIP_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QPointer>
#include <QtDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QEventLoop>
#include "Public/public_function.h"
#include <QSlider>


class DB_CustomWidget_2 :  public QWidget
{
    /*
     *效果:带阴影widget
    */
public:
    DB_CustomWidget_2(QWidget *parent = nullptr) :
        QWidget(parent)
    {
        m_pColor = QColor(105, 105, 105);
        m_pBackgroundColor = QColor(Qt::white);
    }

    void show() {
        QWidget::show();
        this->raise();
    }

    //设置背景颜色
    void setBackGroundColor(const QColor &color) {
        m_pBackgroundColor = color;
    }
    //设置阴影宽度
    void setBorder(int width) { this->m_pBorder = width; }
    //设置阴影圆角
    void setRadius(int radius) { this->m_pRadius = radius; }
    //设置绘制阴影效果
    void setBorderNum(int num) {
        m_pBorderNum = num;
    }
    //设置阴影颜色
    void setColor(const QColor &color) {
        m_pColor = color;
    }
    //设置不透明度
    void setAlpha(int A1 = -1, int A2 = -1, int A3 = -1, int A4 = -1, int A5 = -1, int A6 = -1) {
        if (0 <= A1 && A1 <= 255)
            m_pAlpha1 = A1;
        if (0 <= A2 && A2 <= 255)
            m_pAlpha2 = A2;
        if (0 <= A3 && A3 <= 255)
            m_pAlpha3 = A3;
        if (0 <= A4 && A4 <= 255)
            m_pAlpha4 = A4;
        if (0 <= A5 && A5 <= 255)
            m_pAlpha5 = A5;
        if (0 <= A6 && A6 <= 255)
            m_pAlpha6 = A6;
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        /* 绘制阴影效果 */
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.fillRect(this->rect(), QBrush(Qt::transparent));
        QPainterPath path;

        QColor color(105, 105, 105);
        int border = m_pBorder;
        //设置背景颜色，边框部分保持透明
        if (2 == m_pBorderNum)
            path.addRoundedRect(QRect(0, border, this->width(), this->height() - border), m_pRadius, m_pRadius);
        else
            path.addRoundedRect(QRect(border, border, this->width() - 2*border, this->height() - 2*border),
                             m_pRadius, m_pRadius);
        painter.fillPath(path, QBrush(m_pBackgroundColor));
        int j;
        for(int i=0; i<border; i++)
        {
            j = border - i;
            path -= path;
            path.setFillRule(Qt::WindingFill);
            if (2 == m_pBorderNum)
                path.addRoundedRect(0, j, this->width() + 1, this->height() - border + j, m_pRadius, m_pRadius);
            else
                path.addRoundedRect(j, j, this->width() - j*2, this->height() - j*2, m_pRadius, m_pRadius);
            switch(i)
            {
            case 0:
                color.setAlpha(m_pAlpha1);
                break;
            case 1:
                color.setAlpha(m_pAlpha2);
                break;
            case 2:
                color.setAlpha(m_pAlpha3);
                break;
            case 3:
                color.setAlpha(m_pAlpha4);
                break;
            case 4:
                color.setAlpha(m_pAlpha5);
                break;
            case 5:
                color.setAlpha(m_pAlpha6);
                break;
            default:
                break;
            }
            QPen pen;
            pen.setColor(color);
            pen.setStyle(Qt::SolidLine);
            pen.setCapStyle(Qt::RoundCap);
            pen.setJoinStyle(Qt::RoundJoin);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(pen);
            painter.drawPath(path);
        }
    }

private:
    int m_pBorder = 6;      //阴影宽度,最大为6
    int m_pAlpha1 = 80;     //阴影不透明度(0~255),往外递减
    int m_pAlpha2 = 50;
    int m_pAlpha3 = 20;
    int m_pAlpha4 = 15;
    int m_pAlpha5 = 10;
    int m_pAlpha6 = 7;
    int m_pRadius = 8;      //阴影圆角
    int m_pBorderNum = -1;  //0=只绘制左边阴影  1=只绘制上边阴影 2=只绘制右边阴影 3=只绘制下边阴影 其他=绘制四条边阴影
    QColor m_pColor;        //阴影颜色
    QColor m_pBackgroundColor;  //背景颜色
};







class DB_CustomWidget_6 : public QWidget
{
    /*
    *   颜色面板专用
    */
    Q_OBJECT
public:
    explicit DB_CustomWidget_6(QWidget *parent = 0):QWidget(parent)
    {
        m_width = 0;
        m_height = 0;
        point = QPoint(0,0);
    }

    QPainterPath trigon(QPointF )
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.moveTo(0,point.y());
        path.lineTo(6,point.y()+6);
        path.lineTo(0,point.y()+12);
        path.moveTo(m_width,point.y());
        path.lineTo(m_width -6,point.y()+6);
        path.lineTo(m_width,point.y()+12);
        return path;
    }

private:
    int m_width;
    int m_height;
    QPoint point;
    QPixmap *pixmap;
    QColor color;
signals:
    void send_color(int ,int ,int ,int);

protected:
    void paintEvent(QPaintEvent *)
    {
        pixmap = new QPixmap(this->width(),this->height());
        QPainter painter(pixmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        QPainterPath path;
        m_width = this->width() -0;
        m_height = this->height() -0;
        QRect rect = QRect(0,0,m_width,m_height);
        QLinearGradient linear(m_width/2, 0, m_width/2, this->height());
        linear.setColorAt(0, QColor(255, 0, 0, 255));
        linear.setColorAt(0.166, QColor(255, 255, 0, 255));
        linear.setColorAt(0.333, QColor(0, 255, 0, 255));
        linear.setColorAt(0.499, QColor(0, 255, 255, 255));
        linear.setColorAt(0.665, QColor(0, 0, 255, 255));
        linear.setColorAt(0.831, QColor(255, 0, 255, 255));
        linear.setColorAt(1, QColor(255, 0, 0, 255));
        painter.setBrush(linear);
        painter.drawRect(rect);
        painter.setBrush(QBrush(Qt::black));
        path = trigon(point);
        painter.drawPath(path);
        QPainter pait(this);
        pait.drawPixmap(0,0,m_width,m_height,*pixmap);
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        point = event->pos();
        if(point.y() <= 0)point.setY(0);
        else if(point.y() >= m_height - 12)point.setY(m_height - 12);
        color = pixmap->toImage().pixel(m_width / 2, point.y());
        int red = color.red();
        int green = color.green();
        int blue = color.blue();
        int alpha = color.alpha();
        emit send_color(red,green,blue,alpha);
        update();
    }

    void mousePressEvent(QMouseEvent *event)
    {
        point = event->pos();
        if(point.y() <= 0)point.setY(0);
        else if(point.y() >= m_height - 12)point.setY(m_height - 12);
        color = pixmap->toImage().pixel(m_width / 2, point.y());
        int red = color.red();
        int green = color.green();
        int blue = color.blue();
        int alpha = color.alpha();
        emit send_color(red,green,blue,alpha);
        update();
    }
};

class DB_CustomWidget_7 : public QWidget
{
    /*
    *   颜色面板专用
    */
    Q_OBJECT
public:
    DB_CustomWidget_7(QWidget *parent):QWidget(parent) {
        point = QPoint(0,this->height()/2 +60);
    }
    void Get_color(int r,int g,int b ,int a){
        R = r;
        G = g;
        B = b;
        A = a;
        update();
    }

signals:
    void select_color(int ,int , int ,int );
protected:
    void paintEvent(QPaintEvent *)
    {
        pixmap = new QPixmap(this->width(),this->height());
        QPainter painter(pixmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        QRect rect = QRect(0,0,width(),height());
        QLinearGradient linear_white(0, this->height(), width(), this->height());
        QLinearGradient linear_black(width(), 0, width(), this->height());
        painter.setBrush(QColor(R, G, B, 255));
        painter.drawRect(rect);
        linear_white.setColorAt(0,QColor(255, 255, 255, 255));
        linear_white.setColorAt(1,QColor(255, 255, 255, 0));
        painter.setBrush(linear_white);
        painter.drawRect(rect);
        linear_black.setColorAt(1,QColor(0, 0, 0, 255));
        linear_black.setColorAt(0,QColor(0, 0, 0, 0));
        painter.setBrush(linear_black);
        painter.drawRect(rect);
        painter.setBrush(QBrush(Qt::white));
        QPainterPath ellpath;
        ellpath.setFillRule(Qt::OddEvenFill);
        ellpath.addEllipse(point,4,4);
        ellpath.addEllipse(point,6,6);
        painter.drawPath(ellpath);
        QPainter pait(this);
        pait.drawPixmap(0,0,width(),height(),*pixmap);

        color = pixmap->toImage().pixel(point.x(), point.y());
        int red = color.red();
        int green = color.green();
        int blue = color.blue();
        int alpha = A;
        emit select_color(red,green,blue,alpha);

    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        point = event->pos();
        if(point.y() < 0)point.setY(0);
        if(point.y() > height())point.setY(height());
        if(point.x() < 0)point.setX(0);
        if(point.x() > width())point.setX(width());
        update();
    }

    void mousePressEvent(QMouseEvent *event)
    {
        point = event->pos();
        update();
    }

public:
    int R = 91;
    int G = 116;
    int B = 127;
    int A = 255;
    QPoint point;
    QColor color;
    QPixmap* pixmap;
};


#endif // DB_MBOXTOOLTIP_H
