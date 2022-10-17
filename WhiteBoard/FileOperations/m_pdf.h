#ifndef M_PDF_H
#define M_PDF_H

#include <QVector>
#include <QPixmap>
#include <QDesktopWidget>
#include <QPainter>
#include <QPrinter>
#include <QApplication>
#include <QFileInfo>
extern "C"{
#include "mupdf/fitz.h"
#include "mupdf/pdf.h"
#include "mupdf/pdf/page.h"
#include "mupdf/fitz/document.h"
}
#include <QDebug>
class MPdf : public QWidget
{
    Q_OBJECT
public:
    MPdf() {}
    virtual ~MPdf() {}

static bool Savepdf(QVector<QPixmap> map,QString str_fileName)
{
    QDesktopWidget *desktop = QApplication::desktop();
    float width_size = desktop->width();
    float height_size = desktop->height();
    QPrinter printer_pixmap(QPrinter::HighResolution);
    printer_pixmap.setPageSize(QPagedPaintDevice::Custom);
    printer_pixmap.setPageSizeMM(QSizeF(width_size*16.67/47.25,height_size*16.67/47.25));
    printer_pixmap.setPageMargins(0, 0, 0, 0, QPrinter::DevicePixel);
    printer_pixmap.setOutputFormat(QPrinter::PdfFormat);  //设置输出格式为pdf
    printer_pixmap.setOutputFileName(str_fileName);   //设置输出路径
    QPainter painter_pixmap;
    painter_pixmap.begin(&printer_pixmap);
    float multiple = (double(painter_pixmap.viewport().width()) / map.at(0).width());
    float yMultiple = (double(painter_pixmap.viewport().height()) / map.at(0).height());
    float fMin = (multiple < yMultiple) ? multiple : yMultiple;
    painter_pixmap.scale(fMin, fMin); //将图像(所有要画的东西)在pdf上放大multiple-1倍

    for(int i = 0; i < map.count(); i++)
    {
        QPixmap pixmap = map.at(i);
        qDebug()<<pixmap.width()<<pixmap.height();
        painter_pixmap.drawPixmap(0,0,map.at(i));  //画图
        if(i != map.count() - 1)
        {
            printer_pixmap.newPage();
        }
    }
    painter_pixmap.end();
    QFileInfo file(str_fileName);
    if(file.exists()== true)
        return true;
    else
        return false;
}

/* page_number: 第一页   zoom: 缩放率  rotate: 旋转 */
static QVector<QPixmap> Openpdf(QString fileName, int page_number = 0, float zoom = 100, float rotate = 0)
{
    QVector<QPixmap> pixmap_list;
    int page_count = 0;     //总页数

    fz_context *ctx;
    fz_document *doc;
    fz_pixmap *pix;
    fz_matrix ctm;

    /* 创建上下文 */
    ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    if (!ctx)
    {
        qDebug()<<stderr<<"cannot create mupdf context";
        return pixmap_list;
    }

    /* 注册要处理的默认文件类型 */
    fz_try(ctx)
        fz_register_document_handlers(ctx);
    fz_catch(ctx)
    {
        qDebug()<<stderr<<"无法注册文档处理程序："<<fz_caught_message(ctx);
        fz_drop_context(ctx);
        return pixmap_list;
    }

    /* 打开文档 */
    fz_try(ctx)
        doc = fz_open_document(ctx, fileName.toStdString().c_str());
    fz_catch(ctx)
    {
        qDebug()<<stderr<<"无法打开文档："<<fz_caught_message(ctx);
        fz_drop_context(ctx);
        return pixmap_list;
    }

    /* 计算页数 */
    fz_try(ctx)
        {page_count = fz_count_pages(ctx, doc);
    qDebug() << " page_count" << page_count <<Qt::endl;}
    fz_catch(ctx)
    {
        qDebug()<<stderr<<"无法计算页数："<<fz_caught_message(ctx);
        fz_drop_document(ctx, doc);
        fz_drop_context(ctx);
        return pixmap_list;
    }

    if (page_number < 0 || page_number >= page_count)
    {
        qDebug()<<stderr<<"页码超出范围："<<page_number + 1<<" (页数 "<<page_count<<" )";
        fz_drop_document(ctx, doc);
        fz_drop_context(ctx);
        return pixmap_list;
    }

    /* 计算所需缩放和旋转的变换矩阵。*/
    /* 没有缩放的默认分辨率是 72 dpi。*/
    ctm = fz_scale(zoom / 100, zoom / 100);
    ctm = fz_pre_rotate(ctm, rotate);

    for(; page_number < page_count; page_number++)
    {
        /* 将页面渲染为 RGB 像素图。*/
        fz_try(ctx)
            pix = fz_new_pixmap_from_page_number(ctx, doc, page_number, ctm, fz_device_rgb(ctx), 0);
        fz_catch(ctx)
        {
            qDebug()<<stderr<<"无法渲染页面："<<fz_caught_message(ctx);
            fz_drop_document(ctx, doc);
            fz_drop_context(ctx);
            pixmap_list.clear();
            return pixmap_list;
        }

        unsigned char *samples = pix->samples;
        int width = fz_pixmap_width(ctx, pix);
        int height = fz_pixmap_height(ctx, pix);
        QImage image(samples, width, height, pix->stride, QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(image);
        pixmap_list.append(pixmap);
    }

    /* 清理。*/
    fz_drop_pixmap(ctx, pix);
    fz_drop_document(ctx, doc);
    fz_drop_context(ctx);

    return pixmap_list;
}
};

#endif // M_PDF_H
