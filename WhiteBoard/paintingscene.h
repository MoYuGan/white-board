#ifndef PAINTINGSCENE_H
#define PAINTINGSCENE_H

/*
*   绘画场景
*/

#include <QWidget>
#include <QPixmap>
#include <QVector>
#include <QColor>
#include <QTouchEvent>

//#define MouseDrawing

enum FileSaveType   //保存文件的格式
{
    FT_PNG,
    FT_JPG,
    FT_BMP,
    FT_DOC,
    FT_DOCX,
    FT_PPT,
    FT_PPTX,
    FT_PDF
};

class PaintingScene : public QWidget
{
    Q_OBJECT
public:
    explicit PaintingScene(QWidget *parent = nullptr, int width = 0, int height = 0);
    void show();
    void undo_painting();                                           //撤消绘画
    void restore_painting();                                        //恢复绘画
    void save_pixmap(FileSaveType fType, QString fileName);         //保存绘画
    void load_pixmap(FileSaveType fType, QString fileName);         //加载绘画
    void clear_handwriting();                                       //清除笔迹

protected:
#ifdef MouseDrawing
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
#endif
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pixmap;                     //绘图区
    QPixmap tempPixmap;                 //临时绘图区
    QPixmap erasePixmap;                //橡皮擦擦除临时保存区
    bool drawAcitonComplete;            //绘图动作完成标志
    QVector<QLineF> linefVector;        //多点线段集合
    QVector<QPixmap> undoVector;        //撤销图集合
    QVector<QPixmap> recoveVector;      //恢复图集合   

    ToolBarAction::ActionType toolType; //工具

    BrushType brushType;                //画笔类型
    QColor brushColor;                  //画笔颜色
    int brushSize;                      //画笔大小

    bool canPaint;

#ifdef MouseDrawing
    /********************* 鼠标画图 **************/
    bool mousePressed;                  //鼠标按住标志位
    QPoint lastPosition;                //上一个点
    QPoint currentPosition;             //当前点
#endif
    void add_lineF(QTouchEvent *e);                 //多点触摸画线
    void save_pixmap_to_pdf(QString fileName);      //保存成pdf格式文件
    void save_pixmap_to_word(QString fileName);     //保存成word格式文件
    void save_pixmap_to_ppt(QString fileName);      //保存成ppt格式文件

    void load_picture_to_pixmap(QString fileName);  //加载图片格式文件
    void load_pdf_to_pixmap(QString fileName);      //加载pdf格式文件
signals:

public slots:
    void pen_changed_slot(BrushType, QColor, int);
    void toolBar_action_changed_slot(ToolBarAction::ActionType);

signals:
    void mouse_pressed();
};

#endif // PAINTINGSCENE_H
