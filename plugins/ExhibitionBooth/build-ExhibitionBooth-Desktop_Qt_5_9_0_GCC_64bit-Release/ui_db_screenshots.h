/********************************************************************************
** Form generated from reading UI file 'db_screenshots.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DB_SCREENSHOTS_H
#define UI_DB_SCREENSHOTS_H

#include <CustomWidget/db_custompushbutton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DB_ScreenShots
{
public:
    QFrame *frame;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    DB_CustomPushButton *pSave;
    QSpacerItem *horizontalSpacer_5;
    DB_CustomPushButton *pClose;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *DB_ScreenShots)
    {
        if (DB_ScreenShots->objectName().isEmpty())
            DB_ScreenShots->setObjectName(QStringLiteral("DB_ScreenShots"));
        DB_ScreenShots->resize(828, 554);
        frame = new QFrame(DB_ScreenShots);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(199, 410, 151, 80));
        frame->setStyleSheet(QLatin1String("#frame{\n"
"border: none;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_2 = new QWidget(frame);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(-10, 10, 121, 61));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pSave = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pSave->setObjectName(QStringLiteral("pSave"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pSave->sizePolicy().hasHeightForWidth());
        pSave->setSizePolicy(sizePolicy);
        pSave->setStyleSheet(QStringLiteral("border-image: url(\":/images/baocun.png\");"));

        horizontalLayout_2->addWidget(pSave);

        horizontalSpacer_5 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pClose = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pClose->setObjectName(QStringLiteral("pClose"));
        sizePolicy.setHeightForWidth(pClose->sizePolicy().hasHeightForWidth());
        pClose->setSizePolicy(sizePolicy);
        pClose->setStyleSheet(QStringLiteral("border-image: url(\":/images/guanbi3.png\");"));

        horizontalLayout_2->addWidget(pClose);

        horizontalSpacer_4 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        retranslateUi(DB_ScreenShots);

        QMetaObject::connectSlotsByName(DB_ScreenShots);
    } // setupUi

    void retranslateUi(QWidget *DB_ScreenShots)
    {
        DB_ScreenShots->setWindowTitle(QApplication::translate("DB_ScreenShots", "Form", Q_NULLPTR));
        pSave->setText(QString());
        pClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DB_ScreenShots: public Ui_DB_ScreenShots {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DB_SCREENSHOTS_H
