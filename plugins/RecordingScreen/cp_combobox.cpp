#include "cp_combobox.h"

CP_Combobox::CP_Combobox(QWidget *parent):QWidget(parent),m_isClick(false)
{
    this->setFixedSize(Public_Function::getScaleSize(360,42));
    //m_List = new QListView(this);
    m_Text = new QLabel(this);
    m_Btn = new QLabel(this);

    m_Text->setFixedSize(Public_Function::getScaleSize(356,42));
    m_Text->setText("请选择");
    m_Text->setStyleSheet("QLabel{border:none;border-radius:4px;background:#eeeeee;font-size: 14px;"
                          "font-family: Microsoft YaHei Regular, Microsoft YaHei Regular-Regular;"
                          "font-weight: 400;text-align: left;color: #888888;}");
    m_Text->installEventFilter(this);
    m_Text->setContentsMargins(10,0,0,0);

    m_Btn->setFixedSize(Public_Function::getScaleSize(42,42));
    m_Btn->setPixmap(QPixmap(":/prc/ScreenCap/zhankai3@2x.png"));
    m_Btn->setAlignment(Qt::AlignCenter);
    m_Btn->installEventFilter(this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_Text);
    layout->addWidget(m_Btn);
    layout->setSpacing(0);
    layout->setMargin(0);
}

CP_Combobox::~CP_Combobox()
{

}

void CP_Combobox::Combo_Setting(QString text)
{
    m_Text->setText(text);
    m_Text->setStyleSheet("QLabel{border:none;border-radius:4px;background:#eeeeee;font-size: 14px;"
                          "font-family: Microsoft YaHei Regular, Microsoft YaHei Regular-Regular;"
                          "font-weight: 400;text-align: left;color: #444444;}");
    m_Btn->setPixmap(QPixmap(":/prc/ScreenCap/zhankai3@2x.png"));
    m_isClick = false;
}

bool CP_Combobox::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_Btn || watched == m_Text)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if(!m_isClick)
            {
                m_Btn->setPixmap(QPixmap(":/prc/ScreenCap/zhankai4@2x.png"));
                m_isClick = true;
            }
            else
            {
                m_Btn->setPixmap(QPixmap(":/prc/ScreenCap/zhankai3@2x.png"));
                m_isClick = false;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}



void CP_Combobox::Slot_BtnClick()
{

}

void CP_Combobox::Slot_ListClick()
{

}

