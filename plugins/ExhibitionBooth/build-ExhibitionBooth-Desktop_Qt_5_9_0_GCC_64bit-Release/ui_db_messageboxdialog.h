/********************************************************************************
** Form generated from reading UI file 'db_messageboxdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DB_MESSAGEBOXDIALOG_H
#define UI_DB_MESSAGEBOXDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DB_MessageBoxDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *frame_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_text;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_retry;
    QLabel *label_close;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DB_MessageBoxDialog)
    {
        if (DB_MessageBoxDialog->objectName().isEmpty())
            DB_MessageBoxDialog->setObjectName(QStringLiteral("DB_MessageBoxDialog"));
        DB_MessageBoxDialog->resize(400, 243);
        horizontalLayoutWidget = new QWidget(DB_MessageBoxDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 30, 352, 201));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(horizontalLayoutWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(350, 0));
        frame->setStyleSheet(QLatin1String("#frame{\n"
"border: 1px solid rgba(185, 185, 185, 185);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(frame);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 331, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 40));
        label->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("background-color: rgb(134, 189, 255);\n"
"color: white;"));

        verticalLayout->addWidget(label);

        frame_2 = new QFrame(verticalLayoutWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setStyleSheet(QLatin1String("#frame_2{\n"
"border: none;\n"
"background-color: white;\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_2 = new QWidget(frame_2);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 331, 161));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_text = new QLabel(verticalLayoutWidget_2);
        label_text->setObjectName(QStringLiteral("label_text"));
        label_text->setMinimumSize(QSize(0, 100));
        QFont font1;
        font1.setPointSize(14);
        label_text->setFont(font1);
        label_text->setStyleSheet(QLatin1String("color: gray;\n"
"\n"
""));
        label_text->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_text);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_retry = new QLabel(verticalLayoutWidget_2);
        label_retry->setObjectName(QStringLiteral("label_retry"));
        label_retry->setMinimumSize(QSize(80, 30));
        label_retry->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setPointSize(12);
        label_retry->setFont(font2);
        label_retry->setStyleSheet(QLatin1String("background-color: rgb(134, 189, 255);\n"
"color: white;"));
        label_retry->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_retry);

        label_close = new QLabel(verticalLayoutWidget_2);
        label_close->setObjectName(QStringLiteral("label_close"));
        label_close->setMinimumSize(QSize(80, 30));
        label_close->setMaximumSize(QSize(16777215, 30));
        label_close->setFont(font2);
        label_close->setStyleSheet(QLatin1String("background-color: rgb(134, 189, 255);\n"
"color: white;"));
        label_close->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_close);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayout_2->setStretch(0, 1);

        verticalLayout->addWidget(frame_2);


        horizontalLayout->addWidget(frame);


        retranslateUi(DB_MessageBoxDialog);

        QMetaObject::connectSlotsByName(DB_MessageBoxDialog);
    } // setupUi

    void retranslateUi(QDialog *DB_MessageBoxDialog)
    {
        DB_MessageBoxDialog->setWindowTitle(QApplication::translate("DB_MessageBoxDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DB_MessageBoxDialog", "\346\217\220\347\244\272", Q_NULLPTR));
        label_text->setText(QApplication::translate("DB_MessageBoxDialog", "\346\234\252\346\243\200\346\265\213\345\210\260\350\256\276\345\244\207\343\200\202", Q_NULLPTR));
        label_retry->setText(QApplication::translate("DB_MessageBoxDialog", "\351\207\215\350\257\225", Q_NULLPTR));
        label_close->setText(QApplication::translate("DB_MessageBoxDialog", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DB_MessageBoxDialog: public Ui_DB_MessageBoxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DB_MESSAGEBOXDIALOG_H
