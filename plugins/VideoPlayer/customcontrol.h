#ifndef CUSTOMCONTROL_H
#define CUSTOMCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QSlider>
#include <QLayout>
#include <QPushButton>
#include <QButtonGroup>

class Icon_Lab : public QLabel
{
    Q_OBJECT
public:
    explicit Icon_Lab(QWidget *parent = nullptr);
    virtual ~Icon_Lab() {}
    void changeSizeAndPixmap(QSize ,QPixmap );
    void changePixmapSize(QSize );
    void changePixmap(QPixmap );

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pixmap;
};


/******************播放按钮**********************/
class Player_Lab : public QLabel
{
    Q_OBJECT
public:
    explicit Player_Lab(QWidget *parent = nullptr);
    virtual ~Player_Lab() {}
    void changeSizeAndPixmap(QSize ,QPixmap );
    void changePixmapSize(QSize ,int number =1);
    void changeSize(QSize );
    void changePixmap(QPixmap );

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pixmap;
    int num =1;
};


/***********************进度条********************/
class Progressbar : public QSlider
{
    Q_OBJECT
public:
    explicit Progressbar(QWidget *parent = nullptr);
    virtual ~Progressbar() {}
    void changeSize(int ,int ,int );
    void setProgressbarVlaue(int );

protected:
    bool ispress =false;
    int number =0;

signals:
    void sendPos(int );
    void sendPressProgressbarSignal();

};

/*********************音量窗口**********************/
class Volumewidget  : public QFrame
{
    Q_OBJECT
public:
    explicit Volumewidget(QWidget *parent = nullptr);
    virtual ~Volumewidget () {}
    void initWidget();
    void changeSize(int width =0,int heigth =0,int borderradius =0,int tetxSize =0,int textWidth =0,int textHigth =0,int sliderHeight =0,int sliderWidth =0,int sliderWidth1 =0);
    void changeVolume(QString );
    int getVolume();

signals:
    void sendVolumeNumber(int );

private:
    QLabel text_Lab;
    QSlider *slider_Sli;
    int volumenumber =0;
};


/*********************速度窗口**********************/
class Speedwidget  : public QFrame
{
    Q_OBJECT
public:
    explicit Speedwidget(QWidget *parent = nullptr);
    virtual ~Speedwidget ();
    void initWidget();
    void changeSize(int width =0,int heigth =0,int borderradius =0,int tetxSize =0);
    float getCurrentSpeed();

protected:
    void buttonPress(QAbstractButton *button);

signals:
    void speedChange(QString  ,float );

private:
    QPushButton *speed1_Btn;
    QPushButton *speed2_Btn;
    QPushButton *speed3_Btn;
    QPushButton *speed4_Btn;
    QPushButton *speed5_Btn;
    QPushButton *speed_Btn =nullptr;
    QButtonGroup *group_Btn;
    QLabel line1_Lab;
    QLabel line2_Lab;
    QLabel line3_Lab;
    QLabel line4_Lab;
    int textsize;
    float currentspeed =1.0;
};

#endif // CUSTOMCONTROL_H
