#include "MouseEventHandler.h"
#include <QDebug>

MouseEventHandler::MouseEventHandler(QWidget* parent)
    : QGraphicsView(parent)
{
    setMouseTracking(true);  // �������׷��
}

void MouseEventHandler::mousePressEvent(QMouseEvent* event) {
    // ���ڱ༭ģʽ�´��������
    if (editMode && currentScene)
    {
        // ����ͼ����ת��Ϊ��������
        QPointF scenePos = mapToScene(event->pos());

        // �ڳ��������һ����
        qreal radius = 5.0; // ��İ뾶
        QGraphicsEllipseItem* pointItem = currentScene->addEllipse(
            scenePos.x() - radius, scenePos.y() - radius,
            radius * 2, radius * 2,
            QPen(Qt::black), QBrush(Qt::red)); // ��ɫ�߿򣬺�ɫ���

         // ��������ʾ���
        int pointIndex = points.size() + 1;  // ����ǵ������
        QString pointText = QString::number(pointIndex);
        QGraphicsTextItem* textItem = currentScene->addText(pointText);
        textItem->setPos(scenePos.x() + 2, scenePos.y() + 2); // �����ı�λ�ã���΢ƫ���

         // ������ӵ�������
        points.push_back(scenePos);

        // �����źŸ��±��
        emit pointAdded(scenePos.x(), -scenePos.y());
    }
    QGraphicsView::mousePressEvent(event); // ����������������¼�
}

void MouseEventHandler::mouseMoveEvent(QMouseEvent* event) {
    // ��ȡ�������ͼ�е�λ��
    QPointF viewPos = event->pos();

    // ����ͼ����ת��Ϊ��������
    QPointF scenePos = mapToScene(viewPos.toPoint());

    // ��ת Y ����
    qreal flippedY = -scenePos.y();  // Y ���귴ת

    // ��ʾ��������
    QString coordText = QString("X: %1, Y: %2").arg(scenePos.x()).arg(flippedY);

    // ����״̬����ʾ������ MainWindow ʹ�� statusBar()��
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