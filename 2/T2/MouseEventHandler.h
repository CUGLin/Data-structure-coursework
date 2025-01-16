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
    void pointAdded(double x, double y); // 信号：点添加后传递其坐标

protected:
    // 鼠标按下事件
    void mousePressEvent(QMouseEvent* event) override;

    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent* event) override;

    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QGraphicsScene* currentScene = nullptr; //场景指针
    bool editMode = false; //编辑模式，初始化为关闭状态
    std::vector<QPointF> points; //存储点的容器
};

