#ifndef CUSTOMPUSHBUTTON_2_H
#define CUSTOMPUSHBUTTON_2_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "custompushbutton.h"

class CustomPushButton_2 : public CustomPushButton
{
    Q_OBJECT
public:
    CustomPushButton_2(QWidget *parent = Q_NULLPTR);
    void mSetIcon(const QPixmap &pixmap, const QPixmap &checkedPixmap = QPixmap());
    void mSetText(const QString &text);
    void mSetColor(const QColor &textColor, const QColor &checkedTextColor = QColor());
    void mSetBGColor(const QColor &BGColor, const QColor &hoverBGColor = QColor(), const QColor &checkedBGColor = QColor());
    void mSetSpacing(int spacing = 0);
    void mSetIconSize(int width, int height);
    inline void mSetIconSize(QSize size) { this->mSetIconSize(size.width(), size.height()); }
    void mSetFont(const QFont &font);
private:
    QVBoxLayout *m_pLayout;
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    QLabel *m_pLabelNull;
    QPixmap m_pIconPixmap = QPixmap();
    QPixmap m_pIconCheckedPixmap = QPixmap();
    QColor m_pTextColor = QColor();
    QColor m_pTextCheckedColor = QColor();
private:
    void initWidget();
private slots:
    void onBtnToggled(bool checked);
};

#endif // CUSTOMPUSHBUTTON_2_H
