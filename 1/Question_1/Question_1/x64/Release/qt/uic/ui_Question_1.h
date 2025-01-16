/********************************************************************************
** Form generated from reading UI file 'Question_1.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTION_1_H
#define UI_QUESTION_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Question_1Class
{
public:
    QWidget *centralWidget;
    QPushButton *SelectFile;
    QPushButton *ShowFile;
    QGraphicsView *graphicsView;
    QPushButton *LoadFile;
    QLineEdit *FileLine;
    QLineEdit *TextFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Question_1Class)
    {
        if (Question_1Class->objectName().isEmpty())
            Question_1Class->setObjectName(QStringLiteral("Question_1Class"));
        Question_1Class->resize(754, 478);
        Question_1Class->setStyleSheet(QStringLiteral("font: 9pt \"Times New Roman\";"));
        centralWidget = new QWidget(Question_1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SelectFile = new QPushButton(centralWidget);
        SelectFile->setObjectName(QStringLiteral("SelectFile"));
        SelectFile->setGeometry(QRect(10, 360, 80, 21));
        ShowFile = new QPushButton(centralWidget);
        ShowFile->setObjectName(QStringLiteral("ShowFile"));
        ShowFile->setGeometry(QRect(10, 390, 80, 21));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 731, 291));
        LoadFile = new QPushButton(centralWidget);
        LoadFile->setObjectName(QStringLiteral("LoadFile"));
        LoadFile->setGeometry(QRect(10, 330, 80, 21));
        FileLine = new QLineEdit(centralWidget);
        FileLine->setObjectName(QStringLiteral("FileLine"));
        FileLine->setGeometry(QRect(100, 330, 641, 22));
        TextFile = new QLineEdit(centralWidget);
        TextFile->setObjectName(QStringLiteral("TextFile"));
        TextFile->setGeometry(QRect(100, 360, 641, 22));
        Question_1Class->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Question_1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Question_1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Question_1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Question_1Class->setStatusBar(statusBar);

        retranslateUi(Question_1Class);

        QMetaObject::connectSlotsByName(Question_1Class);
    } // setupUi

    void retranslateUi(QMainWindow *Question_1Class)
    {
        Question_1Class->setWindowTitle(QApplication::translate("Question_1Class", "Question_1", nullptr));
        SelectFile->setText(QApplication::translate("Question_1Class", "\347\235\200\350\211\262\345\210\244\346\226\255", nullptr));
        ShowFile->setText(QApplication::translate("Question_1Class", "\345\261\225\347\244\272\347\273\223\346\236\234", nullptr));
        LoadFile->setText(QApplication::translate("Question_1Class", "\345\212\240\350\275\275\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Question_1Class: public Ui_Question_1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTION_1_H
