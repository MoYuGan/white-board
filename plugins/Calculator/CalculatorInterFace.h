#ifndef CALCULATORINTERFACE_H
#define CALCULATORINTERFACE_H
#include <QWidget>
class CalculatorInterFace : public QWidget
{
    Q_OBJECT
public:
    CalculatorInterFace(QWidget *parent =0): QWidget(parent){}
    virtual ~CalculatorInterFace() {}
    virtual CalculatorInterFace* getWidget() =0;

    virtual void updateLanguage(bool isChinese){}

public slots:
    //定义虚槽函数

signals:
    void sendCloseMessage();

};
//内部第一个函数为类名，第二个函数为接口标识，可以随意写
Q_DECLARE_INTERFACE(CalculatorInterFace, "CalculatorInterFace/01")
#endif // CALCULATORINTERFACE_H
