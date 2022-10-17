#include "displaywidget.h"
#include <QHBoxLayout>
#include <QFrame>
#include <QListWidget>
#include <QEvent>
#include <QFileDialog>
#include <QtDebug>
#include "ShareStyle/db_scale.h"

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
    this->initWidget();
    this->installEventFilter(this);
}

void DisplayWidget::hide()
{
    QWidget::hide();
    this->showTool(false);
}

void DisplayWidget::setDisplayWidget(QWidget *widget)
{
    m_pDisplayWidget = widget;
    m_pBoardView->setDisplayWidget(widget);
}

void DisplayWidget::showTool(bool bo)
{
    if (bo){    //展开工具条
        if (!m_pToolBtnShowTool->isChecked())
            m_pToolBtnShowTool->click();
    }else {     //收起工具条
        if (m_pToolBtnShowTool->isChecked())
            m_pToolBtnShowTool->click();
    }
}

void DisplayWidget::setChecked(bool bo)
{
    if (bo) {
        m_pFrame->setStyleSheet(QString("#%1{border: %2px solid red;}")
                                .arg(m_pFrame->objectName())
                                .arg(DB_ApplicationScale::getScaleWidth(2)));
    }else {
        m_pFrame->setStyleSheet(QString("#%1{border: %2px solid transparent;}")
                                .arg(m_pFrame->objectName())
                                .arg(DB_ApplicationScale::getScaleWidth(2)));
    }
    m_pChecked = bo;
}

void DisplayWidget::setShowFullScreenStyle(bool bo)
{
    if (bo) {
        m_pToolBtnFullScreen->setStyleSheet("QPushButton{border-image: url(':/images/shouqi.png');}");
    }else {
        m_pToolBtnFullScreen->setStyleSheet("QPushButton{border-image: url(':/images/quanping.png');}");
    }
}

void DisplayWidget::setDrawTool(DrawTool tool)
{
    m_pBoardView->setDrawTool(tool);
}

void DisplayWidget::undo()
{
    m_pBoardView->undo();
}

void DisplayWidget::redo()
{
    m_pBoardView->redo();
}

void DisplayWidget::zoomIn()
{
    m_pBoardView->zoomIn();
}

void DisplayWidget::zoomOut()
{
    m_pBoardView->zoomOut();
}

void DisplayWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    m_pBoardView->setGeometry(this->rect());
    m_pBoardView->raise();
    m_pTool->move(QPoint(DB_ApplicationScale::getScaleWidth(50),
                         this->height() - DB_ApplicationScale::getScaleWidth(100) - m_pTool->maxHeight()));
    m_pTool->raise();
}

bool DisplayWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (!m_pChecked) {
            this->setChecked(true);
            emit windowChecked();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void DisplayWidget::initWidget()
{
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->setSpacing(0);
    hlayout->setSizeConstraint(QLayout::SetDefaultConstraint);

    m_pFrame = new QFrame(this);
    m_pFrame->setObjectName("frame");
    m_pFrame->setStyleSheet(QString("#%1{border: %2px solid transparent;}")
                            .arg(m_pFrame->objectName())
                            .arg(DB_ApplicationScale::getScaleWidth(2)));
    QHBoxLayout *hlayout1 = new QHBoxLayout(m_pFrame);
    hlayout1->setSizeConstraint(QLayout::SetDefaultConstraint);
    hlayout1->setContentsMargins(0, 0, 0, 0);
    hlayout1->setSpacing(0);
    hlayout->addWidget(m_pFrame);

    m_pBoardView = new DB_BoardView(this);
    hlayout1->addWidget(m_pBoardView);

    /* 创建工具条 */
    m_pTool = new ImageTool(ToolDirection::LeftToRight, this);
    m_pTool->raise();
    m_pTool->setActionSize(DB_ApplicationScale::getScaleSize(QSize(60, 60)));
    //收起（展开图标）
    m_pToolBtnShowTool = m_pTool->mSetAction(":/images/gongju.png", "", true, ":/images/gongjuchecked.png", true);
    //全屏图标
    m_pToolBtnFullScreen = m_pTool->mSetAction(":/images/quanping.png", "");
    //加载图片图标
    m_pToolBtnOpenFile = m_pTool->mSetAction(":/images/tupian.png", "");
    //打开摄像头图标
    m_pToolBtnUseCamera = m_pTool->mSetAction(":/images/shexiangtou@2x.png", "", true, ":/images/shexiangtou2@2x.png");
    m_pToolBtnUseCamera->setChecked(true);
    connect(m_pToolBtnShowTool, &QPushButton::toggled, [=](){
        if (m_pToolBtnShowTool->isChecked())
            m_pTool->showTool();
        else
            m_pTool->hideTool();
    });
    connect(m_pToolBtnFullScreen, &QPushButton::clicked, [=](){
        emit this->windowShowFullScreen();
    });
    connect(m_pToolBtnOpenFile, &QPushButton::clicked, [=](){
        QFileDialog fileDialog;
        QString fileName = fileDialog.getOpenFileName(this, tr("打开文件"), "", "PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)");
        if (fileName.length() != 0) {
            QPixmap pixmap;
            pixmap.load(fileName);
            m_pToolBtnUseCamera->setChecked(false);
            emit this->showCameraFrame(false, m_pDisplayWidget, pixmap);
        }
    });
    connect(m_pToolBtnUseCamera, &QPushButton::toggled, this, [=](){
        if (m_pToolBtnUseCamera->isChecked()) {
            emit this->showCameraFrame(true, m_pDisplayWidget, QPixmap());
        }else {
            emit this->showCameraFrame(false, m_pDisplayWidget, QPixmap());
        }

    });
}
