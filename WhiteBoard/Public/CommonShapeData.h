#ifndef COMMONSHAPEDATA_H
#define COMMONSHAPEDATA_H

#include <QColor>

//border property data
struct  BorderStyle
{
public:
    BorderStyle(int _width,  const QColor& _color,  Qt::PenStyle  _lineStyle) : borderWidth(_width), borderColor(_color), borderLineStyle(_lineStyle) {}
    BorderStyle() { borderWidth = 1;  borderColor = Qt::red; borderLineStyle = Qt::SolidLine; }
    //default style of construct function
    int borderWidth;
    QColor borderColor;
    Qt::PenStyle borderLineStyle;
};

//Fill property data
struct  FillStyle
{
public:
    FillStyle(const QColor& color) : fillColor(color), isNone(false){}
    FillStyle() : isNone(true){ fillColor = Qt::red;}
    QColor fillColor;
    bool isNone;
};

//operation Record Type
enum ShapeOperRecordType { Add = 1, MoveChanged, RotateChanged,  PathChanged, BorderStyleChange, FillStyleChange, ZIndexChange, Delete, NoneRecord};

enum ShapePropertyType{  BorderProperty =1,  FillProperty, FlipProperty, MirrorProperty,
                                                  CloneProperty,  ToTopProperty, ToBottomProperty,  DeleteProperty,  ResizeProperty,  NoneProperty};


enum ShapeType{ CustomShape = 1,  LineShape,  PolygenShape,  PictureShape, PictureArrayShape , RulerShape };

#endif // COMMONSHAPEDATA_H
