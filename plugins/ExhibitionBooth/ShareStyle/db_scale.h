#ifndef DB_SCALE_H
#define DB_SCALE_H

#include <QFont>
#include <QDesktopWidget>
#include <QApplication>

/*
*   程序缩放，自适应分辨率
*/

//标准大小，以1920x1080的显示器为标准
#define BASE_SIZE 1920.00

class DB_ApplicationScale {
public:
    //根据缩放比例缩放大小字体
    static QFont getFont(int fontSize) {
        int newFontSize = fontSize * getScaling();

        QFont font;
        font.setPixelSize(newFontSize);
        return font;
    }

    //根据缩放比例缩放QSize
    static QSize getScaleSize(const QSize &size) {
        int w = size.width() * getScaling();
        int h = size.height() * getScaling();
        return QSize(w, h);

    }

    static int getScaleSize(int width) {
        int w = width * getScaling();
        return w;
    }

    static int getScaleWidth(int width) {
        int w = width * getScaling();
        return w;
    }

    static QColor getTextColor() {
        return QColor(105, 105, 105);
    }

    /*
     * 功能:以1920x1080的显示器为标准，获取当前主屏幕的大小，计算缩放比例
    */
    static qreal getScaling() {
        QDesktopWidget *desktopWidget = QApplication::desktop();
        int screenWidth = desktopWidget->screenGeometry(desktopWidget->primaryScreen()).width();

        return screenWidth/BASE_SIZE;
    }

    static QColor getFontColor() {
        return QColor(105, 105, 105);
    }
};

#endif // DB_SCALE_H
