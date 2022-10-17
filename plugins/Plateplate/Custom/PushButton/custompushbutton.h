#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

/*
 *效果:
 * 1、鼠标进入改变光标样式
*/

#include <QPushButton>
#include <QCursor>
#include <QEvent>

class CustomPushButton : public QPushButton
{
    Q_OBJECT
public:
    CustomPushButton(QWidget *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event);
    void setEnterCursor(const QCursor &cursor);

private:
    QCursor m_pCursor;
    QCursor m_pOrgCursor;
};

#endif // CUSTOMPUSHBUTTON_H
