#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QLineEdit>
#include <QPainter>

namespace Ui {
class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = 0);
    ~Keyboard();
    void initCustomText(int );
    void initStyle();
    void resize();
    void initConnect();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    bool eventFilter(QObject *watched, QEvent *event);

signals:

private slots:

    void focusChanged(QWidget *, QWidget *);

    void on_close_clicked();

    void on_capslock_clicked();

    void on_capslock_2_clicked();

    void on_num_clicked();

    void on_enter_clicked();

    void on_backspace_clicked();

private:
    Ui::Keyboard *ui;

private:
    QPoint mousepress;
    bool mouserelease =true;
    QLineEdit *currentLineEdit;
    int mode = 2;
    QString str;
    QString strbefore;
    QString strafter;
    bool myhide = true;
};


#endif // KEYBOARD_H
