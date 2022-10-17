#ifndef BACKGROUNDSTYLE_H
#define BACKGROUNDSTYLE_H

#include <QWidget>
#include <QPainter>
#include "Custom/PushButton/pushbutton_10.h"
#include "Custom/PushButton/pushbutton_11.h"
#include <QButtonGroup>
#include "Extern/extern.h"

namespace Ui {
class BackgroundStyle;
}

class BackgroundStyle : public QWidget
{
    Q_OBJECT

public:
    explicit BackgroundStyle(QWidget *parent = nullptr);
    ~BackgroundStyle();

    void initWidget();
    void initeventFilter();
    void initConnect();
    void show();
    void hide();
    QPixmap getBackgroundPixmap();
    int getBackgroundId();
    QPixmap getDefaultPixmap();
    int getDefaultId();
    void setCheckedIndex(int index =0);

    void updateLanguage();
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void changePage(QAbstractButton *button);
    void changeBackgroundPixmap(QAbstractButton *button);

signals:
    void backgroundChanged();
    void goBack();
    void panelHide();
    void sendChangeAllBackgroundSianal();

private:
    Ui::BackgroundStyle *ui;
    QButtonGroup *group;
    QButtonGroup *backgroundgroup;
    QString custompixmappath;

};

#endif // BACKGROUNDSTYLE_H
