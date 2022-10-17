#include "light.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QFileDialog>
#include "Public/public_function.h"
#include "VirtualKeyBoard/keyboard.h"
#include "ToolPanel/db_colorpanel.h"
#define my_r  8

Light::Light(QWidget *parent) : QWidget(parent)
{
   QDesktopWidget *desktop = QApplication::desktop();
   this->resize(desktop->width(),desktop->height());        //设置界面大小
   this->setAutoFillBackground(false);                      //关闭自动填充
   this->setAttribute(Qt::WA_TranslucentBackground,true);   //设置背景透明，不设置透视为黑色
   this->setMouseTracking(true);//开启鼠标追踪
   initCustom();
   initConnect();
}

void Light::initCustom()
{
    mytool = new QFrame(this);
    mytool->setFixedSize(Public_Function::getScaleSize(454,82));
    mytool->setStyleSheet(QString("background-color:white ;border-radius: %1px;").arg(12));
    mytool->hide();
    textLab = new QLabel(tr("请拖拽一个区域"),this);
    textLab->setFont(Public_Function::getFont(72));
    textLab->setMouseTracking(true);
    textLab->setAlignment(Qt::AlignCenter);
    textLab->setStyleSheet(QString("color:white;"));
    textLab->setFixedSize(Public_Function::getScaleSize(800,100));
    textLab->move((this->width() -textLab->width())/2,(this->height() -textLab->height())/2);
    textLab->show();
    QHBoxLayout *hlayout = new QHBoxLayout(mytool); //水平布局
    rectBtn = new DB_CustomPushButton_16(tr("矩形"),QPixmap(":/images/Light/rect2.png"),mytool);
    roundBtn = new DB_CustomPushButton_16(tr("圆形"),QPixmap(":/images/Light/round2.png"),mytool);
    maxBtn = new DB_CustomPushButton_16(tr("放大"),QPixmap(":/images/Light/max2.png"),mytool);
    minBtn = new DB_CustomPushButton_16(tr("缩小"),QPixmap(":/images/Light/min2.png"),mytool);
    pictureBtn = new DB_CustomPushButton_16(tr("图片"),QPixmap(":/images/Light/picture2.png"),mytool);
    fillBtn = new DB_CustomPushButton_16(tr("填充"),QPixmap(":/images/Light/fill2.png"),mytool);
    closeBtn = new DB_CustomPushButton_16(tr("取消"),QPixmap(":/images/Light/close2.png"),mytool);

    hlayout->setMargin(Public_Function::getScaleSize(6));
    hlayout->addWidget(rectBtn);
    hlayout->addWidget(roundBtn);
    hlayout->addWidget(maxBtn);
    hlayout->addWidget(minBtn);
    hlayout->addWidget(pictureBtn);
    hlayout->addWidget(fillBtn);
    hlayout->addWidget(closeBtn);
    QButtonGroup *group = new QButtonGroup(this); //启用按钮組功能进行管理按钮
    group->setExclusive(true); //设置按钮互斥
    group->addButton(rectBtn);
    group->addButton(roundBtn);
    group->addButton(maxBtn);
    group->addButton(minBtn);
    group->addButton(pictureBtn);
    group->addButton(fillBtn);
    group->addButton(closeBtn);
    rectBtn->setChecked(true);
    copypixmap = new QPixmap;
}

void Light::initConnect()
{
    connect(rectBtn,&DB_CustomPushButton_16::clicked,this,[=](){
        rectandround = RECTANDROUND::RECT;
        update();});

    connect(roundBtn,&DB_CustomPushButton_16::clicked,this,[=](){
        rectandround = RECTANDROUND::ROUND;
        update();});

    connect(maxBtn,&DB_CustomPushButton_16::clicked,this,[=](){
        emit getShowPixmap(copypixmap);
        if(copypixmap == nullptr)
            return;
        maxandmin =MAXANDMIN::MAX;
        if(index < 3)
        index += 0.2;
        if(index >= 3)
        {
            index =3;
        }
        update();
        ;});

    connect(minBtn,&DB_CustomPushButton_16::clicked,[=](){
        emit getShowPixmap(copypixmap);
        if(copypixmap == nullptr)
            return;
        maxandmin =MAXANDMIN::MIN;
        if(index > 1)
        index -= 0.2;
        if(index <= 1.0)
        {
            index =1.0;
        }
        update();
        ;});

    connect(pictureBtn,&DB_CustomPushButton_16::clicked,this,[=](){
        emit getShowPixmap(copypixmap);
        if(copypixmap == nullptr)return;
        Keyboard key;
        key.hide();
        QString fileName = QFileDialog::getOpenFileName(this,tr("打开图片"),".",tr("Image File (*.jpg *.png *.bmp)"));
        if (fileName.length() == 0)return;
        pixmap.load(fileName);
        fillandpicture = FILLANDPICTURE::PICTURE;
        update();});

    connect(fillBtn,&DB_CustomPushButton_16::clicked,this,[=](){
        getColor();
        update();});

    connect(closeBtn,&DB_CustomPushButton_16::clicked,this,[=](){
        this->close();});
}

void Light::outRect(QPainter& paint)
{
    paint.setBrush(QColor(0,184,169));
    paint.drawEllipse((moverect.topLeft() +moverect.topRight())/2,Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
    paint.drawEllipse(moverect.topLeft(),Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
    paint.drawEllipse(moverect.topRight(),Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
    paint.drawEllipse((moverect.topLeft() +moverect.bottomLeft())/2,Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
    paint.drawEllipse((moverect.topRight() +moverect.bottomRight())/2,Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
    paint.drawEllipse((moverect.bottomLeft() +moverect.bottomRight())/2,Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
    paint.drawEllipse(moverect.bottomLeft(),Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
    paint.drawEllipse(moverect.bottomRight(),Public_Function::getScaleSize(my_r),Public_Function::getScaleSize(my_r));
}

Light::MOUSEPOS Light::getMousePos(QPoint dot) //通过长度与半径的比较判断点是否在圆内
{
    if(QLineF(dot,(moverect.topLeft() + moverect.topRight())/2).length() <= Public_Function::getScaleSize(my_r))
    {
        this->setCursor(Qt::SizeVerCursor);
        return mousepos = MOUSEPOS::UP;
    }
    else if(QLineF(dot,moverect.topLeft()).length() <= Public_Function::getScaleSize(my_r))
    {
        this->setCursor(Qt::SizeFDiagCursor);
        return mousepos = MOUSEPOS::UPLEFT;
    }
    else if(QLineF(dot,moverect.topRight()).length() <= Public_Function::getScaleSize(my_r))
    {
        this->setCursor(Qt::SizeBDiagCursor);
        return mousepos = MOUSEPOS::UPRIGHT;
    }
    else if(QLineF(dot,(moverect.topLeft() + moverect.bottomLeft())/2).length() <= Public_Function::getScaleSize(my_r))
    {
        this->setCursor(Qt::SizeHorCursor);
        return mousepos = MOUSEPOS::LEFT;
    }
    else if(QLineF(dot,(moverect.topRight() + moverect.bottomRight())/2).length() <= Public_Function::getScaleSize(my_r))
    {
        this->setCursor(Qt::SizeHorCursor);
        return mousepos = MOUSEPOS::RIGHT;
    }
    else if(QLineF(dot,(moverect.bottomLeft() + moverect.bottomRight())/2).length() <= my_r)
    {
        this->setCursor(Qt::SizeVerCursor);
        return mousepos = MOUSEPOS::DOWN;
    }
    else if(QLineF(dot,moverect.bottomLeft()).length() <= Public_Function::getScaleSize(my_r))
    {
        this->setCursor(Qt::SizeBDiagCursor);
        return mousepos = MOUSEPOS::DOWNLEFT;
    }
    else if(QLineF(dot,moverect.bottomRight()).length() <= Public_Function::getScaleSize(my_r))
    {
        this->setCursor(Qt::SizeFDiagCursor);
        return mousepos = MOUSEPOS::DOWNRIGHT;
    }
    else if(moverect.contains(dot))
    {
        this->setCursor(Qt::SizeAllCursor);
        return mousepos = MOUSEPOS::MOVE;
    }
    else
    {
       this->setCursor(Qt::ArrowCursor);
       return mousepos = MOUSEPOS::NO;
    }

}

void Light::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPainterPath path;
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
     if(fillandpicture == FILLANDPICTURE::FILL)
    {
        painter.setBrush(fillcolor);
        painter.setPen(Qt::NoPen);
        path.setFillRule(Qt::OddEvenFill);
        path.addRect(this->rect());
    }
    else if(fillandpicture == FILLANDPICTURE::PICTURE)
    {
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
        if(copypixmap->isNull())qDebug() << " isnull " << endl;
         QPixmap pix = copypixmap->copy(moverect);
         pix = pix.scaled(moverect.width(),moverect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
         QBrush brush(pix);
         painter.setBrushOrigin(moverect.topLeft());
         painter.setBrush(brush);
    }

    if(rectandround == RECTANDROUND::RECT)
    {
        path.addRect(moverect);
    }
    else if(rectandround == RECTANDROUND::ROUND)
    {
        path.addEllipse(moverect);
    }
    painter.drawPath(path);
    if(maxandmin == MAXANDMIN::MAX)
    {
        QPixmap pix = copypixmap->copy(QRect(moverect.center().x() -moverect.width()/(2*index),
                      moverect.center().y() -moverect.height()/(2*index),moverect.width()/index,moverect.height()/index));
        pix = pix.scaled(moverect.width(),moverect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QBrush brush(pix);
        painter.setBrush(brush);
    }
    else if(maxandmin == MAXANDMIN::MIN)
    {
        QPixmap pix = copypixmap->copy(QRect(moverect.center().x() -moverect.width()/(2*index),
                      moverect.center().y() -moverect.height()/(2*index),moverect.width()/index,moverect.height()/index));
        pix = pix.scaled(moverect.width(),moverect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QBrush brush(pix);
        painter.setBrush(brush);
        if(index == 1)
        {
            maxandmin = MAXANDMIN::NOCHANGE;
        }
    }
    if((maxandmin == MAXANDMIN::MIN)||(maxandmin == MAXANDMIN::MAX))
    {
         painter.setBrushOrigin(moverect.topLeft());//设置画刷起点和矩形起点一致，否则会出现矩阵
        if(rectandround == RECTANDROUND::RECT)
        {
            painter.drawRect(moverect);
        }
        else if(rectandround == RECTANDROUND::ROUND)
        {
            painter.drawEllipse(moverect);
        }
    }

    if(drawflag != 0)
    {
        outRect(painter);
    }
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(QColor(0,184,169),2,Qt::SolidLine,Qt::SquareCap));
    painter.drawRect(moverect);
}

void Light::mousePressEvent(QMouseEvent *event)
{
    textLab->hide();
    mousepos = getMousePos(event->pos());
    mousepress =true;
    if(mousepos != MOUSEPOS::NO)
    {
         mytool->hide();
    }
    presspoint = event->pos();
    oldrect =moverect;
    if(drawflag ==0)
    {
        drawflag =1;
        moverect = QRect(presspoint,presspoint);
    }
}

void Light::mouseMoveEvent(QMouseEvent *event)
{
   if(drawflag == 1)
   {
    releasepoint = event->pos();
    moverect = QRect(presspoint,releasepoint);
   }
   else if((mousepos == MOUSEPOS::UP)&&mousepress)
   {
       moverect.setTop(event->pos().y());
   }
   else if((mousepos == MOUSEPOS::UPLEFT)&&mousepress)
   {
       moverect.setTopLeft(event->pos());
   }
   else if((mousepos == MOUSEPOS::UPRIGHT)&&mousepress)
   {
       moverect.setTopRight(event->pos());
   }
   else if((mousepos == MOUSEPOS::LEFT)&&mousepress)
   {
       moverect.setLeft(event->pos().x());
   }
   else if((mousepos == MOUSEPOS::RIGHT)&&mousepress)
   {
       moverect.setRight(event->pos().x());
   }
   else if((mousepos == MOUSEPOS::DOWN)&&mousepress)
   {
       moverect.setBottom(event->pos().y());
   }
   else if((mousepos == MOUSEPOS::DOWNLEFT)&&mousepress)
   {
       moverect.setBottomLeft(event->pos());
   }
   else if((mousepos == MOUSEPOS::DOWNRIGHT)&&mousepress)
   {
       moverect.setBottomRight(event->pos());
   }
   else if((mousepos == MOUSEPOS::MOVE)&&mousepress)
   {
       int X = event->globalPos().x() -(presspoint.x() -oldrect.topLeft().x());
       int Y = event->globalPos().y() -(presspoint.y() -oldrect.topLeft().y());
       X = X > 0 ? (X + moverect.width() > this->width() ? this->width() - moverect.width() : X) : 0;
       Y = Y > 0 ? (Y + moverect.height() > this->height() ? this->height() - moverect.height() : Y) : 0;
       moverect.moveTo(X,Y);
   }
   else
   {
       getMousePos(event->pos());
   }
   update();
}

void Light::mouseReleaseEvent(QMouseEvent *event)
{
    if(drawflag == 1)
    {
     releasepoint = event->pos();
     moverect = QRect(presspoint,releasepoint);

     QPoint topleft;
     QPoint bottomright;
     topleft.setX(moverect.topLeft().x() <moverect.bottomRight().x()?moverect.topLeft().x() :moverect.bottomRight().x());
     topleft.setY(moverect.topLeft().y() <moverect.bottomRight().y()?moverect.topLeft().y() :moverect.bottomRight().y());
     bottomright.setX(moverect.topLeft().x() >moverect.bottomRight().x()?moverect.topLeft().x() :moverect.bottomRight().x());
     bottomright.setY(moverect.topLeft().y() >moverect.bottomRight().y()?moverect.topLeft().y() :moverect.bottomRight().y());
     moverect = QRect(topleft,bottomright);

     drawflag =2;
    }
    mousepress =false;
    mousepos = MOUSEPOS::NO;
    if(moverect.bottomLeft().y() > moverect.topLeft().y())
    {
        if( moverect.bottom() + mytool->height() +Public_Function::getScaleSize(20) >this->height())
        {
            mytool->move(moverect.left() +(moverect.width() -mytool->width())/2,moverect.top() - Public_Function::getScaleSize(20) -mytool->height());
        }
        else
        {
            mytool->move(moverect.left() +(moverect.width() -mytool->width())/2,moverect.bottom() + Public_Function::getScaleSize(20));
        }
    }
    else
    {
        if( moverect.top() + mytool->height() +Public_Function::getScaleSize(20) >this->height())
        {
            mytool->move(moverect.left() +(moverect.width() -mytool->width())/2,moverect.bottom() - Public_Function::getScaleSize(20) -mytool->height());
        }
        else
        {
            mytool->move(moverect.left() +(moverect.width() -mytool->width())/2,moverect.top() + Public_Function::getScaleSize(20));
        }

    }
    mytool->show();
    update();
}

void Light::getColor()
{
    DB_ColorPanel  *colorpanel = new DB_ColorPanel;
    colorpanel->setParent(this);
    connect(colorpanel, &DB_ColorPanel::colorPanelClosed,this,[=](int ret){
            if (1 == ret){
                fillcolor = colorpanel->getColor();
                fillandpicture = FILLANDPICTURE::FILL;
                update();
            }
            colorpanel->deleteLater();
    });
    colorpanel->setGeometry((this->width() - Public_Function::getScaleSize(colorpanel->width()))/2,(this->height() -Public_Function::getScaleSize(colorpanel->height()))/2,
                            Public_Function::getScaleSize(colorpanel->width()),Public_Function::getScaleSize(colorpanel->height()));
    colorpanel->show();
}
