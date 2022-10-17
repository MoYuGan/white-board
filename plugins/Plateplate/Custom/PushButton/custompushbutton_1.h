#ifndef CUSTOMPUSHBUTTON_1_H
#define CUSTOMPUSHBUTTON_1_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "custompushbutton.h"
#include "Public/publicfunction.h"

class CustomPushButton_1 : public CustomPushButton
{
    Q_OBJECT
public:
    CustomPushButton_1(QWidget *parent = Q_NULLPTR);
    void mSetText(const QString &text);
    void mSetTextColor(const QColor &textColor, const QColor &checkedTextColor = QColor());
    void mSetFont(const QFont &font);
    void mSetIcon(const QPixmap &icon, const QPixmap &checkedIcon = QPixmap(),
                  const QPixmap &hoverIcon = QPixmap());
    void mSetColor(const QColor &hoverColor = QColor(), const QColor &backgroundColor = QColor(),
                   const QColor &checkedColor = QColor());
    void mEnabledChecked();
    void mSetIconSize(const QSize &size);
    void mSetRadius(int radius);
    bool eventFilter(QObject *watched, QEvent *event);
    void mSetCheckedIcon(const QPixmap &pixmap = QPixmap());
    void mSetMargin(int left = 0, int top = 0, int right = 0, int bottom = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVBoxLayout *m_pLayout;
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    QColor m_pTextColor = QColor();
    QColor m_pCheckedTextColor = QColor();
    QPixmap m_pIcon = QPixmap();
    QPixmap m_pCheckedIcon = QPixmap();
    QPixmap m_pHoverIcon = QPixmap();
    QColor m_pBGColor = QColor();
    QColor m_pHoverColor = QColor();
    QColor m_pCheckedColor = QColor();
    int m_pRadius = 0;
    bool m_pMouseEnter = false;

private:
    void initWidget();

private slots:
    void onBtnToggled(bool checked);

signals:
    void checkedClicked();
};

#endif // CUSTOMPUSHBUTTON_1_H
