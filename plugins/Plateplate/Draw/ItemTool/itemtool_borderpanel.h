#ifndef ITEMTOOL_BORDERPANEL_H
#define ITEMTOOL_BORDERPANEL_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class ItemTool_BorderPanel;
}

class ItemTool_BorderPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ItemTool_BorderPanel(int width, QColor color, QWidget *parent = 0);
    ~ItemTool_BorderPanel();

private:
    Ui::ItemTool_BorderPanel *ui;
    int m_pBorderWidth;
    QColor m_pBorderColor;

    void initWidget();
    void resize();

private slots:
    void onBorderSizeGroup(QAbstractButton*,bool);
    void onBorderColorGroup(QAbstractButton*,bool);

signals:
    void borderSizeChanged(int);
    void borderColorChanged(QColor);
};

#endif // ITEMTOOL_BORDERPANEL_H
