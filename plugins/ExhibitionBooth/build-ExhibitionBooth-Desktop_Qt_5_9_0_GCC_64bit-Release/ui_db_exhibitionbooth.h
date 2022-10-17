/********************************************************************************
** Form generated from reading UI file 'db_exhibitionbooth.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DB_EXHIBITIONBOOTH_H
#define UI_DB_EXHIBITIONBOOTH_H

#include <CustomWidget/db_custompushbutton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <displaywidget.h>

QT_BEGIN_NAMESPACE

class Ui_DB_ExhibitionBooth
{
public:
    QWidget *verticalLayoutWidget_9;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_left;
    QSpacerItem *horizontalSpacer_67;
    QFrame *frame_mid;
    QSpacerItem *horizontalSpacer_65;
    QFrame *frame_right;
    QWidget *widget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    DisplayWidget *widget_5;
    DisplayWidget *widget_3;
    DisplayWidget *widget_6;
    DisplayWidget *widget_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_1;
    DB_CustomPushButton_2 *pMenu;
    DB_CustomPushButton_2 *pMinimize;
    DB_CustomPushButton_2 *pReforeLeft;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    DB_CustomPushButton_2 *pReforeRight;
    DB_CustomPushButton_2 *pOneScreen;
    DB_CustomPushButton_2 *pTwoScreen;
    DB_CustomPushButton_2 *pFourScreen;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    DB_CustomPushButton_2 *pCursor;
    DB_CustomPushButton_2 *pPen;
    DB_CustomPushButton_2 *pEraser;
    DB_CustomPushButton_2 *pUndo;
    DB_CustomPushButton_2 *pRedo;
    DB_CustomPushButton_2 *pZoomIn;
    DB_CustomPushButton_2 *pZoomOut;
    DB_CustomPushButton_2 *pRotate;
    DB_CustomPushButton_2 *pOCR;
    DB_CustomPushButton_2 *pTakingPicture;
    QLabel *label_cover;

    void setupUi(QWidget *DB_ExhibitionBooth)
    {
        if (DB_ExhibitionBooth->objectName().isEmpty())
            DB_ExhibitionBooth->setObjectName(QStringLiteral("DB_ExhibitionBooth"));
        DB_ExhibitionBooth->resize(1097, 709);
        verticalLayoutWidget_9 = new QWidget(DB_ExhibitionBooth);
        verticalLayoutWidget_9->setObjectName(QStringLiteral("verticalLayoutWidget_9"));
        verticalLayoutWidget_9->setGeometry(QRect(10, 20, 765, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_9);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame_left = new QFrame(verticalLayoutWidget_9);
        frame_left->setObjectName(QStringLiteral("frame_left"));
        frame_left->setMinimumSize(QSize(100, 0));
        frame_left->setStyleSheet(QLatin1String("#frame_left{\n"
"border: none;\n"
"background: rgb(230, 230, 230);\n"
"}"));
        frame_left->setFrameShape(QFrame::StyledPanel);
        frame_left->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_left);

        horizontalSpacer_67 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_67);

        frame_mid = new QFrame(verticalLayoutWidget_9);
        frame_mid->setObjectName(QStringLiteral("frame_mid"));
        frame_mid->setMinimumSize(QSize(300, 0));
        frame_mid->setStyleSheet(QLatin1String("#frame_mid{\n"
"border: none;\n"
"background: rgb(230, 230, 230);\n"
"}"));
        frame_mid->setFrameShape(QFrame::StyledPanel);
        frame_mid->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_mid);

        horizontalSpacer_65 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_65);

        frame_right = new QFrame(verticalLayoutWidget_9);
        frame_right->setObjectName(QStringLiteral("frame_right"));
        frame_right->setMinimumSize(QSize(100, 0));
        frame_right->setStyleSheet(QLatin1String("#frame_right{\n"
"border: none;\n"
"background: rgb(230, 230, 230);\n"
"}"));
        frame_right->setFrameShape(QFrame::StyledPanel);
        frame_right->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_right);


        verticalLayout->addLayout(horizontalLayout);

        widget = new QWidget(DB_ExhibitionBooth);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 330, 451, 291));
        gridLayoutWidget = new QWidget(widget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 411, 261));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget_5 = new DisplayWidget(gridLayoutWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));

        gridLayout->addWidget(widget_5, 0, 0, 1, 1);

        widget_3 = new DisplayWidget(gridLayoutWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        gridLayout->addWidget(widget_3, 1, 0, 1, 1);

        widget_6 = new DisplayWidget(gridLayoutWidget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(widget_6, 0, 1, 1, 1);

        widget_4 = new DisplayWidget(gridLayoutWidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(widget_4, 1, 1, 1, 1);

        layoutWidget = new QWidget(DB_ExhibitionBooth);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 270, 107, 25));
        horizontalLayout_1 = new QHBoxLayout(layoutWidget);
        horizontalLayout_1->setSpacing(0);
        horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
        pMenu = new DB_CustomPushButton_2(layoutWidget);
        pMenu->setObjectName(QStringLiteral("pMenu"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pMenu->sizePolicy().hasHeightForWidth());
        pMenu->setSizePolicy(sizePolicy);
        pMenu->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}\n"
"\n"
"QPushButton::menu-indicator{\n"
"	image:	 none;\n"
"}"));

        horizontalLayout_1->addWidget(pMenu);

        pMinimize = new DB_CustomPushButton_2(layoutWidget);
        pMinimize->setObjectName(QStringLiteral("pMinimize"));
        sizePolicy.setHeightForWidth(pMinimize->sizePolicy().hasHeightForWidth());
        pMinimize->setSizePolicy(sizePolicy);
        pMinimize->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_1->addWidget(pMinimize);

        pReforeLeft = new DB_CustomPushButton_2(layoutWidget);
        pReforeLeft->setObjectName(QStringLiteral("pReforeLeft"));
        sizePolicy.setHeightForWidth(pReforeLeft->sizePolicy().hasHeightForWidth());
        pReforeLeft->setSizePolicy(sizePolicy);
        pReforeLeft->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_1->addWidget(pReforeLeft);

        layoutWidget1 = new QWidget(DB_ExhibitionBooth);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(670, 270, 142, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pReforeRight = new DB_CustomPushButton_2(layoutWidget1);
        pReforeRight->setObjectName(QStringLiteral("pReforeRight"));
        sizePolicy.setHeightForWidth(pReforeRight->sizePolicy().hasHeightForWidth());
        pReforeRight->setSizePolicy(sizePolicy);
        pReforeRight->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_3->addWidget(pReforeRight);

        pOneScreen = new DB_CustomPushButton_2(layoutWidget1);
        pOneScreen->setObjectName(QStringLiteral("pOneScreen"));
        sizePolicy.setHeightForWidth(pOneScreen->sizePolicy().hasHeightForWidth());
        pOneScreen->setSizePolicy(sizePolicy);
        pOneScreen->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}\n"
"\n"
"QPushButton::checked{\n"
"background-color: rgb(78,  155,  252);\n"
"}"));
        pOneScreen->setCheckable(true);
        pOneScreen->setChecked(false);

        horizontalLayout_3->addWidget(pOneScreen);

        pTwoScreen = new DB_CustomPushButton_2(layoutWidget1);
        pTwoScreen->setObjectName(QStringLiteral("pTwoScreen"));
        sizePolicy.setHeightForWidth(pTwoScreen->sizePolicy().hasHeightForWidth());
        pTwoScreen->setSizePolicy(sizePolicy);
        pTwoScreen->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background:transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}\n"
"\n"
"QPushButton::checked{\n"
"background-color: rgb(78,  155,  252);\n"
"}"));
        pTwoScreen->setCheckable(true);

        horizontalLayout_3->addWidget(pTwoScreen);

        pFourScreen = new DB_CustomPushButton_2(layoutWidget1);
        pFourScreen->setObjectName(QStringLiteral("pFourScreen"));
        sizePolicy.setHeightForWidth(pFourScreen->sizePolicy().hasHeightForWidth());
        pFourScreen->setSizePolicy(sizePolicy);
        pFourScreen->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}\n"
"\n"
"QPushButton::checked{\n"
"background-color: rgb(78,  155,  252);\n"
"}"));
        pFourScreen->setCheckable(true);

        horizontalLayout_3->addWidget(pFourScreen);

        layoutWidget2 = new QWidget(DB_ExhibitionBooth);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(210, 270, 352, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pCursor = new DB_CustomPushButton_2(layoutWidget2);
        pCursor->setObjectName(QStringLiteral("pCursor"));
        sizePolicy.setHeightForWidth(pCursor->sizePolicy().hasHeightForWidth());
        pCursor->setSizePolicy(sizePolicy);
        pCursor->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}\n"
"\n"
"QPushButton::checked{\n"
"background: rgb(78,  155,  252);\n"
"}\n"
""));
        pCursor->setCheckable(true);

        horizontalLayout_2->addWidget(pCursor);

        pPen = new DB_CustomPushButton_2(layoutWidget2);
        pPen->setObjectName(QStringLiteral("pPen"));
        sizePolicy.setHeightForWidth(pPen->sizePolicy().hasHeightForWidth());
        pPen->setSizePolicy(sizePolicy);
        pPen->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}\n"
"\n"
"QPushButton::checked{\n"
"background: rgb(78,  155,  252);\n"
"}"));
        pPen->setCheckable(true);

        horizontalLayout_2->addWidget(pPen);

        pEraser = new DB_CustomPushButton_2(layoutWidget2);
        pEraser->setObjectName(QStringLiteral("pEraser"));
        sizePolicy.setHeightForWidth(pEraser->sizePolicy().hasHeightForWidth());
        pEraser->setSizePolicy(sizePolicy);
        pEraser->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}\n"
"\n"
"QPushButton::checked{\n"
"background: rgb(78,  155,  252);\n"
"}"));
        pEraser->setCheckable(true);

        horizontalLayout_2->addWidget(pEraser);

        pUndo = new DB_CustomPushButton_2(layoutWidget2);
        pUndo->setObjectName(QStringLiteral("pUndo"));
        sizePolicy.setHeightForWidth(pUndo->sizePolicy().hasHeightForWidth());
        pUndo->setSizePolicy(sizePolicy);
        pUndo->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_2->addWidget(pUndo);

        pRedo = new DB_CustomPushButton_2(layoutWidget2);
        pRedo->setObjectName(QStringLiteral("pRedo"));
        sizePolicy.setHeightForWidth(pRedo->sizePolicy().hasHeightForWidth());
        pRedo->setSizePolicy(sizePolicy);
        pRedo->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_2->addWidget(pRedo);

        pZoomIn = new DB_CustomPushButton_2(layoutWidget2);
        pZoomIn->setObjectName(QStringLiteral("pZoomIn"));
        sizePolicy.setHeightForWidth(pZoomIn->sizePolicy().hasHeightForWidth());
        pZoomIn->setSizePolicy(sizePolicy);
        pZoomIn->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_2->addWidget(pZoomIn);

        pZoomOut = new DB_CustomPushButton_2(layoutWidget2);
        pZoomOut->setObjectName(QStringLiteral("pZoomOut"));
        sizePolicy.setHeightForWidth(pZoomOut->sizePolicy().hasHeightForWidth());
        pZoomOut->setSizePolicy(sizePolicy);
        pZoomOut->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_2->addWidget(pZoomOut);

        pRotate = new DB_CustomPushButton_2(layoutWidget2);
        pRotate->setObjectName(QStringLiteral("pRotate"));
        sizePolicy.setHeightForWidth(pRotate->sizePolicy().hasHeightForWidth());
        pRotate->setSizePolicy(sizePolicy);
        pRotate->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_2->addWidget(pRotate);

        pOCR = new DB_CustomPushButton_2(layoutWidget2);
        pOCR->setObjectName(QStringLiteral("pOCR"));
        sizePolicy.setHeightForWidth(pOCR->sizePolicy().hasHeightForWidth());
        pOCR->setSizePolicy(sizePolicy);
        pOCR->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_2->addWidget(pOCR);

        pTakingPicture = new DB_CustomPushButton_2(layoutWidget2);
        pTakingPicture->setObjectName(QStringLiteral("pTakingPicture"));
        sizePolicy.setHeightForWidth(pTakingPicture->sizePolicy().hasHeightForWidth());
        pTakingPicture->setSizePolicy(sizePolicy);
        pTakingPicture->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"background: transparent;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background: rgb(216,216,216);\n"
"}"));

        horizontalLayout_2->addWidget(pTakingPicture);

        label_cover = new QLabel(DB_ExhibitionBooth);
        label_cover->setObjectName(QStringLiteral("label_cover"));
        label_cover->setGeometry(QRect(710, 360, 161, 101));
        label_cover->setStyleSheet(QLatin1String("QLabel{\n"
"background: rgb(135, 135, 135, 135);\n"
"color: white;\n"
"}"));
        label_cover->setAlignment(Qt::AlignCenter);

        retranslateUi(DB_ExhibitionBooth);

        QMetaObject::connectSlotsByName(DB_ExhibitionBooth);
    } // setupUi

    void retranslateUi(QWidget *DB_ExhibitionBooth)
    {
        DB_ExhibitionBooth->setWindowTitle(QApplication::translate("DB_ExhibitionBooth", "Form", Q_NULLPTR));
        pMenu->setText(QString());
        pMinimize->setText(QString());
        pReforeLeft->setText(QString());
        pReforeRight->setText(QString());
        pOneScreen->setText(QString());
        pTwoScreen->setText(QString());
        pFourScreen->setText(QString());
        pCursor->setText(QString());
        pPen->setText(QString());
        pEraser->setText(QString());
        pUndo->setText(QString());
        pRedo->setText(QString());
        pZoomIn->setText(QString());
        pZoomOut->setText(QString());
        pRotate->setText(QString());
        pOCR->setText(QString());
        pTakingPicture->setText(QString());
        label_cover->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DB_ExhibitionBooth: public Ui_DB_ExhibitionBooth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DB_EXHIBITIONBOOTH_H
