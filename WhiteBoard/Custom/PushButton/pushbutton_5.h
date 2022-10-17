#ifndef PUSHBUTTON_5_H
#define PUSHBUTTON_5_H

#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include "pushbutton_basic.h"
#include "Public/public_function.h"

//11
class PushButton_5 : public PushButton_Basic
{
    Q_OBJECT
public:
    PushButton_5(QWidget *parent = Q_NULLPTR);

    void mSetCheckedTextColor(const QColor &color);
    void mSetCheckedIcon(const QPixmap &pixmap);
    void mSetIcon(const QPixmap &pixmap);
    void mSetIconSize(const QSize &size);
    void mSetText(const QString &str);
    void mSetMargins(int left, int top, int right, int bottom);
    void mSetSpacing(int spacing);
    void mSetFont(const QFont &font);
    void mSetHoverColor(const QColor &color);
    void mSetBackgroundColor(const QColor &color);
    void mSetEnabled(bool bo);
    void mSetRadius(int topleft, int topright, int bottomleft, int bottomright);
    bool eventFilter(QObject *watched, QEvent *event);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    QLabel *m_pLabelSpacing;
    QHBoxLayout *m_pLayout;
    QColor m_pTextColor;
    QColor m_pHoverColor;
    QColor m_pBackgroundColor;
    QColor m_pCheckedTextColor;
    bool m_pMouseEnter;
    int m_pTopLeftRadius;
    int m_pTopRightRadius;
    int m_pBottomLeftRadius;
    int m_pBottomRightRadius;
    QPixmap m_pIcon;
    QPixmap m_pCheckedIcon;
    QColor m_pCheckedBGColor;

    void initWidget();
};

#endif // PUSHBUTTON_5_H
