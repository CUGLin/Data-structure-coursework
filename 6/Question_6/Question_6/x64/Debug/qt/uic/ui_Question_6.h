/********************************************************************************
** Form generated from reading UI file 'Question_6.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTION_6_H
#define UI_QUESTION_6_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Question_6Class
{
public:
    QWidget *centralWidget;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_5;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QSpinBox *spinBox_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *srandBtn;
    QPushButton *GetTinBtn;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *SearchBtn;
    QPushButton *CleanBtn;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Question_6Class)
    {
        if (Question_6Class->objectName().isEmpty())
            Question_6Class->setObjectName(QString::fromUtf8("Question_6Class"));
        Question_6Class->resize(1369, 773);
        Question_6Class->setStyleSheet(QString::fromUtf8("font: 10pt \"Times New Roman\";"));
        centralWidget = new QWidget(Question_6Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget_4 = new QWidget(centralWidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(980, 0, 316, 711));
        widget_4->setBaseSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(widget_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        groupBox->setFont(font);
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_5 = new QWidget(groupBox);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        formLayout_2 = new QFormLayout(widget_5);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        spinBox_2 = new QSpinBox(widget_5);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setFont(font);
        spinBox_2->setMaximum(6000);
        spinBox_2->setValue(550);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinBox_2);


        verticalLayout_4->addWidget(widget_5);

        widget_6 = new QWidget(groupBox);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        srandBtn = new QPushButton(widget_6);
        srandBtn->setObjectName(QString::fromUtf8("srandBtn"));
        srandBtn->setFont(font);

        horizontalLayout_4->addWidget(srandBtn);

        GetTinBtn = new QPushButton(widget_6);
        GetTinBtn->setObjectName(QString::fromUtf8("GetTinBtn"));
        GetTinBtn->setFont(font);

        horizontalLayout_4->addWidget(GetTinBtn);


        verticalLayout_4->addWidget(widget_6);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        formLayout = new QFormLayout(widget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setFont(font);
        spinBox->setMaximum(6000);
        spinBox->setValue(25);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBox);


        verticalLayout_2->addWidget(widget);

        widget_3 = new QWidget(groupBox_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        SearchBtn = new QPushButton(widget_3);
        SearchBtn->setObjectName(QString::fromUtf8("SearchBtn"));
        SearchBtn->setFont(font);

        horizontalLayout_3->addWidget(SearchBtn);

        CleanBtn = new QPushButton(widget_3);
        CleanBtn->setObjectName(QString::fromUtf8("CleanBtn"));
        CleanBtn->setFont(font);

        horizontalLayout_3->addWidget(CleanBtn);


        verticalLayout_2->addWidget(widget_3);

        widget_2 = new QWidget(groupBox_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        textEdit = new QTextEdit(widget_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setBaseSize(QSize(0, 12));

        verticalLayout->addWidget(textEdit);


        verticalLayout_2->addWidget(widget_2);


        verticalLayout_3->addWidget(groupBox_2);

        Question_6Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Question_6Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1369, 20));
        Question_6Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Question_6Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Question_6Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Question_6Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Question_6Class->setStatusBar(statusBar);

        retranslateUi(Question_6Class);

        QMetaObject::connectSlotsByName(Question_6Class);
    } // setupUi

    void retranslateUi(QMainWindow *Question_6Class)
    {
        Question_6Class->setWindowTitle(QCoreApplication::translate("Question_6Class", "Question_6", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Question_6Class", "\346\236\204\345\273\272", nullptr));
        label_3->setText(QCoreApplication::translate("Question_6Class", "\351\232\217\346\234\272\347\202\271\346\225\260\351\207\217", nullptr));
        srandBtn->setText(QCoreApplication::translate("Question_6Class", "\347\224\237\346\210\220\347\202\271", nullptr));
        GetTinBtn->setText(QCoreApplication::translate("Question_6Class", "\346\236\204\345\273\272TIN", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Question_6Class", "\346\237\245\350\257\242", nullptr));
        label->setText(QCoreApplication::translate("Question_6Class", "\347\202\271      \345\217\267", nullptr));
        SearchBtn->setText(QCoreApplication::translate("Question_6Class", "\346\237\245\350\257\242", nullptr));
        CleanBtn->setText(QCoreApplication::translate("Question_6Class", "\346\270\205\351\231\244\346\237\245\350\257\242", nullptr));
        label_2->setText(QCoreApplication::translate("Question_6Class", "\346\236\204\346\210\220\344\270\211\350\247\222\345\275\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Question_6Class: public Ui_Question_6Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTION_6_H
