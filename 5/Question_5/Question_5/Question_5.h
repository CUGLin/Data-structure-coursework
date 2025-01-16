#pragma execution_character_set("UTF-8") //ȫ������UTF-8����

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
    // �����ͷ�ļ� (Question_5.h) ������ȫ�ֳ�Ա����
    QVector<QPointF> points_;   // ���ڴ洢������
    QVector<QVector<QPointF>> lines_; // ���ڴ洢�ߵ�����
    QVector<double> attributes_;  // ���ڴ洢�������ֵ���������GeoJSON����ȡ����Щ����

    double minLon_, maxLon_, minLat_, maxLat_;  // ��γ�ȷ�Χ
    double scaleX_, scaleY_;  // ��������
};
