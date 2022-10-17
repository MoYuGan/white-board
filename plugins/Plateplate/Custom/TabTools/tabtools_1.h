#ifndef TABTOOLS_1_H
#define TABTOOLS_1_H

/*
*   页签工具: 白板主界面下方页签显示工具
*
*/

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QPainter>
#include <QLabel>
#include <QListWidget>
#include <QScroller>
#include <QButtonGroup>
#include "Custom/PushButton/custompushbutton_1.h"
#include "Public/publicfunction.h"
#include "Custom/PushButton/custompushbutton_2.h"

class TabTools_1 : public QWidget
{
    Q_OBJECT
public:
    explicit TabTools_1(QWidget *parent = nullptr);
    void resize();
    void insertItem(int index, const QPixmap &pixmap);
    void setItemChecked(int index);
    void changeItemPixmap(int index, const QPixmap &pixmap);
    inline int mGetTransparentBorder() { return m_TransparentBorder; }
    void addPage();
    void hidePageListWidget();

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    QHBoxLayout *m_Layout;
    CustomPushButton_1 *m_BtnAdd;
    CustomPushButton_1 *m_BtnLastPage;
    CustomPushButton_1 *m_BtnNextPage;
    CustomPushButton_1 *m_BtnShowPageList;
    QFrame *m_Frame;
    QVBoxLayout *m_vLayout;
    QLabel *m_LabelPageText;
    QFrame *m_PageListFrame;
    QListWidget *m_PageListWidget;
    QLabel *m_PageListLabelText;
    QList<CustomPushButton_2 *> m_ItemList;
    QButtonGroup *m_ItemGroup;
    //工具栏透明边距
    int m_TransparentBorder = 4;

private:
    void initWidget();

private slots:
    void onShowPageListBtnToggled(bool checked);
    void onAddBtnClicked();
    void onLastPageBtnClicked();
    void onNextPageBtnClicked();
    void onItemDelete();
    void onItemToggled(bool checked);

signals:
    void hasDelete(int);
    void currentItemChanged(int);
    void addPageClicked();
    void nextPageClicked();
    void lastPageClicked();
};

#endif // TABTOOLS_1_H
