
#include "Question_5.h"
#include <QGraphicsEllipseItem>
#include <QMessageBox>


Question_5::Question_5(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    scene = new QGraphicsScene;
    ui.graphicsView->setScene(scene);
    //ui.graphicsView->setScene(scene);
    connect(ui.actionTxt, &QAction::triggered, this, &Question_5::on_actionTxt_triggered);
    connect(ui.actionGeojson, &QAction::triggered, this, &Question_5::on_actionGeojson_triggered);
    connect(ui.actionIDW, &QAction::triggered, this, &Question_5::on_actionIDW_triggered);
}

Question_5::~Question_5()
{}

// ����Txt���ݲ������ֵ
void Question_5::on_actionTxt_triggered()
{
    // ���ļ��Ի���ѡ��txt�ļ�
    QString filePath = QFileDialog::getOpenFileName(this, "���ı��ļ�", "", "Text Files (*.txt)");
    if (filePath.isEmpty())
    {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "�޷����ļ�";
        return;
    }

    QTextStream in(&file);

    // ��ȡ��������Ͳ�ֵ�����ٽ���ĸ���
    int n, m;
    in >> n >> m;

    // ���ڴ洢������������ֵ
    QVector<QPointF> points;
    QVector<double> attributes;

    // ��ȡÿ��������������ֵ
    for (int i = 0; i < n; ++i) {
        double x, y, attr;
        in >> x >> y >> attr;
        points.append(QPointF(x, y));
        attributes.append(attr);
        qDebug() << attr;
    }

    // ������Ե�ĺ�������
    double testX, testY;
    bool okX, okY;
    testX = QInputDialog::getDouble(this, "������Ե�X����", "X����:", 0.0, -1e6, 1e6, 2, &okX);
    testY = QInputDialog::getDouble(this, "������Ե�Y����", "Y����:", 0.0, -1e6, 1e6, 2, &okY);

    if (!okX || !okY) {
        return; // �û�ȡ��������
    }

    // ����IDW��ֵ����
    IDW idw(points, attributes, m);

    // ���в�ֵ����
    QPointF testPoint(testX, testY);
    double interpolatedValue = idw.interpolate(testPoint);

    // �����ֵ���
    QMessageBox::information(this, "��ֵ���", QString("��ֵ������ (%1, %2) �Ĳ�ֵ���Ϊ: %3")
        .arg(testX).arg(testY).arg(interpolatedValue));

    // ������еĳ���
    scene->clear();

    // ��ӵ㵽���е�scene
    for (int i = 0; i < points.size(); ++i) {
        // ��ÿ������������СԲ�α�ʾ�� (���磬����Ϊ 2x2)
        QGraphicsEllipseItem* pointItem = new QGraphicsEllipseItem(points[i].x() - 1, points[i].y() - 1, 2, 2);  // СԲ��
        pointItem->setBrush(QBrush(Qt::blue));  // ��ɫ��ʾ���ݵ�
        scene->addItem(pointItem);
    }

    // ��ѡ���ڲ��Ե�λ����ӱ��
    QGraphicsEllipseItem* testPointItem = new QGraphicsEllipseItem(testPoint.x() - 2, testPoint.y() - 2, 4, 4);  // СԲ�α��
    testPointItem->setBrush(QBrush(Qt::red));  // ��ɫ��ʾ���Ե�
    scene->addItem(testPointItem);

    // ��ѡ����ʾ��ֵ�����λ�ã�����ʹ���ı���������ʽ��
    QGraphicsTextItem* textItem = new QGraphicsTextItem(QString("��ֵ���: %1").arg(interpolatedValue));
    QFont font = textItem->font();
    font.setPointSize(2);  // ���������СΪ��Сֵ
    textItem->setFont(font);
    textItem->setPos(testPoint.x()-10, testPoint.y()+10);
    scene->addItem(textItem);

    // ���ó����߽粢������ͼ����Ӧ
    qreal minX = 0, minY = 0;
    qreal maxX = 0, maxY = 0;
    for (int i = 0; i < points.size(); ++i) {
        minX = qMin(minX, points[i].x());
        minY = qMin(minY, points[i].y());
        maxX = qMax(maxX, points[i].x());
        maxY = qMax(maxY, points[i].y());
    }

    // ����һЩ�߾�
    minX -= 10;
    minY -= 10;
    maxX += 10;
    maxY += 10;

    // ���ó����ı߽�
    scene->setSceneRect(minX, minY, maxX - minX, maxY - minY);

    // �Զ�������ͼ���ţ�����Ӧ���е�
    ui.graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}





void Question_5::on_actionGeojson_triggered()
{
    // ���ļ��Ի���ѡ��GeoJSON�ļ�
    QString filePath = QFileDialog::getOpenFileName(this, "��GeoJSON�ļ�", "", "GeoJSON Files (*.geojson *.json)");
    if (filePath.isEmpty())
    {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "�޷����ļ�";
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);

    if (!doc.isObject()) {
        QMessageBox::warning(this, "�ļ���ʽ����", "�޷�����GeoJSON�ļ����ļ���ʽ����ȷ��");
        return;
    }

    QJsonObject jsonObject = doc.object();
    QJsonArray features = jsonObject["features"].toArray();

    // ������г���
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 600); // ����һ��Ĭ�ϵĳ����ߴ�
    ui.graphicsView->resize(800, 600); // ������ͼ�ߴ��볡��ƥ��

    QVector<QPointF> points;   // ���ڴ洢������
    QVector<QVector<QPointF>> lines; // ���ڴ洢�ߵ�����
    QVector<double> attributes; // ���ڴ洢ÿ���������ֵ����ELEV��

    // ����ͼ�������ʽ
    QPen pointPen(Qt::blue);  // �����ɫ
    QBrush pointBrush(Qt::blue);  // ��������ɫ
    QPen linePen(Qt::green);   // �ߵ���ɫ
    linePen.setWidth(3);  // ���������Ŀ�ȣ�Ĭ�Ͽ����1��3�Ǹ��ֵ�����

    // ���㾭γ�ȷ�Χ
    double minLon = std::numeric_limits<double>::max();
    double maxLon = std::numeric_limits<double>::lowest();
    double minLat = std::numeric_limits<double>::max();
    double maxLat = std::numeric_limits<double>::lowest();

    // ����GeoJSON�о�γ�ȷ�Χ
    for (const QJsonValue& featureValue : features) {
        QJsonObject feature = featureValue.toObject();
        QJsonObject geometry = feature["geometry"].toObject();
        QString type = geometry["type"].toString();

        if (type == "LineString") {
            QJsonArray coordinates = geometry["coordinates"].toArray();
            for (const QJsonValue& coordValue : coordinates) {
                QJsonArray coord = coordValue.toArray();
                double lon = coord[0].toDouble();
                double lat = coord[1].toDouble();

                minLon = std::min(minLon, lon);
                maxLon = std::max(maxLon, lon);
                minLat = std::min(minLat, lat);
                maxLat = std::max(maxLat, lat);
            }
        }
    }

    // ��ȡ��ͼ�Ŀ�Ⱥ͸߶�
    int viewWidth = ui.graphicsView->width();
    int viewHeight = ui.graphicsView->height();

    // ���㾭γ�ȵ����ص���������
    double scaleX = viewWidth / (maxLon - minLon);  // ������������
    double scaleY = viewHeight / (maxLat - minLat); // γ����������

    // ����ÿ��Feature
    for (const QJsonValue& featureValue : features) {
        QJsonObject feature = featureValue.toObject();
        QJsonObject geometry = feature["geometry"].toObject();
        QString type = geometry["type"].toString();

        // �����LineString����
        if (type == "LineString") {
            QJsonArray coordinates = geometry["coordinates"].toArray();
            QVector<QPointF> line;
            double elev = feature["properties"].toObject()["ELEV"].toDouble();  // ��ȡ���߶ε�ELEVֵ

            for (const QJsonValue& coordValue : coordinates) {
                QJsonArray coord = coordValue.toArray();
                double lon = coord[0].toDouble();
                double lat = coord[1].toDouble();

                // ����γ��ת��Ϊ��ͼ����ϵ����������
                double pixelX = (lon - minLon) * scaleX;
                double pixelY = (maxLat - lat) * scaleY; // ע��γ�������ת������

                line.append(QPointF(pixelX, pixelY));  // �洢�߶εĵ�����
                points.append(QPointF(pixelX, pixelY));  // �洢���е�
                attributes.append(elev);  // ÿ����ĸ߳�����ͬ�ģ����Ե�ǰ�߶ε�ELEVֵ
            }
            lines.append(line);  // �洢������

            // ʹ�� QPainterPath ��������
            QPainterPath path;
            if (!line.isEmpty()) {
                path.moveTo(line[0]);  // �ƶ�����һ����
                for (int i = 1; i < line.size(); ++i) {
                    path.lineTo(line[i]);  // ����ֱ�߶�
                }
            }

            // �ڳ����������
            QGraphicsPathItem* lineItem = new QGraphicsPathItem(path);
            lineItem->setPen(linePen);  // ���ø��ֵ�����
            scene->addItem(lineItem);
        }
    }

    // ȷ���е�����
    if (points.isEmpty()) {
        QMessageBox::warning(this, "���ݴ���", "GeoJSON��û����Ч�ĵ�����");
        return;
    }

    // ���³����ı߽粢������ͼ
    scene->setSceneRect(scene->itemsBoundingRect());
    ui.graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui.graphicsView->show();

    // �洢ȫ������
    points_ = points;
    attributes_ = attributes;
    lines_ = lines;

    minLon_ = minLon;
    maxLon_ = maxLon;
    minLat_ = minLat;
    maxLat_ = maxLat;
    scaleX_ = scaleX;
    scaleY_ = scaleY;

    // ���������Ϣ
    qDebug() << "points_:" << points_ << "attributes_:" << attributes_;
    qDebug() << minLon << maxLon << minLat << maxLat << scaleX << scaleY;
}




void Question_5::on_actionIDW_triggered()
{

    qDebug() << minLon_ << maxLon_ << minLat_ << maxLat_ << scaleX_ << scaleY_;

    // ��ȡ�û������Ŀ��㾭γ��
    bool ok;
    double targetLon = QInputDialog::getDouble(this, "����Ŀ���", "������Ŀ���ľ���:", 102.6, -180.0, 180.0, 6, &ok);
    if (!ok) {
        return;  // ����û�ȡ�������룬���˳�
    }

    double targetLat = QInputDialog::getDouble(this, "����Ŀ���", "������Ŀ����γ��:", 23.1, -90.0, 90.0, 6, &ok);
    if (!ok) {
        return;  // ����û�ȡ�������룬���˳�
    }

    // ����GeoJSON�����еľ�γ�ȷ�Χ��������ת��
    // ��Ŀ�꾭γ��ת��Ϊ��ͼ����ϵ����������
    double targetPixelX = (targetLon - minLon_) * scaleX_;
    double targetPixelY = (maxLat_ - targetLat) * scaleY_;  // ע��γ�������ת������

    // ȷ���е�����
    if (points_.isEmpty()) {
        QMessageBox::warning(this, "���ݴ���", "GeoJSON��û����Ч�ĵ�����");
        return;
    }

    // ���ԣ����Ŀ���ת�������������
    qDebug() << "Target point in pixels:" << targetPixelX << targetPixelY;

    // ���� m Ϊ 4����ʾ��������� 4 ����
    IDW idw(points_, attributes_, 4);  // ����ȡ�����е㴫�ݸ� IDW ��

    // ���� interpolate ���в�ֵ
    double interpolatedValue = idw.interpolate(QPointF(targetPixelX, targetPixelY));

    // ��ʾ��ֵ���
    QMessageBox::information(this, "IDW��ֵ���", QString("Ŀ����ֵ���Ϊ: %1").arg(interpolatedValue));

    // �ڽ����п��ӻ�Ŀ���
    QGraphicsScene* scene = ui.graphicsView->scene();  // ��ȡ��ǰ����
    if (!scene) {
        qWarning() << "����δ��ʼ��";
        return;
    }

    // ����Ŀ������ɫ
    QPen targetPointPen(Qt::red);  // ��ɫ�߿�
    QBrush targetPointBrush(Qt::yellow);  // ��ɫ���

    // ��Ŀ���λ�û���һ��СԲ
    QGraphicsEllipseItem* targetPointItem = new QGraphicsEllipseItem(targetPixelX - 5, targetPixelY - 5, 10, 10);  // 10��Բ���ֱ��
    targetPointItem->setPen(targetPointPen);
    targetPointItem->setBrush(targetPointBrush);

    // ��Ŀ�����ӵ�������
    scene->addItem(targetPointItem);

    // ������ͼ
    ui.graphicsView->show();
}



