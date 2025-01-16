
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

    std::vector<QPointF> pointContainer; // �洢�������

    MouseEventHandler* graphicsView;
    QGraphicsScene* scene;

    QTableView* tableView;               // ��ʾ����Ϣ�ı��
    QStandardItemModel* tableModel;      // ����ģ��

private slots:

    //���ñ༭ģʽ
    void on_actionEditStart_triggered();
    //ͣ�ñ༭ģʽ
    void on_actionEditStop_triggered();

    //����Ӳۺ���
    void onPointAdded(double x, double y); 

    //͹������ۺ���
    void on_actionCalculate_triggered();


public:
    void initializeCoordinateSystem(); //��ʼ������ϵ

    void initializeTableView(); //��ʼ�����

    void visualizeConvexHull(vector<QPointF>points); //͹�����ӻ�
};
