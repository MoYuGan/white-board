#include "keyboard.h"
#include "ui_keyboard.h"
#include "Public/public_function.h"
#include "QDebug"
#include <QCursor>
#include <QApplication>
#include <QtGui>
#include <Public/public_function.h>
#include <QDesktopWidget>

Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
    str.clear();
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    this->setFixedSize(Public_Function::getScaleSize(602,200));
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    initCustomText(2);
    resize();
    initStyle();
    initConnect();
    ui->move->installEventFilter(this);
    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() -this->width())/2,desktop->height() -this->height() -Public_Function::getScaleWidth(30));
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::initCustomText(int n)
{
    if(1 == n)
    {
        ui->q->setText("Q");
        ui->w->setText("W");
        ui->e->setText("E");
        ui->r->setText("R");
        ui->t->setText("T");
        ui->y->setText("Y");
        ui->u->setText("U");
        ui->i->setText("I");
        ui->o->setText("O");
        ui->p->setText("P");
        ui->backspace->setText("Backspace");
        ui->a->setText("A");
        ui->s->setText("S");
        ui->d->setText("D");
        ui->f->setText("F");
        ui->g->setText("G");
        ui->h->setText("H");
        ui->j->setText("J");
        ui->k->setText("K");
        ui->l->setText("L");
        ui->enter->setText("Enter");
        ui->capslock->setText("CapsLock");
        ui->z->setText("Z");
        ui->x->setText("X");
        ui->c->setText("C");
        ui->v->setText("V");
        ui->b->setText("B");
        ui->n->setText("N");
        ui->m->setText("M");
        ui->douhao->setText(",");
        ui->juhao->setText(".");
        ui->capslock_2->setText("CapsLock");
        ui->num->setText("123");
        ui->kongge->setText(" ");
        ui->danyinghao->setText("'");
        ui->close->setText("Esc");
    }
    else if(2 == n)
    {
        ui->q->setText("q");
        ui->w->setText("w");
        ui->e->setText("e");
        ui->r->setText("r");
        ui->t->setText("t");
        ui->y->setText("y");
        ui->u->setText("u");
        ui->i->setText("i");
        ui->o->setText("o");
        ui->p->setText("p");
        ui->backspace->setText("Backspace");
        ui->a->setText("a");
        ui->s->setText("s");
        ui->d->setText("d");
        ui->f->setText("f");
        ui->g->setText("g");
        ui->h->setText("h");
        ui->j->setText("j");
        ui->k->setText("k");
        ui->l->setText("l");
        ui->enter->setText("Enter");
        ui->capslock->setText("CapsLock");
        ui->z->setText("z");
        ui->x->setText("x");
        ui->c->setText("c");
        ui->v->setText("v");
        ui->b->setText("b");
        ui->n->setText("n");
        ui->m->setText("m");
        ui->douhao->setText(",");
        ui->juhao->setText(".");
        ui->capslock_2->setText("CapsLock");
        ui->num->setText("123");
        ui->kongge->setText(" ");
        ui->danyinghao->setText("'");
        ui->close->setText("Esc");
    }
    else if(3 == n)
    {
        ui->q->setText("1");
        ui->w->setText("2");
        ui->e->setText("3");
        ui->r->setText("4");
        ui->t->setText("5");
        ui->y->setText("6");
        ui->u->setText("7");
        ui->i->setText("8");
        ui->o->setText("9");
        ui->p->setText("0");
        ui->backspace->setText("Backspace");
        ui->a->setText("@");
        ui->s->setText("#");
        ui->d->setText("%");
        ui->f->setText("&&");
        ui->g->setText("*");
        ui->h->setText("-");
        ui->j->setText("+");
        ui->k->setText("(");
        ui->l->setText(")");
        ui->enter->setText("Enter");
        ui->capslock->setText("1/2");
        ui->z->setText("!");
        ui->x->setText("''");
        ui->c->setText("<");
        ui->v->setText(">");
        ui->b->setText("'");
        ui->n->setText(":");
        ui->m->setText(";");
        ui->douhao->setText("/");
        ui->juhao->setText("?");
        ui->capslock_2->setText("1/2");
        ui->num->setText("ABC");
        ui->kongge->setText(" ");
        ui->danyinghao->setText("'");
        ui->close->setText("Esc");
    }
    else if(4 == n)
    {
        ui->q->setText("~");
        ui->w->setText("`");
        ui->e->setText("|");
        ui->r->setText("·");
        ui->t->setText("√");
        ui->y->setText("÷");
        ui->u->setText("×");
        ui->i->setText("½");
        ui->o->setText("{");
        ui->p->setText("}");
        ui->backspace->setText("Backspace");
        ui->a->setText("$");
        ui->s->setText("€");
        ui->d->setText("£");
        ui->f->setText("￠");
        ui->g->setText("¥");
        ui->h->setText("=");
        ui->j->setText("§");
        ui->k->setText("[");
        ui->l->setText("]");
        ui->enter->setText("Enter");
        ui->capslock->setText("2/2");
        ui->z->setText("_");
        ui->x->setText("™");
        ui->c->setText("®");
        ui->v->setText("《");
        ui->b->setText("》");
        ui->n->setText("“");
        ui->m->setText("”");
        ui->douhao->setText("\\");
        ui->juhao->setText("^");
        ui->capslock_2->setText("2/2");
        ui->num->setText("ABC");
        ui->kongge->setText(" ");
        ui->danyinghao->setText("'");
        ui->close->setText("Esc");
    }
    QIcon icon(QPixmap("://pixmap/lock@4x.png").scaled(Public_Function::getScaleSize(32),Public_Function::getScaleSize(32),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->move->setIcon(icon);
    ui->move->setIconSize(Public_Function::getScaleSize(40,40));

}

void Keyboard::initStyle()
{
    ui->q->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->w->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->e->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->r->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->t->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->y->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->u->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->i->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->o->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->p->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->backspace->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->a->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->s->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->d->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->f->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->g->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->h->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->j->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->k->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->l->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->enter->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->capslock->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->z->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->x->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->c->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->v->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->b->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->n->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->m->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->douhao->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->juhao->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->capslock_2->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->num->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->kongge->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->danyinghao->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->move->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    ui->close->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
}

void Keyboard::resize()
{
    ui->q->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->w->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->e->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->r->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->t->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->y->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->u->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->i->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->o->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->p->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->backspace->setFixedSize(Public_Function::getScaleSize(80,40));
    ui->a->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->s->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->d->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->f->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->g->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->h->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->j->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->k->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->l->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->enter->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->capslock->setFixedSize(Public_Function::getScaleSize(80,40));
    ui->z->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->x->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->c->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->v->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->b->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->n->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->m->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->douhao->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->juhao->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->capslock_2->setFixedSize(Public_Function::getScaleSize(80,40));
    ui->num->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->kongge->setFixedSize(Public_Function::getScaleSize(240,40));
    ui->danyinghao->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->move->setFixedSize(Public_Function::getScaleSize(40,40));
    ui->close->setFixedSize(Public_Function::getScaleSize(40,40));

}

void Keyboard::initConnect()
{
    connect(ui->q,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->q->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->w,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->w->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->e,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->e->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->r,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->r->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->t,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->t->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->y,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->y->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->u,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->u->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->i,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->i->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->o,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->o->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->p,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->p->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->a,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->a->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->s,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->s->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->d,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->d->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->f,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->f->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->g,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->g->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->h,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->h->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->j,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->j->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->k,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->k->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->l,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->l->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->z,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->z->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->x,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->x->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->c,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->c->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->v,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->v->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->b,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->b->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->n,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->n->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->m,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->m->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->douhao,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->douhao->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->juhao,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->juhao->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->kongge,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->kongge->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
    connect(ui->danyinghao,&QPushButton::clicked,this,[=](){cursorpos =currentLineEdit->cursorPosition();strbefore +=ui->danyinghao->text(); str =strbefore +strafter;currentLineEdit->setText(str);currentLineEdit->setCursorPosition(cursorpos +1);});
}

void Keyboard::changeText(int num, int num2)
{
    str.clear();
    str = currentLineEdit->text();
    strbefore =str.mid(0,currentLineEdit->cursorPosition());
    strafter =str.mid(currentLineEdit->cursorPosition());
}

void Keyboard::mouseMoveEvent(QMouseEvent *event)
{
    if(!mouserelease)
    {
        this->move(event->globalPos() -mousepress);
    }
}

void Keyboard::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mouserelease =true;
}

bool Keyboard::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->move)
    {

        if(event->type() == QEvent::MouseButtonPress)
        {
           QMouseEvent* ev = static_cast<QMouseEvent*>(event);
            mouserelease = false;
            mousepress = ev->globalPos() -this->pos();
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void Keyboard::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(this->rect(),Public_Function::getScaleSize(15),Public_Function::getScaleSize(15));
}




void Keyboard::focusChanged(QWidget *, QWidget *nowWidget)
{
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget))
    {
        if (nowWidget->inherits("QLineEdit"))
        {
            if(qGuiApp->focusWindow()->isModal())qGuiApp->focusWindow()->setModality(Qt::WindowModal);
//            if(currentLineEdit != nullptr)disconnect(currentLineEdit,&QLineEdit::cursorPositionChanged,this,&Keyboard::changeText);
            currentLineEdit = (QLineEdit *)nowWidget;
            if(currentLineEdit->objectName() == "fileNameEdit")keyisshow =0;
            else {
                keyisshow =1;
            }
            if(keyisshow ==1)
            {
               this->show();
               this->raise();
            }
            if(name != currentLineEdit->objectName()){changeText();};
            name = currentLineEdit->objectName();
            connect(currentLineEdit,&QLineEdit::cursorPositionChanged,this,&Keyboard::changeText,Qt::UniqueConnection);
        }
        else
        {
           //myhide = true;
        }
   }
}


void Keyboard::on_close_clicked()
{
   this->hide();
   //keyisshow =0;
   //myhide = false;
}

void Keyboard::on_capslock_clicked()
{
    if(ui->q->text() == "q")
    {
       initCustomText(1);
       ui->capslock->setStyleSheet("background-color:green;color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:green;color: rgb(255, 255, 255);");
    }
    else if(ui->q->text() == "Q")
    {
       initCustomText(2);
       ui->capslock->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    }
    else if(ui->q->text() == "1")
    {
       initCustomText(4);
       ui->capslock->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    }
    else
    {
       initCustomText(3);
       ui->capslock->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    }
}

void Keyboard::on_capslock_2_clicked()
{
    if(ui->q->text() == "q")
    {
       initCustomText(1);
       ui->capslock->setStyleSheet("background-color:green;color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:green;color: rgb(255, 255, 255);");
    }
    else if(ui->q->text() == "Q")
    {
       initCustomText(2);
       ui->capslock->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    }
    else if(ui->q->text() == "1")
    {
       initCustomText(4);
       ui->capslock->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    }
    else
    {
       initCustomText(3);
       ui->capslock->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:rgb(53,50,47);color: rgb(255, 255, 255);");
    }
}

void Keyboard::on_num_clicked()
{
    if(ui->num->text() == "123")
    {
        initCustomText(3);
    }
    else
    {
       initCustomText(1);
       ui->capslock->setStyleSheet("background-color:green;color: rgb(255, 255, 255);");
       ui->capslock_2->setStyleSheet("background-color:green;color: rgb(255, 255, 255);");
    }
}

void Keyboard::on_enter_clicked()
{
  emit currentLineEdit->returnPressed();
}

void Keyboard::on_backspace_clicked()
{
    if(strbefore.count() >0)
    {
        cursorpos = currentLineEdit->cursorPosition();
        strbefore.chop(1);
        str = strbefore +strafter;
        currentLineEdit->setText(str);
        currentLineEdit->setCursorPosition(cursorpos -1);
    }
}
