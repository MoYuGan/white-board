#include "toolkit.h"
#include <QPropertyAnimation>
#include "../applicationconfig.h"

QTranslator* ToolKit::pTranslator = nullptr;
bool ToolKit::mIsChinese = true;

void ToolKit::StartAnimation(QWidget* wid, const QPoint& fromPnt, const QPoint& toPnt, int playTime)
{
    if( wid == nullptr)
        return;
    QPropertyAnimation* animation = new QPropertyAnimation(wid,  "pos");
    animation->setDuration(playTime);
    animation->setStartValue(fromPnt);
    animation->setEndValue( toPnt );
    animation->setEasingCurve(QEasingCurve::InOutQuad) ;
    animation->start();

}


void ToolKit::installTranslator()
{
    if( pTranslator == nullptr)
    {
        pTranslator = new QTranslator();
        QString value = ApplicationConfig::readConfig(CONFIG_KEY_LANGUAGE); //2 is for english
        if (0 == value.compare("2"))
        {
            //设置语言环境为英文
            pTranslator->load(":/en.qm"); //:/en.qm
            mIsChinese = false;
        }else
        {
             //设置语言环境为中文
            pTranslator->load(":/zh.qm");
        }
        //安装语言包
        qApp->installTranslator(pTranslator);
    }
}

void ToolKit::ToggleLanguage(bool isChinese)
{
    if( isChinese)
    {
        if( pTranslator!= nullptr)
            pTranslator->load(":/zh.qm");
        ApplicationConfig::writeConfig(CONFIG_KEY_LANGUAGE, "1");
        mIsChinese = true;
    }
    else
     {
        if( pTranslator!= nullptr)
            pTranslator->load(":/en.qm"); //:/en.qm
        ApplicationConfig::writeConfig(CONFIG_KEY_LANGUAGE, "2");
        mIsChinese = false;
     }

}

ToolKit::ToolKit()
{

}
