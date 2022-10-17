/********************************************************************************
** Form generated from reading UI file 'ocrwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCRWIDGET_H
#define UI_OCRWIDGET_H

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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OCRWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_title;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QFrame *frame_bottom;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    DB_CustomPushButton *pushButton_redoOCR;
    DB_CustomPushButton *pushButton_copySelect;
    DB_CustomPushButton *pushButton_copyAll;
    DB_CustomPushButton *pushButton_close;
    QFrame *frame;

    void setupUi(QWidget *OCRWidget)
    {
        if (OCRWidget->objectName().isEmpty())
            OCRWidget->setObjectName(QStringLiteral("OCRWidget"));
        OCRWidget->resize(949, 711);
        verticalLayoutWidget = new QWidget(OCRWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(250, 70, 441, 401));
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

        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setStyleSheet(QLatin1String("QTextEdit{\n"
"border: none;\n"
"border-top: 1px solid rgb(225, 225, 225);\n"
"border-bottom: 1px solid rgb(225, 225, 225);\n"
"}"));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_2);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("border: none;"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout_2->addWidget(label);

        verticalSpacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addLayout(verticalLayout_2);

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

        pushButton_redoOCR = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pushButton_redoOCR->setObjectName(QStringLiteral("pushButton_redoOCR"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_redoOCR->sizePolicy().hasHeightForWidth());
        pushButton_redoOCR->setSizePolicy(sizePolicy);
        pushButton_redoOCR->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"color: white;\n"
"background-color: rgb(78,  155,  252);\n"
"}"));

        horizontalLayout_2->addWidget(pushButton_redoOCR);

        pushButton_copySelect = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pushButton_copySelect->setObjectName(QStringLiteral("pushButton_copySelect"));
        sizePolicy.setHeightForWidth(pushButton_copySelect->sizePolicy().hasHeightForWidth());
        pushButton_copySelect->setSizePolicy(sizePolicy);
        pushButton_copySelect->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"color: white;\n"
"background-color: rgb(78,  155,  252);\n"
"}"));

        horizontalLayout_2->addWidget(pushButton_copySelect);

        pushButton_copyAll = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pushButton_copyAll->setObjectName(QStringLiteral("pushButton_copyAll"));
        sizePolicy.setHeightForWidth(pushButton_copyAll->sizePolicy().hasHeightForWidth());
        pushButton_copyAll->setSizePolicy(sizePolicy);
        pushButton_copyAll->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"color: white;\n"
"background-color: rgb(78,  155,  252);\n"
"}"));

        horizontalLayout_2->addWidget(pushButton_copyAll);

        pushButton_close = new DB_CustomPushButton(horizontalLayoutWidget_2);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        sizePolicy.setHeightForWidth(pushButton_close->sizePolicy().hasHeightForWidth());
        pushButton_close->setSizePolicy(sizePolicy);
        pushButton_close->setStyleSheet(QLatin1String("QPushButton{\n"
"border: none;\n"
"color: white;\n"
"background-color: rgb(78,  155,  252);\n"
"}"));

        horizontalLayout_2->addWidget(pushButton_close);


        verticalLayout->addWidget(frame_bottom);

        frame = new QFrame(OCRWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 70, 211, 411));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(OCRWidget);

        QMetaObject::connectSlotsByName(OCRWidget);
    } // setupUi

    void retranslateUi(QWidget *OCRWidget)
    {
        OCRWidget->setWindowTitle(QApplication::translate("OCRWidget", "Form", Q_NULLPTR));
        label_title->setText(QApplication::translate("OCRWidget", "QCR\346\226\207\345\255\227\350\257\206\345\210\253", Q_NULLPTR));
        label->setText(QString());
        pushButton_redoOCR->setText(QApplication::translate("OCRWidget", "\351\207\215\346\226\260\350\257\206\345\210\253", Q_NULLPTR));
        pushButton_copySelect->setText(QApplication::translate("OCRWidget", "\345\244\215\345\210\266\351\200\211\344\270\255", Q_NULLPTR));
        pushButton_copyAll->setText(QApplication::translate("OCRWidget", "\345\244\215\345\210\266\346\211\200\346\234\211", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("OCRWidget", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OCRWidget: public Ui_OCRWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCRWIDGET_H
