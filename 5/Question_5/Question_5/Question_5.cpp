
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

// 导入Txt数据并计算插值
void Question_5::on_actionTxt_triggered()
{
    // 打开文件对话框选择txt文件
    QString filePath = QFileDialog::getOpenFileName(this, "打开文本文件", "", "Text Files (*.txt)");
    if (filePath.isEmpty())
    {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "无法打开文件";
        return;
    }

    QTextStream in(&file);

    // 读取点的总数和插值所需临近点的个数
    int n, m;
    in >> n >> m;

    // 用于存储点的坐标和属性值
    QVector<QPointF> points;
    QVector<double> attributes;

    // 读取每个点的坐标和属性值
    for (int i = 0; i < n; ++i) {
        double x, y, attr;
        in >> x >> y >> attr;
        points.append(QPointF(x, y));
        attributes.append(attr);
        qDebug() << attr;
    }

    // 输入测试点的横纵坐标
    double testX, testY;
    bool okX, okY;
    testX = QInputDialog::getDouble(this, "输入测试点X坐标", "X坐标:", 0.0, -1e6, 1e6, 2, &okX);
    testY = QInputDialog::getDouble(this, "输入测试点Y坐标", "Y坐标:", 0.0, -1e6, 1e6, 2, &okY);

    if (!okX || !okY) {
        return; // 用户取消了输入
    }

    // 创建IDW插值对象
    IDW idw(points, attributes, m);

    // 进行插值计算
    QPointF testPoint(testX, testY);
    double interpolatedValue = idw.interpolate(testPoint);

    // 输出插值结果
    QMessageBox::information(this, "插值结果", QString("插值点坐标 (%1, %2) 的插值结果为: %3")
        .arg(testX).arg(testY).arg(interpolatedValue));

    // 清空现有的场景
    scene->clear();

    // 添加点到现有的scene
    for (int i = 0; i < points.size(); ++i) {
        // 以每个点的坐标绘制小圆形表示点 (例如，调整为 2x2)
        QGraphicsEllipseItem* pointItem = new QGraphicsEllipseItem(points[i].x() - 1, points[i].y() - 1, 2, 2);  // 小圆形
        pointItem->setBrush(QBrush(Qt::blue));  // 蓝色表示数据点
        scene->addItem(pointItem);
    }

    // 可选：在测试点位置添加标记
    QGraphicsEllipseItem* testPointItem = new QGraphicsEllipseItem(testPoint.x() - 2, testPoint.y() - 2, 4, 4);  // 小圆形标记
    testPointItem->setBrush(QBrush(Qt::red));  // 红色表示测试点
    scene->addItem(testPointItem);

    // 可选：显示插值结果的位置（可以使用文本或其他方式）
    QGraphicsTextItem* textItem = new QGraphicsTextItem(QString("插值结果: %1").arg(interpolatedValue));
    QFont font = textItem->font();
    font.setPointSize(2);  // 设置字体大小为较小值
    textItem->setFont(font);
    textItem->setPos(testPoint.x()-10, testPoint.y()+10);
    scene->addItem(textItem);

    // 设置场景边界并调整视图以适应
    qreal minX = 0, minY = 0;
    qreal maxX = 0, maxY = 0;
    for (int i = 0; i < points.size(); ++i) {
        minX = qMin(minX, points[i].x());
        minY = qMin(minY, points[i].y());
        maxX = qMax(maxX, points[i].x());
        maxY = qMax(maxY, points[i].y());
    }

    // 增加一些边距
    minX -= 10;
    minY -= 10;
    maxX += 10;
    maxY += 10;

    // 设置场景的边界
    scene->setSceneRect(minX, minY, maxX - minX, maxY - minY);

    // 自动调整视图缩放，以适应所有点
    ui.graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}





void Question_5::on_actionGeojson_triggered()
{
    // 打开文件对话框选择GeoJSON文件
    QString filePath = QFileDialog::getOpenFileName(this, "打开GeoJSON文件", "", "GeoJSON Files (*.geojson *.json)");
    if (filePath.isEmpty())
    {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "无法打开文件";
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);

    if (!doc.isObject()) {
        QMessageBox::warning(this, "文件格式错误", "无法解析GeoJSON文件，文件格式不正确。");
        return;
    }

    QJsonObject jsonObject = doc.object();
    QJsonArray features = jsonObject["features"].toArray();

    // 清空现有场景
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 600); // 设置一个默认的场景尺寸
    ui.graphicsView->resize(800, 600); // 设置视图尺寸与场景匹配

    QVector<QPointF> points;   // 用于存储点坐标
    QVector<QVector<QPointF>> lines; // 用于存储线的坐标
    QVector<double> attributes; // 用于存储每个点的属性值（如ELEV）

    // 设置图形项的样式
    QPen pointPen(Qt::blue);  // 点的颜色
    QBrush pointBrush(Qt::blue);  // 点的填充颜色
    QPen linePen(Qt::green);   // 线的颜色
    linePen.setWidth(3);  // 增加线条的宽度，默认宽度是1，3是更粗的线条

    // 计算经纬度范围
    double minLon = std::numeric_limits<double>::max();
    double maxLon = std::numeric_limits<double>::lowest();
    double minLat = std::numeric_limits<double>::max();
    double maxLat = std::numeric_limits<double>::lowest();

    // 计算GeoJSON中经纬度范围
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

    // 获取视图的宽度和高度
    int viewWidth = ui.graphicsView->width();
    int viewHeight = ui.graphicsView->height();

    // 计算经纬度到像素的缩放因子
    double scaleX = viewWidth / (maxLon - minLon);  // 经度缩放因子
    double scaleY = viewHeight / (maxLat - minLat); // 纬度缩放因子

    // 遍历每个Feature
    for (const QJsonValue& featureValue : features) {
        QJsonObject feature = featureValue.toObject();
        QJsonObject geometry = feature["geometry"].toObject();
        QString type = geometry["type"].toString();

        // 如果是LineString类型
        if (type == "LineString") {
            QJsonArray coordinates = geometry["coordinates"].toArray();
            QVector<QPointF> line;
            double elev = feature["properties"].toObject()["ELEV"].toDouble();  // 获取该线段的ELEV值

            for (const QJsonValue& coordValue : coordinates) {
                QJsonArray coord = coordValue.toArray();
                double lon = coord[0].toDouble();
                double lat = coord[1].toDouble();

                // 将经纬度转换为视图坐标系的像素坐标
                double pixelX = (lon - minLon) * scaleX;
                double pixelY = (maxLat - lat) * scaleY; // 注意纬度坐标的转换方向

                line.append(QPointF(pixelX, pixelY));  // 存储线段的点坐标
                points.append(QPointF(pixelX, pixelY));  // 存储所有点
                attributes.append(elev);  // 每个点的高程是相同的，来自当前线段的ELEV值
            }
            lines.append(line);  // 存储线数据

            // 使用 QPainterPath 来绘制线
            QPainterPath path;
            if (!line.isEmpty()) {
                path.moveTo(line[0]);  // 移动到第一个点
                for (int i = 1; i < line.size(); ++i) {
                    path.lineTo(line[i]);  // 绘制直线段
                }
            }

            // 在场景中添加线
            QGraphicsPathItem* lineItem = new QGraphicsPathItem(path);
            lineItem->setPen(linePen);  // 设置更粗的线条
            scene->addItem(lineItem);
        }
    }

    // 确保有点数据
    if (points.isEmpty()) {
        QMessageBox::warning(this, "数据错误", "GeoJSON中没有有效的点数据");
        return;
    }

    // 更新场景的边界并适配视图
    scene->setSceneRect(scene->itemsBoundingRect());
    ui.graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui.graphicsView->show();

    // 存储全局数据
    points_ = points;
    attributes_ = attributes;
    lines_ = lines;

    minLon_ = minLon;
    maxLon_ = maxLon;
    minLat_ = minLat;
    maxLat_ = maxLat;
    scaleX_ = scaleX;
    scaleY_ = scaleY;

    // 输出调试信息
    qDebug() << "points_:" << points_ << "attributes_:" << attributes_;
    qDebug() << minLon << maxLon << minLat << maxLat << scaleX << scaleY;
}




void Question_5::on_actionIDW_triggered()
{

    qDebug() << minLon_ << maxLon_ << minLat_ << maxLat_ << scaleX_ << scaleY_;

    // 获取用户输入的目标点经纬度
    bool ok;
    double targetLon = QInputDialog::getDouble(this, "输入目标点", "请输入目标点的经度:", 102.6, -180.0, 180.0, 6, &ok);
    if (!ok) {
        return;  // 如果用户取消了输入，则退出
    }

    double targetLat = QInputDialog::getDouble(this, "输入目标点", "请输入目标点的纬度:", 23.1, -90.0, 90.0, 6, &ok);
    if (!ok) {
        return;  // 如果用户取消了输入，则退出
    }

    // 根据GeoJSON数据中的经纬度范围进行坐标转换
    // 将目标经纬度转换为视图坐标系的像素坐标
    double targetPixelX = (targetLon - minLon_) * scaleX_;
    double targetPixelY = (maxLat_ - targetLat) * scaleY_;  // 注意纬度坐标的转换方向

    // 确保有点数据
    if (points_.isEmpty()) {
        QMessageBox::warning(this, "数据错误", "GeoJSON中没有有效的点数据");
        return;
    }

    // 调试：输出目标点转换后的像素坐标
    qDebug() << "Target point in pixels:" << targetPixelX << targetPixelY;

    // 假设 m 为 4，表示考虑最近的 4 个点
    IDW idw(points_, attributes_, 4);  // 将提取的所有点传递给 IDW 类

    // 调用 interpolate 进行插值
    double interpolatedValue = idw.interpolate(QPointF(targetPixelX, targetPixelY));

    // 显示插值结果
    QMessageBox::information(this, "IDW插值结果", QString("目标点插值结果为: %1").arg(interpolatedValue));

    // 在界面中可视化目标点
    QGraphicsScene* scene = ui.graphicsView->scene();  // 获取当前场景
    if (!scene) {
        qWarning() << "场景未初始化";
        return;
    }

    // 设置目标点的颜色
    QPen targetPointPen(Qt::red);  // 红色边框
    QBrush targetPointBrush(Qt::yellow);  // 黄色填充

    // 在目标点位置绘制一个小圆
    QGraphicsEllipseItem* targetPointItem = new QGraphicsEllipseItem(targetPixelX - 5, targetPixelY - 5, 10, 10);  // 10是圆点的直径
    targetPointItem->setPen(targetPointPen);
    targetPointItem->setBrush(targetPointBrush);

    // 将目标点添加到场景中
    scene->addItem(targetPointItem);

    // 更新视图
    ui.graphicsView->show();
}



