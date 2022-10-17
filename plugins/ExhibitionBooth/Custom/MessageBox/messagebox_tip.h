#ifndef MESSAGEBOX_TIP_H
#define MESSAGEBOX_TIP_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QTimer>
#include "Public/publicfunction.h"

class MessageBox_Tip : public QWidget
{
    Q_OBJECT
public:
    explicit MessageBox_Tip(QWidget *parent = nullptr);
    void setText(const QString &text);
    void resizeWidget();
    void show();

protected:
    void paintEvent(QPaintEvent *) override;
private:
    QLabel *m_Label = nullptr;
    QTimer *m_Timer;
    QString m_Text;
private:
    void initWidget();

private slots:
    void onTimeOut();
signals:

};

#endif // MESSAGEBOX_TIP_H
