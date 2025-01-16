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
    void mouseClicked(QPointF pt);  //����������¼�
signals:
    void mouseMoved(QPointF pt);

protected:
    void mousePressEvent(QMouseEvent* event) override;  //������갴���¼�
    void mouseMoveEvent(QMouseEvent* event) override;  //��������ƶ��¼�
};



class CampusNavigation : public QMainWindow
{
    Q_OBJECT

public slots:
    void mouseClicked(QPointF pt);                 // ������¼�����
    void mouseMoved(QPointF pt);                   // ����ƶ��¼�����
    void on_actionOpenFile_triggered();            // ���ļ�����
    void on_actionSaveFile_triggered();            // �����ļ�����
    void on_actionAddVertex_triggered();           // ��Ӷ������
    void on_actionAddEdge_triggered();             // ��ӱ߲���
    void on_actionZoomIn_triggered();              // ������ͼ - �Ŵ�
    void on_actionZoomOut_triggered();             // ������ͼ - ��С
    void on_actionCalculatePaths_triggered();      // �������·������

public:
    CampusNavigation(QWidget *parent = nullptr);
    ~CampusNavigation();
    // ��ͼ��ط���
    bool DrawGraph(GraphAdjList* graph);         // ����ͼ
    // ���ƶ���
    bool DrawVertex(const Vertexf* vertex, float size, QPen pen = QPen(Qt::red, 3.0), QBrush brush = QBrush(Qt::red)); // �����������Ϊ3.0
    // ���ƶ������ӵı�
    bool DrawVertexLinkEdges(const Vertexf* vertex, GraphAdjList* graph, QPen pen = QPen(Qt::gray, 1.0)); // �����������Ϊ1.0

protected:
    // ����¼�������
    void mousePressEventAddVertex(QPointF pt);  // ��Ӷ���
    void mousePressEventAddEdge(QPointF pt);    // ��ӱ�
    void mousePressEventCalculatePaths(QPointF pt); // �������·��
    QGraphicsEllipseItem* getEllipseItemFromScenePt(QPointF pt); // �ӳ��������ȡ����ͼ����

private:
    Ui::CampusNavigationClass* ui;
    CampusNavigationView* mpView;              // �Զ�����ͼ��
    QGraphicsScene* mpScene;                   // ͼ�γ���
    CampusNavigationThread* mCampusNavigationThread; // �����̶߳���
    QRectF mSceneRect;                         // �����߽����
    float maxWidth = 0;                        // ���������
    State mState = State::None;                // ��ǰ����״̬
    vector<QPointF> mvScenePoints;             // �����㼯��
    QGraphicsPathItem* mpPathItem = nullptr;   // ·��ͼ����ָ��
};
