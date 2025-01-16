#include "T2.h"
#include <QFileDialog>
#include <QMessageBox>

T2::T2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // ���� MouseEventHandler ʵ��
    graphicsView = new MouseEventHandler(this);
    //���ó���
    scene = new QGraphicsScene(-600, -600, 1200, 1200);
    graphicsView->setScene(scene);
    setCentralWidget(graphicsView);

    // ���� MouseEventHandler �źŵ������²�
    connect(graphicsView, &MouseEventHandler::pointAdded, this, &T2::onPointAdded);


}

T2::~T2()
{}

void T2::initializeCoordinateSystem()
{
    // ���X��
    QGraphicsLineItem* xAxis = scene->addLine(QLineF(-600, 0, 600, 0));
    xAxis->setPen(QPen(Qt::black, 2));

    // ���Y��
    QGraphicsLineItem* yAxis = scene->addLine(QLineF(0, -600, 0, 600));
    yAxis->setPen(QPen(Qt::black, 2));

    // ���X���ͷ
    QPolygonF xArrow;
    xArrow << QPointF(590, -10) << QPointF(600, 0) << QPointF(590, 10);
    QGraphicsPolygonItem* xArrowItem = scene->addPolygon(xArrow);
    xArrowItem->setBrush(Qt::black);

    // ���Y���ͷ
    QPolygonF yArrow;
    yArrow << QPointF(-10, -590) << QPointF(0, -600) << QPointF(10, -590);
    QGraphicsPolygonItem* yArrowItem = scene->addPolygon(yArrow);
    yArrowItem->setBrush(Qt::black);

    // ���X���ǩ
    QGraphicsSimpleTextItem* xLabel = scene->addSimpleText("X");
    xLabel->setPos(610, 10);

    // ���Y���ǩ
    QGraphicsSimpleTextItem* yLabel = scene->addSimpleText("Y");
    yLabel->setPos(10, -610);
}

void T2::on_actionEditStart_triggered()
{
    graphicsView->setEditMode(true);
    statusBar()->showMessage(tr("�༭ģʽ������"));
}

void T2::on_actionEditStop_triggered()
{
    graphicsView->setEditMode(false);
    statusBar()->showMessage(tr("�༭ģʽ��ͣ��"));
}

void T2::initializeTableView()
{
    // ���� QTableView ��ģ��
    tableView = new QTableView(this);
    tableModel = new QStandardItemModel(0, 2, this); // 2 �У�X �� Y
    tableModel->setHeaderData(0, Qt::Horizontal, tr("X"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Y"));

    tableView->setModel(tableModel);
    tableView->setGeometry(10, 10, 300, 400); // ����λ�úʹ�С
    ui.dockWidget->setWidget(tableView);
}

void T2::onPointAdded(double x, double y)
{
    // �ڱ��ģ������ӵ������
    int row = tableModel->rowCount();
    tableModel->insertRow(row);
    tableModel->setData(tableModel->index(row, 0), x); // ���� X ����
    tableModel->setData(tableModel->index(row, 1), y); // ���� Y ����

    // ����洢��������
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
    // ��͹����ת��ΪQPolygonF
    QPolygonF convexHullPolygon;
    for (const auto& point : points)
    {
        // ��ת Y ����
        QPointF adjustedPoint(point.x(), -point.y());

        // ��ӵ������
        convexHullPolygon << adjustedPoint;
    }

    // ����QGraphicsPolygonItem��������ӵ�������
        QGraphicsPolygonItem * hullItem = new QGraphicsPolygonItem(convexHullPolygon);
    hullItem->setPen(QPen(Qt::blue, 2));  // ���ñ߿���ɫ�Ϳ��

    // ���õ�͸�������
    QBrush brush(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 255, 50)); // ����Ϊ��ɫ��50 Ϊ͸���� (0-255)
    hullItem->setBrush(brush);

    scene->addItem(hullItem);
}

