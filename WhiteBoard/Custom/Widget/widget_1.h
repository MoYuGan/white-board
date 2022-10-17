#ifndef WIDGET_1_H
#define WIDGET_1_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include "Public/public_function.h"

//9
class Widget_1 : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_1(QWidget *parent = nullptr);
    void mSetText(const QString &text);
    void mSetFont(const QFont &font);
    void mSetMargin(int left, int right);
    void mSetHandleIcon(const QPixmap &pixmap);
    void mSetHandleSize(const QSize &size);
    void mSetRadius(int radius);
    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_pText;
    QLabel  *m_pHandle;
    QFont m_pFont;
    int m_pLeftMargin;
    int m_pRightMargin;
    int m_pRadius;
    bool m_pMousePressed;
    QPoint m_pMousePressedPoint;

    void initWidget();

signals:
    void clearSignal();
};

#endif // WIDGET_1_H
