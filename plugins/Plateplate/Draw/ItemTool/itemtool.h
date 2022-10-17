#ifndef ITEMTOOL_H
#define ITEMTOOL_H

#include <QWidget>
#include <QAbstractButton>

/*
 * QGraphicsItem选中时的工具条
*/

namespace Ui {
class ItemTool;
}

class ItemTool : public QWidget
{
    Q_OBJECT
public:
    //被选中的items可能包含多种类型，有些工具需要移除
    enum  ToolFlag {
        RM_Border = 0x1,        //移除边框工具
        RM_FillColor = 0x2,     //移除填充工具
        RM_Flip = 0x4,          //移除翻转工具
        RM_Mirror = 0x8,        //移除镜像工具
        RM_Clone = 0x10,        //移除克隆工具
        RM_Bottom = 0x20,       //移除置底工具
        RM_Top = 0x40,          //移除置顶工具
        RM_Delete = 0x80,       //移除删除工具
        RM_Adjust = 0x100,      //移除调节工具
        RM_None = 0x00          //不移除
    };
    Q_DECLARE_FLAGS(ToolFlags, ToolFlag)
    Q_FLAG(ToolFlags)

public:
    explicit ItemTool(ToolFlags flags, bool isClone = false, bool isAdjust = false, QWidget *parent = 0);
    ~ItemTool();
    bool isClone();
    bool isAdjust();
    void clearCheck(QAbstractButton *button = nullptr);

private:
    Ui::ItemTool *ui;
    ToolFlags m_pToolFlags;
    int m_pToolNum;

private:
    void initWidget();
    void resize();

signals:
    void showBorderPanel(bool, QPointF);
    void showFillColorPanel(bool, QPointF);
    void showFlipPanel(bool, QPointF);
    void showMirrorPanel(bool, QPointF);
    void toTop();
    void toBottom();
    void toDelete();
    void toClone(bool);
    void toAdjust(bool);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ItemTool::ToolFlags)

#endif // ITEMTOOL_H
