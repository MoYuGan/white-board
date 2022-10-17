#ifndef CUTOMTOOLBAR_1_H
#define CUTOMTOOLBAR_1_H

/*
*
* 自定义工具条:
*   白板主界面下方工具栏
*
*/

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QFrame>
#include <QMap>
#include <QPainter>
#include <QButtonGroup>
#include "../PushButton/custompushbutton_1.h"
#include "../../Public/publicfunction.h"

class CustomToolBar_1 : public QWidget
{
    Q_OBJECT
public:
    explicit CustomToolBar_1(QWidget *parent = nullptr);
    ~CustomToolBar_1();
    void mAddAction(int id, const QString &text, const QPixmap &icon = QPixmap(),
                    const QColor &textColor = QColor(), const QColor &hoverColor =  QColor(),
                    bool isChecked = true, const QColor &checkedTextColor = QColor(), const QPixmap &checkedIcon = QPixmap(),
                    const QColor &checkedColor = QColor());
    void mSetRadius(int topLeft = 0, int topRight = 0, int bottomLeft = 0, int bottomRight = 0);
    void mSetTransparentBorder(int left = 0, int top = 0, int right = 0, int bottom = 0);
    void mSetMargin(int left = 0, int right = 0);
    void mSetActionMargin(int marginTop = 0, int marginTopChecked = 0, int marginBottom = 0, int marginBottomChecked = 0);
    void mSetActionSize(int fixWidth, const QSize &iconSize, int radius = 0);
    void mSetFont(const QFont &font);
    void mSetExclusive(bool bo);
    void mSetActionChecked(int id, bool bo);
    inline int mGetTransparentBorderBottom() { return m_TransparentBorderBottom; }
    int mGetActionCenterX(int id);
    void mSetActionCheckedIcon(int id, const QPixmap &pixmap);


protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    QHBoxLayout *m_Layout;
    //工具栏透明边距
    int m_TransparentBorderTop = 0;
    int m_TransparentBorderBottom = 0;
    int m_TransparentBorderLeft = 0;
    int m_TransparentBorderRight = 0;
    int m_MaxTransparentBorder = 0;
    //Action上下边距,选中和没选中状态
    int m_ActionMarginTop = 0;
    int m_ActionMarginTopChecked = 0;
    int m_ActionMarginBottom = 0;
    int m_ActionMarginBottomChecked = 0;
    //左右边距
    int m_MarginLeft = 0;
    int m_MarginRight = 0;
    //圆角
    int m_TopLeftRadius = 0;
    int m_TopRightRadius = 0;
    int m_BottomLeftRadius = 0;
    int m_BottomRightRadius = 0;


    QMap<int, CustomPushButton_1*> m_ActionBtnMap;
    QMap<int, QHBoxLayout*> m_ActionLayout;
    QButtonGroup *m_CheckableButtonGroup;

private:
    void initWidget();

signals:
    void actionClicked(int);
    void actionCheckedClicked(int);
    void actionToggled(int, bool);

};

#endif // CUTOMTOOLBAR_1_H
