#ifndef AUDIOCHOOSE_H
#define AUDIOCHOOSE_H

#include <QWidget>
#include "QMouseEvent"
#include "QLabel"
#include "QPainter"
#include "QPen"
#include "cp_combobox.h"
#include "cp_listview.h"
#include "QDesktopWidget"
#include "widget.h"
#include "public_function.h"
namespace Ui {
class AudioChoose;
}

class AudioChoose : public QWidget
{
    Q_OBJECT

public:
    explicit AudioChoose(QWidget *parent = nullptr);
    ~AudioChoose();
    void paintEvent(QPaintEvent *event);
    void init();
    void Btn_MoveTo(double w, double h);
public:
    //为录屏按钮传入2个参数设置坐标
    double m_x = 0;
    double m_y = 0;
public slots:
    void slot_Close();
    void slot_Start();
    void slot_ChangeText();
signals:
    void StartTimes();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void mousePressEvent(QMouseEvent *event)
    {
        last = event->globalPos();
        m_press = true;
        if(m_isShowList)
        {
            m_List->hide();
            m_Combobox->m_Btn->setPixmap(QPixmap(":/prc/ScreenCap/zhankai3@2x.png"));
            m_Combobox->m_isClick = false;
        }
    }

    void mouseMoveEvent(QMouseEvent *event)
    {

        if(m_press)
        {
            int dx = event->globalX() - last.x();
            int dy = event->globalY() - last.y();
            last = event->globalPos();
            move(x()+dx,y()+dy);

        }
    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        m_press = false;
    }
private:
    Ui::AudioChoose *ui;
    bool m_press = false;
    bool m_isShowList = false;
    CP_Combobox* m_Combobox;
    CP_ListVIew* m_List;
    Widget* w;
    QPoint last;
};

#endif // AUDIOCHOOSE_H
