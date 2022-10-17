#ifndef DOWNWIDGET_H
#define DOWNWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include "downwork.h"
#include "NumberWidget.h"
class DownWidget : public QWidget
{
    Q_OBJECT
public:
    DownWidget(QWidget *parent = nullptr);
    void initCustom();
    void initConnect();
    void hideCustom(int );
    void addBlank(QString &str, int n);
    void addText(QString &str, int n);
    void killThread();

    void setLanguage(bool isChinese) ;
signals:
    void sendMessage(QString );
    void sendLabel(QLabel* );
    void sendTimeNum(int ,int ,int );
    void sendTimerStop();
    void sendTimerClear();
    void sendTimerstart();
    void updateText();

public slots:
    void maxBtnslot();
    void startBtnslot();
    void clearBtnslot();

private:
  NumWidget *hour_widget;
  NumWidget *minute_widget;
  NumWidget *second_widget;
  QLabel *label1;
  QLabel *label2;
  QLabel *fillLab;
  QLabel *countLab;
  QLabel *timertextLab;
//  QLabel *remainLab;
  QPushButton *maxBtn;
  QPushButton *startBtn;
  QPushButton *clearBtn;
  QThread *thread;
  DownWork *downwork;
  QHBoxLayout *hlayout1;
  QHBoxLayout *hlayout2;
  QHBoxLayout *hlayout3;
  QHBoxLayout *hlayout4;
  QHBoxLayout *hlayout5;
  QHBoxLayout *hlayout6;
  QVBoxLayout *vlayout;
  bool mIsChinese;
};

#endif // DOWNWIDGET_H
