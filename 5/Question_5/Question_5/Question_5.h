#pragma execution_character_set("UTF-8") //全局启用UTF-8编码

#include <QtWidgets/QMainWindow>
#include "ui_Question_5.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QGraphicsView>
#include <QPointF>
#include <QFileDialog>
#include <QDebug>
#include <QInputDialog>
#include "IDW.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Question_5 : public QMainWindow
{
    Q_OBJECT

public:
    Question_5(QWidget *parent = nullptr);
    ~Question_5();
    void on_actionTxt_triggered();
    void on_actionGeojson_triggered();
    void on_actionIDW_triggered();
private:
    Ui::Question_5Class ui;
    QGraphicsScene* scene;
    // 在类的头文件 (Question_5.h) 中声明全局成员变量
    QVector<QPointF> points_;   // 用于存储点坐标
    QVector<QVector<QPointF>> lines_; // 用于存储线的坐标
    QVector<double> attributes_;  // 用于存储点的属性值（假设你从GeoJSON中提取了这些属性

    double minLon_, maxLon_, minLat_, maxLat_;  // 经纬度范围
    double scaleX_, scaleY_;  // 缩放因子
};
