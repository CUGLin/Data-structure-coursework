#include "T2.h"
#include <QFileDialog>
#include <QMessageBox>

T2::T2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // 创建 MouseEventHandler 实例
    graphicsView = new MouseEventHandler(this);
    //设置场景
    scene = new QGraphicsScene(-600, -600, 1200, 1200);
    graphicsView->setScene(scene);
    setCentralWidget(graphicsView);

    // 连接 MouseEventHandler 信号到表格更新槽
    connect(graphicsView, &MouseEventHandler::pointAdded, this, &T2::onPointAdded);


}

T2::~T2()
{}

void T2::initializeCoordinateSystem()
{
    // 添加X轴
    QGraphicsLineItem* xAxis = scene->addLine(QLineF(-600, 0, 600, 0));
    xAxis->setPen(QPen(Qt::black, 2));

    // 添加Y轴
    QGraphicsLineItem* yAxis = scene->addLine(QLineF(0, -600, 0, 600));
    yAxis->setPen(QPen(Qt::black, 2));

    // 添加X轴箭头
    QPolygonF xArrow;
    xArrow << QPointF(590, -10) << QPointF(600, 0) << QPointF(590, 10);
    QGraphicsPolygonItem* xArrowItem = scene->addPolygon(xArrow);
    xArrowItem->setBrush(Qt::black);

    // 添加Y轴箭头
    QPolygonF yArrow;
    yArrow << QPointF(-10, -590) << QPointF(0, -600) << QPointF(10, -590);
    QGraphicsPolygonItem* yArrowItem = scene->addPolygon(yArrow);
    yArrowItem->setBrush(Qt::black);

    // 添加X轴标签
    QGraphicsSimpleTextItem* xLabel = scene->addSimpleText("X");
    xLabel->setPos(610, 10);

    // 添加Y轴标签
    QGraphicsSimpleTextItem* yLabel = scene->addSimpleText("Y");
    yLabel->setPos(10, -610);
}

void T2::on_actionEditStart_triggered()
{
    graphicsView->setEditMode(true);
    statusBar()->showMessage(tr("编辑模式已启用"));
}

void T2::on_actionEditStop_triggered()
{
    graphicsView->setEditMode(false);
    statusBar()->showMessage(tr("编辑模式已停用"));
}

void T2::initializeTableView()
{
    // 创建 QTableView 和模型
    tableView = new QTableView(this);
    tableModel = new QStandardItemModel(0, 2, this); // 2 列：X 和 Y
    tableModel->setHeaderData(0, Qt::Horizontal, tr("X"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Y"));

    tableView->setModel(tableModel);
    tableView->setGeometry(10, 10, 300, 400); // 设置位置和大小
    ui.dockWidget->setWidget(tableView);
}

void T2::onPointAdded(double x, double y)
{
    // 在表格模型中添加点的坐标
    int row = tableModel->rowCount();
    tableModel->insertRow(row);
    tableModel->setData(tableModel->index(row, 0), x); // 设置 X 坐标
    tableModel->setData(tableModel->index(row, 1), y); // 设置 Y 坐标

    // 将点存储到容器中
    pointContainer.push_back(QPointF(x, y));

}

void T2::on_actionCalculate_triggered()
{
    Graham graham;
    vector<QPointF>hull = graham.computeConvexHull(pointContainer);
    /*for (const auto& it : hull)
    {
        qDebug() << it.x() << it.y();
    }*/
    visualizeConvexHull(hull);

}

void T2::visualizeConvexHull(vector<QPointF>points)
{
    // 将凸包点转换为QPolygonF
    QPolygonF convexHullPolygon;
    for (const auto& point : points)
    {
        // 反转 Y 坐标
        QPointF adjustedPoint(point.x(), -point.y());

        // 添加到多边形
        convexHullPolygon << adjustedPoint;
    }

    // 创建QGraphicsPolygonItem并将其添加到场景中
        QGraphicsPolygonItem * hullItem = new QGraphicsPolygonItem(convexHullPolygon);
    hullItem->setPen(QPen(Qt::blue, 2));  // 设置边框颜色和宽度

    // 设置低透明度填充
    QBrush brush(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 255, 50)); // 设置为蓝色，50 为透明度 (0-255)
    hullItem->setBrush(brush);

    scene->addItem(hullItem);
}

