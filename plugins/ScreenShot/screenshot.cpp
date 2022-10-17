#include "screenshot.h"
#include <QPainterPath>
#include <QDebug>
#include "Public/public_function.h"
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QScreen>
#include <QTimer>
#include <QApplication>

ScreenShot::ScreenShot(QWidget *parent) : ScreenShotInterFace(parent),mIsChinese(true)
{
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->initLayout();
    this->resize();

    timer = new QTimer(this);
    loop = new QEventLoop(this);
    connect(timer,&QTimer::timeout,this,[=](){
        timer->stop();
        QScreen* screen  = QGuiApplication::primaryScreen();
        pixmap =screen->grabWindow(QApplication::desktop()->winId(),0,0,-1,-1);
        this->show();
        loop->quit();
    });
}

void ScreenShot::show()
{
    QWidget::show();
    this->raise();
}

void ScreenShot::resize()
{
    QDesktopWidget *desktop =QApplication::desktop();
    textLab->setFont(Public_Function::getFont(64));
    textLab->setFixedSize(Public_Function::getScaleSize(desktop->width(),100));
    QSize size = Public_Function::getScaleSize(QSize(600, 80));
    size = Public_Function::getScaleSize(QSize(60, 70));
    confirm->setFixedSize(size);
    cancel->setFixedSize(size);
    size = Public_Function::getScaleSize(QSize(136, 82));
    toolwidget->setFixedSize(size);
    textLab->move((desktop->width() -textLab->width())/2,(desktop->height() -textLab->height())/2);
    r =Public_Function::getScaleSize(8);
    R = Public_Function::getScaleSize(12);
}

void ScreenShot::initLayout()
{   
    this->setGeometry(0,0,Public_Function::getScaleSize(301),Public_Function::getScaleSize(156));
    textLab = new QLabel(tr("请拖拽一个区域"),this);
    textLab->setMouseTracking(true);
    textLab->setAlignment(Qt::AlignCenter);
    textLab->setStyleSheet(QString("color:white;"));
    textLab->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    textLab->hide();
    toolwidget = new QWidget(this);
    toolwidget->setStyleSheet(QString("background-color:white;border-radius:%1px;").arg(Public_Function::getScaleSize(12)));
    toolwidget->hide();
    confirm = new mPushButton_1(this);
    confirm->setTextAndPixmap(tr("确定"),QPixmap(":/pixmap/yuansu2@2x.png"));
    cancel =  new mPushButton_1(this);
    cancel->setTextAndPixmap(tr("取消"),QPixmap(":/pixmap/yuansu1@2x.png"));
    QHBoxLayout *hlayout = new QHBoxLayout(toolwidget);
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addStretch(0);
    hlayout->addWidget(cancel);
    hlayout->addStretch(0);
    hlayout->addWidget(confirm);
    hlayout->addStretch(0);

    connect(cancel,&mPushButton_1::clicked,this,[=](){
        toolwidget->hide();
        setShow(2);
        this->setGeometry(recordpos);
        shotshape =4;
        update();
        emit sendShotPixmap(QPixmap());
    });

    connect(confirm,&mPushButton_1::clicked,this,[=](){
        toolwidget->hide();
        this->hide();
        timer->start(50);
        loop->exec();
        if(shotshape ==0)
        {
            toolwidget->hide();
            pixmap = pixmap.copy(mrect);
            emit sendShotPixmap(pixmap);
            this->setGeometry(recordpos);
            shotshape =4;
            desktop_Lab->setObjectName("desktop");
            desktop_Lab->changePixmapAndText(QPixmap(":/pixmap/jietu3@2x.png"),tr("显示桌面"));
            if( !mIsChinese)
                desktop_Lab->setLocalText("ShowDesktop");
            setShow(2);
            update();

        }
        else if(shotshape ==1 ||shotshape ==3)
        {
            toolwidget->hide();
            setShow(2);
            QPixmap pix = getShotPixmap(pixmap);
            emit sendShotPixmap(pix);
            this->setGeometry(recordpos);
            shotshape =4;
            desktop_Lab->setObjectName("desktop");
            desktop_Lab->changePixmapAndText(QPixmap(":/pixmap/jietu3@2x.png"),tr("显示桌面"));
            if( !mIsChinese)
                desktop_Lab->setLocalText("ShowDesktop");
            update();
        }
    });


    back_Lab = new QLabel(this);
    back_Lab->installEventFilter(this);
    back_Lab->setPixmap(QPixmap(":/pixmap/fanhui@2x.png"));

    text_Lab = new QLabel(tr("截图"),this);
    text_Lab->setStyleSheet(QString("font-size:%1px;font-family: Microsoft YaHei;").arg(Public_Function::getScaleSize(16)));

    rect_Lab = new Label_1(QPixmap(":/pixmap/jietu1@2x.png"),tr("矩形截图"),this);
    rect_Lab->installEventFilter(this);

    free_Lab = new Label_1(QPixmap(":/pixmap/jietu2@2x.png"),tr("自由截图"),this);
    free_Lab->installEventFilter(this);

    desktop_Lab = new Label_1(QPixmap(":/pixmap/jietu3@2x.png"),tr("显示桌面"),this);
    desktop_Lab->installEventFilter(this);
    desktop_Lab->setObjectName("desktop");

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(back_Lab);
    hlayout1->addWidget(text_Lab);
    hlayout1->addStretch(0);
    hlayout1->setSpacing(Public_Function::getScaleSize(15));
    hlayout1->setContentsMargins(Public_Function::getScaleSize(20),Public_Function::getScaleSize(16),0,Public_Function::getScaleSize(27));

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(rect_Lab);
    hlayout2->addWidget(free_Lab);
    hlayout2->addStretch(0);
    hlayout2->addWidget(desktop_Lab);
    hlayout2->setSpacing(Public_Function::getScaleSize(26));
    hlayout2->setContentsMargins(Public_Function::getScaleSize(26),0,Public_Function::getScaleSize(26),0);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addStretch(0);
    vlayout->setMargin(0);
}

void ScreenShot::changeFreeShot(int a)
{
    this->hide();
    setShow(1);
    this->show();
    if(a ==1)
    {
        this->setMouseTracking(true);
        if( mIsChinese)
            textLab->setText(tr("请拖拽一个区域"));
        else
            textLab->setText(tr("Please Drag An Rect Area"));
        shotshape =0;
        drawflag =0;
    }
    if(a ==2)
    {
        this->setMouseTracking(false);
        textLab->setText( mIsChinese ? tr("请自由绘制一个区域截图") : "Please Draw A Custom Area");
        shotshape =1;
        shotpath.clear();
        listpoint.clear();
    }
    toolwidgethide =1;
    mrect =QRect();
    recordpos = this->geometry();
    textLab->show();
    QDesktopWidget *desktop =QApplication::desktop();
    this->setGeometry(desktop->rect());
    update();
}

ScreenShotInterFace *ScreenShot::getWidget()
{
    ScreenShot *screenshot = new ScreenShot();
    return screenshot;
}

void ScreenShot::updateLanguage(bool isChinese)
{
    mIsChinese = isChinese;
    if( isChinese)
    {
        text_Lab->setText(tr("截图"));
        rect_Lab->setLocalText( tr("矩形截图"));
        free_Lab->setLocalText( tr("自由截图"));
        desktop_Lab->setLocalText(tr("显示桌面"));
        confirm->setLocalText(tr("确定"));
        cancel->setLocalText(tr("取消"));
    }else
    {
        text_Lab->setText("ScreenShot ");
        rect_Lab->setLocalText( tr("Rect"));
        free_Lab->setLocalText( tr("Custom"));
        desktop_Lab->setLocalText(tr("Desktop"));
        confirm->setLocalText("Yes");
        cancel->setLocalText("No");
    }

}

void ScreenShot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(shotshape <4)
    {
        if(shotshape ==0)
        {
            QPainterPath path;
            path.addRect(this->rect());
            path.addRect(mrect);
            path.setFillRule(Qt::OddEvenFill);
            painter.fillPath(path, QBrush(QColor(115, 115, 115, 200)));
            if(drawflag != 0)
            {
                painter.setPen(QPen(QBrush(QColor(20,134,250)), 1, Qt::SolidLine));
                painter.setBrush(Qt::transparent);
                painter.drawRect(mrect);
                painter.setBrush(Qt::white);
                if(mousestate ==true)
                {
                    if(mousepos ==MOUSEPOS::UP)painter.drawEllipse((mrect.topLeft() +mrect.topRight())/2, R, R);
                    else if(mousepos ==MOUSEPOS::LEFTUP)painter.drawEllipse(mrect.topLeft(), R, R);
                    else if(mousepos ==MOUSEPOS::RIGHTUP)painter.drawEllipse(mrect.topRight(), R, R);
                    else if(mousepos ==MOUSEPOS::LEFT)painter.drawEllipse((mrect.topLeft() +mrect.bottomLeft())/2, R, R);
                    else if(mousepos ==MOUSEPOS::RIGHT)painter.drawEllipse((mrect.topRight() +mrect.bottomRight())/2, R, R);
                    else if(mousepos ==MOUSEPOS::DOWN)painter.drawEllipse((mrect.bottomLeft() +mrect.bottomRight())/2, R, R);
                    else if(mousepos ==MOUSEPOS::LEFTDOWN)painter.drawEllipse(mrect.bottomLeft(), R, R);
                    else if(mousepos ==MOUSEPOS::RIGHTDOWN)painter.drawEllipse(mrect.bottomRight(), R, R);
                }
                painter.setBrush(QColor(20,134,250));
                painter.setPen(QPen(QColor(20,134,250), 1, Qt::SolidLine));
                painter.drawEllipse((mrect.topLeft() +mrect.topRight())/2,r,r);
                painter.drawEllipse(mrect.topLeft(),r,r);
                painter.drawEllipse(mrect.topRight(),r,r);
                painter.drawEllipse((mrect.topLeft() +mrect.bottomLeft())/2,r,r);
                painter.drawEllipse((mrect.topRight() +mrect.bottomRight())/2,r,r);
                painter.drawEllipse((mrect.bottomLeft() +mrect.bottomRight())/2,r,r);
                painter.drawEllipse(mrect.bottomLeft(),r,r);
                painter.drawEllipse(mrect.bottomRight(),r,r);
            }
        }
        else if((shotshape ==1)||(shotshape ==3))
        {
            QPainterPath pathOut;
            QPainterPath pathIn;
            pathOut.addRect(this->rect());
            pathOut.setFillRule(Qt::OddEvenFill);
            pathIn.setFillRule(Qt::OddEvenFill);
            for (int var = 0; var < listpoint.size(); ++var) {
               if(var ==0)
               {
                   pathIn.moveTo(listpoint.at(0));
                   x1 =listpoint.at(0).x();
                   x2 =listpoint.at(0).x();
                   y1 =listpoint.at(0).y();
                   y2 =listpoint.at(0).y();
               }
               else pathIn.quadTo(listpoint.at(var -1),(listpoint.at(var -1) +listpoint.at(var))/2);
               x1 =x1 > listpoint.at(var).x()?listpoint.at(var).x():x1;
               x2 =x2 < listpoint.at(var).x()?listpoint.at(var).x():x2;
               y1 =y1 > listpoint.at(var).y()?listpoint.at(var).y():y1;
               y2 =y2 < listpoint.at(var).y()?listpoint.at(var).y():y2;
            }
            painter.setPen(QPen(Qt::green,2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
            pathOut.addPath(pathIn);
            painter.setBrush(QColor(115, 115, 115, 200));
            painter.drawPath(pathOut);
            shotpath.clear();
            shotpath =pathIn;
        }
    }
    else if(shotshape ==4)
    {
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(this->rect(),Public_Function::getScaleSize(12),Public_Function::getScaleSize(12));
        painter.setPen(QPen(QColor(224,224,224),Public_Function::getScaleSize(1)));
        painter.drawLine(Public_Function::getScaleSize(24),Public_Function::getScaleSize(48),
                         this->width() -Public_Function::getScaleSize(24),Public_Function::getScaleSize(48));
        painter.drawLine(Public_Function::getScaleSize(191),Public_Function::getScaleSize(85),
                         Public_Function::getScaleSize(191),this->height() -Public_Function::getScaleSize(35));
    }
}

void ScreenShot::mousePressEvent(QMouseEvent *event)
{
    if(shotshape <4)
    {
        textLab->hide();
        if(!toolwidget->isHidden())toolwidget->hide();
        mousestate =true;
        if(shotshape == 0)
        {
            toolwidgethide =2;
            mousepos=getMousePos(event->pos());
            if(drawflag ==0)
            {
                drawflag =1;
                mousepos =MOUSEPOS::RIGHTDOWN;
                mousepressdot = event->pos();
            }
            else
            {
                mousepressdot = event->pos() -mrect.topLeft();
            }
        }
        else if(shotshape == 1)
        {
            toolwidgethide =2;
            listpoint.append(event->pos());
        }
    }
    else
    {
       mousestate =true;
       mousepressdot = event->pos();
    }
}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    if(shotshape < 4)
    {
        if(shotshape == 0)
        {
            if(mousestate == true)
            {
                if(drawflag == 1)
                {
                    mrect =QRect(mousepressdot,event->pos());
                }
                if(mousepos == MOUSEPOS::UP)
                {
                    mrect.setTop(event->y());
                }
                else if(mousepos == MOUSEPOS::LEFTUP)
                {
                    mrect.setTopLeft(event->pos());
                }
                else if(mousepos == MOUSEPOS::RIGHTUP)
                {
                    mrect.setTopRight(event->pos());
                }
                else if(mousepos == MOUSEPOS::LEFT)
                {
                    mrect.setLeft(event->pos().x());
                }
                else if(mousepos == MOUSEPOS::RIGHT)
                {
                    mrect.setRight(event->pos().x());
                }
                else if(mousepos == MOUSEPOS::DOWN)
                {
                    mrect.setBottom(event->pos().y());
                }
                else if(mousepos == MOUSEPOS::LEFTDOWN)
                {
                    mrect.setBottomLeft(event->pos());
                }
                else if(mousepos == MOUSEPOS::RIGHTDOWN)
                {
                    mrect.setBottomRight(event->pos());
                }
                else if(mousepos == MOUSEPOS::MOVE)
                {
                    int X = event->pos().x() -mousepressdot.x();
                    int Y = event->pos().y() -mousepressdot.y();
                    X = X>0? (this->width() -X -mrect.width() >0? X:this->width() -mrect.width()):0;
                    Y = Y>0? (this->height() -Y -mrect.height() >0? Y:this->height() -mrect.height()):0;
                    mrect.moveTo(X,Y);
                }
            }
            else
            {
                mousepos=getMousePos(event->pos());
            }
        }
        else if(shotshape == 1)
        {
            listpoint.append(event->pos());
        }
    }
    else {
        if(mousestate == true)
        {
            this->move(event->globalPos() -mousepressdot);
        }
    }
    update();
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *event)
{
    if(shotshape < 4)
    {
        if(shotshape == 0)
        {
            mousestate =false;
            if(drawflag ==1)
            {
                drawflag =2;
                mrect =QRect(mousepressdot,event->pos());
            }
            x1 = mrect.topLeft().x() <mrect.bottomRight().x()?mrect.topLeft().x():mrect.bottomRight().x();
            y1 = mrect.topLeft().y() <mrect.bottomRight().y()?mrect.topLeft().y():mrect.bottomRight().y();
            x2 = mrect.topLeft().x() >mrect.bottomRight().x()?mrect.topLeft().x():mrect.bottomRight().x();
            y2 = mrect.topLeft().y() >mrect.bottomRight().y()?mrect.topLeft().y():mrect.bottomRight().y();
            mrect = QRect(QPoint(x1,y1),QPoint(x2,y2));
        }
        else if((shotshape == 1)&&(toolwidgethide != 1))
        {
            listpoint.append(event->pos());
            mrect = QRect(QPoint(x1,y1),QPoint(x2,y2));
            qDebug()<< "mrect12 " << mrect <<Qt::endl;
            shotshape =3;
            update();
        }

        if(toolwidget->isHidden()&&(toolwidgethide != 1))
        {
            qreal x = mrect.bottomLeft().x() +(mrect.width() -toolwidget->width())/2;
            qreal y = mrect.bottomRight().y() + Public_Function::getScaleSize(15);
            qreal y1 = (y +toolwidget->height())>this->height()? (y -toolwidget->height() -Public_Function::getScaleSize(30)):y;
            toolwidget->move(x,y1);
            toolwidget->show();
        }
    }
    else
    {
        mousestate =false;
    }
    update();
}

bool ScreenShot::eventFilter(QObject *watched, QEvent *event)
{   
    if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if(watched == back_Lab)
        {
            qDebug()<< " back_Lab"  <<Qt::endl;
            emit sendCloseMessage();
            return true;
        }
        else if(watched == rect_Lab)
        {
            changeFreeShot(1);
            return true;
        }
        else if(watched == free_Lab)
        {
            changeFreeShot(2);
            return true;
        }
        else if(watched == desktop_Lab)
        {
            if(desktop_Lab->objectName() == "desktop")
            {
                desktop_Lab->setObjectName("white");
                desktop_Lab->changePixmapAndText(QPixmap(":/pixmap/jietu3b@2x.png"),tr("返回白板"));
                if( !mIsChinese)
                    desktop_Lab->setLocalText("  Back  ");
                emit sendDesktopShow(1);
            }
            else if(desktop_Lab->objectName() == "white")
            {
                desktop_Lab->setObjectName("desktop");
                desktop_Lab->changePixmapAndText(QPixmap(":/pixmap/jietu3@2x.png"),tr("显示桌面"));
                if( !mIsChinese)
                    desktop_Lab->setLocalText("Desktop");
                emit sendDesktopShow(2);
            }
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

ScreenShot::MOUSEPOS ScreenShot::getMousePos(QPoint dot)
{
    if(QLineF((mrect.topLeft() +mrect.topRight())/2,dot).length() <r)
    {
        this->setCursor(Qt::SizeVerCursor);
        return MOUSEPOS::UP;
    }
    else if(QLineF(mrect.topLeft() ,dot).length() <r)
    {
        this->setCursor(Qt::SizeFDiagCursor);
        return MOUSEPOS::LEFTUP;
    }
    else if(QLineF(mrect.topRight() ,dot).length() <r)
    {
        this->setCursor(Qt::SizeBDiagCursor);
        return MOUSEPOS::RIGHTUP;
    }
    else if(QLineF((mrect.topLeft() +mrect.bottomLeft())/2 ,dot).length() <r)
    {
        this->setCursor(Qt::SizeHorCursor);
        return MOUSEPOS::LEFT;
    }
    else if(QLineF((mrect.topRight() +mrect.bottomRight())/2 ,dot).length() <r)
    {
        this->setCursor(Qt::SizeHorCursor);
        return MOUSEPOS::RIGHT;
    }
    else if(QLineF((mrect.bottomLeft() +mrect.bottomRight())/2 ,dot).length() <r)
    {
        this->setCursor(Qt::SizeVerCursor);
        return MOUSEPOS::DOWN;
    }
    else if(QLineF(mrect.bottomLeft(),dot).length() <r)
    {
        this->setCursor(Qt::SizeBDiagCursor);
        return MOUSEPOS::LEFTDOWN;
    }
    else if(QLineF(mrect.bottomRight(),dot).length() <r)
    {
        this->setCursor(Qt::SizeFDiagCursor);
        return MOUSEPOS::RIGHTDOWN;
    }
    else if(mrect.contains(dot))
    {
        this->setCursor(Qt::SizeAllCursor);
        return MOUSEPOS::MOVE;
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
        return MOUSEPOS::NO;
    }
}

QPixmap ScreenShot::getShotPixmap(QPixmap pix)
{
    QPixmap picture(this->width(),this->height());
    picture.fill(Qt::transparent);
    QPainter painter(&picture);
    QBrush brush(pix);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawPath(shotpath);
    return picture.copy(mrect);
}

void ScreenShot::setShow(int a)
{
    if(a == 1)
    {
        back_Lab->hide();
        text_Lab->hide();
        rect_Lab->hide();
        free_Lab->hide();
        desktop_Lab->hide();
    }
    else if(a ==2)
    {
        back_Lab->show();
        text_Lab->show();
        rect_Lab->show();
        free_Lab->show();
        desktop_Lab->show();
    }
}

#if QT_VERSION < 0x050000
//第一个参数为接口类名，第二个参数为当前类名
Q_EXPORT_PLUGIN2(ScreenShotInterFace, ScreenShot)
#endif // QT_VERSION < 0x050000
