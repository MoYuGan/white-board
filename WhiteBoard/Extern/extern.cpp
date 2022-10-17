#include "extern.h"

int g_ScreenWidth;
int g_ScreenHeight;
int z_ValueMax =0;
int g_PenSize =5;
QColor g_PenColor =Qt::white;
QSize g_EraserSize;
PenType g_PenType = PenType::None;
ToolType g_ToolType = ToolType::Pen;
GraphicType g_GraphicType = GraphicType::None;

GangBi g_GangBi;
RuanBi g_RuanBi;
YingGuangBi g_YingGuangBi;
TuAnBi g_TuAnBi;

bool g_DrawGraphic = false;
bool g_CanBeSave = false;

int e_MinBoardPenSize;
QColor e_MinBoardPenColor;
QSize e_MinBoardEraseSize;
