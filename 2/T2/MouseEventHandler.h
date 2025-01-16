#pragma once
#include "D:\Qt\5.15.2\msvc2019_64\include\QtWidgets\qgraphicsview.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMainWindow>
#include <QStatusBar>
#include <QGraphicsEllipseItem>

#include <vector>

class MouseEventHandler :
    public QGraphicsView
{
    Q_OBJECT

public:
    explicit MouseEventHandler(QWidget* parent = nullptr);
    void setScene(QGraphicsScene* scene);
    void setEditMode(bool isEditing);

signals:
    void pointAdded(double x, double y); // �źţ�����Ӻ󴫵�������

protected:
    // ��갴���¼�
    void mousePressEvent(QMouseEvent* event) override;

    // ����ƶ��¼�
    void mouseMoveEvent(QMouseEvent* event) override;

    // ����ͷ��¼�
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QGraphicsScene* currentScene = nullptr; //����ָ��
    bool editMode = false; //�༭ģʽ����ʼ��Ϊ�ر�״̬
    std::vector<QPointF> points; //�洢�������
};

