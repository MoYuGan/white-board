#ifndef ITEMTOOL_FILLCOLORPANEL_H
#define ITEMTOOL_FILLCOLORPANEL_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class ItemTool_FillColorPanel;
}

class ItemTool_FillColorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ItemTool_FillColorPanel(QColor color, QWidget *parent = 0);
    ~ItemTool_FillColorPanel();

private:
    Ui::ItemTool_FillColorPanel *ui;
    QColor m_pFillColor;

    void initWidget();
    void resize();

private slots:
    void onFillColorGroup(QAbstractButton*,bool);

signals:
    void fillColorChanged(QColor);
};

#endif // ITEMTOOL_FILLCOLORPANEL_H
