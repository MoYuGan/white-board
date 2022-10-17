#ifndef DEVICESMENU_H
#define DEVICESMENU_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QPainter>
#include "Public/publicfunction.h"

namespace Ui {
class DevicesMenu;
}

class DevicesMenu : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesMenu(QWidget *parent = 0);
    ~DevicesMenu();
    void show();
    void resizeWidget();
    void mSetAction(const QList<QString> &descriptionList, const QList<QString> &deviceNameList);
    void clearAction();
    void setChecked(int index, bool checked);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DevicesMenu *ui;
    QVector<QPushButton *> m_DeviceBtnList;
    QButtonGroup *m_DevicesGroup;

    void initWidget();

private slots:
    void onDevicesGroupToggled(QAbstractButton *button, bool checked);

signals:
    void deviceChanged(bool, int);
};

#endif // DEVICESMENU_H
