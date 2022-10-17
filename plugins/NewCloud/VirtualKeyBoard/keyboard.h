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
    void changeText(int num =0,int num2 =0);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *);

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
    QLineEdit *currentLineEdit =nullptr;
    QString str;
    QString strbefore;
    QString strafter;
    bool myhide = true;
    int cursorpos =0;
    QString name;

public:
    int keyisshow =0;
};


#endif // KEYBOARD_H
