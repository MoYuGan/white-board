#ifndef TAKINGPHOTOWIDGET_H
#define TAKINGPHOTOWIDGET_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class TakingPhotoWidget;
}

class TakingPhotoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TakingPhotoWidget(const QPixmap &pixmap, QWidget *parent = 0);
    ~TakingPhotoWidget();
    void show();
    void resize();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::TakingPhotoWidget *ui;
    QPixmap m_pPixmap;
    void initWidget();
};

#endif // TAKINGPHOTOWIDGET_H
