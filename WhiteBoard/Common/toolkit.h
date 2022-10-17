#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <QWidget>
#include <QTranslator>

class ToolKit
{
public:
    /***
     * to start Animation
     *
     * **/
    static void StartAnimation(QWidget* wid, const QPoint& fromPnt, const QPoint& toPnt, int playTime = 2000);
    static void installTranslator();
    static void ToggleLanguage(bool isChinese);
    static bool IsChineseLanguage(){return mIsChinese; }
private:
    static QTranslator* pTranslator;
    static bool mIsChinese;
    ToolKit();
};

#endif // TOOLKIT_H
