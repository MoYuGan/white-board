#ifndef RESOLUTIONMENU_H
#define RESOLUTIONMENU_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPen>
#include <QButtonGroup>
#include "Public/publicfunction.h"

namespace Ui {
class ResolutionMenu;
}

class ResolutionMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ResolutionMenu(QWidget *parent = 0);
    ~ResolutionMenu();
    void show();
    void resizeWidget();
    void mSetAction(const QList<QString> &resolutionList);
    void clearAction();
    void setChecked(int index, bool checked);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ResolutionMenu *ui;
    QVector<QPushButton *> m_ResolutionBtnList;
    QButtonGroup *m_ResolutionGroup;

    void initWidget();

private slots:
    void onResolutionGroupToggled(QAbstractButton *button, bool checked);

signals:
    void resolutionChanged(QString);
};

#endif // RESOLUTIONMENU_H
