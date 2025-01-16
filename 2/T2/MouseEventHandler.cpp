#include "MouseEventHandler.h"
#include <QDebug>

MouseEventHandler::MouseEventHandler(QWidget* parent)
    : QGraphicsView(parent)
{
    setMouseTracking(true);  // 启用鼠标追踪
}

void MouseEventHandler::mousePressEvent(QMouseEvent* event) {
    // 仅在编辑模式下处理鼠标点击
    if (editMode && currentScene)
    {
        // 将视图坐标转换为场景坐标
        QPointF scenePos = mapToScene(event->pos());

        // 在场景中添加一个点
        qreal radius = 5.0; // 点的半径
        QGraphicsEllipseItem* pointItem = currentScene->addEllipse(
            scenePos.x() - radius, scenePos.y() - radius,
            radius * 2, radius * 2,
            QPen(Qt::black), QBrush(Qt::red)); // 黑色边框，红色填充

         // 创建并显示点号
        int pointIndex = points.size() + 1;  // 点号是点的索引
        QString pointText = QString::number(pointIndex);
        QGraphicsTextItem* textItem = currentScene->addText(pointText);
        textItem->setPos(scenePos.x() + 2, scenePos.y() + 2); // 调整文本位置，稍微偏离点

         // 将点添加到容器中
        points.push_back(scenePos);

        // 发送信号更新表格
        emit pointAdded(scenePos.x(), -scenePos.y());
    }
    QGraphicsView::mousePressEvent(event); // 继续处理其他鼠标事件
}

void MouseEventHandler::mouseMoveEvent(QMouseEvent* event) {
    // 获取鼠标在视图中的位置
    QPointF viewPos = event->pos();

    // 将视图坐标转换为场景坐标
    QPointF scenePos = mapToScene(viewPos.toPoint());

    // 反转 Y 坐标
    qreal flippedY = -scenePos.y();  // Y 坐标反转

    // 显示场景坐标
    QString coordText = QString("X: %1, Y: %2").arg(scenePos.x()).arg(flippedY);

    // 更新状态栏显示（假设 MainWindow 使用 statusBar()）
    QMainWindow* mainWindow = qobject_cast<QMainWindow*>(parentWidget());
    if (mainWindow) {
        mainWindow->statusBar()->showMessage(coordText);
    }
}

void MouseEventHandler::mouseReleaseEvent(QMouseEvent* event) {
    QPointF scenePos = mapToScene(event->pos());
    /*qDebug() << "Mouse Released at: " << scenePos;*/
}

void MouseEventHandler::setScene(QGraphicsScene* scene)
{
    currentScene = scene;
    QGraphicsView::setScene(scene);
}

void MouseEventHandler::setEditMode(bool isEditing)
{
    editMode = isEditing;
}