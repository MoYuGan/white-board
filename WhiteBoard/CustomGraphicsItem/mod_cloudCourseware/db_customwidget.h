#ifndef DB_CUSTOMWIDGET_H
#define DB_CUSTOMWIDGET_H

#include <QPushButton>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QFrame>
#include <QHBoxLayout>

#include "db_define.h"
#include "ShareStyle/db_scale.h"

class ItemButton
{
public:
    enum BUTTON_STATUS
    {
        NONE, HOVER, PRESSED, RELEASED
    };

public:
    ItemButton(QString iconName, QWidget *parent = nullptr) : m_iconName(iconName), m_buttonWidget(new QPushButton(parent)) {
        m_buttonWidget->setStyleSheet(QString("QPushButton{ \
                                                    border: none; \
                                                    background-color: transparent; \
                                                    border-image: url('%1');   \
                                                }").arg(m_iconName));

    }

    void paintButton(QPainter* painter, const QPoint& displayPos, const QPoint &mousePos) {
        QStyleOptionButton buttonOption;
        int buttonSize = DB_ApplicationScale::getScaleWidth(ITEM_BUTTON_SIZE);
        QRect rect = QRect(displayPos.x(), displayPos.y(), buttonSize, buttonSize);
        buttonOption.rect = rect;
        buttonOption.state = QStyle::State_Enabled;
        if(buttonOption.rect.contains(mousePos))
        {
            if(m_buttonStatus == BUTTON_STATUS::HOVER)
                buttonOption.state |= QStyle::State_MouseOver;
            else if(m_buttonStatus == BUTTON_STATUS::PRESSED)
                buttonOption.state |= QStyle::State_Sunken;
        }

        m_buttonWidget.data()->style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter, m_buttonWidget.data());
    }

    void inline setStatusNone() { m_buttonStatus = NONE; }
    void inline setStatusHover() { m_buttonStatus = HOVER; }
    void inline setStatusPressed() { m_buttonStatus = PRESSED; }
    void inline setStatusReleased() { m_buttonStatus = RELEASED; }

    //判断鼠标（触摸）事件点是否在QPushButton里面
    static bool withinButtonRegion(const QPoint& displayPos, const QPoint &mousePos) {
        int buttonSize = DB_ApplicationScale::getScaleWidth(ITEM_BUTTON_SIZE);
        QRect rect = QRect(displayPos.x(), displayPos.y(), buttonSize, buttonSize);
        return rect.contains(mousePos);
    }


private:
    QString m_iconName;
    QScopedPointer<QPushButton> m_buttonWidget;
    BUTTON_STATUS m_buttonStatus = NONE;
};


#endif // DB_CUSTOMWIDGET_H
