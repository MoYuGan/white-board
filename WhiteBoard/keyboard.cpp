#include "keyboard.h"
#include "ui_keyboard.h"
#include "Public/public_function.h"
#include "QDebug"
#include <QCursor>
#include <QApplication>
#include <QtGui>

Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
    str.clear();
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    this->setFixedSize(Public_Function::getScaleSize(602,200));
    this->setStyleSheet(QString("background-color:black;border-radius:%1px").arg(Public_Function::getScaleSize(3)));
    initCustomText(2);
    resize();
    initStyle();
    initConnect();
    ui->move->installEventFilter(this);
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
    QIcon icon(QPixmap(":/images/lock@4x.png").scaled(Public_Function::getScaleSize(32),Public_Function::getScaleSize(32),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
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
    connect(ui->q,&QPushButton::clicked,this,[=](){strbefore +=ui->q->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->w,&QPushButton::clicked,this,[=](){strbefore +=ui->w->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->e,&QPushButton::clicked,this,[=](){strbefore +=ui->e->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->r,&QPushButton::clicked,this,[=](){strbefore +=ui->r->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->t,&QPushButton::clicked,this,[=](){strbefore +=ui->t->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->y,&QPushButton::clicked,this,[=](){strbefore +=ui->y->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->u,&QPushButton::clicked,this,[=](){strbefore +=ui->u->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->i,&QPushButton::clicked,this,[=](){strbefore +=ui->i->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->o,&QPushButton::clicked,this,[=](){strbefore +=ui->o->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->p,&QPushButton::clicked,this,[=](){strbefore +=ui->p->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->a,&QPushButton::clicked,this,[=](){strbefore +=ui->a->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->s,&QPushButton::clicked,this,[=](){strbefore +=ui->s->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->d,&QPushButton::clicked,this,[=](){strbefore +=ui->d->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->f,&QPushButton::clicked,this,[=](){strbefore +=ui->f->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->g,&QPushButton::clicked,this,[=](){strbefore +=ui->g->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->h,&QPushButton::clicked,this,[=](){strbefore +=ui->h->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->j,&QPushButton::clicked,this,[=](){strbefore +=ui->j->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->k,&QPushButton::clicked,this,[=](){strbefore +=ui->k->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->l,&QPushButton::clicked,this,[=](){strbefore +=ui->l->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->z,&QPushButton::clicked,this,[=](){strbefore +=ui->z->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->x,&QPushButton::clicked,this,[=](){strbefore +=ui->x->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->c,&QPushButton::clicked,this,[=](){strbefore +=ui->c->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->v,&QPushButton::clicked,this,[=](){strbefore +=ui->v->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->b,&QPushButton::clicked,this,[=](){strbefore +=ui->b->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->n,&QPushButton::clicked,this,[=](){strbefore +=ui->n->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->m,&QPushButton::clicked,this,[=](){strbefore +=ui->m->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->douhao,&QPushButton::clicked,this,[=](){strbefore +=ui->douhao->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->juhao,&QPushButton::clicked,this,[=](){strbefore +=ui->juhao->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->kongge,&QPushButton::clicked,this,[=](){strbefore +=ui->kongge->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
    connect(ui->danyinghao,&QPushButton::clicked,this,[=](){strbefore +=ui->danyinghao->text(); str =strbefore +strafter;currentLineEdit->setText(str);});
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




void Keyboard::focusChanged(QWidget *, QWidget *nowWidget)
{
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget))
    {
        if (nowWidget->inherits("QLineEdit"))
        {
            if(qGuiApp->focusWindow()->isModal())
               qGuiApp->focusWindow()->setModality(Qt::WindowModal);

            this->setWindowFlags( Qt::Tool|Qt::WindowDoesNotAcceptFocus|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

            if(myhide)
            {
               this->show();
            }

            currentLineEdit = (QLineEdit *)nowWidget;
            connect(currentLineEdit,&QLineEdit::cursorPositionChanged,[=](int mold,int mnew){
                   str.clear();
                   str = currentLineEdit->text();
                   strbefore =str.mid(0,mnew);
                   strafter =str.mid(mnew);
            });
        }
        else
        {
           myhide = true;
        }
    }
}


void Keyboard::on_close_clicked()
{
   this->hide();
   myhide = false;
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
        str.chop(1);
        currentLineEdit->setText(str);
    }
}
