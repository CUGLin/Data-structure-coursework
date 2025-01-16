#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_CampusNavigation.h"
#include"ui_AddVertexDialog.h"

#include"CampusNavigationThread.h"
#include"AddVertexDialog.h"

#include<qevent.h>
#include<qfiledialog.h>
#include<qmessagebox.h>
#include<qinputdialog.h>
#include<qgraphicsitem.h>
#include<qgraphicsview.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CampusNavigationClass; class AddVertexDialog; };
QT_END_NAMESPACE

Q_DECLARE_METATYPE(VertexData)




class CampusNavigationView:public QGraphicsView
{
    Q_OBJECT
public:

    CampusNavigationView();
    ~CampusNavigationView();

signals:
    void mouseClicked(QPointF pt);  //定义鼠标点击事件
signals:
    void mouseMoved(QPointF pt);

protected:
    void mousePressEvent(QMouseEvent* event) override;  //定义鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event) override;  //定义鼠标移动事件
};



class CampusNavigation : public QMainWindow
{
    Q_OBJECT

public slots:
    void mouseClicked(QPointF pt);                 // 鼠标点击事件处理
    void mouseMoved(QPointF pt);                   // 鼠标移动事件处理
    void on_actionOpenFile_triggered();            // 打开文件操作
    void on_actionSaveFile_triggered();            // 保存文件操作
    void on_actionAddVertex_triggered();           // 添加顶点操作
    void on_actionAddEdge_triggered();             // 添加边操作
    void on_actionZoomIn_triggered();              // 缩放视图 - 放大
    void on_actionZoomOut_triggered();             // 缩放视图 - 缩小
    void on_actionCalculatePaths_triggered();      // 计算最短路径操作

public:
    CampusNavigation(QWidget *parent = nullptr);
    ~CampusNavigation();
    // 绘图相关方法
    bool DrawGraph(GraphAdjList* graph);         // 绘制图
    // 绘制顶点
    bool DrawVertex(const Vertexf* vertex, float size, QPen pen = QPen(Qt::red, 3.0), QBrush brush = QBrush(Qt::red)); // 设置线条宽度为3.0
    // 绘制顶点连接的边
    bool DrawVertexLinkEdges(const Vertexf* vertex, GraphAdjList* graph, QPen pen = QPen(Qt::gray, 1.0)); // 设置线条宽度为1.0

protected:
    // 鼠标事件处理方法
    void mousePressEventAddVertex(QPointF pt);  // 添加顶点
    void mousePressEventAddEdge(QPointF pt);    // 添加边
    void mousePressEventCalculatePaths(QPointF pt); // 计算最短路径
    QGraphicsEllipseItem* getEllipseItemFromScenePt(QPointF pt); // 从场景坐标获取顶点图形项

private:
    Ui::CampusNavigationClass* ui;
    CampusNavigationView* mpView;              // 自定义视图类
    QGraphicsScene* mpScene;                   // 图形场景
    CampusNavigationThread* mCampusNavigationThread; // 导航线程对象
    QRectF mSceneRect;                         // 场景边界矩形
    float maxWidth = 0;                        // 场景最大宽度
    State mState = State::None;                // 当前操作状态
    vector<QPointF> mvScenePoints;             // 场景点集合
    QGraphicsPathItem* mpPathItem = nullptr;   // 路径图形项指针
};
