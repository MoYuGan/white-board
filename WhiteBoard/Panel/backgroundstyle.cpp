#include "backgroundstyle.h"
#include "ui_backgroundstyle.h"
#include "Public/public_function.h"
#include <QTabBar>
#include <QDebug>
#include <QScrollBar>
#include <QFileDialog>
#include <QScroller>

BackgroundStyle::BackgroundStyle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackgroundStyle)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint,true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    initeventFilter();
    initWidget();
    initConnect();
    ui->atrovirens_Btn->setChecked(true);
    ui->purecolor_Btn->setChecked(true);
    ui->tabWidget->setCurrentWidget(ui->pure_Tab);
}

BackgroundStyle::~BackgroundStyle()
{
    delete ui;
}

void BackgroundStyle::initWidget()
{
    this->setFixedSize(Public_Function::getScaleSize(576,508));

    ui->back_Lab->setFixedSize(Public_Function::getScaleSize(31,24));
    ui->back_Lab->setPixmap(QPixmap(":/images/backgroundpixmap/fanhui@2x.png"));

    ui->text_Lab->setText(tr("背景样式"));
    ui->text_Lab->setStyleSheet(QString("color:rgb(68,68,68);font-size:%1px").arg(16));

    ui->all_Lab->setText(tr("应用到全部"));
    ui->all_Lab->setStyleSheet(QString("color:rgb(20,134,250);font-size:%1px").arg(16));

    ui->horizontalLayout_1->setContentsMargins(Public_Function::getScaleSize(16),Public_Function::getScaleSize(10),
                                               Public_Function::getScaleSize(20),Public_Function::getScaleSize(13));
    ui->horizontalLayout_1->setSpacing(Public_Function::getScaleSize(12));

    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setStyleSheet(QString("background-color:white;border:0px;border-bottom-right-radius:%1px;").arg(Public_Function::getScaleSize(8)));
    ui->purecolor_Btn->m_setText(tr("纯色背景"));
    ui->subject_Btn->m_setText(tr("学科背景"));
    ui->poetry_Btn->m_setText(tr("诗歌背景"));
    ui->custom_Btn->m_setText(tr("自定义"));

    group =new QButtonGroup(this);
    group->setExclusive(true);
    group->addButton(ui->purecolor_Btn,1);
    group->addButton(ui->subject_Btn,2);
    group->addButton(ui->poetry_Btn,3);
    group->addButton(ui->custom_Btn,4);

    backgroundgroup=new QButtonGroup(this);
    backgroundgroup->setExclusive(true);

    /******************纯色背景页面********************/
    backgroundgroup->addButton(ui->gray_Btn,1);
    backgroundgroup->addButton(ui->black_Btn,2);
    backgroundgroup->addButton(ui->atrovirens_Btn,3);
    ui->pure_Lab->setText(tr("纯色背景"));
    ui->verticalLayout_101->setContentsMargins(Public_Function::getScaleSize(32),Public_Function::getScaleSize(21),0,0);
    ui->verticalLayout_104->setContentsMargins(0,Public_Function::getScaleSize(16),Public_Function::getScaleSize(8),0);
    ui->verticalLayout_104->setSpacing(Public_Function::getScaleSize(12));
    ui->verticalLayout_105->setContentsMargins(0,Public_Function::getScaleSize(16),0,0);
    ui->verticalLayout_105->setSpacing(Public_Function::getScaleSize(12));


    ui->gray_Btn->m_setText(tr("浅灰色"),QColor(228,230,233));
    ui->black_Btn->m_setText(tr("深灰色"),QColor(32,32,34));
    ui->atrovirens_Btn->m_setText(tr("墨绿色"),QColor(36,66,66));


    /******************学科背景页面********************/
    ui->scrollAreaWidgetContents_2->setFixedSize(Public_Function::getScaleSize(460),Public_Function::getScaleSize(900));
    ui->subject_Lab->setText(tr("学科背景"));
    ui->verticalLayout_201->setContentsMargins(Public_Function::getScaleSize(32),Public_Function::getScaleSize(21),0,0);
    ui->verticalLayout_204->setContentsMargins(0,Public_Function::getScaleSize(16),Public_Function::getScaleSize(8),0);
    ui->verticalLayout_204->setSpacing(Public_Function::getScaleSize(16));
    ui->verticalLayout_205->setContentsMargins(0,Public_Function::getScaleSize(16),0,Public_Function::getScaleSize(0));
    ui->verticalLayout_205->setSpacing(Public_Function::getScaleSize(16));
    ui->tianzi_Btn->m_setText(tr("田字格"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing1@2x.png"));
    backgroundgroup->addButton(ui->tianzi_Btn,4);
    ui->mizi_Btn->m_setText(tr("米字格"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing2@2x.png"));
    backgroundgroup->addButton(ui->mizi_Btn,5);
    ui->sixian_Btn->m_setText(tr("四线格"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing3@2x.png"));
    backgroundgroup->addButton(ui->sixian_Btn,6);
    ui->xiaofang_Btn->m_setText(tr("小方格"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing4@2x.png"));
    backgroundgroup->addButton(ui->xiaofang_Btn,7);
    ui->pinyin_Btn->m_setText(tr("拼音田字格"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing5@2x.png"));
    backgroundgroup->addButton(ui->pinyin_Btn,8);
    ui->wuxian_Btn->m_setText(tr("五线谱"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing6@2x.png"));
    backgroundgroup->addButton(ui->wuxian_Btn,9);
    ui->zuobiao_Btn->m_setText(tr("坐标系"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing7@2x.png"));
    backgroundgroup->addButton(ui->zuobiao_Btn,10);
    ui->lanqiu_Btn->m_setText(tr("篮球场"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing8@2x.png"));
    backgroundgroup->addButton(ui->lanqiu_Btn,11);
    ui->zuqiu_Btn->m_setText(tr("足球场"),QColor(),QPixmap(":/images/backgroundpixmap/xuekebeijing9@2x.png"));
    backgroundgroup->addButton(ui->zuqiu_Btn,12);

    ui->scrollArea_2->verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical{width:%1px;background:transparent;margin:0px,0px,0px,0px;padding-top:0px;padding-bottom:0px;}"
                                                                "QScrollBar::handle:vertical{width:%1px;background:rgb(204,204,204);border-radius:%2px;min-height:%3;}"
                                                               "QScrollBar::add-line:vertical{height:0px;width:0px;subcontrol-position:bottom;}"
                                                               "QScrollBar::sub-line:vertical{height:0px;width:0px;subcontrol-position:top;}"
                                                               ).arg(Public_Function::getScaleSize(6)).arg(Public_Function::getScaleSize(3)).arg(Public_Function::getScaleSize(200)));
    QScroller::grabGesture(ui->scrollArea_2, QScroller::LeftMouseButtonGesture);//设置滑动手势
    /******************诗歌背景页面********************/
    ui->scrollAreaWidgetContents_3->setFixedSize(Public_Function::getScaleSize(460),Public_Function::getScaleSize(600));//2300
    ui->poetry_Lab->setText(tr("诗歌背景"));
    ui->verticalLayout_301->setContentsMargins(Public_Function::getScaleSize(32),Public_Function::getScaleSize(21),0,0);
    ui->verticalLayout_304->setContentsMargins(0,Public_Function::getScaleSize(16),Public_Function::getScaleSize(8),0);
    ui->verticalLayout_304->setSpacing(Public_Function::getScaleSize(16));
    ui->verticalLayout_305->setContentsMargins(0,Public_Function::getScaleSize(16),0,Public_Function::getScaleSize(0));
    ui->verticalLayout_305->setSpacing(Public_Function::getScaleSize(16));
    ui->poetry1_Btn->m_setText(tr("诗歌背景1"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing7@2x.png"));
    backgroundgroup->addButton(ui->poetry1_Btn,13);
    ui->poetry2_Btn->m_setText(tr("诗歌背景2"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing2@2x.png"));
    backgroundgroup->addButton(ui->poetry2_Btn,14);
    ui->poetry3_Btn->m_setText(tr("诗歌背景3"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing3@2x.png"));
    backgroundgroup->addButton(ui->poetry3_Btn,15);
    ui->poetry4_Btn->m_setText(tr("诗歌背景4"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing8@2x.png"));
    backgroundgroup->addButton(ui->poetry4_Btn,16);
    ui->poetry5_Btn->m_setText(tr("诗歌背景5"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing5@2x.png"));
    backgroundgroup->addButton(ui->poetry5_Btn,17);
    ui->poetry6_Btn->m_setText(tr("诗歌背景6"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing6@2x.png"));
    backgroundgroup->addButton(ui->poetry6_Btn,18);
#if  0
    ui->poetry7_Btn->m_setText(tr("诗歌背景7"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing7@2x.png"));
    backgroundgroup->addButton(ui->poetry7_Btn,19);
    ui->poetry8_Btn->m_setText(tr("诗歌背景8"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing8@2x.png"));
    backgroundgroup->addButton(ui->poetry8_Btn,20);
    ui->poetry9_Btn->m_setText(tr("诗歌背景9"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing9@2x.png"));
    backgroundgroup->addButton(ui->poetry9_Btn,21);
    ui->poetry10_Btn->m_setText(tr("诗歌背景10"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing10@2x.png"));
    backgroundgroup->addButton(ui->poetry10_Btn,22);
    ui->poetry11_Btn->m_setText(tr("诗歌背景11"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing11@2x.png"));
    backgroundgroup->addButton(ui->poetry11_Btn,23);
    ui->poetry12_Btn->m_setText(tr("诗歌背景12"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing12@2x.png"));
    backgroundgroup->addButton(ui->poetry12_Btn,24);
    ui->poetry13_Btn->m_setText(tr("诗歌背景13"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing13@2x.png"));
    backgroundgroup->addButton(ui->poetry13_Btn,25);
    ui->poetry14_Btn->m_setText(tr("诗歌背景14"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing14@2x.png"));
    backgroundgroup->addButton(ui->poetry14_Btn,26);
    ui->poetry15_Btn->m_setText(tr("诗歌背景15"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing15@2x.png"));
    backgroundgroup->addButton(ui->poetry15_Btn,27);
    ui->poetry16_Btn->m_setText(tr("诗歌背景16"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing16@2x.png"));
    backgroundgroup->addButton(ui->poetry16_Btn,28);
    ui->poetry17_Btn->m_setText(tr("诗歌背景17"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing17@2x.png"));
    backgroundgroup->addButton(ui->poetry17_Btn,29);
    ui->poetry18_Btn->m_setText(tr("诗歌背景18"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing18@2x.png"));
    backgroundgroup->addButton(ui->poetry18_Btn,30);
    ui->poetry19_Btn->m_setText(tr("诗歌背景19"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing19@2x.png"));
    backgroundgroup->addButton(ui->poetry19_Btn,31);
    ui->poetry20_Btn->m_setText(tr("诗歌背景20"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing20@2x.png"));
    backgroundgroup->addButton(ui->poetry20_Btn,32);
    ui->poetry21_Btn->m_setText(tr("诗歌背景21"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing21@2x.png"));
    backgroundgroup->addButton(ui->poetry21_Btn,33);
    ui->poetry22_Btn->m_setText(tr("诗歌背景22"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing22@2x.png"));
    backgroundgroup->addButton(ui->poetry22_Btn,34);
    ui->poetry23_Btn->m_setText(tr("诗歌背景23"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing23@2x.png"));
    backgroundgroup->addButton(ui->poetry23_Btn,35);
    ui->poetry24_Btn->m_setText(tr("诗歌背景24"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing24@2x.png"));
    backgroundgroup->addButton(ui->poetry24_Btn,36);
    ui->poetry25_Btn->m_setText(tr("诗歌背景25"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing25@2x.png"));
    backgroundgroup->addButton(ui->poetry25_Btn,37);
    ui->poetry26_Btn->m_setText(tr("诗歌背景26"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing26@2x.png"));
    backgroundgroup->addButton(ui->poetry26_Btn,38);
    ui->poetry27_Btn->m_setText(tr("诗歌背景27"),QColor(),QPixmap(":/images/backgroundpixmap/shigebeijing27@2x.png"));
    backgroundgroup->addButton(ui->poetry27_Btn,39);
#endif
    ui->poetry7_Btn->hide();
    ui->poetry8_Btn->hide();
    ui->poetry9_Btn->hide();
    ui->poetry10_Btn->hide();
    ui->poetry11_Btn->hide();
    ui->poetry12_Btn->hide();
    ui->poetry13_Btn->hide();
    ui->poetry14_Btn->hide();
    ui->poetry15_Btn->hide();
    ui->poetry16_Btn->hide();
    ui->poetry17_Btn->hide();
    ui->poetry18_Btn->hide();
    ui->poetry19_Btn->hide();
    ui->poetry20_Btn->hide();
    ui->poetry21_Btn->hide();
    ui->poetry22_Btn->hide();
    ui->poetry23_Btn->hide();
    ui->poetry24_Btn->hide();
    ui->poetry25_Btn->hide();
    ui->poetry26_Btn->hide();
    ui->poetry27_Btn->hide();

    ui->scrollArea_3->verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical{width:%1px;background:transparent;margin:0px,0px,0px,0px;padding-top:0px;padding-bottom:0px;}"
                                                                "QScrollBar::handle:vertical{width:%1px;background:rgb(204,204,204);border-radius:%2px;min-height:%3;}"
                                                               "QScrollBar::add-line:vertical{height:0px;width:0px;subcontrol-position:bottom;}"
                                                               "QScrollBar::sub-line:vertical{height:0px;width:0px;subcontrol-position:top;}"
                                                               ).arg(Public_Function::getScaleSize(6)).arg(Public_Function::getScaleSize(3)).arg(Public_Function::getScaleSize(200)));
    QScroller::grabGesture(ui->scrollArea_3->viewport(), QScroller::LeftMouseButtonGesture);//设置滑动手势
    /******************自定义背景页面********************/
    ui->custom_Lab->setText(tr("自定义背景"));
    backgroundgroup->addButton(ui->custompix_Btn,40);
    ui->horizontalLayout_401->setContentsMargins(Public_Function::getScaleSize(32),Public_Function::getScaleSize(21),0,0);
    ui->horizontalLayout_402->setContentsMargins(Public_Function::getScaleSize(32),Public_Function::getScaleSize(22),Public_Function::getScaleSize(0),0);
    ui->horizontalLayout_403->setContentsMargins(Public_Function::getScaleSize(32),Public_Function::getScaleSize(18),Public_Function::getScaleSize(0),0);
    ui->update_Btn->setFixedSize(Public_Function::getScaleSize(96),Public_Function::getScaleSize(38));
    ui->update_Btn->hide();
    ui->update_Btn->setStyleSheet("color:rgb(102,102,102);background-color:rgb(255,255,255);border:2px solid rgb(204,204,204);border-radius:4px;");
    ui->update_Btn->setText(tr("重新上传"));

}

void BackgroundStyle::initeventFilter()
{
    ui->back_Lab->installEventFilter(this);
    ui->all_Lab->installEventFilter(this);
}

void BackgroundStyle::initConnect()
{
    connect(group,QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&BackgroundStyle::changePage);
    connect(backgroundgroup,QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&BackgroundStyle::changeBackgroundPixmap);

    connect(ui->update_Btn,&QPushButton::clicked,this,[=](){
       QString filepath =QFileDialog::getOpenFileName(this,tr("Open File"),"/home",tr("Images (*.png *.jpg)"));
       if(filepath.isEmpty())return;
       ui->custompix_Btn->changePixmap(filepath);
       custompixmappath =filepath;
       ui->custompix_Btn->setChecked(true);
       changeBackgroundPixmap(backgroundgroup->button(40));
    });

    connect(ui->custompix_Btn,&PushButton_12::sendShowButtonSignal,this,[=](QString path){
        custompixmappath =path;
        changeBackgroundPixmap(backgroundgroup->button(40));
        ui->update_Btn->show();});
}

void BackgroundStyle::show()
{
    QWidget::show();
    this->raise();
}

void BackgroundStyle::hide()
{
    QWidget::hide();
    emit this->panelHide();
}

QPixmap BackgroundStyle::getBackgroundPixmap()
{

    QPixmap pixmap(g_ScreenWidth, g_ScreenHeight);
    if (ui->gray_Btn->isChecked()) {
        pixmap.fill(QColor(228,230,233));
    }else if (ui->black_Btn->isChecked()) {
        pixmap.fill(QColor(32,32,34));
    }else if (ui->atrovirens_Btn->isChecked()) {
        pixmap.fill(QColor(36,66,66));
    }else if (ui->tianzi_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJtianzige@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->sixian_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJsixiange@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->mizi_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJmizige@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->pinyin_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJpingtian@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->xiaofang_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJxiaofangge@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->wuxian_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJwuxianpu@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->zuobiao_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJzuobiaoxi@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->lanqiu_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJlanqiuchang@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }else if (ui->zuqiu_Btn->isChecked()) {
        pixmap = QPixmap(":/images/main/sceneBG/XKBJzuqiuchang@2x.png").scaled(g_ScreenWidth, g_ScreenHeight);
    }
    else if (ui->poetry1_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige7.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry2_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige2.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry3_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige3.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry4_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige8.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry5_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige5.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry6_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige6.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry7_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige7.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry8_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige8.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry9_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige9.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry10_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige10.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry11_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige11.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry12_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige12.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry13_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige13.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry14_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige14.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry15_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige15.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry16_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige16.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry17_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige17.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry18_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige18.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry19_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige19.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry20_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige20.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry21_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige21.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry22_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige22.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry23_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige23.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry24_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige24.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry25_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige25.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry26_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige26.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->poetry27_Btn->isChecked()) {
            pixmap = QPixmap(":/images/main/sceneBG/shige27.png").scaled(g_ScreenWidth, g_ScreenHeight);
        }
    else if (ui->custompix_Btn->isChecked()) {
            pixmap = QPixmap(custompixmappath).scaled(g_ScreenWidth, g_ScreenHeight);
        }

    return pixmap;
}

int BackgroundStyle::getBackgroundId()
{
    int id =-1;
    if (ui->gray_Btn->isChecked()) {
        id =1;
    }else if (ui->black_Btn->isChecked()) {
        id =2;
    }else if (ui->atrovirens_Btn->isChecked()) {
        id =3;
    }else if (ui->tianzi_Btn->isChecked()) {
        id =4;
    }else if (ui->sixian_Btn->isChecked()) {
        id =5;
    }else if (ui->mizi_Btn->isChecked()) {
        id =6;
    }else if (ui->pinyin_Btn->isChecked()) {
        id =7;
    }else if (ui->xiaofang_Btn->isChecked()) {
        id =8;
    }else if (ui->wuxian_Btn->isChecked()) {
        id =9;
    }else if (ui->zuobiao_Btn->isChecked()) {
        id =10;
    }else if (ui->lanqiu_Btn->isChecked()) {
        id =11;
    }else if (ui->zuqiu_Btn->isChecked()) {
        id =12;
    }else if (ui->poetry1_Btn->isChecked()) {
        id =13;
    }else if (ui->poetry2_Btn->isChecked()) {
        id =14;
    }else if (ui->poetry3_Btn->isChecked()) {
        id =15;
    }else if (ui->poetry4_Btn->isChecked()) {
        id =16;
    }else if (ui->poetry5_Btn->isChecked()) {
        id =17;
    }else if (ui->poetry6_Btn->isChecked()) {
        id =18;
    }else if (ui->poetry7_Btn->isChecked()) {
        id =19;
    }else if (ui->poetry8_Btn->isChecked()) {
        id =20;
    }else if (ui->poetry9_Btn->isChecked()) {
        id =21;
    }else if (ui->poetry10_Btn->isChecked()) {
        id =22;
    }else if (ui->poetry11_Btn->isChecked()) {
        id =23;
    }else if (ui->poetry12_Btn->isChecked()) {
        id =24;
    }else if (ui->poetry13_Btn->isChecked()) {
        id =25;
    }else if (ui->poetry14_Btn->isChecked()) {
        id =26;
    }else if (ui->poetry15_Btn->isChecked()) {
        id =27;
    }else if (ui->poetry16_Btn->isChecked()) {
        id =28;
    }else if (ui->poetry17_Btn->isChecked()) {
        id =29;
    }else if (ui->poetry18_Btn->isChecked()) {
        id =30;
    }else if (ui->poetry19_Btn->isChecked()) {
        id =31;
    }else if (ui->poetry20_Btn->isChecked()) {
        id =32;
    }else if (ui->poetry21_Btn->isChecked()) {
        id =33;
    }else if (ui->poetry22_Btn->isChecked()) {
        id =34;
    }else if (ui->poetry23_Btn->isChecked()) {
        id =35;
    }else if (ui->poetry24_Btn->isChecked()) {
        id =36;
    }else if (ui->poetry25_Btn->isChecked()) {
        id =37;
    }else if (ui->poetry26_Btn->isChecked()) {
        id =38;
    }else if (ui->poetry27_Btn->isChecked()) {
        id =39;
    }else if (ui->poetry27_Btn->isChecked()) {
        id =40;
    }else{
        id = -1;
    }
    return id;
}

QPixmap BackgroundStyle::getDefaultPixmap()
{
    QPixmap pixmap(g_ScreenWidth, g_ScreenHeight);
    pixmap.fill(QColor(36,66,66));
    return pixmap;
}

int BackgroundStyle::getDefaultId()
{
    return 3;
}

void BackgroundStyle::setCheckedIndex(int index)
{
    //disconnect(m_BgBtnGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onBtnGroupToggled(QAbstractButton*,bool)));
    if (1 == index) {
        ui->gray_Btn->setChecked(true);
    }else if (2 == index) {
        ui->black_Btn->setChecked(true);
    }else if (3 == index) {
        ui->atrovirens_Btn->setChecked(true);
    }else if (4 == index) {
        ui->tianzi_Btn->setChecked(true);
    }else if (5 == index) {
        ui->sixian_Btn->setChecked(true);
    }else if (6 == index) {
        ui->mizi_Btn->setChecked(true);
    }else if (7 == index) {
        ui->pinyin_Btn->setChecked(true);
    }else if (8 == index) {
        ui->xiaofang_Btn->setChecked(true);
    }else if (9 == index) {
        ui->wuxian_Btn->setChecked(true);
    }else if (10 == index) {
        ui->zuobiao_Btn->setChecked(true);
    }else if (11 == index) {
        ui->lanqiu_Btn->setChecked(true);
    }else if (12 == index) {
        ui->zuqiu_Btn->setChecked(true);
    }else if (13 == index) {
        ui->poetry1_Btn->setChecked(true);
    }else if (14 == index) {
        ui->poetry2_Btn->setChecked(true);
    }else if (15 == index) {
        ui->poetry3_Btn->setChecked(true);
    }else if (16 == index) {
        ui->poetry4_Btn->setChecked(true);
    }else if (17 == index) {
        ui->poetry5_Btn->setChecked(true);
    }else if (18 == index) {
        ui->poetry6_Btn->setChecked(true);
    }else if (19 == index) {
        ui->poetry7_Btn->setChecked(true);
    }else if (20 == index) {
        ui->poetry8_Btn->setChecked(true);
    }else if (21 == index) {
        ui->poetry9_Btn->setChecked(true);
    }else if (22 == index) {
        ui->poetry10_Btn->setChecked(true);
    }else if (23 == index) {
        ui->poetry11_Btn->setChecked(true);
    }else if (24 == index) {
        ui->poetry12_Btn->setChecked(true);
    }else if (25 == index) {
        ui->poetry13_Btn->setChecked(true);
    }else if (26 == index) {
        ui->poetry14_Btn->setChecked(true);
    }else if (27 == index) {
        ui->poetry15_Btn->setChecked(true);
    }else if (28 == index) {
        ui->poetry16_Btn->setChecked(true);
    }else if (29 == index) {
        ui->poetry17_Btn->setChecked(true);
    }else if (30 == index) {
        ui->poetry18_Btn->setChecked(true);
    }else if (31 == index) {
        ui->poetry19_Btn->setChecked(true);
    }else if (32 == index) {
        ui->poetry20_Btn->setChecked(true);
    }else if (33 == index) {
        ui->poetry21_Btn->setChecked(true);
    }else if (34 == index) {
        ui->poetry22_Btn->setChecked(true);
    }else if (35 == index) {
        ui->poetry23_Btn->setChecked(true);
    }else if (36 == index) {
        ui->poetry24_Btn->setChecked(true);
    }else if (37 == index) {
        ui->poetry25_Btn->setChecked(true);
    }else if (38 == index) {
        ui->poetry26_Btn->setChecked(true);
    }else if (39 == index) {
        ui->poetry27_Btn->setChecked(true);
    }else if (40 == index) {
        ui->custompix_Btn->setChecked(true);
    }

    //connect(m_BgBtnGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onBtnGroupToggled(QAbstractButton*,bool)));
}

void BackgroundStyle::updateLanguage()
{
    ui->text_Lab->setText(tr("背景样式"));
    ui->all_Lab->setText(tr("应用到全部"));
    ui->purecolor_Btn->m_setText(tr("纯色背景"));
    ui->subject_Btn->m_setText(tr("学科背景"));
    ui->poetry_Btn->m_setText(tr("诗歌背景"));
    ui->custom_Btn->m_setText(tr("自定义"));
    ui->pure_Lab->setText(tr("纯色背景"));

    ui->gray_Btn->m_setText(tr("浅灰色"),QColor(228,230,233));
    ui->black_Btn->m_setText(tr("深灰色"),QColor(32,32,34));
    ui->atrovirens_Btn->m_setText(tr("墨绿色"),QColor(36,66,66));

    ui->subject_Lab->setText(tr("学科背景"));

    ui->tianzi_Btn->setLocalTest(tr("田字格"));
    ui->mizi_Btn->setLocalTest(tr("米字格"));
    ui->sixian_Btn->setLocalTest(tr("四线格"));
    ui->xiaofang_Btn->setLocalTest(tr("小方格"));
    ui->pinyin_Btn->setLocalTest(tr("拼音田字格"));
    ui->wuxian_Btn->setLocalTest(tr("五线谱"));
    ui->zuobiao_Btn->setLocalTest(tr("坐标系"));
    ui->lanqiu_Btn->setLocalTest(tr("篮球场"));
    ui->zuqiu_Btn->setLocalTest(tr("足球场"));


     ui->poetry_Lab->setText(tr("诗歌背景"));     
     ui->poetry1_Btn->setLocalTest(tr("诗歌背景1"));
     ui->poetry2_Btn->setLocalTest(tr("诗歌背景2"));
     ui->poetry3_Btn->setLocalTest(tr("诗歌背景3"));
     ui->poetry4_Btn->setLocalTest(tr("诗歌背景4"));
     ui->poetry5_Btn->setLocalTest(tr("诗歌背景5"));
     ui->poetry6_Btn->setLocalTest(tr("诗歌背景6"));


     ui->custom_Lab->setText(tr("自定义背景"));
     ui->update_Btn->setText(tr("重新上传"));



}


void BackgroundStyle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.setBrush(QColor(255,255,255));
    painter.setPen(Qt::NoPen);

    QPainterPath uprect;
    uprect.moveTo(Public_Function::getScaleSize(8),0);
    uprect.lineTo(this->width() -Public_Function::getScaleSize(8),0);
    uprect.arcTo(QRect(QPoint(this->width() -2*Public_Function::getScaleSize(8),0),QPoint(this->width(),2*Public_Function::getScaleSize(8))),90,-90);
    uprect.lineTo(this->width(),Public_Function::getScaleSize(47));
    uprect.lineTo(0,Public_Function::getScaleSize(47));
    uprect.lineTo(0,Public_Function::getScaleSize(8));
    uprect.arcTo(QRect(QPoint(0,0),QPoint(2*Public_Function::getScaleSize(8),2*Public_Function::getScaleSize(8))),180,-90);
    painter.drawPath(uprect);

    painter.setBrush(QColor(224,224,224));
    painter.drawRect(QRect(QPoint(0,Public_Function::getScaleSize(47)),QPoint(this->width(),Public_Function::getScaleSize(48))));

    QPainterPath downrect;
    downrect.moveTo(0,Public_Function::getScaleSize(48));
    downrect.lineTo(this->width(),Public_Function::getScaleSize(48));
    downrect.lineTo(this->width(),this->height() -Public_Function::getScaleSize(8));
    downrect.arcTo(QRect(QPoint(this->width() -2*Public_Function::getScaleSize(8),this->height() -2*Public_Function::getScaleSize(8)),QPoint(this->width(),this->height())),0,-90);
    downrect.lineTo(Public_Function::getScaleSize(8),this->height());
    downrect.arcTo(QRect(QPoint(0,this->height() -2*Public_Function::getScaleSize(8)),QPoint(2*Public_Function::getScaleSize(8),this->height())),270,-90);
    downrect.lineTo(0,Public_Function::getScaleSize(48));

    painter.setBrush(QColor(238,238,238));
    painter.drawPath(downrect);
}

bool BackgroundStyle::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(watched == ui->back_Lab)
        {
            emit goBack();
            return true;
        }
        else if(watched == ui->all_Lab)
        {
            emit sendChangeAllBackgroundSianal();
            return true;
        };
   }
    return QWidget::eventFilter(watched,event);
}

void BackgroundStyle::changePage(QAbstractButton *button)
{
    if(group->id(button) ==1)ui->tabWidget->setCurrentWidget(ui->pure_Tab);
    else if(group->id(button) ==2)ui->tabWidget->setCurrentWidget(ui->subject_Tab);
    else if(group->id(button) ==3)ui->tabWidget->setCurrentWidget(ui->poetry_Tab);
    else if(group->id(button) ==4)ui->tabWidget->setCurrentWidget(ui->custom_Tab);
}

void BackgroundStyle::changeBackgroundPixmap(QAbstractButton *button)
{
   if(backgroundgroup->id(button) ==40)
   {
       if(custompixmappath.isEmpty())return;
   }
   emit backgroundChanged();
}
