/********************************************************************************
** Form generated from reading UI file 'takingphotowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAKINGPHOTOWIDGET_H
#define UI_TAKINGPHOTOWIDGET_H

#include <CustomWidget/db_custompushbutton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TakingPhotoWidget
{
public:
    QFrame *frame;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_title;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *frame_bottom;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    DB_CustomPushButton *pSave;
    QSpacerItem *horizontalSpacer_2;
    DB_CustomPushButton *pClose;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *TakingPhotoWidget)
    {
        if (TakingPhotoWidget->objectName().isEmpty())
            TakingPhotoWidget->setObjectName(QStringLiteral("TakingPhotoWidget"));
        TakingPhotoWidget->resize(751, 569);
        frame = new QFrame(TakingPhotoWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 30, 211, 411));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(TakingPhotoWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(250, 30, 441, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_title = new QLabel(verticalLayoutWidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setStyleSheet(QLatin1String("QLabel{\n"
"border: none;\n"
"color: white;\n"
"background-color: rgb(78,  155,  252);\n"
"}"));

        verticalLayout->addWidget(label_title);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("border: none;"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        horizontalLayout->addWidget(label);


        verticalLayout->addLayout(horizontalLayout);

        frame_bottom = new QFrame(verticalLayoutWidget);
        frame_bottom->setObjectName(QStringLiteral("frame_bottom"));
        frame_bottom->setMinimumSize(QSize(0, 50));
        frame_bottom->setStyleSheet(QLatin1String("#frame_bottom{\n"
"border: none;\n"
"}"));
        frame_bottom->setFrameShape(QFrame::StyledPanel);
        frame_bottom->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_2 = new QWidget(frame_bottom);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 10, 439, 25));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pSave = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pSave->setObjectName(QStringLiteral("pSave"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pSave->sizePolicy().hasHeightForWidth());
        pSave->setSizePolicy(sizePolicy);
        pSave->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"color: white;\n"
"background-color: rgb(78,  155,  252);\n"
"}"));

        horizontalLayout_2->addWidget(pSave);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pClose = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pClose->setObjectName(QStringLiteral("pClose"));
        sizePolicy.setHeightForWidth(pClose->sizePolicy().hasHeightForWidth());
        pClose->setSizePolicy(sizePolicy);
        pClose->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"color: white;\n"
"background-color: rgb(78,  155,  252);\n"
"}"));

        horizontalLayout_2->addWidget(pClose);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(frame_bottom);

        verticalLayout->setStretch(1, 1);

        retranslateUi(TakingPhotoWidget);

        QMetaObject::connectSlotsByName(TakingPhotoWidget);
    } // setupUi

    void retranslateUi(QWidget *TakingPhotoWidget)
    {
        TakingPhotoWidget->setWindowTitle(QApplication::translate("TakingPhotoWidget", "Form", Q_NULLPTR));
        label_title->setText(QApplication::translate("TakingPhotoWidget", "\346\213\215\347\205\247\345\256\214\346\210\220", Q_NULLPTR));
        label->setText(QString());
        pSave->setText(QApplication::translate("TakingPhotoWidget", "\345\217\246\345\255\230\344\270\272", Q_NULLPTR));
        pClose->setText(QApplication::translate("TakingPhotoWidget", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TakingPhotoWidget: public Ui_TakingPhotoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAKINGPHOTOWIDGET_H
