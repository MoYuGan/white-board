#ifndef DB_FONT_H
#define DB_FONT_H

#include <QFont>
#include <QDesktopWidget>
#include <QApplication>

#define BASE_DPIX 96.00

class DB_Font {
public:
    /*
     * 功能:获取控件使用的字体,根据缩放比例调整字体大小
     * 参数说明：
     *  fontsize，对于不同字体大小的控件可传入不同的值得到缩放后的值，默认是9
    */
    static QFont getFont(int fontSize = 9) {
        int newFontSize = fontSize * getDpiScale();

        QFont font;
        font.setPixelSize(newFontSize);
        return font;
    }

    /*
     * 功能:根据系统当前DPI计算缩放比例，系统缩放比例是1:1时DPI是96
    */
    static double getDpiScale() {
        QDesktopWidget *desktopWidget = QApplication::desktop();
        int dpiX = desktopWidget->logicalDpiX();

        static double scaleDpi = ((double)dpiX)/BASE_DPIX;
        return scaleDpi;
    }
};

#endif // DB_FONT_H
