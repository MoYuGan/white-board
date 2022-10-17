#ifndef CUSTOMBTN_H
#define CUSTOMBTN_H
#include <QPushButton>
#include <QPainter>
#include "Public/public_function.h"
#include <QLabel>
#include <QButtonGroup>
#include <QBoxLayout>
#include <QDebug>
#include <qrencode.h>
/*****************************Custom_Btn1*******************************/
/*****************自定义登录界面中的账号登录和扫码登录按钮*********************/
class Custom_Btn1 : public QPushButton
{
    Q_OBJECT
public:
    Custom_Btn1(QWidget *parent =0):QPushButton(parent) {
        this->setCheckable(true);
    }

    void setText_m(QString st)
    {
        str = st;
        update();
    }

    virtual ~Custom_Btn1() {}
    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        //painter.drawRect(this->rect());
        if(this->isChecked())
        {
            painter.setPen(QPen(QColor(20,134,250),8,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.drawPoint(Public_Function::getScaleWidth(5),this->height()/2);
            painter.setFont(Public_Function::getFont(16));
            painter.drawText(QRect(Public_Function::getScaleWidth(14),0,this->width() -Public_Function::getScaleWidth(14),this->height()),str);
        }
        else
         {
            painter.setPen(QPen(QColor(170,170,170),8,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.setFont(Public_Function::getFont(16));
            painter.drawText(this->rect(),Qt::AlignCenter,str);
        }
}

private:
    QString str;

};


/*****************************Custom_Btn2*******************************/
/*****************自定义登录之后我的备课和我的网盘按钮************************/
class Custom_Btn2 : public QPushButton
{
    Q_OBJECT
public:
    Custom_Btn2(QWidget *parent =0):QPushButton(parent) {
        this->setCheckable(true);
    }

    void setTextAndPixmap(QString st,QPixmap pixmap)
    {
        pix = pixmap;
        str = st;
        update();
    }

    virtual ~Custom_Btn2() {}
    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        if(this->isChecked())
        {
           painter.setBrush(QBrush(Qt::white));
           painter.setPen(Qt::NoPen);
           painter.drawPath(drawRoundRect(Public_Function::getScaleWidth(4)));
           painter.drawPixmap(QRect(Public_Function::getScaleWidth(17),Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(24),Public_Function::getScaleWidth(24)),pix);
           painter.setPen(QPen(QColor(20,134,250)));
           painter.setFont(Public_Function::getFont(16));
           painter.drawText(QRect(Public_Function::getScaleWidth(53),Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(65),Public_Function::getScaleWidth(24)),str);
        }
        else
        {
            painter.setBrush(QBrush(QColor(17,111,206)));
            painter.setPen(Qt::NoPen);
            painter.drawPath(drawRoundRect(Public_Function::getScaleWidth(4)));
            painter.drawPixmap(QRect(Public_Function::getScaleWidth(17),Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(24),Public_Function::getScaleWidth(24)),pix);
            painter.setPen(QPen(Qt::white));
            painter.setFont(Public_Function::getFont(16));
            painter.drawText(QRect(Public_Function::getScaleWidth(53),Public_Function::getScaleWidth(12),Public_Function::getScaleWidth(65),Public_Function::getScaleWidth(24)),str);
         }
}

    QPainterPath drawRoundRect(int r)
    {
        QPainterPath path;
        path.moveTo(r,0);
        path.lineTo(this->width() -r,0);
        path.arcTo(this->width() -2*r,0,2*r,2*r,90,-90);
        path.lineTo(this->width(),this->height() -r);
        path.arcTo(this->width() -2*r,this->height() -2*r,2*r,2*r,0,-90);
        path.lineTo(this->width() -r,this->height());
        path.arcTo(0,this->height() -2*r,2*r,2*r,-90,-90);
        path.lineTo(0,r);
        path.arcTo(0,0,2*r,2*r,180,-90);
        return path;
    }

private:
    QString str;
    QPixmap pix;

};

/*****************************Custom_Btn3*******************************/
/**************自定义选中时蓝色背景白字和未选中时白色背景灰字按钮***************/
class Custom_Btn3 : public QPushButton
{
    Q_OBJECT
public:
    Custom_Btn3(QWidget *parent =0):QPushButton(parent) {
        this->setCheckable(true);
    }

    void setText_m(QString st)
    {
        str = st;
        update();
    }

    virtual ~Custom_Btn3() {}
    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        if(this->isChecked())
        {
            painter.setPen(QPen(QColor(224,224,224),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.setBrush(QColor(20,134,250));
            painter.drawPath(drawRoundRect(Public_Function::getScaleWidth(4)));
            painter.setPen(QPen(QColor(255,255,255),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.setFont(Public_Function::getFont(16));
            painter.drawText(this->rect(),Qt::AlignCenter,str);
        }
        else
         {
            painter.setPen(QPen(QColor(224,224,224),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.setBrush(QColor(255,255,255));
            painter.drawPath(drawRoundRect(Public_Function::getScaleWidth(4)));
            painter.setPen(QPen(QColor(102,102,102),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            painter.setFont(Public_Function::getFont(16));
            painter.drawText(this->rect(),Qt::AlignCenter,str);
        }
}


QPainterPath drawRoundRect(int r)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-90);
    path.lineTo(this->width(),this->height() -r);
    path.arcTo(this->width() -2*r,this->height() -2*r,2*r,2*r,0,-90);
    path.lineTo(this->width() -r,this->height());
    path.arcTo(0,this->height() -2*r,2*r,2*r,-90,-90);
    path.lineTo(0,r);
    path.arcTo(0,0,2*r,2*r,180,-90);
    return path;
}

private:
    QString str;

};


/*****************************Custom_Btn4*******************************/
/********************自定义文件云分享中的一天一周一月按钮*********************/
class Custom_Btn4 : public QPushButton
{
    Q_OBJECT
public:
    Custom_Btn4(QWidget *parent =0):QPushButton(parent) {
        this->setCheckable(true);
    }

    void setText_m(QString st)
    {
        str = st;
        update();
    }

    virtual ~Custom_Btn4() {}
    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        if(this->isChecked())
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(255,255,255));
            painter.drawPath(drawRoundRect(this->height()/2));
            painter.setPen(QPen(QColor(68,68,68),Public_Function::getScaleWidth(1)));
            QFont font(Public_Function::getFont(14));
            font.setWeight(75);
            painter.setFont(font);
            painter.drawText(this->rect(),Qt::AlignCenter,str);
        }
        else
         {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(240,240,240));
            painter.drawPath(drawRoundRect(this->height()/2));
            painter.setPen(QPen(QColor(136,136,136),Public_Function::getScaleWidth(1)));
            QFont font(Public_Function::getFont(14));
            font.setWeight(50);
            painter.setFont(font);
            painter.drawText(this->rect(),Qt::AlignCenter,str);
        }
}


QPainterPath drawRoundRect(int r)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-180);
    path.lineTo(r,this->height());
    path.arcTo(0,this->height() -2*r,2*r,2*r,-90,-180);
    return path;
}

private:
    QString str;

};


/*****************************Custom_Btn5*******************************/
/**********************自定义文件云分享中的公开和加密按钮*********************/
class Custom_Btn5 : public QPushButton
{
    Q_OBJECT
public:
    Custom_Btn5(QWidget *parent =0):QPushButton(parent) {
        publicBtn = new Custom_Btn4(this);
        publicBtn->setFixedSize(Public_Function::getScaleSize(94,34));
        publicBtn->setText_m(tr("公开"));

        privateBtn = new Custom_Btn4(this);
        privateBtn->setFixedSize(Public_Function::getScaleSize(94,34));
        privateBtn->setText_m(tr("加密"));

        group = new QButtonGroup(this);
        group->setExclusive(true);
        group->addButton(publicBtn);
        group->addButton(privateBtn);
        publicBtn->setChecked(true);

        QHBoxLayout *hlayout = new QHBoxLayout(this);
        hlayout->addWidget(publicBtn);
        hlayout->addStretch(0);
        hlayout->addWidget(privateBtn);
        hlayout->setSpacing(0);
        hlayout->setContentsMargins(Public_Function::getScaleWidth(4),Public_Function::getScaleWidth(4),Public_Function::getScaleWidth(4),Public_Function::getScaleWidth(4));

        connect(publicBtn,&Custom_Btn4::clicked,[=](){
        });

        connect(privateBtn,&Custom_Btn4::clicked,[=](){
        });
    }

    virtual ~Custom_Btn5() {}

QString getBtnText()
{
    QString st;
    if(publicBtn->isChecked())
    {
        st.append("publicBtn");
    }
    else if(privateBtn->isChecked())
    {
        st.append("privateBtn");
    }
    return st;
}

    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        if(this->isChecked())
        {
            painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleWidth(1)));
            painter.setBrush(QColor(255,255,255));
            painter.drawPath(drawRoundRect(this->height()/2));
        }
        else
         {
            painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleWidth(1)));
            painter.setBrush(QColor(240,240,240));
            painter.drawPath(drawRoundRect(this->height()/2));
        }
}


QPainterPath drawRoundRect(int r)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-180);
    path.lineTo(r,this->height());
    path.arcTo(0,this->height() -2*r,2*r,2*r,-90,-180);
    return path;
}

private:
    Custom_Btn4 *publicBtn;
    Custom_Btn4 *privateBtn;
    QButtonGroup *group;

};


/*****************************Custom_Btn6*******************************/
/***********************自定义文件云分享中的圆形按钮*************************/
class Custom_Btn6 : public QPushButton
{
    Q_OBJECT
public:
    Custom_Btn6(QWidget *parent =0):QPushButton(parent) {
        dayBtn = new Custom_Btn4(this);
        dayBtn->setFixedSize(Public_Function::getScaleSize(94,34));
        dayBtn->setText_m(tr("一天"));

        weekBtn = new Custom_Btn4(this);
        weekBtn->setFixedSize(Public_Function::getScaleSize(94,34));
        weekBtn->setText_m(tr("一周"));

        moothBtn = new Custom_Btn4(this);
        moothBtn->setFixedSize(Public_Function::getScaleSize(94,34));
        moothBtn->setText_m(tr("一个月"));

        group = new QButtonGroup(this);
        group->setExclusive(true);
        group->addButton(dayBtn);
        group->addButton(weekBtn);
        group->addButton(moothBtn);
        dayBtn->setChecked(true);

        QHBoxLayout *hlayout = new QHBoxLayout(this);
        hlayout->addWidget(dayBtn);
        hlayout->addStretch(0);
        hlayout->addWidget(weekBtn);
        hlayout->addStretch(0);
        hlayout->addWidget(moothBtn);
        hlayout->setSpacing(0);
        hlayout->setContentsMargins(Public_Function::getScaleWidth(4),Public_Function::getScaleWidth(4),Public_Function::getScaleWidth(4),Public_Function::getScaleWidth(4));

        connect(dayBtn,&Custom_Btn4::clicked,[=](){
        });

        connect(weekBtn,&Custom_Btn4::clicked,[=](){
        });

        connect(moothBtn,&Custom_Btn4::clicked,[=](){
        });
    }

    virtual ~Custom_Btn6() {}

    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        if(this->isChecked())
        {
            painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleWidth(1)));
            painter.setBrush(QColor(255,255,255));
            painter.drawPath(drawRoundRect(this->height()/2));
        }
        else
         {
            painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleWidth(1)));
            painter.setBrush(QColor(240,240,240));
            painter.drawPath(drawRoundRect(this->height()/2));
        }
}

QString getBtnText()
{
    QString st;
    if(dayBtn->isChecked())
    {
        st.append("one day");
    }
    else if(weekBtn->isChecked())
    {
        st.append("one week");
    }
    else if(moothBtn->isChecked())
    {
        st.append("one mooth");
    }
    return st;
}


QPainterPath drawRoundRect(int r)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-180);
    path.lineTo(r,this->height());
    path.arcTo(0,this->height() -2*r,2*r,2*r,-90,-180);
    return path;
}

private:
    Custom_Btn4 *dayBtn;
    Custom_Btn4 *weekBtn;
    Custom_Btn4 *moothBtn;
    QButtonGroup *group;
};

/*****************************Custom_Btn7*******************************/
/***************************自定义文件云页码按钮***************************/
class Custom_Btn7 : public QPushButton
{
    Q_OBJECT
public:
    Custom_Btn7(QString st,QWidget *parent =0):QPushButton(parent),str(st) {
        this->setCheckable(true);
        this->setFixedSize(Public_Function::getScaleSize(40,30));
    }
    virtual ~Custom_Btn7() {}
    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        if(this->isChecked())
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(20,134,250));
            painter.drawPath(drawRoundRect(Public_Function::getScaleWidth(4)));
            painter.setPen(QPen(QColor(255,255,255)));
            painter.setFont(Public_Function::getFont(14));
            painter.drawText(this->rect(),Qt::AlignCenter,str);
        }
        else
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(240,240,240));
            painter.drawPath(drawRoundRect(Public_Function::getScaleWidth(4)));
            painter.setPen(QPen(QColor(102,102,102)));
            painter.setFont(Public_Function::getFont(14));
            painter.drawText(this->rect(),Qt::AlignCenter,str);
        }
}

QPainterPath drawRoundRect(int r)
{
    QPainterPath path;
    path.moveTo(r,0);
    path.lineTo(this->width() -r,0);
    path.arcTo(this->width() -2*r,0,2*r,2*r,90,-90);
    path.lineTo(this->width(),this->height() -r);
    path.arcTo(this->width() -2*r,this->height() -2*r,2*r,2*r,0,-90);
    path.lineTo(this->width() -r,this->height());
    path.arcTo(0,this->height() -2*r,2*r,2*r,-90,-90);
    path.lineTo(0,r);
    path.arcTo(0,0,2*r,2*r,180,-90);
    return path;
}

private:
   QString str;
   bool mshow =false;
};


/*****************************Custom_Lab1*******************************/
/*************************自定义云课件内的圆形头像**************************/
class Custom_Lab1 : public QLabel
{
    Q_OBJECT
public:
    Custom_Lab1(QWidget *parent =0):QLabel(parent) {}

    void setPixmap_m(QPixmap pixmap)
    {
        pix = pixmap;
        update();
    }

    virtual ~Custom_Lab1() {}
    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(pix.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        painter.setBrushOrigin(this->rect().topLeft());
        painter.drawEllipse(this->rect());
}

private:
    QPixmap pix;

};

/*****************************Custom_Lab2*******************************/
/*************************自定义云课件内的圆形头像**************************/
class Custom_Lab2 : public QLabel
{
    Q_OBJECT
public:
    Custom_Lab2(QPixmap pictrue,QWidget *parent =0):QLabel(parent),pix(pictrue) {}



    virtual ~Custom_Lab2() {}
    void paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(240,240,240));
        QPainterPath path;
        path.addRoundedRect(1,1,this->width() -2,this->height() -2,5,5);
        painter.drawPath(path);
        painter.drawPixmap(Public_Function::getScaleWidth(11),Public_Function::getScaleWidth(9),Public_Function::getScaleWidth(7),
                           Public_Function::getScaleWidth(12),pix);
}

private:
    QPixmap pix;
};


/*****************************Custom_Lab3*******************************/
/*************************自定义二维码显示**************************/
class Custom_Lab3 : public QLabel
{
    /*
     *功能:
     * 1、二维码显示
    */
    Q_OBJECT

public:
    explicit Custom_Lab3(QWidget *parent = Q_NULLPTR) : QLabel(parent) {
        qrcode = nullptr;
        m_pShowLogo = false;
    }

    ~Custom_Lab3() {
        if(qrcode != nullptr) {
            QRcode_free(qrcode);
        }
    }

    void setString(const QString str) {
        if(qrcode != nullptr) {
            QRcode_free(qrcode);
        }
        qrcode = QRcode_encodeString(str.toStdString().c_str(), 2, QR_ECLEVEL_H, QR_MODE_8, 1);
        update();
    }

    void isShowLogo(bool bo) {
        m_pShowLogo = bo;
        update();
    }

protected:
    void paintEvent(QPaintEvent *ev) {
        Q_UNUSED(ev);
        int width = this->width() - 20;
        int height = this->height() - 20;
        if (qrcode == NULL)
            return;

        int qrWidth = qrcode->width > 0 ? qrcode->width : 1 ;
        double scaleX = (double)width / (double)qrWidth ;
        double scaleY = (double)height / (double)qrWidth ;
        QPainter painter(this);
        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawRect(this->rect());
        painter.setBrush(Qt::black);
        for(int y = 0; y < qrWidth; ++y) {
            for(int x = 0; x < qrWidth; ++x) {
                uchar node = qrcode->data[y*qrWidth + x];
                if(node & 0x01) {
                    QRectF rectf(x*scaleX + 10, y*scaleY + 10, scaleX, scaleY);
                    painter.drawRects(&rectf, 1);
                }
            }
        }

        painter.setRenderHint(QPainter::Antialiasing);
        if(m_pShowLogo) {
            QPixmap pixmap(":/images/courseware/weixin-2@2x.png");
            painter.setPen(QPen(QColor(85, 85, 85, 0)));
            painter.setBrush(QBrush(QColor(85, 85, 85, 85)));
            painter.drawRoundedRect(this->rect(), 8, 8);
            QPoint centerPos = this->rect().center();
            int pixmapWidth = 70;
            pixmap.scaled(QSize(pixmapWidth, pixmapWidth));
            QRect pixmapRect = QRect(centerPos.x() - pixmapWidth/2, centerPos.y() - pixmapWidth/2, pixmapWidth, pixmapWidth);
            painter.drawPixmap(pixmapRect, pixmap);
        }
    }

private:
    QRcode* qrcode;
    QPixmap* image;
    bool m_pShowLogo;
};


#endif // CUSTOMBTN_H
