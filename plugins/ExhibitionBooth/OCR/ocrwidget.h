#ifndef OCRWIDGET_H
#define OCRWIDGET_H

#include <QWidget>
#include "ocrthread.h"

namespace Ui {
class OCRWidget;
}

class OCRWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OCRWidget(const QPixmap &pixmap, QWidget *parent = 0);
    ~OCRWidget();
    void show();
    void resizeWidget();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::OCRWidget *ui;
    QPixmap m_pPixmap;
    OcrThread *m_pOcrThread = nullptr;

    void initWidget();
private slots:
    void copyText(const QString &text);
};

#endif // OCRWIDGET_H
