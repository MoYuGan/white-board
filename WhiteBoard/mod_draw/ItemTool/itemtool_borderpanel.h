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
    explicit ItemTool_BorderPanel(int width, const QColor& color,Qt::PenStyle penStyle = Qt::NoPen, QWidget *parent = 0);
    ~ItemTool_BorderPanel();
    void hideOtherPenStyle();

    //djf add update function
    void updateBorder(int width, const QColor& color, Qt::PenStyle penStyle);

private:
    Ui::ItemTool_BorderPanel *ui;
    int m_pBorderWidth;
    QColor m_pBorderColor =QColor();

    void initWidget();
    void resize();
    QButtonGroup *borderColorGroup;
    QButtonGroup *borderSizeGroup;
    QButtonGroup *borderLineGroup;
protected:
   bool event(QEvent *event);

private slots:
    void onBorderSizeGroup(QAbstractButton* );
    void onBorderLineGroup(QAbstractButton* );
    void onBorderColorGroup(QAbstractButton* );

signals:
    void borderSizeChanged(int);
    void borderColorChanged(QColor);
    void borderLineChanged(Qt::PenStyle );
};

#endif // ITEMTOOL_BORDERPANEL_H
