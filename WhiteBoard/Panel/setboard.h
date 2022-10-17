#ifndef SETBOARD_H
#define SETBOARD_H

#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QHBoxLayout>
#include <QMouseEvent>

namespace Ui {
class SetBoard;
}

class SetBoard : public QWidget
{
    Q_OBJECT

public:
    explicit SetBoard(QWidget *parent = nullptr);
    ~SetBoard();
    void setBoardNumber(int );
    void initWidget();
    bool switchBtnState();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
   void sendOpenBoardSignal();
   void sendCloseBoardSignal();
   void sendSetCloseSignal();
   void sendAgainOpenBoardSignal();

private:
    Ui::SetBoard *ui;
    QPoint pressdot;
    bool ispress =false;
};

#endif // SETBOARD_H
