#ifndef PUSHBUTTON_2_H
#define PUSHBUTTON_2_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include "pushbutton_basic.h"
#include "Public/public_function.h"

//10
class PushButton_2 : public PushButton_Basic
{
    Q_OBJECT
public:
    PushButton_2(QWidget *parent = Q_NULLPTR);
    void mSetIcon(const QPixmap &pixmap);
    void mSetIconSize(const QSize &size);
    void mSetCheckedTextColor(const QColor &color);
    void mSetText(const QString &str);
    void mSetTextColor(const QColor &color);
    void mSetFont(const QFont &font);
    void mSetCheckedIcon(const QPixmap &pixmap);
    void mSetCheckedBGColor(const QColor &color);
    void mSetRadius(int radius);
    void mSetCheckedBorderColor(const QColor &color);
    bool eventFilter(QObject *watched, QEvent *event);
    //bool event(QEvent *e);

protected:
    void paintEvent(QPaintEvent *);

private:
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
    QPixmap m_pIcon;
    QPixmap m_pCheckedIcon;
    QColor m_pCheckedTextColor;
    QColor m_pTextColor;
    QColor m_pHoverColor;
    QColor m_pCheckedBGColor;
    QVBoxLayout *m_pLayout;
    QColor m_pCheckedBorderColor;
    int m_pRadius;
    bool m_pMouseEnter;

private:
    void initWidget();

private slots:
    void onToggled(bool checked);

signals:
    void checkedClicked();
};

#endif // PUSHBUTTON_2_H
