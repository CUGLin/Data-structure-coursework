/********************************************************************************
** Form generated from reading UI file 'Question_5.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTION_5_H
#define UI_QUESTION_5_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Question_5Class
{
public:
    QAction *actionTxt;
    QAction *actionGeojson;
    QAction *actionIDW;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Question_5Class)
    {
        if (Question_5Class->objectName().isEmpty())
            Question_5Class->setObjectName(QString::fromUtf8("Question_5Class"));
        Question_5Class->resize(1077, 645);
        actionTxt = new QAction(Question_5Class);
        actionTxt->setObjectName(QString::fromUtf8("actionTxt"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Question_5/resource/TXT.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTxt->setIcon(icon);
        actionGeojson = new QAction(Question_5Class);
        actionGeojson->setObjectName(QString::fromUtf8("actionGeojson"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Question_5/resource/JSON.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGeojson->setIcon(icon1);
        actionIDW = new QAction(Question_5Class);
        actionIDW->setObjectName(QString::fromUtf8("actionIDW"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Question_5/resource/midware1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionIDW->setIcon(icon2);
        centralWidget = new QWidget(Question_5Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        Question_5Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Question_5Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1077, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        Question_5Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Question_5Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Question_5Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Question_5Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Question_5Class->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionTxt);
        menu->addAction(actionGeojson);
        menu_2->addAction(actionIDW);
        mainToolBar->addAction(actionTxt);
        mainToolBar->addAction(actionGeojson);
        mainToolBar->addAction(actionIDW);

        retranslateUi(Question_5Class);

        QMetaObject::connectSlotsByName(Question_5Class);
    } // setupUi

    void retranslateUi(QMainWindow *Question_5Class)
    {
        Question_5Class->setWindowTitle(QCoreApplication::translate("Question_5Class", "Question_5", nullptr));
        actionTxt->setText(QCoreApplication::translate("Question_5Class", "Txt", nullptr));
        actionGeojson->setText(QCoreApplication::translate("Question_5Class", "Geojson", nullptr));
        actionIDW->setText(QCoreApplication::translate("Question_5Class", "IDW", nullptr));
        menu->setTitle(QCoreApplication::translate("Question_5Class", "\345\257\274\345\205\245\346\225\260\346\215\256", nullptr));
        menu_2->setTitle(QCoreApplication::translate("Question_5Class", "\351\253\230\347\250\213\346\217\222\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Question_5Class: public Ui_Question_5Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTION_5_H
