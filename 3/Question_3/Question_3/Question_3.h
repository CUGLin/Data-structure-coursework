#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Question_3.h"
#include "DecisionTree.h"
#include <QGraphicsView>


class Question_3 : public QMainWindow
{
    Q_OBJECT

public:
    Question_3(QWidget *parent = nullptr);
    ~Question_3();
    QString getSelectedRadio(QGroupBox* groupBox);
private slots:
    void on_loadCsvButton_clicked();
    void on_analyzeButton_clicked();
    void updateAlgorithmType(); // 更新算法类型
private:
    Ui::Question_3Class ui;

    QGraphicsScene* scene;

    DecisionTree dt;
};
