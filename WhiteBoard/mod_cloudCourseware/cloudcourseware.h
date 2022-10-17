#ifndef CLOUDCOURSEWARE_H
#define CLOUDCOURSEWARE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include "mod_cloudCourseware/db_loginpanel.h"
#include "mod_cloudCourseware/db_clouduserpanel.h"
#include "MyKeyboard/keyboard.h"

class CloudCourseware : public QWidget
{
    Q_OBJECT
public:
    CloudCourseware(QWidget *parent = nullptr) :
        QWidget(parent) {
        this->initWidget();
    }

    void show() {
        m_KeyBoard = new Keyboard;
        m_KeyBoard->hide();
        QWidget::show();
        this->raise();
    }

    void hide() {
        if (nullptr != m_KeyBoard) {
            m_KeyBoard->deleteLater();
            m_KeyBoard = nullptr;
        }
        QWidget::hide();
    }

private:
    void initWidget() {
        m_pLayout = new QHBoxLayout(this);
        m_pLayout->setSpacing(0);
        m_pLayout->setContentsMargins(0, 0, 0, 0);

        m_pLoginPanel = new DB_LoginPanel(this);
        connect(m_pLoginPanel, &DB_LoginPanel::panelClosed, [=](){ this->hide();});
        connect(m_pLoginPanel, &DB_LoginPanel::showUserPanel, this, &CloudCourseware::onShowUserPanel);
        m_pLayout->addWidget(m_pLoginPanel, Qt::AlignCenter);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.fillRect(this->rect(), QBrush(Qt::transparent));
    }

public slots:
    void onShowUserPanel(_UserInfoData data) {
        m_pLoginPanel->hide();
        DB_CloudUserPanel *cloudUserPanel = new DB_CloudUserPanel(data, this);
        connect(cloudUserPanel, &DB_CloudUserPanel::panelClose, [=](){ this->hide(); });
        connect(cloudUserPanel, &DB_CloudUserPanel::cancellation, [=](){
            cloudUserPanel->deleteLater();
            m_pLoginPanel->show();
        });
        m_pLayout->addWidget(cloudUserPanel, Qt::AlignCenter);
        cloudUserPanel->show();
    }

private:
    DB_LoginPanel *m_pLoginPanel;
    QHBoxLayout *m_pLayout;
    Keyboard *m_KeyBoard = nullptr;
};

#endif // CLOUDCOURSEWARE_H
