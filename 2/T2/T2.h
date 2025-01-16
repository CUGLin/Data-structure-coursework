
#include <QtWidgets/QMainWindow>
#include "ui_T2.h"
#include "MouseEventHandler.h"
#include "Graham.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPolygonItem>
#include <QPointF>
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>`
#include <iostream>
#include <vector>
class T2 : public QMainWindow
{
    Q_OBJECT

public:
    T2(QWidget *parent = nullptr);
    ~T2();

private:
    Ui::T2Class ui;

    std::vector<QPointF> pointContainer; // 存储点的容器

    MouseEventHandler* graphicsView;
    QGraphicsScene* scene;

    QTableView* tableView;               // 显示点信息的表格
    QStandardItemModel* tableModel;      // 数据模型

private slots:

    //启用编辑模式
    void on_actionEditStart_triggered();
    //停用编辑模式
    void on_actionEditStop_triggered();

    //点添加槽函数
    void onPointAdded(double x, double y); 

    //凸包计算槽函数
    void on_actionCalculate_triggered();


public:
    void initializeCoordinateSystem(); //初始化坐标系

    void initializeTableView(); //初始化表格

    void visualizeConvexHull(vector<QPointF>points); //凸包可视化
};
