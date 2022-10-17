#include "myveil.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QBoxLayout>
#include <QFileDialog>
#include <QButtonGroup>
#include "ToolPanel/db_colorpanel.h"
#include "Public/public_function.h"
#include "VirtualKeyBoard/keyboard.h"
Myveil::Myveil(QWidget *parent) : QWidget(parent)
{
    iconwidth = adapt(24);
    margin = adapt(6);
    QDesktopWidget *desktop = QApplication::desktop();
    this->setGeometry(0,0,desktop->width(),desktop->height());
    this->setWindowFlag(Qt::FramelessWindowHint,true);
    this->setMinimumSize(adapt(260),adapt(260));
    interFaceInit();
    connectInit();

}

void Myveil::getMousePos(QPoint dot)
{
    if(QLineF(topleft.center(),dot).length() <= iconwidth/2)
    {
        mousepos = MOUSEPOS::TOPLEFT;
    }
    else if(QLineF(topright.center(),dot).length() <= iconwidth/2)
    {
        mousepos = MOUSEPOS::TOPRIGHT;
    }
    else if(QLineF(bottomleft.center(),dot).length() <= iconwidth/2)
    {
        mousepos = MOUSEPOS::BOTTOMLEFT;
    }
    else if(QLineF(bottomright.center(),dot).length() <= iconwidth/2)
    {
        mousepos = MOUSEPOS::BOTTOMRIGHT;
    }
    else
    {
        mousepos = MOUSEPOS::MOVE;
    }

}

void Myveil::interFaceInit()
{
    topleft =QRect(0,0,iconwidth,iconwidth);
    topright =QRect(0,0,iconwidth,iconwidth);
    bottomleft =QRect(0,0,iconwidth,iconwidth);
    bottomright =QRect(0,0,iconwidth,iconwidth);
    frame = new QFrame(this);
    frame->resize(adapt(158),adapt(54));
    frame->setStyleSheet(QString("background-color:rgb(9,61,115);border-radius: %1px;").arg(adapt(12)));
    pictureBtn = new QPushButton(this);
    pictureBtn->setIcon(QIcon(":/images/veilpixmap/picture2.png"));
    pictureBtn->setIconSize(adapt(40,40));
    pictureBtn->setCheckable(true);
    pictureBtn->setFlat(true);
    fillBtn = new QPushButton(this);
    fillBtn->setIcon(QIcon(":/images/veilpixmap/fill2.png"));
    fillBtn->setIconSize(adapt(40,40));
    fillBtn->setCheckable(true);
    fillBtn->setFlat(true);
    closeBtn = new QPushButton(this);
    closeBtn->setIcon(QIcon(":/images/veilpixmap/close2.png"));
    closeBtn->setIconSize(adapt(40,40));
    closeBtn->setCheckable(true);
    closeBtn->setFlat(true);
    QHBoxLayout *hlayout = new QHBoxLayout(frame);
    hlayout->addWidget(pictureBtn);
    hlayout->addWidget(fillBtn);
    hlayout->addWidget(closeBtn);
    hlayout->setContentsMargins(adapt(10),0,adapt(10),0);
    pictureBtn->setStyleSheet("QPushButton:hover{background-color: rgb(6,41,78);}");
    fillBtn->setStyleSheet("QPushButton:hover{background-color: rgb(6,41,78);}");
    closeBtn->setStyleSheet("QPushButton:hover{background-color: rgb(6,41,78);}");
    QButtonGroup *group = new QButtonGroup(this);
    group->setExclusive(true);
    group->addButton(pictureBtn);
    group->addButton(fillBtn);
    group->addButton(closeBtn);


}

void Myveil::connectInit()
{
    connect(pictureBtn,&QPushButton::clicked,this,[=](){
        pictureBtn->setStyleSheet(QString("background-color:rgb(6,41,78);border-radius: %1px;").arg(adapt(12)));
        fillBtn->setStyleSheet(QString("background-color:rgb(9,61,115);border-radius: %1px;").arg(adapt(12)));
        closeBtn->setStyleSheet(QString("background-color:rgb(9,61,115);border-radius: %1px;").arg(adapt(12)));
        Keyboard key;
        //key.move((this->width() -key.width())/2,this->rect().bottom() -key.height() -Public_Function::getScaleSize(70));
        key.hide();
        QString filename = QFileDialog::getOpenFileName(this,tr("打开图片"),".",tr("Image File (*.jpg *.png *.bmp)"));
        if(!filename.isEmpty())
        {
           pixmap.load(filename);
           fillandpicture = FILLANDPICTURE::PICTURE;
        }
        update();
    });

    connect(fillBtn,&QPushButton::clicked,this,[=](){
        fillBtn->setStyleSheet(QString("background-color:rgb(6,41,78);border-radius: %1px;").arg(adapt(12)));
        pictureBtn->setStyleSheet(QString("background-color:rgb(9,61,115);border-radius: %1px;").arg(adapt(12)));
        closeBtn->setStyleSheet(QString("background-color:rgb(9,61,115);border-radius: %1px;").arg(adapt(12)));
         QWidget *parent = static_cast<QWidget *>(this->parent());
        DB_ColorPanel *colorPanel = new DB_ColorPanel(backgroundcolor, parent);
        connect(colorPanel, &DB_ColorPanel::colorPanelClosed, [=](int ret){
            if (1 == ret) {
                backgroundcolor = colorPanel->getColor();
                 fillandpicture = FILLANDPICTURE::FILL;
                update();
            }
            colorPanel->deleteLater();
        });
        colorPanel->setGeometry(0, 0, parent->width(), parent->height());
        colorPanel->show();
    });

    connect(closeBtn,&QPushButton::clicked,this,[=](){
        closeBtn->setStyleSheet("background-color:rgb(6,41,78)");
        this->close();
    });
}

int Myveil::adapt(int n)
{
    return Public_Function::getScaleSize(n);
}

QSize Myveil::adapt(int m, int n)
{
    return Public_Function::getScaleSize(m,n);
}

void Myveil::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform,true);
    painter.setPen(Qt::NoPen);
    topleft.moveTo(margin,margin);
    topright.moveTo(this->width() -margin -iconwidth,margin);
    bottomleft.moveTo(margin,this->height() -margin -iconwidth);
    bottomright.moveTo(this->width() -margin -iconwidth,this->height() -margin -iconwidth);
    frame->move((this->width() -frame->width())/2,this->height() -frame->height() -adapt(12));
    if(fillandpicture == FILLANDPICTURE::FILL)
    {
        QBrush brush(backgroundcolor);
        painter.setBrush(brush);
        painter.drawRoundedRect(this->rect(),adapt(8),adapt(8));
    }
    else if(fillandpicture == FILLANDPICTURE::PICTURE)
    {
        QPixmap pix = pixmap.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        QBrush brush(pix);
        painter.setBrushOrigin(this->rect().topLeft());
        painter.setBrush(brush);
        painter.drawRoundedRect(this->rect(),adapt(8),adapt(8));
    }
    if(mousepos != MOUSEPOS::MOVE)
    {
        painter.setBrush(QColor(9,61,115));
        painter.drawEllipse(topleft);
        painter.drawEllipse(topright);
        painter.drawEllipse(bottomleft);
        painter.drawEllipse(bottomright);
        painter.drawPixmap(topleft,QPixmap(":/images/veilpixmap/topleft2.png"));
        painter.drawPixmap(topright,QPixmap(":/images/veilpixmap/topright2.png"));
        painter.drawPixmap(bottomleft,QPixmap(":/images/veilpixmap/topright2.png"));
        painter.drawPixmap(bottomright,QPixmap(":/images/veilpixmap/topleft2.png"));
        if(mousestate)
        {
            if(mousepos ==MOUSEPOS::TOPLEFT)
            {
                painter.drawPixmap(topleft,QPixmap(":/images/veilpixmap/topleftclick2.png"));
            }
            else if(mousepos ==MOUSEPOS::TOPRIGHT)
            {
                painter.drawPixmap(topright,QPixmap(":/images/veilpixmap/toprightclick2.png"));
            }
            else if(mousepos ==MOUSEPOS::BOTTOMLEFT)
            {
                painter.drawPixmap(bottomleft,QPixmap(":/images/veilpixmap/toprightclick2.png"));
            }
            else if(mousepos ==MOUSEPOS::BOTTOMRIGHT)
            {
                painter.drawPixmap(bottomright,QPixmap(":/images/veilpixmap/topleftclick2.png"));
            }
        }
    }
}


void Myveil::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
       getMousePos(event->pos());
       mousepress = event->pos();
       mousestate = true;
       oldrect = this->geometry();
    }
    update();
}

void Myveil::mouseMoveEvent(QMouseEvent *event)
{
    if(mousepos == MOUSEPOS::TOPLEFT)
    {
        QRect rect = this->geometry();
        int x = (event->globalPos() -mousepress).x();
        int y = (event->globalPos() -mousepress).y();
        int width = rect.bottomRight().x() -x;
        int height = rect.bottomRight().y() -y;
        x = width > adapt(260) ? x : rect.bottomRight().x() - adapt(260);
        y = height > adapt(260) ? y : rect.bottomRight().y() - adapt(260);
        rect.setTopLeft(QPoint(x,y));
        this->setGeometry(rect);
    }
    else if(mousepos == MOUSEPOS::TOPRIGHT)
    {
        QRect rect = this->geometry();
        int x = event->globalPos().x() +oldrect.width() -mousepress.x();
        int y = event->globalPos().y() -mousepress.y();
        int width = x -rect.topLeft().x();
        int height = rect.bottomLeft().y() -y;
        x = width > adapt(260) ? x : rect.bottomLeft().x() + adapt(260);
        y = height > adapt(260) ? y : rect.bottomRight().y() - adapt(260);
        rect.setTopRight(QPoint(x,y));
        this->setGeometry(rect);
    }
    else if(mousepos == MOUSEPOS::BOTTOMLEFT)
    {
        QRect rect = this->geometry();
        int x = event->globalPos().x() -mousepress.x();
        int y = event->globalPos().y() + oldrect.height() -mousepress.y();
        int width = rect.topRight().x() - x;
        int height = y - rect.topRight().y();
        x = width > adapt(260) ? x : rect.topRight().x() - adapt(260);
        y = height > adapt(260) ? y : rect.topRight().y() + adapt(260);
        rect.setBottomLeft(QPoint(x, y));
        this->setGeometry(rect);
    }
    else if(mousepos == MOUSEPOS::BOTTOMRIGHT)
    {
        QRect rect = this->geometry();
        rect.setBottomRight(QPoint(event->globalPos().x() +oldrect.width() -mousepress.x(),event->globalPos().y() + oldrect.height() -mousepress.y()));
        this->setGeometry(rect);
    }
    else
    {
        frame->hide();
        QDesktopWidget *desktop = QApplication::desktop();
        int X = event->globalPos().x() >mousepress.x()?(this->width() -mousepress.x() +event->globalPos().x() >desktop->width()?desktop->width() -this->width():event->globalPos().x() -mousepress.x()):0;
        int Y = event->globalPos().y() >mousepress.y()?(this->height() -mousepress.y() +event->globalPos().y() >desktop->height()?desktop->height() -this->height():event->globalPos().y() -mousepress.y()):0;
        this->setGeometry(X,Y,this->width(),this->height());
    }
    update();
}

void Myveil::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mousestate = false;
    mousepos = MOUSEPOS::NO;
    frame->show();
    update();
}
