#ifndef ERASEPANEL_H
#define ERASEPANEL_H

#include <QWidget>
#include <QPainter>
#include <QAbstractButton>
#include <QButtonGroup>
#include "Extern/extern.h"
#include "Public/public_function.h"

namespace Ui {
class ErasePanel;
}

class ErasePanel : public QWidget
{
    Q_OBJECT

public:
    explicit ErasePanel(QWidget *parent = 0);
    ~ErasePanel();
    void show();
    void hide();
    void resizeWidget();
    void setCheckedSize(int id);

    void updateLanguage();
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ErasePanel *ui;
    QButtonGroup *m_EraseSizeGroup = nullptr;

    void initWidget();

private slots:
    void onSizeGroupToggled(QAbstractButton* button, bool checked);

signals:
    void panelHide();
    void clearSignal();
    void eraseSizeChanged(QSize);
};

#endif // ERASEPANEL_H
