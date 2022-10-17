#ifndef PUSHBUTTON_BASIC_H
#define PUSHBUTTON_BASIC_H

#include <QPushButton>
#include <QCursor>
#include <QEvent>

class PushButton_Basic : public QPushButton
{
    Q_OBJECT
public:
    PushButton_Basic(QWidget *parent = Q_NULLPTR);
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    QCursor m_pOrgCursor;
};

#endif // PUSHBUTTON_BASIC_H
