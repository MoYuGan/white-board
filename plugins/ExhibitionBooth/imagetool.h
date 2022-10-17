#ifndef IMAGETOOL_H
#define IMAGETOOL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QEventLoop>
#include <QtDebug>
#include <QFrame>
#include "ShareStyle/db_scale.h"
#include "Custom/CustomPushButton/custompushbutton.h"

enum class ToolDirection
{
    LeftToRight,
    RightToLeft,
    TopToBottom,
    BottomToTop
};

class ImageTool : public QWidget
{
    Q_OBJECT
public:
    ImageTool(ToolDirection direction, QWidget *parent = nullptr) : QWidget(parent), m_pDirection(direction)
    {
        this->installEventFilter(this);
        this->initWidget();
        m_pActionSize = QSize(24, 24);
        m_pIsShowing = true;
    }

    //添加按钮
    QPushButton* mSetAction(const QString &fileName, const QString &hoverFileName = QString(),
                    bool checkable = false, const QString &checkecFileName = QString(), bool checked = false) {
        CustomPushButton *pushButton = new CustomPushButton(this);
        pushButton->setAutoFillBackground(true);
        pushButton->setFixedSize(m_pActionSize);
        pushButton->setCheckable(checkable);
        if (checkable)
            pushButton->setChecked(checked);
        QString styleSheet = QString("QPushButton{border-image: url('%1');}").arg(fileName);
        if (!hoverFileName.isEmpty()) {
            styleSheet.append(QString("QPushButton::hover{border-image: url('%1');}").arg(hoverFileName));
        }
        if (!checkecFileName.isEmpty())
            styleSheet.append(QString("QPushButton::checked{border-image: url('%1');}").arg(checkecFileName));
        pushButton->setStyleSheet(styleSheet);
        QPalette palette;
        palette.setBrush(QPalette::Background, QPixmap(fileName));
        pushButton->setPalette(palette);
        switch(m_pDirection) {
        case ToolDirection::LeftToRight: {
            m_pLayout->addWidget(pushButton, 0, m_pBtnList.size());
        }break;
        case ToolDirection::RightToLeft: {
            m_pLayout->addWidget(pushButton, 0, 0);
        }break;
        case ToolDirection::TopToBottom: {
             m_pLayout->addWidget(pushButton, m_pBtnList.size(), 0);
        }break;
        case ToolDirection::BottomToTop: {
            m_pLayout->addWidget(pushButton, 0, 0);
        }break;
        default:
            break;
        }
        m_pBtnList.append(pushButton);
        m_pFrame->adjustSize();
        this->setFixedSize(m_pFrame->size());
        this->getMaxSize();
        return pushButton;
    }

    void setActionSize(const QSize &size) {
        m_pActionSize = size;
        foreach (QPushButton *button, m_pBtnList) {
            button->setFixedSize(size);
        }
        m_pFrame->adjustSize();
        this->setFixedSize(m_pFrame->size());
        this->getMaxSize();
    }

    bool isToolShowing() {
        return m_pIsShowing;
    }

    int maxHeight() {
        return this->height();
    }

    void showTool() {
//        QEventLoop loop;
//        connect(this, &ImageTool::scaleFinished, &loop, &QEventLoop::quit);
//        m_pTimer->start(m_pStartTime);
//        loop.exec();
        this->setFixedWidth(m_pMaxSize);

        m_pIsShowing = true;
    }

    void hideTool() {
//        QEventLoop loop;
//        connect(this, &ImageTool::scaleFinished, &loop, &QEventLoop::quit);
//        m_pTimer->start(m_pStartTime);
//        loop.exec();
        this->setFixedWidth(m_pMinSize);
        m_pIsShowing = false;
    }

private:
    QGridLayout *m_pLayout;
    QList<QPushButton *> m_pBtnList;
    QSize m_pActionSize;                //按钮大小
    int m_pMaxSize;                   //窗口的最大高度，加入按钮越多高度越大
    QTimer *m_pTimer;                   //弹出（收起）定时器
    int m_pSpacing;                     //按钮之间的间隔
    int m_pShowHeightEveryTimes;        //每次弹出（收起）增加（减少）的高度
    int m_pMinSize;                   //最小高度，至少显示一个按钮，所以第一个按钮用来控制显示和收起
    bool m_pIsShowing;                  //是否已经弹出
    int m_pStartTime = 10;              //每次显示（缩起）时间间隔(ms)
    QFrame *m_pFrame;
    ToolDirection m_pDirection;

    void initWidget() {
        m_pFrame = new QFrame(this);
        m_pFrame->setObjectName("frame");
        m_pFrame->setStyleSheet("#frame{border: none;}");
        m_pFrame->move(QPoint(0, 0));
        m_pLayout = new QGridLayout(m_pFrame);
        m_pLayout->setContentsMargins(0, 0, 0, 0);
        m_pSpacing = DB_ApplicationScale::getScaleWidth(10);
        m_pLayout->setSpacing(m_pSpacing);

        m_pTimer = new QTimer(this);
        connect(m_pTimer, &QTimer::timeout, [=](){
            m_pTimer->stop();
            if (m_pIsShowing) {     //收起
                switch(m_pDirection) {
                case ToolDirection::LeftToRight: {
                    int width = this->width() - m_pShowHeightEveryTimes;
                    width = width <  m_pMinSize ? m_pMinSize : width;
                    this->setFixedWidth(width);

                    if (this->width() > m_pMinSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                case ToolDirection::RightToLeft: {
                    int width = this->width() - m_pShowHeightEveryTimes;
                    width = width <  m_pMinSize ? m_pMinSize : width;
                    QPoint pos = this->rect().topRight();
                    this->setFixedWidth(width);
                    this->move(QPoint(pos.x() - width, pos.y()));
                    if (this->width() > m_pMinSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                case ToolDirection::TopToBottom: {
                    int height = this->height() - m_pShowHeightEveryTimes;
                    height = height <  m_pMinSize ? m_pMinSize : height;
                    this->setFixedHeight(height);

                    if (this->height() > m_pMinSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                case ToolDirection::BottomToTop: {
                    int height = this->height() - m_pShowHeightEveryTimes;
                    height = height <  m_pMinSize ? m_pMinSize : height;
                    QPoint pos = this->rect().bottomLeft();
                    this->setFixedHeight(height);
                    this->move(QPoint(pos.x(), pos.y() - height));

                    if (this->height() > m_pMinSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                default:
                    break;
                }
            }else { //弹出
                switch(m_pDirection) {
                case ToolDirection::LeftToRight: {
                    int width = this->width() + m_pShowHeightEveryTimes;
                    width = width >  m_pMaxSize ? m_pMaxSize : width;
                    this->setFixedWidth(width);

                    if (this->width() < m_pMaxSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                case ToolDirection::RightToLeft: {
                    int width = this->width() + m_pShowHeightEveryTimes;
                    width = width >  m_pMaxSize ? m_pMaxSize : width;
                    QPoint pos = this->rect().topRight();
                    this->setFixedWidth(width);
                    this->move(QPoint(pos.x() - width, pos.y()));

                    if (this->width() < m_pMaxSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                case ToolDirection::TopToBottom: {
                    int height = this->height() + m_pShowHeightEveryTimes;
                    height = height >  m_pMaxSize ? m_pMaxSize : height;
                    this->setFixedHeight(height);

                    if (this->height() < m_pMaxSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                case ToolDirection::BottomToTop: {
                    int height = this->height() + m_pShowHeightEveryTimes;
                    height = height >  m_pMaxSize ? m_pMaxSize : height;
                    QPoint pos = this->rect().bottomLeft();
                    this->setFixedHeight(height);
                    this->move(QPoint(pos.x(), pos.y() - height));

                    if (this->height() < m_pMaxSize) {
                        m_pTimer->start(m_pStartTime);
                    }else {
                        emit scaleFinished();
                    }
                }break;
                default:
                    break;
                }
            }
        });
    }

    void getMaxSize() {
        int size = m_pBtnList.size();
        if (0 == size)
            return;

        switch(m_pDirection) {
        case ToolDirection::LeftToRight: {
            m_pMaxSize = size*m_pActionSize.width() + (size - 1)*m_pSpacing;
            m_pMinSize = m_pActionSize.width();
        }break;
        case ToolDirection::RightToLeft: {
            m_pMaxSize = size*m_pActionSize.width() + (size - 1)*m_pSpacing;
            m_pMinSize = m_pActionSize.width();
        }break;
        case ToolDirection::TopToBottom: {
            m_pMaxSize = size*m_pActionSize.height() + (size - 1)*m_pSpacing;
            m_pMinSize = m_pActionSize.height();
        }break;
        case ToolDirection::BottomToTop: {
            m_pMaxSize = size*m_pActionSize.height() + (size - 1)*m_pSpacing;
            m_pMinSize = m_pActionSize.height();
        }break;
        default:
            break;
        }

        m_pShowHeightEveryTimes = m_pMaxSize/10;
    }

signals:
    void scaleFinished();
};

#endif // IMAGETOOL_H
