#include "paintingscene.h"

#include <QLineF>
#include <QPainter>
#include <QtDebug>
#include <QPrinter>
#include <QPdfWriter>
#include <QHBoxLayout>

PaintingScene::PaintingScene(QWidget *parent, int width, int height) : QWidget(parent)
{
    this->resize(width, height);
    setMouseTracking(true);

    pixmap = QPixmap(width, height);
    pixmap.fill(Qt::white);
    undoVector.append(pixmap);

    #ifndef MouseDrawing
    this->setAttribute(Qt::WA_AcceptTouchEvents, true);//开启接受触摸事件
    #endif

    drawAcitonComplete = true;
#ifdef MouseDrawing
    mousePressed = false;
#endif
    canPaint = false;
    toolType = ToolBarAction::ActionType::None;
}

void PaintingScene::show()
{
    canPaint = true;
    QWidget::show();
}

void PaintingScene::undo_painting()
{
    if (undoVector.size() < 2)
        return;

    pixmap = undoVector.at(undoVector.size()-2);
    recoveVector.append(undoVector.at(undoVector.size()-1));
    undoVector.pop_back();

    update();
}

void PaintingScene::restore_painting()
{
    if (0 == recoveVector.size())
        return;

    pixmap = recoveVector.at(recoveVector.size()-1);
    undoVector.append(recoveVector.at(recoveVector.size()-1));
    recoveVector.pop_back();

    update();
}

void PaintingScene::save_pixmap(FileSaveType fType, QString fileName)
{
    switch (fType)
    {
    case FileSaveType::FT_PNG:
        pixmap.save(fileName);
        break;
    case FileSaveType::FT_JPG:
        pixmap.save(fileName);
        break;
    case FileSaveType::FT_BMP:
        pixmap.save(fileName);
        break;
    case FileSaveType::FT_DOC:
        save_pixmap_to_word(fileName);
        break;
    case FileSaveType::FT_DOCX:
        save_pixmap_to_word(fileName);
        break;
    case FileSaveType::FT_PPT:
        save_pixmap_to_ppt(fileName);
        break;
    case FileSaveType::FT_PPTX:
        save_pixmap_to_ppt(fileName);
        break;
    case FileSaveType::FT_PDF: {
        save_pixmap_to_pdf(fileName);
    }break;
    default:
        break;
    }

}

void PaintingScene::load_pixmap(FileSaveType fType, QString fileName)
{
    switch (fType)
    {
    case FileSaveType::FT_PNG:
        load_picture_to_pixmap(fileName);
        break;
    case FileSaveType::FT_JPG:
        load_picture_to_pixmap(fileName);
        break;
    case FileSaveType::FT_BMP:
        load_picture_to_pixmap(fileName);
        break;
    case FileSaveType::FT_DOC:
        break;
    case FileSaveType::FT_DOCX:
        break;
    case FileSaveType::FT_PPT:
        break;
    case FileSaveType::FT_PPTX:
        break;
    case FileSaveType::FT_PDF: {
    }break;
    default:
        break;
    }
}

void PaintingScene::clear_handwriting()
{
    pixmap.fill(Qt::white);
    undoVector.append(pixmap);
    update();
}

#ifdef MouseDrawing
void PaintingScene::mousePressEvent(QMouseEvent *event)
{
    emit mouse_pressed();

    if (event->button() == Qt::LeftButton && toolType != ToolBarAction::ActionType::None)
    {
        lastPosition = event->globalPos();
        currentPosition = lastPosition;
        mousePressed = true;
        drawAcitonComplete = false;

        if(0 < undoVector.size())
            tempPixmap = undoVector.at(undoVector.size()-1);

        update();
    }

    event->accept();
}

void PaintingScene::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed || toolType == ToolBarAction::ActionType::Eraser)
    {
        currentPosition = event->globalPos();
        update();
    }

    event->accept();
}



void PaintingScene::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && toolType != ToolBarAction::ActionType::None)
    {
//        if (toolType == ToolBarAction::ActionType::Eraser)  //判断使用橡皮擦后画板是否有改变，避免重复将相同的pixmap加入撤消集合
//        {
//            QImage image_1 = pixmap.toImage();
//            QImage image_2 = tempPixmap.toImage();

//            int i, j;
//            for(i = 0; i < pixmap.height(); i++)
//            {
//                for (j = 0; j < pixmap.width(); j++)
//                {
//                    if (image_1.pixel(i, j) != image_2.pixel(i, j))
//                        break;
//                }

//                if (j != pixmap.width())
//                    break;
//            }

//            if (i != pixmap.height() || j != pixmap.width()) {
//                pixmap = tempPixmap;
//                undoVector.append(pixmap);
//            }
//        }else {
//            pixmap = tempPixmap;
//            undoVector.append(pixmap);
//        }

        pixmap = tempPixmap;
        undoVector.append(pixmap);

        mousePressed = false;
        drawAcitonComplete = true;
        update();
    }
}
#endif

bool PaintingScene::event(QEvent *event)
{
#ifdef MouseDrawing
    if (toolType == ToolBarAction::ActionType::Eraser && event->type() == QEvent::Leave)
    {
        currentPosition = QPoint(-1, -1);
        update();
    }

    return QWidget::event(event);
#else
    switch (event->type())
    {
    case QEvent::TouchBegin:
    {
        drawAcitonComplete = false;

        tempPixmap = undoVector.at(undoVector.size() - 1);

        break;
    }
    case QEvent::TouchUpdate:
    {
        QTouchEvent *te = static_cast<QTouchEvent *>(event);

        if (toolType == ToolBarAction::ActionType::Pen)
            add_lineF(te);
        else if (toolType == ToolBarAction::ActionType::Eraser) {
//            QList<QTouchEvent::TouchPoint> touchPoints = te->touchPoints();  //将存储的所有点存储到容器


//            qDebug()<<endl;
//            foreach(QTouchEvent::TouchPoint i, touchPoints)                 //遍历出所有点
//            {
//                /**
//                 *    i.lastPos() //上次点击位置lastPos()
//                 *    i.pos()     //本次点击位置pos()
//                **/
//                qDebug<<i.pos()<<i.lastPos();
//            }
        }

        update();
        break;
    }
    case QEvent::TouchEnd:
    {
        pixmap = tempPixmap;
        undoVector.append(pixmap);

        recoveVector.clear();

        drawAcitonComplete = true;

        update();
        break;
    }
    default:
        return QWidget::event(event);
    }

    return true;
#endif
}


void PaintingScene::paintEvent(QPaintEvent *event)
{
    if (!canPaint)
        return QWidget::paintEvent(event);

#ifdef MouseDrawing
    if (mousePressed) {

        QPainter painter(&tempPixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿

        switch (toolType)
        {
        case ToolBarAction::ActionType::Pen: {
            QPen pen;
            pen.setWidth(brushSize);
            pen.setColor(brushColor);

            painter.setPen(pen);
            painter.drawLine(lastPosition, currentPosition);
            lastPosition = currentPosition;
        }break;
        case ToolBarAction::ActionType::Eraser: {            //实行擦除功能
            QPen pen;
            pen.setWidth(20);
            pen.setColor(QColor(Qt::white));

            painter.setPen(pen);
            painter.drawLine(lastPosition, currentPosition);
            lastPosition = currentPosition;

            erasePixmap = tempPixmap;

            QPainter painter2(&erasePixmap);
            painter2.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿

            pen.setWidth(2);
            pen.setColor(QColor(Qt::green));
            pen.setStyle(Qt::DashLine);

            painter2.setPen(pen);
            painter2.drawEllipse(currentPosition, 20, 20);
        }break;

        }
    }else if (toolType == ToolBarAction::ActionType::Eraser) {      //鼠标未按住，只画橡皮擦虚线框
        if (currentPosition != QPoint(-1, -1)) {                    //鼠标在画板内，画虚线框
            erasePixmap = pixmap;

            QPainter painter(&erasePixmap);
            painter.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿

            QPen pen;
            pen.setWidth(2);
            pen.setColor(QColor(Qt::green));
            pen.setStyle(Qt::DashLine);

            painter.setPen(pen);
            painter.drawEllipse(currentPosition, 20, 20);
        }
    }

    QPainter painter(this);
    if (toolType != ToolBarAction::ActionType::Eraser) {
        if (!drawAcitonComplete) {
            painter.drawPixmap(0, 0, tempPixmap);
        }else {
            painter.drawPixmap(0, 0, pixmap);
        }
    }else {
        if (currentPosition == QPoint(-1, -1)) {            //鼠标离开画板，删除橡皮擦虚线框
            painter.drawPixmap(0, 0, pixmap);
        }else {
            painter.drawPixmap(0, 0, erasePixmap);
        }

    }

#else
    //if (!canPaint)
     //   return QWidget::paintEvent(event);

    if (drawAcitonComplete){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        painter.drawPixmap(0, 0, pixmap);
    }else {
        QPainter painter(&tempPixmap);

        QPen pen;

        pen.setWidth(brushSize);
        pen.setColor(brushColor);

        painter.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿
        painter.setPen(pen);
        painter.drawLines(linefVector);

        linefVector.clear();

        QPainter mPainter(this);
        mPainter.drawPixmap(0, 0, tempPixmap);
    }
#endif
}

void PaintingScene::add_lineF(QTouchEvent *e)
{
    QLineF linef;
    QList<QTouchEvent::TouchPoint> touchPoints = e->touchPoints();  //将存储的所有点存储到容器

    foreach(QTouchEvent::TouchPoint i, touchPoints)                 //遍历出所有点
    {
        /**
         *    i.lastPos() //上次点击位置lastPos()
         *    i.pos()     //本次点击位置pos()
        **/
        linef.setP1(i.lastPos());
        linef.setP2(QPointF((i.lastPos().x()+i.pos().x())/2,(i.lastPos().y()+i.pos().y())/2));
        linefVector.push_back(linef);
        linef.setP1(QPointF((i.lastPos().x()+i.pos().x())/2,(i.lastPos().y()+i.pos().y())/2));
        linef.setP2(i.pos());
        linefVector.push_back(linef);
    }
}

void PaintingScene::save_pixmap_to_pdf(QString fileName)
{
    QPdfWriter writer(fileName);
    writer.setPageSize(QPdfWriter::A3);
    writer.setPageMargins(QMargins(0, 0, 0, 0));
    writer.setResolution(300);

    QPainter painter(&writer);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawPixmap(0, 0, pixmap);
}

void PaintingScene::save_pixmap_to_word(QString fileName)
{
#if 0
    // 初始化;
    HRESULT result = OleInitialize(0);
    if (result != S_OK && result != S_FALSE)
    {
        qDebug() << QString("Could not initialize OLE (error %x)").arg((unsigned int)result);
    }
    //新建一个word应用程序;
    QAxObject *m_pWord = new QAxObject();
    bool bFlag = m_pWord->setControl("word.Application");
    if (!bFlag) return;

    // 设置 Office 应用不可见;
    m_pWord->setProperty("Visible", false);

    // 获取所有的工作文档;
    QAxObject *m_pWorkDocuments = m_pWord->querySubObject("Documents");
    if (!m_pWorkDocuments) return;

    // 新建文档;
    m_pWorkDocuments->dynamicCall("Add(void)");
    // 以模板 sFile (.dot) 为基础创建文档, sFile为空 表示新建文档;
    // document->dynamicCall( "Add(QString)" , sFile);

    // 获取当前激活的文档;
    QAxObject *m_pWorkDocument = m_pWord->querySubObject("ActiveDocument");
    if (!m_pWorkDocument) return;

    for (int i = 0; i < 5; ++i)
    {
        QString picNamePath = "E:\1.png";
        QAxObject *  bookmark_pic = m_pWord->querySubObject("Selection");
        if (!bookmark_pic->isNull())
        {
            //光标跳到最后一行;
            bookmark_pic->dynamicCall("EndOf(QVariant&, QVariant&)", 6,0).toInt();
            // selection->dynamicCall("EndOf(void)").toInt();//使用"EndOf(void)"也可实现
            QAxObject* range = bookmark_pic->querySubObject("Range");
            //插入图片;
            range->querySubObject("InlineShapes")->dynamicCall("AddPicture(const    QString&)", picNamePath);
        }
    }

    // 保存 Word 文档;
    m_pWorkDocument->dynamicCall("SaveAs (const QString&)", fileName);

    // 删除 析构 操作;
    m_pWord->setProperty("DisplayAlerts", true);
    m_pWorkDocument->dynamicCall("Close(bool)", true);
    m_pWord->dynamicCall("Quit()");

    delete m_pWorkDocuments;
    delete m_pWord;

    OleUninitialize();

#endif

}

void PaintingScene::save_pixmap_to_ppt(QString fileName)
{

}

void PaintingScene::load_picture_to_pixmap(QString fileName)
{
    pixmap.load(fileName);
    update();
}

void PaintingScene::load_pdf_to_pixmap(QString fileName)
{

}

void PaintingScene::pen_changed_slot(BrushType type, QColor color, int size)
{
    brushType = type;
    brushColor = color;
    brushSize = size;

    toolType = ToolBarAction::ToolBarAction::Pen;
}

void PaintingScene::toolBar_action_changed_slot(ToolBarAction::ActionType type)
{
    toolType = type;
}
