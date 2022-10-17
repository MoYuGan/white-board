#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "CalculatorInterFace.h"
namespace Ui {
class Calculator;
}

class Calculator : public CalculatorInterFace
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "CalculatorInterFace/01" FILE "MyCalculatorInterFace.json")
    Q_INTERFACES(CalculatorInterFace)
#endif
public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();
    void initLayout();
    void initConnect();
    CalculatorInterFace *getWidget();
    void closeMessage(QWidget* );

    void updateLanguage(bool isChinese);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void digitClicked(int );
    void unaryOperatorClicked(int );
    void additiveOperatorClicked(QString );
    void multiplicativeOperatorClicked(QString );
    void equalClicked();
    void pointClicked();
    void percentageClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();

private:
    Ui::Calculator *ui;
    QPoint mousepressdot;
    bool mousepress =false;
    QString stylesheet1;
    QString stylesheet2;

private:
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);
    double sumInMemory= 0.0;
    double sumSoFar= 0.0;
    double factorSoFar= 0.0;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand= true;
    QWidget *widget;
};

#endif // CALCULATOR_H
