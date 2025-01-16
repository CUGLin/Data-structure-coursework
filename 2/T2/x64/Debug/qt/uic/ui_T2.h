/********************************************************************************
** Form generated from reading UI file 'T2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_T2_H
#define UI_T2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MouseEventHandler.h"

QT_BEGIN_NAMESPACE

class Ui_T2Class
{
public:
    QAction *actionEditStart;
    QAction *actionEditStop;
    QAction *actionCalculate;
    QAction *actionTxt;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    MouseEventHandler *graphicsView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;

    void setupUi(QMainWindow *T2Class)
    {
        if (T2Class->objectName().isEmpty())
            T2Class->setObjectName(QString::fromUtf8("T2Class"));
        T2Class->resize(970, 600);
        actionEditStart = new QAction(T2Class);
        actionEditStart->setObjectName(QString::fromUtf8("actionEditStart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/T2/resource/\345\274\200\345\247\213\347\274\226\350\276\221.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditStart->setIcon(icon);
        actionEditStop = new QAction(T2Class);
        actionEditStop->setObjectName(QString::fromUtf8("actionEditStop"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/T2/resource/\347\273\223\346\235\237\347\274\226\350\276\221.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditStop->setIcon(icon1);
        actionCalculate = new QAction(T2Class);
        actionCalculate->setObjectName(QString::fromUtf8("actionCalculate"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/T2/resource/\345\207\270\345\214\205.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCalculate->setIcon(icon2);
        actionTxt = new QAction(T2Class);
        actionTxt->setObjectName(QString::fromUtf8("actionTxt"));
        centralWidget = new QWidget(T2Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new MouseEventHandler(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        T2Class->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(T2Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        T2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(T2Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        T2Class->setStatusBar(statusBar);
        dockWidget = new QDockWidget(T2Class);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(dockWidgetContents);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        dockWidget->setWidget(dockWidgetContents);
        T2Class->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        mainToolBar->addAction(actionEditStart);
        mainToolBar->addAction(actionEditStop);
        mainToolBar->addAction(actionCalculate);

        retranslateUi(T2Class);

        QMetaObject::connectSlotsByName(T2Class);
    } // setupUi

    void retranslateUi(QMainWindow *T2Class)
    {
        T2Class->setWindowTitle(QCoreApplication::translate("T2Class", "T2", nullptr));
        actionEditStart->setText(QCoreApplication::translate("T2Class", "\345\274\200\345\247\213\347\274\226\350\276\221", nullptr));
        actionEditStop->setText(QCoreApplication::translate("T2Class", "\347\273\223\346\235\237\347\274\226\350\276\221", nullptr));
        actionCalculate->setText(QCoreApplication::translate("T2Class", "\350\256\241\347\256\227\345\207\270\345\214\205", nullptr));
        actionTxt->setText(QCoreApplication::translate("T2Class", "\346\267\273\345\212\240\346\225\260\346\215\256", nullptr));
#if QT_CONFIG(tooltip)
        actionTxt->setToolTip(QCoreApplication::translate("T2Class", "\346\267\273\345\212\240\346\225\260\346\215\256", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class T2Class: public Ui_T2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_T2_H
