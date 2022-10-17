#ifndef CUSTOMMBOX_H
#define CUSTOMMBOX_H

#include <QWidget>

namespace Ui {
class MessageBox_1;
}

class MessageBox_1 : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBox_1(QWidget *parent = 0);
    MessageBox_1(const QString &title = QString(), const QString &text = QString(),
               const QString &leftText = QString(), const QString &midText = QString(),
               const QString &rightText = QString(), QWidget *parent = 0);
    ~MessageBox_1();
    void show();
    void mSetTitle(const QString &title);
    void mSetText(const QString &text);
    void mSetLeftBtnText(const QString &str);
    void mSetMidBtnText(const QString &str);
    void mSetRightBtnText(const QString &str);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MessageBox_1 *ui;

    void initWidget();
    void resize();

signals:
    void mboxClosed(int);
};

#endif // CUSTOMMBOX_H
