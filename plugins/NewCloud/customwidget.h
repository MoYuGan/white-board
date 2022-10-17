#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <Public/public_function.h>
#include <QLineEdit>
#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QPushButton>
#include <QTimer>
#include <QLineEdit>
#include "custombtn.h"
#include <QTextEdit>
#include <QTableView>
#include <QtWebEngineWidgets/QWebEngineView>

/**************************************CustomWidget_3****************************************/
//自定义账号登录框中下拉框中listwidget的滑块样式
class CustomWidget_3 : public QListWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_3(QWidget *parent = nullptr);
    virtual ~CustomWidget_3() {}

};


/**************************************CustomWidget_4****************************************/
//自定义账号登录框中下拉框内部文字框，不带下划线
class CustomWidget_4 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_4(QString st,QWidget *parent = nullptr);
     virtual ~CustomWidget_4() {}

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString str;

};

/**************************************CustomWidget_5****************************************/
//自定义账号登录框中下拉框内部文字框，带下划线
class CustomWidget_5 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_5(QString st,QWidget *parent = nullptr);
     virtual ~CustomWidget_5() {}

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString str;

};

/**************************************CustomWidget_1****************************************/
//自定义账号登录框
class CustomWidget_1 : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget_1(QWidget *parent = nullptr);
    QString getEditText(); //获得编辑文本
    void setEditText(const QString &text);
    void setEditFocus();
//    QSqlDatabase* getQSql();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void setText(int );
signals:
   void getTelNumber(QListWidget* );

public slots:

private:
 QLabel *lab;
 QLabel *down_lab;
 QLabel *iphone1;
 QLabel *iphone2;
 QLabel *iphone3;
 QLabel *iphone4;
 QLabel *list_lab;
 CustomWidget_3 *listwidget;
 QSqlDatabase* database;
 QSqlQuery* sql_query;
 int num =4;

public:
 QLineEdit *edit;
};


/**************************************CustomWidget_2****************************************/
//自定义Lineedit账号和密码的输入框
class CustomWidget_2 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_2(QWidget *parent = nullptr);
     virtual ~CustomWidget_2() {}
     void changeText(QString ,QString ,int );
     QString getEditText(); //获得编辑文本
     void clearEditText();
     void setEditText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event);

private:
 QLabel *lab;
 int keystyle =0;

public:
 QLineEdit *edit;

};


/**************************************CustomWidget_6****************************************/
//自定义验证码输入框
class CustomWidget_6 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_6(QWidget *parent = nullptr);
     virtual ~CustomWidget_6() {}
     QString getEditText();     //获得编辑文本
     void enableBtn(bool );          //使能发送按钮
     void getPhoneNumber(QString );
     void getCode();
     void clearEditText();

signals:
     void sendPhoneCode(QString );
     void checkPhoneNumber();

protected:
    void paintEvent(QPaintEvent *event);


private:
 QLabel *lab;
 QPushButton *sendBtn;
 int countTim =61;

public:
 QLineEdit *edit;
 QString str;
};


/**************************************CustomWidget_7****************************************/
//自定义服务协议和隐私政策界面
class CustomWidget_7 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_7(int num,QWidget *parent = nullptr);
     virtual ~CustomWidget_7() {}

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void initLayout();

signals:
    void sendCloseMassage7();

private:
    QLabel *mcloseLab;
    QLabel *mtextLab;
    QPushButton *mBtn;
    QTextEdit *edit;
    int flage =0;
};


/**************************************CustomWidget_8****************************************/
//自定义带有圆角的tabwidget
class CustomWidget_8 : public QTabWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_8(QWidget *parent = nullptr);
     virtual ~CustomWidget_8() {}

protected:
    void paintEvent(QPaintEvent *event);

private:

};

/**************************************CustomWidget_9****************************************/
//自定义我的备课界面
class CustomWidget_9 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_9(QWidget *parent = nullptr);
     virtual ~CustomWidget_9() ;
     void initLayout();
     void webDownload(QWebEngineDownloadItem *item);
     void mydownloadFinished();
     void mydownloadProgress(qint64,qint64);
     void loadWeb(QString );
     void reLoad();

private:
    QWebEngineView *mwebView = nullptr;
};


/**************************************CustomWidget_10****************************************/
//自定义我的网盘界面
class CustomWidget_10 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_10(QWidget *parent = nullptr);
     virtual ~CustomWidget_10();
     void initLayout();
     void webDownload(QWebEngineDownloadItem *item);
     void mydownloadFinished();
     void mydownloadProgress(qint64,qint64);
     void loadWeb(QString );
     void reLoad();
private:
     QWebEngineView *mwebView = nullptr;
};

/**************************************CustomWidget_11****************************************/
//自定义我的网盘界面中的本地上传界面
class CustomWidget_11 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_11(QWidget *parent = nullptr);
     virtual ~CustomWidget_11() {}
     void initLayout();

protected:
    void paintEvent(QPaintEvent *event);
    QPainterPath drawProgressbar();
    QPainterPath drawProgressbar2(int length);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void sendCloseMassage11();

private:
        int length = 468;
        int number =0;
        QLabel *mcloseLab;
        QLabel *mpercentageLab;
        QLabel *mtetxLab;
        QPushButton *mcancelBtn;
};

/**************************************CustomWidget_12****************************************/
//自定义我的网盘界面中的链接添加界面
class CustomWidget_12 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_12(QWidget *parent = nullptr);
     virtual ~CustomWidget_12() {}
     void initLayout();

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void sendCloseMassage12();
    void sendAddMassage();

private:
        QLabel *miconLab;
        QLabel *mtetxLab;
        Custom_Btn3 *mbackBtn;
        QLineEdit *edit;
        QButtonGroup *group;

public:
        Custom_Btn3 *maddBtn;
};


/**************************************CustomWidget_13****************************************/
//自定义我的网盘界面中的链接添加成功界面
class CustomWidget_13 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_13(QWidget *parent = nullptr);
     virtual ~CustomWidget_13() {}
     void initLayout();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void sendCloseMassage13();

private:
        QLabel *mcloseLab;
        QLabel *miconLab;
        QLabel *mtetxLab;
        Custom_Btn3 *mbackBtn;
};

/**************************************CustomWidget_14****************************************/
//自定义我的网盘界面中的云分享分享界面
class CustomWidget_14 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_14(QWidget *parent = nullptr);
     virtual ~CustomWidget_14() {}
     void initLayout();
     void changeTextIcon(QString ,QPixmap );
protected:
    QPainterPath drawRoundRect_1(int r,int mheight);
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void sendCloseMassage14();

public:
    Custom_Btn3 *mbackBtn;
    Custom_Btn3 *mlinkBtn;

private:
        QLabel *mcloseLab;
        QLabel *mtitelLab;
        QLabel *mLab1;
        QLabel *mLab2;
        QLabel *mLab3;
        QLabel *miconLab;
        QLabel *mtetxLab;
        Custom_Btn5 *mvisitBtn;
        Custom_Btn6 *mtimeBtn;
        QButtonGroup *mgroup;
};

/**************************************CustomWidget_16****************************************/
//自定义我的网盘界面中的云分享链接分享界面中的短信发送成功界面
class CustomWidget_16 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_16(QWidget *parent = nullptr);
     virtual ~CustomWidget_16() {}
     void initLayout();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void sendCloseMassage16();

private:
        QLabel *miconLab;
        QLabel *mtitelLab;

};

/**************************************CustomWidget_15****************************************/
//自定义我的网盘界面中的云分享链接分享界面
class CustomWidget_15 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_15(QWidget *parent = nullptr);
     virtual ~CustomWidget_15() {}
     void initLayout();
     void changeTextIcon(QString ,QPixmap );

protected:
    QPainterPath drawRoundRect_1(int r,int mheight);
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void sendCloseMassage15();

private:
        QLabel *mcloseLab;
        QLabel *mtitelLab;
        QLabel *mLab1;
        QLabel *mLab2;
        QLabel *mLab3;
        QLabel *miconLab;
        QLabel *mtetxLab;
        Custom_Btn3 *mcloseBtn;
        Custom_Btn3 *mcopyBtn;
        QPushButton *msendBtn;
        QButtonGroup *mgroup;
        QTextEdit *mtextEdit;
        QLineEdit *mlineEdit;
};


/**************************************CustomWidget_17****************************************/
//自定义文件头标，文件名，时间，大小的文件窗口
class CustomWidget_17 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_17(int num ,QWidget *parent = nullptr);
     virtual ~CustomWidget_17() {}
     void initLayout();
     void setStyle(int num);
     void changePixAndTitel(QPixmap ,QString );
     void setLoadNum(int );
     void setTimeNum(QString );

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void getInstruct(QString );

signals:
    void sendMessage17();

private:
     QLabel *micon1Lab;
     QLabel *micon2Lab;
     QLabel *mtext1Lab;
     QLabel *mtext2Lab;
     QLabel *mtext3Lab;
     QLabel *mtext4Lab;
     int mnum =0;
};


/**************************************CustomWidget_18****************************************/
//自定义网盘中放置文件的窗口
class CustomWidget_18 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_18(QWidget *parent = nullptr);
     virtual ~CustomWidget_18() {}
     void initLayout();
     void setPageNum(int );
protected:
    void paintEvent(QPaintEvent *event);

signals:

private:
    int num =0;
    int pagenum =0;

public:
    QVector<CustomWidget_17*> listwi;
};


/**************************************CustomWidget_19****************************************/
//自定义我的网盘界面中的分享，下载，重命名，删除功能的窗口
class CustomWidget_19 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_19(QWidget *parent = nullptr);
     virtual ~CustomWidget_19() {}
     void initLayout();
     void initConnect();
     void changeLoadText(QString );
protected:
    void paintEvent(QPaintEvent *event);

signals:
    void sendMessage(QString st);

private:

public:
    QPushButton *shareBtn;
    QPushButton *loadBtn;
    QPushButton *renameBtn;
    QPushButton *deleteBtn;
};


/**************************************CustomWidget_20****************************************/
//自定义我的网盘界面中的云分享分享界面
class CustomWidget_20 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_20(QWidget *parent = nullptr);
     virtual ~CustomWidget_20() {}
     void initLayout();

protected:
    QPainterPath drawRoundRect_1(int r,int mheight);
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void sendCloseMassage20();
    void sendCheckOut();
public:
    Custom_Btn3 *mcancelBtn;
    Custom_Btn3 *mcheckoutBtn;

private:
        QLabel *mcloseLab;
        QLabel *mtitelLab;
        QLabel *mLab1;
        QLineEdit *medit;
        QButtonGroup *mgroup;
};



/**************************************CustomWidget_21****************************************/
//自定义消息提示框
class CustomWidget_21 :  public QWidget
{
public:
    explicit CustomWidget_21(QWidget *parent = nullptr);

    static CustomWidget_21 *getToolTip(int tooltipStyle = 0);

    void setToolTipStyle(int tooltipStyle);

    void showMBox(QPoint pt);

    void showMBox(QWidget *parent, const QString &text, QPoint pt);

    void setText(const QString &text);

    QString getText();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QLabel *m_pLabelText;
    QTimer *m_pTimer;
    QHBoxLayout *hLayout;
    QFrame *m_pFrame;
    int m_pToolTipStyle = 0;    //ToolTip的样式

private:
    void initWidget();
};


/**************************************CustomWidget_22****************************************/
//登录时界面的各种状态窗口
class CustomWidget_22 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_22(QWidget *parent = nullptr);
     virtual ~CustomWidget_22() {}

protected:
    void paintEvent(QPaintEvent *event);
    void initLayout();
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void sendStateMessage(int );
public:
    void changePixAndText(QPixmap pictrue,QString st1,QString st2,QString st3,int);

private:
    QLabel *pixLab;
    QLabel *text1Lab;
    QLabel *text2Lab;
    QLabel *text3Lab;
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    int flag =0;

};


/**************************************CustomWidget_23****************************************/
//登录时界面的各种状态窗口
class CustomWidget_23 : public QWidget
{
    Q_OBJECT
public:
     explicit CustomWidget_23(QWidget *parent = nullptr);
     virtual ~CustomWidget_23() {}

protected:
    void paintEvent(QPaintEvent *event);
    QPainterPath drawRoundRect(int r);
};


#endif // CUSTOMWIDGET_H
