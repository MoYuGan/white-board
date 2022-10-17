#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QPainter>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);
    void showText(const QString &text, const QFont &font, const QColor &color);
    void clearText();

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    QString m_pText;
    QFont m_pFont;
    QColor m_pTextColor;
    QPixmap m_pPixmap;
};

#endif // CUSTOMWIDGET_H
