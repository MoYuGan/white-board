#ifndef CP_COMBOBOX_H
#define CP_COMBOBOX_H

#include <QObject>
#include <QWidget>
#include "QComboBox"
#include "QPushButton"
#include "QTextEdit"
#include "QListView"
#include "QBoxLayout"
#include "QLineEdit"
#include "QDebug"
#include "QLabel"
#include "QEvent"
#include "public_function.h"
#include "QMouseEvent"
class CP_Combobox : public QWidget
{
    Q_OBJECT
public:
    CP_Combobox(QWidget *parent = nullptr);
    ~CP_Combobox();
    void Combo_Setting(QString text);
public slots:
    void Slot_BtnClick();
    void Slot_ListClick();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    bool event(QEvent *e){
        if (e->type()==QEvent::MouseButtonPress)
        {
            //做父与子之间类型转换
            QMouseEvent *ev=static_cast<QMouseEvent *>(e);
            //做了一个拦截
            //只有鼠标按下自己处理
            return true;
        }
        //其他事件让父亲做默认处理
        return QWidget::event(e);

    }
public:
    bool m_isClick;
    QLabel* m_Btn;
    QLabel* m_Text;
};

#endif // CP_COMBOBOX_H
