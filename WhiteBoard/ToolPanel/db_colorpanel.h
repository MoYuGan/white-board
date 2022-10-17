#ifndef DB_COLORPANEL_H
#define DB_COLORPANEL_H

#include <QWidget>

namespace Ui {
class DB_ColorPanel;
}

class DB_ColorPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DB_ColorPanel(const QColor &color = Qt::white, QWidget *parent = 0);
    ~DB_ColorPanel();
    void show();
    void resize();
    QColor getColor();

private:
    Ui::DB_ColorPanel *ui;
    QColor m_pCurrentColor;

    void initWidget();
    void setLabelColor();
signals:
    void colorPanelClosed(int);
};

#endif // DB_COLORPANEL_H
