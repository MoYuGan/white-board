#ifndef CUSTOMPUSHBUTTON_3_H
#define CUSTOMPUSHBUTTON_3_H

#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QColor>
#include "Custom/PushButton/custompushbutton.h"
#include "Public/publicfunction.h"

class CustomPushButton_3 : public CustomPushButton
{
    Q_OBJECT
public:
    CustomPushButton_3(QWidget *parent = Q_NULLPTR);
    void mSetText(const QString &text, const QColor &color = QColor(), const QColor &checkedColor = QColor());
    void mSetColor(const QColor& bgColor, const QColor hoverColor = QColor(), const QColor &checkedColor = QColor());
    void mSetIcon(const QPixmap &icon, const QPixmap &checkedIcon = QPixmap());
    void mSetIconSize(QSize size);
    void mSetTextSize(QSize size);
    void mSetFont(const QFont &font);
    void mSetRadius(int radius);
    bool eventFilter(QObject *watched, QEvent *event);
    void mSetEnabled(bool bo, const QPixmap &pixmap = QPixmap(), const QColor &textColor = QColor());

protected:
    void paintEvent(QPaintEvent *event);

private:
    QHBoxLayout *m_Layout;
    QLabel *m_LabelIcon;
    QLabel *m_LabelText;
    QLabel *m_LabelArrow;
    QLabel *m_LabelSpacing;
    QColor m_BGColor;
    QColor m_HoverColor;
    QColor m_CheckedColor;
    QPixmap m_Icon;
    QPixmap m_CheckedIcon;
    QColor m_TextColor;
    QColor m_CheckedTextColor;
    bool m_MouseEnter = false;
    int m_Radius = 0;

    void initWidget();

private slots:
    void onBtnToggled(bool checked);
};

#endif // CUSTOMPUSHBUTTON_3_H
