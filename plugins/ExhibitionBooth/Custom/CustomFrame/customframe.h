#ifndef CUSTOMFRAME_H
#define CUSTOMFRAME_H
#include <QFrame>

class CustomFrame : public QFrame
{
    Q_OBJECT
public:
    CustomFrame(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void frameClicked();
};

#endif // CUSTOMFRAME_H
