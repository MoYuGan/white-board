#ifndef CUSTOMPUSHBUTTON_1_H
#define CUSTOMPUSHBUTTON_1_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "custompushbutton.h"

class CustomPushButton_1 : public CustomPushButton
{
    Q_OBJECT
public:
    CustomPushButton_1(QWidget *parent = Q_NULLPTR);
    void mSetIcon(const QPixmap &pixmap, const QPixmap &checkedPixmap = QPixmap());
    void mSetText(const QString &text);
    void mSetColor(const QColor &textColor, const QColor &checkedTextColor = QColor());
    void mSetArrow(const QPixmap &pixmap, const QPixmap &checkedPixmap = QPixmap());
    void mSetBGColor(const QColor &BGColor, const QColor &hoverBGColor = QColor(), const QColor &checkedBGColor = QColor());
    void mSetMarginAndSpacing(int left = 0, int top = 0, int right = 0, int bottom = 0, int spacing = 0);
    void mSetIconSize(int width, int height);
    void mSetArrowSize(int width, int height);
    inline void mSetIconSize(QSize size) { this->mSetIconSize(size.width(), size.height()); }
    inline void mSetArrowSize(QSize size) { this->mSetArrowSize(size.width(), size.height()); }
    void mSetFont(const QFont &font);
private:
    QHBoxLayout *m_pLayout;
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    QLabel *m_pLabelArrow;
    QLabel *m_pLabelNull;
    QPixmap m_pIconPixmap = QPixmap();
    QPixmap m_pIconCheckedPixmap = QPixmap();
    QPixmap m_pArrowPixmap = QPixmap();
    QPixmap m_pArrowCheckedPixmap = QPixmap();
    QColor m_pTextColor = QColor();
    QColor m_pTextCheckedColor = QColor();
private:
    void initWidget();
private slots:
    void onBtnToggled(bool checked);
};

#endif // CUSTOMPUSHBUTTON_1_H
