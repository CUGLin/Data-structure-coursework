/********************************************************************************
** Form generated from reading UI file 'Question_3.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTION_3_H
#define UI_QUESTION_3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Question_3Class
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_9;
    QPushButton *analyzeButton;
    QSpacerItem *verticalSpacer_6;
    QPushButton *loadCsvButton;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_1;
    QVBoxLayout *verticalLayout_10;
    QRadioButton *radioButton_0;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QLabel *resultLabel;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *radioButton_10;
    QRadioButton *radioButton_11;

    void setupUi(QMainWindow *Question_3Class)
    {
        if (Question_3Class->objectName().isEmpty())
            Question_3Class->setObjectName(QString::fromUtf8("Question_3Class"));
        Question_3Class->resize(1102, 772);
        Question_3Class->setStyleSheet(QString::fromUtf8("font: 10pt \"Times New Roman\";"));
        centralWidget = new QWidget(Question_3Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        Question_3Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Question_3Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1102, 20));
        Question_3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Question_3Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Question_3Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Question_3Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Question_3Class->setStatusBar(statusBar);
        dockWidget_3 = new QDockWidget(Question_3Class);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        gridLayout_2 = new QGridLayout(dockWidgetContents_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_4 = new QGroupBox(dockWidgetContents_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        groupBox_4->setFont(font);
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        radioButton_8 = new QRadioButton(groupBox_4);
        radioButton_8->setObjectName(QString::fromUtf8("radioButton_8"));

        verticalLayout_4->addWidget(radioButton_8);

        radioButton_9 = new QRadioButton(groupBox_4);
        radioButton_9->setObjectName(QString::fromUtf8("radioButton_9"));

        verticalLayout_4->addWidget(radioButton_9);


        gridLayout_2->addWidget(groupBox_4, 8, 0, 1, 1);

        analyzeButton = new QPushButton(dockWidgetContents_3);
        analyzeButton->setObjectName(QString::fromUtf8("analyzeButton"));
        analyzeButton->setFont(font);

        gridLayout_2->addWidget(analyzeButton, 10, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 36, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 7, 0, 1, 1);

        loadCsvButton = new QPushButton(dockWidgetContents_3);
        loadCsvButton->setObjectName(QString::fromUtf8("loadCsvButton"));
        loadCsvButton->setFont(font);

        gridLayout_2->addWidget(loadCsvButton, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(dockWidgetContents_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font);
        verticalLayout_9 = new QVBoxLayout(groupBox_3);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        radioButton_6 = new QRadioButton(groupBox_3);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));

        verticalLayout_9->addWidget(radioButton_6);

        radioButton_7 = new QRadioButton(groupBox_3);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));

        verticalLayout_9->addWidget(radioButton_7);


        gridLayout_2->addWidget(groupBox_3, 6, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 36, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 3, 0, 1, 1);

        groupBox_1 = new QGroupBox(dockWidgetContents_3);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        groupBox_1->setFont(font);
        verticalLayout_10 = new QVBoxLayout(groupBox_1);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        radioButton_0 = new QRadioButton(groupBox_1);
        radioButton_0->setObjectName(QString::fromUtf8("radioButton_0"));
        radioButton_0->setTabletTracking(false);

        verticalLayout_10->addWidget(radioButton_0);

        radioButton_1 = new QRadioButton(groupBox_1);
        radioButton_1->setObjectName(QString::fromUtf8("radioButton_1"));

        verticalLayout_10->addWidget(radioButton_1);

        radioButton_2 = new QRadioButton(groupBox_1);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_10->addWidget(radioButton_2);


        gridLayout_2->addWidget(groupBox_1, 2, 0, 1, 1);

        resultLabel = new QLabel(dockWidgetContents_3);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setFont(font);

        gridLayout_2->addWidget(resultLabel, 11, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 5, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 36, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 9, 0, 1, 1);

        groupBox_2 = new QGroupBox(dockWidgetContents_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_3->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout_3->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));

        verticalLayout_3->addWidget(radioButton_5);


        gridLayout_2->addWidget(groupBox_2, 4, 0, 1, 1);

        groupBox_5 = new QGroupBox(dockWidgetContents_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFont(font);
        verticalLayout_11 = new QVBoxLayout(groupBox_5);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        radioButton_10 = new QRadioButton(groupBox_5);
        radioButton_10->setObjectName(QString::fromUtf8("radioButton_10"));
        radioButton_10->setTabletTracking(false);

        verticalLayout_11->addWidget(radioButton_10);

        radioButton_11 = new QRadioButton(groupBox_5);
        radioButton_11->setObjectName(QString::fromUtf8("radioButton_11"));

        verticalLayout_11->addWidget(radioButton_11);


        gridLayout_2->addWidget(groupBox_5, 0, 0, 1, 1);

        dockWidget_3->setWidget(dockWidgetContents_3);
        Question_3Class->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_3);

        retranslateUi(Question_3Class);

        QMetaObject::connectSlotsByName(Question_3Class);
    } // setupUi

    void retranslateUi(QMainWindow *Question_3Class)
    {
        Question_3Class->setWindowTitle(QCoreApplication::translate("Question_3Class", "Question_3", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("Question_3Class", "\351\243\216\345\212\233(Wind)", nullptr));
        radioButton_8->setText(QCoreApplication::translate("Question_3Class", "Weak", nullptr));
        radioButton_9->setText(QCoreApplication::translate("Question_3Class", "Strong", nullptr));
        analyzeButton->setText(QCoreApplication::translate("Question_3Class", "\345\210\206\346\236\220\347\273\223\346\236\234", nullptr));
        loadCsvButton->setText(QCoreApplication::translate("Question_3Class", "\351\200\211\346\213\251CSV\346\226\207\344\273\266", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Question_3Class", "\346\271\277\345\272\246(Humidity)", nullptr));
        radioButton_6->setText(QCoreApplication::translate("Question_3Class", "Normal", nullptr));
        radioButton_7->setText(QCoreApplication::translate("Question_3Class", "High", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("Question_3Class", "\345\244\251\346\260\224(Weather)", nullptr));
        radioButton_0->setText(QCoreApplication::translate("Question_3Class", "Overcast", nullptr));
        radioButton_1->setText(QCoreApplication::translate("Question_3Class", "Sunny", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Question_3Class", "Rain", nullptr));
        resultLabel->setText(QCoreApplication::translate("Question_3Class", "\350\276\223\345\207\272\347\273\223\346\236\234", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Question_3Class", "\346\270\251\345\272\246(Temperature)", nullptr));
        radioButton_3->setText(QCoreApplication::translate("Question_3Class", "Mild", nullptr));
        radioButton_4->setText(QCoreApplication::translate("Question_3Class", "Hot", nullptr));
        radioButton_5->setText(QCoreApplication::translate("Question_3Class", "Cool", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("Question_3Class", "\347\256\227\346\263\225\351\200\211\346\213\251", nullptr));
        radioButton_10->setText(QCoreApplication::translate("Question_3Class", "ID3", nullptr));
        radioButton_11->setText(QCoreApplication::translate("Question_3Class", "C45", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Question_3Class: public Ui_Question_3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTION_3_H
