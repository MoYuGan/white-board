#ifndef EXTERN_H
#define EXTERN_H

#include <QSize>
#include <QColor>
#include "Public/public_function.h"
#include <QGraphicsView>

#define MAX_HISTORY_NUM 10          //最大撤销次数
#define MSG_ID_SAVE "MSG_ID_SAVE"   //“保存”信号ID

//笔尖类型
enum class PenType
{
    GangBi,     //钢笔
    RuanBi,    //软笔
    YingGuangBi, //荧光笔
    TuAnBi, //图案笔
    None
};


struct GangBi
{
    QColor penColor =Qt::white;
    int PenSize =5;
};

struct RuanBi
{
    QColor penColor =Qt::white;
    int PenSize =5;
};


struct YingGuangBi
{
    QColor penColor =QColor(255,168,0,125);
    int PenSize =13;
};

struct TuAnBi
{
    QString str =QString(":/images/pen/plaint@2x.png");
    int PenSize =80;
};

//工具类型
enum class ToolType
{
    Cursor,     //光标
    Pen,        //画笔
    Erase       //橡皮擦
};

//图形类型
enum class GraphicType
{
    ZhiXian,            //直线
    XvXian,             //虚线
    XianDuan,           //线段
    JianTou,            //箭头
    ShuangJianTou,      //双箭头
    TuoYuan,            //椭圆
    JuXing,             //矩形
    YuanJiaoJuXing,     //圆角矩形
    PingXingSiBianXing, //平行四边形
    LingXing,           //菱形梯形
    TiXing,             //梯形
    ShanXing,           //扇形
    SanJiaoXing,        //三角形
    ZhiJiaoSanJiaoXing, //直角三角形
    WuBianXing,         //五边形
    LiuBianXing,        //六边形
    DuoBianXing,        //多边形
    WuJiaoXing,         //五角星
    TianZiGe,           //田字格
    LiFangTi,           //立方体
    YuanZhuTi,          //圆柱体
    YuanZhuiTi,         //圆锥
    SanLengZhui,        //三棱锥
    SiLengZhui,         //四棱锥
    None
};

enum class ItemType {
    PathItem = 99,
    GraphicItem = 100,
    LineItem = 101,
    PixmapItem = 102,
    SelectedRectItem = 110,
    ChiGuiItem = 108
};

extern int g_ScreenWidth;
extern int g_ScreenHeight;

extern int z_ValueMax;
extern int g_PenSize;
extern QColor g_PenColor;
extern QSize g_EraserSize;
extern PenType g_PenType;
extern ToolType g_ToolType;
extern GraphicType g_GraphicType;
extern bool g_DrawGraphic;
extern bool g_CanBeSave;                //白板可保存标志位

extern GangBi g_GangBi;
extern RuanBi g_RuanBi;
extern YingGuangBi g_YingGuangBi;
extern TuAnBi g_TuAnBi;

/* 最小化白板时使用 */
extern int e_MinBoardPenSize;
extern QColor e_MinBoardPenColor;
extern QSize e_MinBoardEraseSize;

#endif // EXTERN_H
