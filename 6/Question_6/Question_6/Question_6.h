#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Question_6.h"
#include "BuildTIN.h"
#include <QPainter>
#include <ctime>


class Question_6 : public QMainWindow
{
    Q_OBJECT

public:
    Question_6(QWidget *parent = nullptr);
    ~Question_6();

    virtual void paintEvent(QPaintEvent*);//绘图事件
public slots:
    void GetPoint();//加载点
    void srandPoint();//生成点
    void GetTin();//获取TIN
    void GetTrangleByPoint();//根据点号查询三角形
    void CleanTrangle();//删除查询

private:
    Ui::Question_6Class ui;
    int PointNum = 0;//点数
    int TrangleNum = 0;//三角形数量
    vector<int> trangleList;//选中三角形数量
    vector<int> pointlist;//选中三角形的点集
    BuildTIN* buildtin = nullptr;
};
